/*********************************************************************************************************
** Author: Conrad Lewin
** Date: 11/6/2015
** Description: This class explores the use of operator overloading and copy constructors.
***********************************************************************************************************/
#ifndef MY_INTEGER_HPP
#define MY_INTEGER_HPP

class MyInteger
{
private:
	int* pInteger;

public:
	MyInteger(int x); //default constructor
	MyInteger(const MyInteger &obj);//copy constructor
	~MyInteger(); //destructor

	void setMyInt(int x) { *pInteger = x;    } //setter
	int getMyInt() const { return *pInteger; } //getter

	MyInteger operator=(const MyInteger &right); //overloaded asignment operator
};

#endif //MY_INTEGER_HPP