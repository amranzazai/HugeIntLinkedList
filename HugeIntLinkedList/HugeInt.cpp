/*
 * HugeInt.cpp
 *
 *  Created on: Mar 4, 2021
 *      Author: amranzazai
 */

#include "HugeInt.h"
#include <cstddef>
#include <string>
using namespace std;

HugeInt::HugeInt() {
	// TODO Auto-generated constructor stub
	digits = nullptr; 	//Linked list of digit nodes
	head = nullptr;
	tail = nullptr;
	sign = PLUS; 	//enum of the sign of the HugeInt
	numDigits = 0; 	//Number of digits in the HugeInt
}


bool HugeInt::operator<(HugeInt second){//compare for less than. return true/false

	Node *tempPtr = head; //create a temporary pointer and set it to tail
	Node *tempPtr2 = second.head; //create a temporary pointer and set it to tail
	bool answer;

	while(tempPtr != nullptr || tempPtr2 != nullptr) //while the first list or second list isnt empty
	{
			if(tempPtr<tempPtr2){ //if the first value is less than the second value return true
				answer = true;
			}
			else //else return false
				answer = false;
			tempPtr2=tempPtr2->previous; //traverse the second list by setting tempPtr2 to its next
			tempPtr=tempPtr->previous; //traverse the list by setting the temp ptr to its next

	}

	return answer;

}
bool HugeInt::operator==(HugeInt second){//compare for equal. return true/false

	Node *tempPtr = head; //create a temporary pointer and set it to tail
	Node *tempPtr2 = second.head; //create a temporary pointer and set it to tail
	bool answer1;

	while(tempPtr!=nullptr || tempPtr2 != nullptr) //while the first list isnt empty
	{

			if(tempPtr==tempPtr2){ //if the first value is less than the second value return true
				answer1 = true;
			}
			else //else return false
				answer1 = false;
			tempPtr2=tempPtr2->previous; //traverse the second list by setting tempPtr2 to its next
			tempPtr=tempPtr->previous; //traverse the list by setting the temp ptr to its next


	}

	return answer1;

}
HugeInt HugeInt::operator+(HugeInt second){//add

	Node *tempPtr=tail; //creating a temporary pointer to point to the first list's tail
	Node *tempPtr2=second.tail; //creating a temporary pointer to point to the second list's tail
	HugeInt result; //creating a HugeInt object to store the result in

	int sum = 0; 	//values to do addition
	int carry = 0;

	while(tempPtr!=nullptr || tempPtr2!=nullptr){ //while tempPtr or tempPtr2 does not point to null
		sum = tail->digit + second.tail->digit + carry; //sum equal the first list's LSD plus the second list's LSD plus the carry
		if (sum > 9){//if the sum results in a number larger than 9
			sum = sum % 10;  //make sum equal to the value in the ones place
			carry = 1; //store the value that is in the tens place in carry to be used in the next round of addition
		}
		else  //if the sum is not greater than 9 there is no need for a carry
			carry = 0;
		result.insertDigits(sum); //add the sum into a new HugeInt linked list
		tempPtr = tempPtr->next; //continue traversing the list
		tempPtr2 = tempPtr2->next; //continue traversing the list
	}

	return result; //return HugeInt object
}
HugeInt HugeInt::operator-(HugeInt second){//subtract

	Node *tempPtr = tail; //creating a temporary pointer to point to the first list's tail
	Node *tempPtr2 = second.tail; //creating a temporary pointer to point to the second list's tail
	HugeInt result1;  //creating a HugeInt object to store the result in

	int difference = 0; //values for subtraction
	int carry = 0;

	while(tempPtr!=nullptr || tempPtr2!=nullptr){ //while tempPtr or tempPtr2 does not point to null
		difference = tail->digit - second.tail->digit - carry; //difference is equal to the first lists digit minus the seconds minus the carry(if any)
		if (difference < 0){ //if the difference is a negative number
			difference = difference%10; //we follow borrowing rules
			carry  = 1;
		}
		result1.insertDigits(difference); //insert the digits in HugeInt result
		tempPtr=tempPtr->next; //Continue traversing the list
		tempPtr2=tempPtr2->next;  //continue traversing the list
	}

	return result1; //return HugeInt result
}

HugeInt HugeInt::operator*(HugeInt second){//multiply

	HugeInt result2; //create new HugeInt object

	int product; //holds the product of two linked lists
	int num1 = 0;  //values to convert linked list into integers
	int num2 = 0; //values to convert linked list into integers

	while(head != nullptr || second.head != nullptr){ //While list1 or list2 has an element to point to
		if(head){ //if head exists
			num1 = num1*10 + head->digit; //set num1 equal to the head of the list and move up one power of ten for each loop to convert LL into an int
			head = head->previous; //traverse the list
		}
		if(second.head){ //if the second list has a head pointer
			num2 = num2*10 + second.head->digit;//set num2 equal to the head of the list and move up one power of ten for each loop to convert LL into an int
			second.head = second.head->previous; //traverse the list
		}
	}
	product =  num1*num2; //perform integer multiplication
	int value;
	while(product != 0){ //while product is not equal to zero
		value = product % 10; //set value to the LSD in product
		result2.insertDigits(value); //insert value keeping LL in order LSD->->->MSD
		product = product - value;  //delete the value we inserted already
		product = product / 10; //remove the zero from product
	}

	return result2; //return HugeInt result2

}
HugeInt HugeInt::operator/(HugeInt second){//divide

	int number1; //values to convert linked list into integers
	int number2; //values to convert linked list into integers
	int quotient; //holds the quotient of two linked lists

	HugeInt result3; //create new HugeInt object

	while(head != nullptr || second.head != nullptr){//While list1 or list2 has an element to point to
		if(head){//if head exists
			number1 = number1*10 + head->digit;//set num1 equal to the head of the list and move up one power of ten for each loop to convert LL into an int
			head = head->previous; //traverse list
		}
		if(second.head){//if head exists
			number2 = number2*10 + second.head->digit; //set num1 equal to the head of the list and move up one power of ten for each loop to convert LL into an int
			second.head = second.head->previous; //traverse list
		}
	}
	quotient = number1 / number2; //integer division
	int value1;
	while(quotient != 0){//while quotient is not equal to zero
		value1 = quotient % 10;//set value to the LSD in product
		result3.insertDigits(value1);//insert value keeping LL in order LSD->->->MSD
		quotient = quotient - value1; //delete the value we inserted already
		quotient = quotient / 10; //remove the zero from quotient
	}
	return result3; //return HugeInt result3

}
void HugeInt::insertDigits(int x){ //insert integer number. Insert each digit separately!!!!!!!

	Node *newNode; //creating new node
	newNode = new Node;
	newNode->digit = x; //setting node value to x

	if(head == nullptr)  //if list is empty
	{
		digits=newNode; //set digits to list
		head=newNode;  //set head to new node
		tail=newNode; //set tail to new node
		tail->previous = nullptr; //set tails previous to null
	}
	else{ //if list is not empty
		newNode->previous=head;  //set newNode's previous to head
		head->next=newNode; //set head's next to newNode
		head = newNode; //set head to new node
		newNode->next=nullptr; //set newNode's next to null
	}

	numDigits++; //increase counter for number of digits in the list
}
void HugeInt::write(ofstream& fileName){ //Write the digits to a file. Pass ofstream as arg

	Node *tempPtr = head; //create a temporary pointer and set it to head
	while(tempPtr != nullptr) //while the list isnt empty
	{
		fileName<<tempPtr->digit; //write the value of the temporary pointer to a file
		tempPtr=tempPtr->previous; //traverse the list by setting the temp ptr to its next
	}

}
HugeInt::~HugeInt(){

	makeEmpty(); //call private member function make empty so public interface cannot alter values

}
