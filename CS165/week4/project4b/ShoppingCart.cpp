#include "ShoppingCart.hpp"

//default constructor
ShoppingCart::ShoppingCart()
{
	arrayEnd = 0;

	//initialize the items array
	for (int i = 0; i < SIZE; i++)
	{
		items[i] = NULL;
	}

}

/************************************************************************************
** Description: Adds a pointer to an Item to the items array.
*************************************************************************************/
void ShoppingCart::addItem(Item* item)
{
	items[arrayEnd++] = item; //add an item the array and change the position of the iterator (arrayEnd)
}

/*************************************************************************************
** Description: Loops through the items array and calculates the total dollar amount.
**************************************************************************************/
double ShoppingCart::totalPrice()
{
	double price = 0.0; //initialize accumulator variable

	for (int i = 0; i < arrayEnd; i++)
	{
		//gets a running total of the price of each item in the items array
		price += (items[i]->getQuantity() * items[i]->getPrice());
	}

	return price;
}