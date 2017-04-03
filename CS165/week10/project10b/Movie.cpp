/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a movie. Provides an interface for creating movies
** that will be added to the library's catalog and for getting information about 
** those movies.
*************************************************************************************************/
#include "Movie.hpp"

const int Movie::CHECK_OUT_LENGTH = 7; //how long any movie can be checked out for

//constructor
Movie::Movie(std::string idc, std::string t, std::string director) : LibraryItem(idc,t)
{
	this->director = director;
}