#include "Item.hpp"

//default constructor
Item::Item()
{
	name = "";
	price = 0.0;
	quantity = 0;
}

//overloaded constructor
Item::Item(std::string name, double price, int quantity)
{
	setName(name);
	setPrice(price);
	setQuantity(quantity);
}
