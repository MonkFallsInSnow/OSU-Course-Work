/*****************************************************************************************************
** Author: Conrad Lewin
** Date: 11/24/2015
** Description: This class provides the blueprint for a linked list data structure. Each node in
** the list contains a string data member. Users will be able to add nodes, search the list for a key
** item, change the data in a node and represent the list as a vector.
******************************************************************************************************/
#include "StringList.hpp"

//constructor
StringList::StringList()
{
	firstNode = NULL;
	lastNode = firstNode;

	numLinks = 0;
}

//copy constructor
StringList::StringList(const StringList& obj)
{
	firstNode = NULL;
	lastNode = firstNode;

	//adds all the nodes present in the right hand operand to the left hand operand
	for (ListNode* curNode = obj.firstNode; curNode != NULL; curNode = curNode->next)
	{
		add(curNode->data);
	}

	numLinks = obj.numLinks; //updates the number of nodes in the list
}

//destructor
StringList::~StringList()
{
	destroyList();
}


/****************************************************************************************************
** Description: Adds a node containing the given string data to the end of the list.
****************************************************************************************************/
void StringList::add(std::string d)
{
	ListNode* newNode = new ListNode(d); //create a new node with the given data

	if (firstNode == NULL) //if the list is empty
	{
		firstNode = newNode; //link the first node to the newly created node
		lastNode = firstNode; //with only one node in the list, the first and last node point to the same node
	}
	else //if the list has at least one node
	{
		lastNode->next = newNode; //link the last node's next reference to the newly created node
		lastNode = lastNode->next; //assign the last node in the list to point at the newly created node's next reference
	}

	numLinks++; //update the number of nodes in the list
	return;
}


/****************************************************************************************************
** Description: Searches the list for a particular key and returns the position where that key is
** located.
****************************************************************************************************/
int StringList::positionOf(std::string key) const
{
	int pos = 0;

	for (ListNode* curNode = firstNode; curNode != NULL; curNode = curNode->next) //loop through list, starting at the first node
	{
		if (curNode->data == key) //if the key is found, return the position
		{
			return pos;
		}

		pos++; //if the key is not found during the iteration, increment the position
	}

	return -1; //return -1 if the key is not found in the list
}


/****************************************************************************************************
** Description: Navigates to a specified position in the list and changes the data stored in 
** the node.
****************************************************************************************************/
bool StringList::setNodeVal(int pos, std::string key)
{
	if (pos <= numLinks) //if the position being searched for is in the list
	{
		ListNode* curNode = firstNode;

		for (int i = 0; i < pos; i++) //perform a linear search for the given position
		{
			curNode = curNode->next;
		}

		curNode->data = key; //once the position is found, update the data within the node

		return true; //return a flag that indicates the data was successfully updated
	}

	return false; //if the user entered an invalid position, then return a flag indicating the data was not updated
}


/****************************************************************************************************
** Description: Adds each node in the list to a vector and returns that vector.
****************************************************************************************************/
std::vector<std::string> StringList::getAsVector() const
{
	std::vector<std::string> vect(0); //creates a vector with no elements

	//loop through the list, adding the data stored in each node to a vector
	for (ListNode* curNode = firstNode; curNode != NULL; curNode = curNode->next)
	{
		vect.push_back(curNode->data);
	}

	return vect;
}


/****************************************************************************************************
** Description: Loops through the list, destroying each node
****************************************************************************************************/
void StringList::destroyList()
{
	ListNode* curNode = firstNode;

	for (int i = 0; i < numLinks; i++)
	{
		if (curNode != NULL) //make sure the current node points to a valid address
		{
			ListNode* temp = curNode->next; //save a copy of the current node's next reference
			delete curNode; //delete the current node
			curNode = temp; //assign the copy to the current node
		}
	}
}