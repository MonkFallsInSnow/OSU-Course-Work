/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a library book. Provides an interface for creating library
** books that will be added to the library's catalog and for getting information about 
** those books.
*************************************************************************************************/
#include "Book.hpp"

const int Book::CHECK_OUT_LENGTH = 21; //how long any book can be checked out for

//constructor
Book::Book(std::string idc, std::string t, std::string author) : LibraryItem(idc,t)
{
	this->author = author;
}
