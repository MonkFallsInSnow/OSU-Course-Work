#ifndef SHOPPING_CART_HPP
#define SHOPPING_CART_HPP

#include "Item.hpp"

const int SIZE = 100;

class ShoppingCart
{
private:
	Item* items[SIZE];
	int arrayEnd;

public:
	ShoppingCart();

	void addItem(Item* item);
	double totalPrice();
};

#endif //SHOPPING_CART_HPP