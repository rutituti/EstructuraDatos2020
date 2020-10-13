/*
 * evaltree.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef EVALTREE_H_
#define EVALTREE_H_

#include <cctype>
#include <string>

#include <sstream>
#include <queue>
#include <stack>
#include "exception.h"

using namespace std;

class EvalTree;

class TreeNode {
private:
	char value;
	TreeNode *left, *right;

	bool isOperator() const;
	bool isVariable() const;
	bool isOperand() const;

public:
	TreeNode(char);
	TreeNode(char, TreeNode*, TreeNode*);
	int depth() const;
	void inorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void levelOrder(std::stringstream&) const;
	int howManyLeaves() const;
	char minValue() const;
	bool find(char) const;
	double eval(double x) const;
	TreeNode* derive() const;
	void removeChilds();
	TreeNode* copy() const;
	friend class EvalTree;
};

TreeNode::TreeNode(char c) {
	value = c;
	left = NULL;
	right = NULL;
}

TreeNode::TreeNode(char c, TreeNode* le, TreeNode* ri) {
	value = c;
	left = le;
	right = ri;
}

bool TreeNode::isOperator() const {
	if(value == '+' || value == '-' || value == '*' || value == '/')
	return true;

	return false;
}

bool TreeNode::isVariable() const {
	if(value == 'x')
	return true;
	return false;
}

bool TreeNode::isOperand() const {
	if(value >='0' && value <= '9')
	return true;
	return false;
}

int TreeNode::depth() const {
	int left_depth = -1;
	//Encontrar la profundidad de la rama IZQUIERDA
	if(left !=NULL)
	left_depth = left -> depth();

	//Encontrar la profundidad de la rama DERECHA
	int right_depth = -1;
	if(right !=NULL)
	right_depth = right -> depth();

	//REGRESAR LA MAYOR DE LAS PROFUNDIDADES
	int depth = left_depth;
	if(right_depth > left_depth)
	depth = right_depth;

	return depth + 1;
}

void TreeNode::inorder(std::stringstream &aux) const {
	//Recorrido in order rama izquierda
	if(left != NULL){
		left->inorder(aux);
	}
	//Imprimir el valor del nodo
	aux<<value<<" ";

	//Recorrido in order rama derecha
	if(right != NULL){
		right->inorder(aux);
	}
}

void TreeNode::postorder(std::stringstream &aux) const {
		//Recorrido in order rama izquierda
	if(left != NULL){
		left->postorder(aux);
	}

	//Recorrido in order rama derecha
	if(right != NULL){
		right->postorder(aux);
	}

	//Imprimir el valor del nodo
	aux<<value<<" ";
}

void TreeNode::preorder(std::stringstream &aux) const {
	//Imprimir el valor del nodo
	aux<<value<<" ";

	//Recorrido in order rama izquierda
	if(left != NULL){
		left->preorder(aux);
	}

	//Recorrido in order rama derecha
	if(right != NULL){
		right->preorder(aux);
	}
}

int TreeNode::howManyLeaves() const {
	//printf("AQUI");
	int count=0, count_left=0, count_right=0, total_count=0;
	if(left != NULL){
		count_left = left->howManyLeaves();
	}

	//Recorrido in order rama derecha
	if(right != NULL){
		count_right = right->howManyLeaves();
	}
	
	if((count_right+count_left) == 0){
		return 1;
	}else{
		return count_right+count_left;
	}
}

char TreeNode::minValue() const {
	
	return '9';
}

bool TreeNode::find(char val) const {
	return false;
}

double TreeNode::eval(double x) const {
	return 0;
}

void TreeNode::removeChilds() {
}

TreeNode* TreeNode::derive() const {
	return 0;
}

TreeNode* TreeNode::copy() const {
	return 0;
}

class EvalTree {
private:
	TreeNode *root;

	std::queue<std::string> tokenize(std::string);

public:
	EvalTree();
	EvalTree(std::string) throw (IllegalAction);
	~EvalTree();
	bool empty() const;
	int height() const;
	std::string inorder() const;
	std::string postorder() const;
	std::string preorder() const;
	std::string levelOrder() const;
	int howManyLeaves() const;
	char minValue() const throw (IllegalAction);
	bool find(char) const;
	double eval(double) const throw (IllegalAction) ;
	EvalTree* derive() const;
	void removeAll();
	bool isFull() const;
	int internalNodes() const;
	bool isPerfect() const;
	bool isDegenerate() const;
};

EvalTree::EvalTree() {
	root = NULL;
}

std::queue<std::string> EvalTree::tokenize(std::string str) {
	int i = 0;
	int length = str.size();
	std::string aux;
	std::queue<std::string> result;

	while (i < length) {
		if (isdigit(str[i])) {
			aux.clear();
			do {
				aux += str[i];
				i++;
			} while(isdigit(str[i]));
			result.push(aux);
		} else if (isspace(str[i])) {
			i++;
		} else {
			aux.clear();
			aux += str[i];
			result.push(aux);
			i++;
		}
	}
	return result;
}

EvalTree::EvalTree(std::string str) throw (IllegalAction) {
	root = 0;
	std::stack<TreeNode*> s;
	std::queue<std::string> tokens = tokenize(str);
	std::string aux;
	TreeNode *left, *right, *newNode;

	while (!tokens.empty()) {
		aux = tokens.front(); tokens.pop();
		if (aux == "+" || aux == "-" || aux == "*" || aux == "/") {
			if (s.empty()) {
				throw IllegalAction();
			}
			left = s.top(); s.pop();
			if (s.empty()) {
				throw IllegalAction();
			}
			right = s.top(); s.pop();
			newNode = new TreeNode(aux[0], left, right);
			s.push(newNode);
		} else if (aux[0] == 'x' || isdigit(aux[0])) {
			newNode = new TreeNode(aux[0]);
			s.push(newNode);
		}
	}
	newNode = s.top(); s.pop();
	if (!s.empty()) {
		throw IllegalAction();
	}
	root = newNode;
}

EvalTree::~EvalTree() {
}

bool EvalTree::empty() const {

	if(root == NULL){
		return true;
	}else{
		return false;
	}
	
}

int EvalTree::height() const {
	if(empty())
	return 0;
	return root->depth() + 1;
}

std::string EvalTree::inorder() const {
	std::stringstream aux;
	root->inorder(aux);
	return aux.str();
}

std::string EvalTree::preorder() const {
	std::stringstream aux;
	root->preorder(aux);
	return aux.str();
}

std::string EvalTree::postorder() const {
	std::stringstream aux;
	root->postorder(aux);
	return aux.str();
}

std::string EvalTree::levelOrder() const {
	std::stringstream aux;
	//Necesitamos una fila para el recorrido por niveles
	std::queue<TreeNode*> q;



	//Metemos a la fila la raiz
	TreeNode* nodo = root;
	q.push(nodo);

	//Mientras la fila no este vacia
	while(!q.empty()){
		//Imprimir el frente de la fila
		nodo = q.front();
		aux<< nodo->value <<" ";
		//sacar el elemento de la fila
		q.pop();
		//Si tiene hijo izq, meter el hijo izq a la fila
		if(nodo->left !=0){
			q.push(nodo->left);
		}

		//Si tiene hijo derecho, meter el hijo derecho a la fila
		if(nodo->right !=0){
			q.push(nodo->right);
		}

	}
	return aux.str();
}

int EvalTree::howManyLeaves() const {
	if(empty()){
		return 0;
	}
	else{
		return root->howManyLeaves();
	}
}

char EvalTree::minValue() const throw (IllegalAction) {
	if(empty()){
		throw IllegalAction();
	}
	return '9';
}

bool EvalTree::find(char c) const {
	return false;
}

double EvalTree::eval(double x) const throw (IllegalAction) {
	return 0.0;
}

EvalTree* EvalTree::derive() const {
	return 0;
}

void EvalTree::removeAll() {
}
#endif /* EVALTREE_H_ */
