#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>

#include "stack.h"

using namespace std;

int main(int argc, const char *argv[])
{
	Stack<double> operands;
	Stack<char> operators;

	string exp;
	istringstream is;
	while (getline(cin, exp)) {
		string token;
		is.str(exp);
		while (is >> token) {
			if (token == "(") {
				continue;
			}
			// operator
			else if (token == "+" || token == "-" || token == "*" || token == "/" ||
					token == "sqrt") {
				operators.push(token[0]);
			}
			else if (token == ")") {
				char optor = operators.pop();
				double operand = operands.pop();
				double val = 0;
				switch (optor) {
					case '+': val = operand + operands.pop(); break;
					case '-': val = operands.pop() - operand; break;
					case '*': val = operand * operands.pop(); break;
					case '/': val = operands.pop() / operand; break;
					case 's': val = sqrt(operand); break;
					default:
								 cerr << "error: unknown operator: [" << optor << "]" << endl;
								 break;
				}
				operands.push(val);
			}
			// operand
			else {
				operands.push(stod(token));
			}
		}
		is.clear();
		cout << " = " << operands.pop() << endl;
	}

	return 0;
}
