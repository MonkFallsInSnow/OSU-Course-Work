/***********************************************************************************************
** Author: Conrad Lewin
** Date: 11/28/2015
** Description: Blueprint for a musical album  that can be checked out from a library.
** Provides an interface for creating albums that will be added to the library's catalog
** and getting information about those albums.
*************************************************************************************************/
#ifndef ALBUM_HPP
#define ALBUM_HPP

#include "LibraryItem.hpp"

class Album : public LibraryItem
{
private:
	static const int CHECK_OUT_LENGTH; //how long the item can be checked out for
	std::string artist;

public:
	Album(std::string idc, std::string t, std::string artist); //constructor

	//getters
	std::string getArtist() const { return artist; }
	virtual int getCheckOutLength() { return CHECK_OUT_LENGTH; }
};

#endif // ALBUM_HPP