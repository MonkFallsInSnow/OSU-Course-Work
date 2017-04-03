/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a movie. Provides an interface for creating movies
** that will be added to the library's catalog and for getting information about 
** those movies.
*************************************************************************************************/
#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "LibraryItem.hpp"
class Movie : public LibraryItem //inherits from LibraryItem
{
private:
	static const int CHECK_OUT_LENGTH; //how long any movie can be checked out for
	std::string director;

public:
	Movie(std::string idc, std::string t, std::string director); //constructor
	
	//getters
	std::string getDirector() const { return director; }
	virtual int getCheckOutLength() { return CHECK_OUT_LENGTH; }
};

#endif //MOVIE_HPP