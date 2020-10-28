/*
 * main.cpp
 *
 *  Created on: 29/10/2015
 *      Author: pperezm
 */

#include <iostream>
#include <cstring>
#include "unit.h"
#include "tree.h"

using namespace std;

class TreeTest : public UnitTest {
public:
	void runTest() {
		UnitTest::total_test = 4;
		SimpleTree a(1), b(2), c(3), d(4);
		
		/* TEST 1 */
		cout << "Test 1...";
		ASSERT_TRUE(a.isFull());
		ASSERT_TRUE(b.isFull());
		ASSERT_FALSE(c.isFull());
		ASSERT_TRUE(d.isFull());
		std::cout << " PASSED.\nTest 2...";
		
		/* TEST 2 */
		ASSERT_TRUE(3 == a.internalNodes());
		//std::cout << "My answer"<<a.internalNodes()<<std::endl;
		ASSERT_TRUE(5 == b.internalNodes());
		//std::cout << "My answer"<<b.internalNodes()<<std::endl;
		ASSERT_TRUE(5 == c.internalNodes());
		//std::cout << "My answer"<<c.internalNodes()<<std::endl;
		ASSERT_TRUE(0 == d.internalNodes());
		//std::cout << "My answer"<<d.internalNodes()<<std::endl;
		std::cout << " PASSED.\nTest 3...";
		
		/* TEST 3 */
		ASSERT_TRUE(a.isPerfect());
		ASSERT_FALSE(b.isPerfect());
		ASSERT_FALSE(c.isPerfect());
		ASSERT_TRUE(d.isPerfect());
		std::cout << " PASSED.\nTest 4...";
		
		/* TEST 4 */
		ASSERT_FALSE(a.isDegenerate());
		std::cout << "\nMy answer"<<a.isDegenerate()<<std::endl;
		ASSERT_FALSE(b.isDegenerate());
		std::cout << "\nMy answer"<<b.isDegenerate()<<std::endl;
		ASSERT_TRUE(c.isDegenerate());
		std::cout << "\nMy answer"<<c.isDegenerate()<<std::endl;
		ASSERT_FALSE(d.isDegenerate());
		std::cout << "\nMy answer"<<d.isDegenerate()<<std::endl;
		std::cout << " PASSED.\n";
	}
};

int main(int argc, char* argv[]) {
	TreeTest test;

	test.runTest();
	std::cout << "SUCESS!\n";
	return 0;
}


