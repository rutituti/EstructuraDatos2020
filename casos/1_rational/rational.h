 /*
 * rational.h
 *
 *  Created on: 17/08/2020
 *      Author: Ruth
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include "exception.h"
#include <string>
#include <sstream>

using namespace std;

class Rational {
private:
	int numerator;
	int denominator;

	void normalize();

public:
	Rational();
	Rational(int);
	Rational(int, int);
	Rational(const Rational&);

	int getNumerator() const;
	int getDenominator() const;
	std::string toString() const;

	void operator=   (const Rational&);
	void operator+=  (const Rational&);

	operator double () const;
};

Rational::Rational() {
    numerator = 0;
    denominator = 1;
}

Rational::Rational(int num){
    numerator = num;
    denominator = 1;
}

Rational::Rational(int num, int dem){
        numerator = num;
        denominator = dem;
    
    normalize();
}

int Rational::getNumerator() const {
  //cout<<"getNumerator = "<<numerator<<endl;
	return numerator;
}

int Rational::getDenominator() const {
 // cout<<"getDenominator = "<<numerator<<endl;
	return denominator;
}

std::string Rational::toString() const {
	std::stringstream aux;

	aux << numerator << "/" << denominator;
	return aux.str();
}

Rational::operator double () const {
  double resultado = (double)numerator/(double)denominator;
	return resultado;
}

//Greatest common divisor
int gcd(int a, int b) {
	int aux;

	while (b != 0) {
		aux = b;
		b = a % b;
		a = aux;
	}
	return a;
}

void Rational::normalize() {
  
    if(denominator%numerator ==0){
    denominator = denominator/numerator;
    numerator = numerator/numerator;
    //cout<<denominator/numerator<<"\n";
    }
  
    if(denominator<0){
    denominator = denominator*-1;
    numerator = numerator*-1;
  }
  if (denominator == 0){
    throw RangeError();
  }
}

void Rational::operator= (const Rational &right) {
  //cout<< right.numerator<<"\n";
  //cout<< right.denominator<<"\n";
  numerator = right.numerator;
  denominator = right.denominator;
}

void Rational::operator+= (const Rational &right) {
  //cout<<"\n"<<"Numerador (1):"<<numerator<<endl;
  //cout<<"Numerador (2):"<<right.numerator<<endl;
  if(denominator == right.denominator){
    numerator = numerator + right.numerator;
  }else{
   // cout<<"\n"<<"Denominator (1):"<<denominator<<endl;
   // cout<<"Denominator (2):"<<right.denominator<<endl;
    numerator = (numerator*right.denominator)+(right.numerator*denominator);
    denominator= denominator*right.denominator;
 // cout<<"\n"<<"Numerador suma: "<<numerator<<endl;
  }

  normalize();
}

Rational operator+ (const Rational &left, const Rational &right) {
  int num=0, dem=0;
  //cout<<"\n"<<"Numerador (1):"<<left.getNumerator()<<endl;
  //cout<<"Numerador (2):"<<right.getNumerator()<<endl;
  if(left.getDenominator() == right.getDenominator()){
    num = left.getNumerator() + right.getNumerator();
    dem = left.getDenominator();
  }else{
    //cout<<"\n"<<"Denominator (1):"<<left.getDenominator()<<endl;
   // cout<<"Denominator (2):"<<right.getDenominator()<<endl;
    num = (left.getNumerator()*right.getDenominator())+(right.getNumerator()*left.getDenominator());
    dem= left.getDenominator()*right.getDenominator();
  //cout<<"\n"<<"Numerador suma: "<<numerator<<endl;
  }

	return Rational(num, dem);
}

Rational operator- (const Rational &left, const Rational &right) {
	 int num=0, dem=0;
  cout<<"\n"<<"Numerador (1):"<<left.getNumerator()<<endl;
  cout<<"Numerador (2):"<<right.getNumerator()<<endl;
  if(left.getDenominator() == right.getDenominator()){
    num = left.getNumerator() - right.getNumerator();
    dem = left.getDenominator();
  }else{
    cout<<"\n"<<"Denominator (1):"<<left.getDenominator()<<endl;
    cout<<"Denominator (2):"<<right.getDenominator()<<endl;
    num = (left.getNumerator()*right.getDenominator()) -(right.getNumerator()*left.getDenominator());
    dem= left.getDenominator()*right.getDenominator();
  //cout<<"\n"<<"Numerador suma: "<<numerator<<endl;
  }

	return Rational(num, dem);
}

Rational operator- (const Rational &right) {
  int num=0;
  num = right.getNumerator()*(-1);
	return Rational(num,right.getDenominator());
}

bool operator== (const Rational &left, const Rational &right) {
  int num, dem;
  num = left.getNumerator()*right.getDenominator();
  dem = left.getDenominator()* right.getNumerator();
  if(num==dem){
    cout<<"NUM="<<num<<endl;
    cout<<"DEM="<<dem<<endl;
    return true;
  }else{
    return false;
  }
	
}

bool operator<  (const Rational &left, const Rational &right) {
	return false;
}

#endif /* RATIONAL_H_ */
