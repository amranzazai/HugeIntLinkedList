/*
 * HugeInt.h
 *
 *  Created on: Mar 4, 2021
 *      Author: amranzazai
 */
#ifndef HUGEINT_H_
#define HUGEINT_H_
#include <cstddef>
#include <fstream>
using namespace std;

enum SignType {PLUS, MINUS};

class HugeInt{
private:
	struct Node
	{
		int digit; // SINGLE DIGIT ONLY ie: (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
		Node *next; // Next More Significant Digit
		Node *previous;
	};

	/*  Integer 345 is stored in List: 3 <- 4 <- 5 <- digits
		Integer 123 is stored in List: 1 <- 2 <- 3 <- digits
		To add: add the least significant digits, potentially
		keeping track of a carry value. Then move to the next
		left nodes in both HugeInts. Add these and the carry.
		Create a new carry value. Continue until both HugeInt
		lists are empty. If one list is empty, keep processing
		the non-empty list.
	*/

	Node *digits; 	//Linked list of digit nodes
	Node *head; //points to the most significant value
	Node *tail; //points to the least significant value
	SignType sign; 	//enum of the sign of the HugeInt
	int numDigits; 	//Number of digits in the HugeInt
	void makeEmpty(){ //clear the linked list of digits
		Node *nodePtr; //creating a node pointer
		Node *previousNode; //creating a pointer to the next node

		nodePtr = head;

		while(nodePtr != nullptr){
			previousNode = nodePtr->previous;
			delete nodePtr;
			nodePtr = previousNode;
		}
	}
public:
	HugeInt();
	~HugeInt();
	bool operator<(HugeInt second);//compare for less than. return true/false
	bool operator==(HugeInt second);//compare for equal. return true/false
	HugeInt operator+(HugeInt second);//add
	HugeInt operator-(HugeInt second);//subtract
	HugeInt operator*(HugeInt second);//multiply
	HugeInt operator/(HugeInt second);//divide
	void insertDigits(int x); //insert integer number. Insert each digit separately!!!!!!!
	void write(ofstream& fileName); //Write the digits to a file. Pass ofstream as arg
};

#endif
