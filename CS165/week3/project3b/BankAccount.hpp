/********************************************************************************************
** Author: Conrad Lewin
** Date: 10/09/2015
** Description: This class provides the structure for a simple bank account interface for
something like an atm.
*********************************************************************************************/
#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <string>

class BankAccount
{
private:
	//member variables
	std::string customerName;
	std::string customerID;
	double customerBalance;

public:
	//default constructor
	BankAccount();
	//overloaded constructor
	BankAccount(std::string name, std::string id, double balance);

	//getters
	std::string getCustomerName() const { return customerName;    }
	std::string getCustomerID()   const { return customerID;      }
	double getCustomerBalance()   const { return customerBalance; }

	void withdraw(double amount);//subtracts a specified amount from the balance
	void deposit(double amount);//adds a specified amount to the balance
};

#endif //BANK_ACCOUNT_HPP
