/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a library book. Provides an interface for creating library
** books that will be added to the library's catalog and for getting information about 
** those books.
*************************************************************************************************/
#ifndef BOOK_HPP
#define BOOK_HPP

#include "LibraryItem.hpp"

class Book : public LibraryItem //inherits from LibraryItem
{
private:
	static const int CHECK_OUT_LENGTH; //how long any book can be checked out for
	std::string author;

public:
	Book(std::string idc, std::string t, std::string author); //constructor
	
	//getters
	std::string getAuthor() const { return author; }
	virtual int getCheckOutLength() { return CHECK_OUT_LENGTH; }
};

#endif //BOOK_HPP