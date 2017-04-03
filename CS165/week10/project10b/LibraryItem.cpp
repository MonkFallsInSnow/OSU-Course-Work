/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: This is an abstract base class that provides an interface for the more 
** specific library items (books, movies and albums)
*************************************************************************************************/
#include "LibraryItem.hpp"

//constructor
LibraryItem::LibraryItem(std::string idc, std::string t)
{
	idCode = idc; //unique identifier for a library item
	title = t; //name of the item
	location = ON_SHELF; //current location in the library
	checkedOutBy = NULL; //current renter
	requestedBy = NULL; //current requesting library patron
}

//-----------getters----------------------------------------------------------------
std::string LibraryItem::getIdCode()
{
	return idCode;
}

std::string LibraryItem::getTitle()
{
	return title;
}

Locale LibraryItem::getLocation()
{
	return location;
}

Patron* LibraryItem::getCheckedOutBy()
{
	return checkedOutBy;
}

Patron* LibraryItem::getRequestedBy()
{
	return requestedBy;
}

int LibraryItem::getDateCheckedOut()
{
	return dateCheckedOut;
}

//----------setters--------------------------------------------------------------------------
void LibraryItem::setLocation(Locale loc)
{
	location = loc;
}

void LibraryItem::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
}

void LibraryItem::setRequestedBy(Patron* p)
{
	requestedBy = p;
}

void LibraryItem::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}