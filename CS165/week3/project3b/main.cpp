#include "BankAccount.hpp"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

int main()
{
	std::string line = "--------------------------";
	BankAccount ba1;
	BankAccount ba2("Sam","5678",359.35);
	BankAccount ba3("Gabo","0987",42.22);

	cout << std::fixed << std::setprecision(2);

	cout << "Bank Account 1" << endl;
	cout << line << endl;
	cout << "Name: " << ba1.getCustomerName() << endl;
	cout << "ID: " << ba1.getCustomerID() << endl;
	cout << "Balance: " << ba1.getCustomerBalance() << endl;
	cout << "Withdraw $-50..." << endl;
	ba1.withdraw(-50);
	cout << "New Balance: " << ba1.getCustomerBalance() << endl;
	cout << "Deposit $-200..." << endl;
	ba1.deposit(-200);
	cout << "New Balance: " << ba1.getCustomerBalance() << endl << endl;

	cout << "Bank Account 2" << endl;
	cout << line << endl;
	cout << "Name: " << ba2.getCustomerName() << endl;
	cout << "ID: " << ba2.getCustomerID() << endl;
	cout << "Balance: " << ba2.getCustomerBalance() << endl;
	cout << "Withdraw $50.15..." << endl;
	ba2.withdraw(50.15);
	cout << "New Balance: " << ba2.getCustomerBalance() << endl;
	cout << "Deposit $200.89..." << endl;
	ba2.deposit(200.89);
	cout << "New Balance: " << ba2.getCustomerBalance() << endl << endl;

	cout << "Bank Account 3" << endl;
	cout << line << endl;
	cout << "Name: " << ba3.getCustomerName() << endl;
	cout << "ID: " << ba3.getCustomerID() << endl;
	cout << "Balance: " << ba3.getCustomerBalance() << endl;
	cout << "Withdraw $50..." << endl;
	ba3.withdraw(50);
	cout << "New Balance: " << ba3.getCustomerBalance() << endl;
	cout << "Deposit $200..." << endl;
	ba3.deposit(200);
	cout << "New Balance: " << ba3.getCustomerBalance() << endl << endl;

	return 0;
} 
