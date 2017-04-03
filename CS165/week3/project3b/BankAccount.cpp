/********************************************************************************************
** Author: Conrad Lewin
** Date: 10/09/2015
** Description: This class provides the structure for a simple bank account interface for
something like an atm.
*********************************************************************************************/
#include "BankAccount.hpp"

//default constructor
BankAccount::BankAccount()
{
	customerName = "";
	customerID = "";
	customerBalance = 0.0;
}

//overloaded constructor
BankAccount::BankAccount(std::string name, std::string id, double balance)
{
	customerName = name;
	customerID = id;
	customerBalance = balance;
}

/**********************************************************************************************
** Description: Checks for a valid withdrawal amount and then subtracts the specified amount 
** from the user's balance.
***********************************************************************************************/
void BankAccount::withdraw(double amount)
{
	if (amount > 0)
	{
		customerBalance -= amount;
	}
}

/**********************************************************************************************
** Description: Checks for a valid deposit amount and then adds the specified amount
** to the user's balance.
***********************************************************************************************/
void BankAccount::deposit(double amount)
{
	if (amount > 0)
	{
		customerBalance += amount;
	}
}
