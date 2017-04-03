/*****************************************************************************************************
** Author: Conrad Lewin
** Date: 11/24/2015
** Description: This class provides the blueprint for a linked list data structure. Each node in
** the list contains a string data member. Users will be able to add nodes, search the list for a key
** item, change the data in a node and represent the list as a vector.
******************************************************************************************************/

#ifndef STRING_LIST_H
#define STRING_LIST_H

#include <string>
#include <vector>

class StringList
{
private:
	//struct that defines the nodes that comprise the list
	struct ListNode
	{
	public:
		std::string data; //the data stored in each node
		ListNode* next; //reference to the next node in the list

		//constructor
		ListNode(std::string data = "", ListNode* next = NULL) { this->data = data; this->next = next; }
	};

	ListNode* firstNode; //reference to the first node in the list
	ListNode* lastNode; //reference to the last node in the list
	int numLinks; //tracks the number of nodes in the list

	void destroyList(); //private function that destroys all the nodes in the list

public:
	StringList(); //constructor
	StringList(const StringList&); //copy constructor
	~StringList(); //destructor

	void add(std::string); //adds a node to the list
	int positionOf(std::string) const; //gets the position of a node in the list
	bool setNodeVal(int, std::string); //changes the data of a particular node in the list
	std::vector<std::string> getAsVector() const; //transforms the contents of the list into a vector
};

#endif //STRING_LIST_H

/*********************************************************MAIN*******************************************************
#include "StringList.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	StringList list;
	list.add("a");
	list.add("b");
	list.add("c");
	std::vector<std::string> vect = list.getAsVector();

	cout << "Printing vector representation (should see a b c): ";
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl << endl;

	cout << "Position of 'a' (should see 0): " << list.positionOf("a") << endl;
	cout << "Position of 'b' (should see 1): " << list.positionOf("b") << endl;
	cout << "Position of 'c' (should see 2): " << list.positionOf("c") << endl;
	cout << "Position of 'd' (should see -1): " << list.positionOf("d") << endl << endl;

	cout << "Replacing 'a' with 'h' (should see 1): " << list.setNodeVal(0, "h") << endl;
	cout << "Attempting to replace element outside of list with 'r' (should see 0): " << list.setNodeVal(20, "r") << endl;
	cout << "Position of 'h' (should see 0): " << list.positionOf("h") << endl;
	cout << "Position of 'a' (should see -1): " << list.positionOf("a") << endl << endl;

	cout << "Replacing 'c' with 's' (should see 1): " << list.setNodeVal(2, "s") << endl;
	cout << "Position of 's' (should see 2): " << list.positionOf("s") << endl;
	cout << "Position of 'c' (should see -1): " << list.positionOf("c") << endl << endl;

	vect = list.getAsVector();
	cout << "Printing vector representation (should see h b s): ";
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
	{
		cout << *i << " ";
	}

	cout << endl << endl << "Testing copy constructor..." << endl << endl;

	StringList list2;
	list2.add("m");
	list2.add("n");

	vect = list2.getAsVector();
	cout << "Printing vector representation of list2 (should see m n): ";
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
	{
		cout << *i << " ";
	}

	cout << endl << endl;

	StringList list3 = list2;

	vect = list3.getAsVector();
	cout << "Printing vector representation of list3 (should see m n): ";
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
	{
		cout << *i << " ";
	}

	cout << endl;

	cout << "Replacing 'm' with 'x' in list 2 (should see 1): " << list2.setNodeVal(0, "x") << endl;
	cout << "Attempting to replace element outside of list with 'r' (should see 0): " << list2.setNodeVal(20, "r") << endl << endl;

	cout << "Printing both lists..." << endl;
	cout << "List 2 (should see x n): ";
	vect = list2.getAsVector();
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
	{
		cout << *i << " ";
	}

	cout << endl << endl;


	cout << "List 3 (should see m n): ";
	vect = list3.getAsVector();
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
	{
		cout << *i << " ";
	}

	cout << endl << endl;

	return 0;
}
**********************************************************END MAIN**********************************************************/