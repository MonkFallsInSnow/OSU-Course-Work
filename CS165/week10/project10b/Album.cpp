/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a musical album  that can be checked out from a library.
** Provides an interface for creating albums that will be added to the library's catalog
** and for getting information about those albums.
*************************************************************************************************/
#include "Album.hpp"

const int Album::CHECK_OUT_LENGTH = 14; //how long any album can be checked out for

//constructor
Album::Album(std::string idc, std::string t, std::string artist) : LibraryItem(idc,t)
{
	this->artist = artist;
}
