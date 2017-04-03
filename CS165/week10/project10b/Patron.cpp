/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a library patron. Provides an interface for tracking items
** rented and for getting information about the patron.
*************************************************************************************************/
#include "Patron.hpp"

//constructor
Patron::Patron(std::string idn, std::string n)
{
	idNum = idn; //patron id
	name = n; //patron's name
	fineAmount = 0.0; //patron's current fine amount
}

//---------getters---------------------------------------------------------
std::string Patron::getIdNum()
{
	return idNum;
}

std::string Patron::getName()
{
	return name;
}

std::vector<LibraryItem*> Patron::getCheckedOutItems()
{
	return checkedOutItems;
}

double Patron::getFineAmount()
{
	return fineAmount;
}

//-------member functions-----------------------------------------------------------------------------
/**************************************************************************************************
** Description: Adds a library item to the patron's list of rented items.
***************************************************************************************************/
void Patron::addLibraryItem(LibraryItem* b)
{
	checkedOutItems.push_back(b);
}


/**************************************************************************************************
** Description: Removes a library item from the  patron's list of rented items.
***************************************************************************************************/
void Patron::removeLibraryItem(LibraryItem* b)
{
	bool itemFound = false; //flag indicating whether or not the item was found in the patron's list of rented items
	int index = 0;

	//search the patron's list of rented items for the given argument
	while (!itemFound || index > checkedOutItems.size()) 
	{
		if (checkedOutItems[index]->getIdCode() != b->getIdCode())
		{
			index++;
		}
		else
		{
			itemFound = true;
		}
	}

	if (itemFound) //if the item was found...
	{
		std::vector<LibraryItem*>::iterator iter = checkedOutItems.begin() + index; //point an iterator to the index of the found item
		checkedOutItems.erase(iter); //remove the item from the underlying vector that represents the patron's list of retned items
	}
}


/**************************************************************************************************
** Description: Tracks a patron's fines.
***************************************************************************************************/
void Patron::amendFine(double amount)
{
	fineAmount += amount;
	
	if (fineAmount > -0.01 && fineAmount < 0.01)
	{
		fineAmount = 0;
	}
}