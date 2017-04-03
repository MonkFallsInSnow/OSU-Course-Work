/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a library. Provides an interface for performing a variety
** of different tasks relating to ordinary library operations such as checking out library
** items, returning those items, calculating fines, etc.
*************************************************************************************************/
#include "Library.hpp"

//constructor
Library::Library()
{
	currentDate = 0; //date 0 represents the founding of the library.
}


/**************************************************************************************************
** Description: Adds a library item to the library's catalog.
***************************************************************************************************/
void Library::addLibraryItem(LibraryItem* item)
{
	holdings.push_back(item); //add the item to underlying vector
}


/**************************************************************************************************
** Description: Adds a patron to the library's list of members.
***************************************************************************************************/
void Library::addPatron(Patron* patron)
{
	members.push_back(patron); //add the patron to underlying vector
}


/**************************************************************************************************
** Description: This function determines whether or not a user can check out a library item,
** printing a message indicating the success of the check out or the reason for failure. If 
** the item is successfully checked out, then the patrons list on rented items is updated.
***************************************************************************************************/
std::string Library::checkOutLibraryItem(std::string patronID, std::string ItemID)
{
	Patron* patron = getPatron(patronID); //get the user trying to check out the item
	LibraryItem* item = getLibraryItem(ItemID); //get the item being checked out

	if (patron != NULL) //make sure a valid patron address was retrieved
	{
		if (item != NULL) //make sure a valid library item address was retrieved
		{
			Patron* requester = item->getRequestedBy(); //get the patron that has placed a hold request on the item (if any)

			switch (item->getLocation()) //get the current location of the library item
			{
			case ON_SHELF: //if on the self...
				item->setCheckedOutBy(patron); //update who has checked out the item
				item->setDateCheckedOut(currentDate); //record the date the item was checked out
				item->setLocation(CHECKED_OUT); //update the location of the item
				patron->addLibraryItem(item); //add the item to the patron's list of rented items

				return "check out successful"; //indicate that the item has been successfully checked out
				break;
				
			case ON_HOLD_SHELF: //if the item is on hold...
				if (requester != NULL && requester->getIdNum() == patronID) //if the item is being checked out by the same patron who put a hold on the item...
				{
					item->setRequestedBy(NULL); //remove the hold request
					item->setCheckedOutBy(patron); //update who has checked out the item
					item->setDateCheckedOut(currentDate); //record the date the item was checked out
					item->setLocation(CHECKED_OUT); //update the location of the item
					patron->addLibraryItem(item); //add the item to the patron's list of rented items

					return "check out successful"; //indicate that the item has been successfully checked out
				}
				else
				{
					return "item on hold by other patron"; //otherwise, indicate that the item is on hold for another patron
				}
				break;
				
			case CHECKED_OUT: //if the item is already checked out
				return "item already checked out"; //indicate that the item has already been checked out
				break;
				
			default:
				break;
			}
		}
		else
		{
			return "item not found"; //otherwise, indicate that the item was not found
		}
	}
	else
	{
		return "patron not found"; //otherwise, indicate that there is no such patron of the library
	}
}


/**************************************************************************************************
** Description: This function determines whether or not an item can be returned to the library,
updating the item's location data and the patron's rented items list.
***************************************************************************************************/
std::string Library::returnLibraryItem(std::string ItemID)
{
	LibraryItem* item = getLibraryItem(ItemID); //get the item to be returned

	if (item != NULL) //if the item is valid...
	{
		if (item->getLocation() != CHECKED_OUT) //if the item has not been checked out...
		{
			return "item already in library"; //indicate that the item is already in the library
		}
		else //if the item has actually been checked out...
		{
			Patron* patron = item->getCheckedOutBy(); //get the patron who checked out the item

			patron->removeLibraryItem(item); //update the patron's list of rented items

			if (item->getRequestedBy() == NULL) //if the item does not have a hold request
			{
				item->setLocation(ON_SHELF); //then put it on the shelf
			}
			else
			{
				item->setLocation(ON_HOLD_SHELF); //otherwise, put it on the hold shelf
			}

			item->setCheckedOutBy(NULL); //update the current renter of the item to no one

			return "return successful"; //indicate a successful return
		}
	}
	else
	{
		return "item not found"; //otherwise, indicate that the item was not found in the library's catalog
	}
}


/**************************************************************************************************
** Description: This function allows a user put a hold request on a library item.
***************************************************************************************************/
std::string Library::requestLibraryItem(std::string patronID, std::string ItemID)
{
	LibraryItem* item = getLibraryItem(ItemID); //get the item requested
	Patron* patron = getPatron(patronID); //get the patron requesting the item

	if (patron != NULL) //make sure the patron is valid
	{
		if (item != NULL) //make sure the item is valid
		{
			if (item->getRequestedBy() == NULL) //if no one else has requested the item...
			{
				item->setRequestedBy(patron); //update who has placed a request on the item

				if (item->getLocation() == ON_SHELF) //move the item to the hold shelf
				{
					item->setLocation(ON_HOLD_SHELF);
				}

				return "request successful"; //indicate the hold request was successful
			}
			else //if there is already a hold on the item, then indicate this reality
			{
				return "item already on hold"; 
			}
		}
		else
		{
			return "item not found"; //otherwise, indicate that there is no such item in the library's catalog
		}
	}
	else
	{
		return "patron not found"; //otherwise, indicate there is no such patron of the library
	}
}


/**************************************************************************************************
** Description: This function allows a user to pay a library fine.
***************************************************************************************************/
std::string Library::payFine(std::string patronID, double payment)
{
	Patron* patron = getPatron(patronID); //get the patron trying to pay a fine

	if (patron != NULL) //make sure the patron is valid
	{
		patron->amendFine(-payment); //reduce the patron's fine by specified amount
		return "payment successful"; //indicate that the payment was successful
	}
	else
	{
		return "patron not found"; //otherwise, indicate that there is no such patron of the library
	}
}


/**************************************************************************************************
** Description: This function tracks how many days the library has been in operation and doles
** out fines on any overdue items to the the appropriate patron.
***************************************************************************************************/
void Library::incrementCurrentDate()
{
	currentDate++; //update the number of days the library has been in operation

	for (int i = 0; i < holdings.size(); i++) //go through the library's catalog
	{
		LibraryItem* item = holdings[i]; //save a copy of the currently examined item

		if (item->getLocation() == CHECKED_OUT) //if that item has been checked out...
		{
			int dateCheckedOut = item->getDateCheckedOut(); //get the date the item was checked out
			int checkOutLen = item->getCheckOutLength(); //get the number of days an item can be checked out without penalty
			int returnDate = dateCheckedOut + checkOutLen; //get the last day the item can been checked out without penalty

			if (currentDate > returnDate) //if the item has been held longer than its check out length...
			{
				Patron* patron = item->getCheckedOutBy(); //get the patron who checked out the item
				patron->amendFine(0.10); //add 10 cents to his/her fine
			}
		}
	}
}


/**************************************************************************************************
** Description: This function searches the library's list of members for a specific patron. A
** linear search was chosen because the nature/content of the patron ID was unknown.
***************************************************************************************************/
Patron* Library::getPatron(std::string patronID)
{
	for (int i = 0; i < members.size(); i++) //performs a linear search for the specified patron
	{
		if (members[i]->getIdNum() == patronID)
		{
			return members[i];
		}
	}

	return NULL;
}


/**************************************************************************************************
** Description: This function searches the library's catalog for a specific item. A
** linear search was chosen because the nature/content of the item ID was unknown.
***************************************************************************************************/
LibraryItem* Library::getLibraryItem(std::string ItemID)
{
	for (int i = 0; i < holdings.size(); i++)
	{
		if (holdings[i]->getIdCode() == ItemID) //performs a linear search for the specified item
		{
			return holdings[i];
		}
	}

	return NULL;
}
