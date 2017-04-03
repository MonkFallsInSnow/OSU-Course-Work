#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
private:
	std::string name;
	double price;
	int quantity;

public:
	Item();
	Item(std::string name, double price, int quantity);

	//setters
	void setName(std::string name)	{ this->name = name;		 }
	void setPrice(double price)		{ this->price = price;       }
	void setQuantity(int quantity)	{ this->quantity = quantity; }

	//getters
	std::string getName()	const { return name;     }
	double getPrice()		const { return price;    }
	int getQuantity()		const { return quantity; }


};

#endif //ITEM_HPP