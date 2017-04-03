/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/24/2015
** Description: This function takes a C-style string representation of a mathematical expression in 
** postfix notation and calculates the result.
*************************************************************************************************************/

#include <stack>
#include <string>
#include <cstring>
#include <cstdlib>

bool isOperator(char oper);

double postfixEval(char* expr)
{
	std::stack<double> stack;
	double result;
	std::string curOperand = ""; //stores an integer extracted from the  C-style string

	for (int i = 0; i < strlen(expr); i++) //examine each character in the C-style string given as a parameter
	{
		//if the current character is a digit, then append that character to a string variable
		if (isdigit(expr[i]))
		{
			curOperand += expr[i];
		}
		else if (expr[i] == ' ' && curOperand != "") //after an integer is pulled from the C-style string... 
		{
			stack.push(atof(curOperand.c_str())); //push it onto the stack
			curOperand = ""; //reset the string variable
		}
		else if (isOperator(expr[i])) //once an operator is read from the C-style string... 
		{
			//get the top two integer values from the top of the stack and pop them off the stack
			double left = stack.top(); 
			stack.pop();
			double right = stack.top();
			stack.pop();

			switch (expr[i]) //match the given operator to the appropriate operation
			{
			case '+':
				result = right + left;
				break;
			case '-':
				result = right - left;
				break;
			case '*':
				result = right * left;
				break;
			case '/':
				result = right / left;
				break;
			default:
				break;
			}

			stack.push(result); //push the result onto the stack
		}
	}

	//after the for loop has finished, there should be only one item left on the stack. return that item
	return stack.top(); 
}


/**********************************************************************************************************************
** Description: Compares a character to the basic arithmetic operators and returns a flag that indicates whether
** or not that character is a +, -, * or /.
***********************************************************************************************************************/
bool isOperator(char oper)
{
	if (oper == '+' || oper == '-' || oper == '*' || oper == '/')
	{
		return true;
	}

	return false;
}

/*********************************************************MAIN***************************************************************
#include <iostream>

using std::cout;
using std::endl;

double postfixEval(char expr[]);

int main()
{
	char s1[] = "25 12 7 - 2 * /";
	char s2[] = "5 6 +";
	char s3[] = "10 3 - 6 / 1 +";
	char s4[] = "3 5 - 8 * 2 + 1 3 + - 2 /";

	cout << "Postfix 25 12 7 - 2 * / (should be 2.5): " << postfixEval(s1) << endl;
	cout << "Postfix 5 6 + (should be 11): " << postfixEval(s2) << endl;
	cout << "Postfix 10 3 - 6 / 1 + (should be ~2.16667): " << postfixEval(s3) << endl;
	cout << "Postfix 3 5 - 8 * 2 + 1 3 + - 2 / (should be -9): " << postfixEval(s4) << endl;

	return 0;
}
*******************************************************************************************************************************/