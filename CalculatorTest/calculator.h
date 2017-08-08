#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

using namespace std;

#define is_operator(c) (c == '+' || c == '-' || c == '/' || c == '*' || c == '!')
#define is_ident(c) (c >= '0' && c <= '9')

class conveer
{
public:
	double value;
	char type = ' ';
	int priority;
};

int loader(char *input, conveer *line);//Load input string to a "conveer" type array (to deal with floating numbers)
bool leftlow(char op1, char op2);//Returns the result of priority comparsion of two operators
int revpolsen(conveer *input, conveer *output);//Convert infix notation into postfix. Uses the Shunting-yard algorithm.
double solve(conveer *line);//Calculate the postfix expression
double calculator(char *input);//Unites 4 functions above

double calculator(char *input)
{
	conveer output[32], line[32];
	/*int i = 0;*/
	if (loader(input, line) == 0)
		return 0;
	revpolsen(line, output);

	/*while (line[i].type != 'e')
	{
		if (line[i].type == 'n')
			fprintf(stdout, "%.2f ", line[i].value);
		else
			fprintf(stdout, "%c ", line[i].type);
		i++;
	}

	fprintf(stdout, "\n");
	i = 0;
	while (output[i].type != ' ')
	{
		if (output[i].type == 'n')
			fprintf(stdout, "%.2f ", output[i].value);
		else
			fprintf(stdout, "%c ", output[i].type);
		i++;
	}
	fprintf(stdout, "\n");*/

	return solve(output);
}

int revpolsen(conveer *input, conveer *output)
{


	conveer stack[32];

	int inposs = 0, outposs = 0, stposs = 0;

	while (input[inposs].type != 'e')//While something is on input array ("e" is a stop pointer placed by "loader" func) 
	{
		if (input[inposs].type == 'n')//If numbers
		{
			output[outposs] = input[inposs];//move it to output
			outposs++;
			inposs++;
		}
		if (is_operator(input[inposs].type))//If operator
		{
			while (is_operator(stack[stposs].type))
			{
				if (leftlow(input[inposs].type, stack[stposs].type))//while there is an operator at the top of the operator stack with
																	//greater than or equal to precedence and the operator is left associative :
																	//pop operators from the operator stack, onto the output queue.
				{
					output[outposs] = stack[stposs];
					stack[stposs].type = ' ';
					if (stposs != 0)stposs--;
					outposs++;
				}
				else
					break;
			}
			if (stposs == 0 && stack[stposs].type == ' ')
			{
				stack[stposs] = input[inposs];//push the read operator onto the operator stack.
				inposs++;


			}
			else
			{
				stack[stposs + 1] = input[inposs];//push the read operator onto the operator stack.
				inposs++;
				stposs++;
			}

		}
		if (input[inposs].type == '(')//if the token is a left bracket (i.e. "("), then:
									  //push it onto the operator stack.
		{
			if (input[inposs + 1].type == '-')
			{
				output[outposs].value = 0;
				output[outposs].type = 'n';
				outposs++;
			}
			if (stposs == 0 && !is_operator(stack[stposs].type))
			{
				stack[stposs] = input[inposs];
				inposs++;

			}
			else
			{
				stack[stposs + 1] = input[inposs];
				inposs++;
				stposs++;
			}

		}
		if (input[inposs].type == ')')//if the token is a right bracket(i.e. ")"), then:
									  //while the operator at the top of the operator stack is not a left bracket :


		{

			if (stack[stposs].type != '(')//pop operators from the operator stack onto the output queue.
			{
				output[outposs] = stack[stposs];
				stack[stposs].type = ' ';
				if (stposs != 0)stposs--;
				outposs++;

			}
			if (stack[stposs].type == '(') //pop the left bracket from the stack.
			{
				stack[stposs].type = ' ';
				if (stposs != 0)stposs--;
				inposs++;
			}


		}


	}
	while (stposs != -1)//if there are no more tokens to read:
	{

		output[outposs] = stack[stposs]; //while there are still operator tokens on the stack :	
		stack[stposs].type = ' ';		//pop the operator onto the output queue.
		stposs--;
		outposs++;

	}
	return 1;
}

bool leftlow(char op1, char op2)
{
	// Operators
	// Priority Pperator Assoc
	// 3		* /		  left
	// 2		+ -		  left

	int p1, p2;
	switch (op1)
	{
	case '+':p1 = 2; break;
	case '-':p1 = 2; break;
	case '*':p1 = 3; break;
	case '/':p1 = 3; break;
	}
	switch (op2)
	{
	case '+':p2 = 2; break;
	case '-':p2 = 2; break;
	case '*':p2 = 3; break;
	case '/':p2 = 3; break;
	}
	if (p1 <= p2)
		return true;
	else
		return false;
}

int loader(char *in, conveer *line)
{
	int b = 0, i = 0, j = 0, pos = 0;
	char box[10];
	char input[128];

	while (in[i] != '\n' && in[i] != '\0')
	{
		if (in[i] == ' ')
			i++;
		else
		{
			input[j] = in[i];
			j++;
			i++;
		}
	}
	input[j] = '\0';
	i = j = 0;
	while (input[i] != '\0')
	{
		while (is_ident(input[i]) || input[i] == '.' || input[i] == ',')//Collect numbers to 'box'
		{
			

			if (input[i] == ',')
				box[pos] = '.';
			else
				box[pos] = input[i];
			i++;
			pos++;

		}
		if (is_ident(input[i - 1]))//if there is no more number-pieces, pull 'box' to output 'line' array
		{
			box[pos] = '\n';
			line[j].value = strtod(box, NULL);
			line[j].type = 'n';
			for (pos = 0; pos < 10; pos++)
			{
				box[pos] = '0';
			}
			pos = 0;
			j++;
		}
		if (is_operator(input[i]))//pull operators to output array
		{
			if (input[i + 1] != '('  && !is_ident(input[i + 1]))
			{
				printf("Number missed\n");
				return 0;
			}
			if (is_operator(input[i - 1]))
			{
				printf("One operator cant follow second\n");
					return 0;
			}
			line[j].type = input[i];
			j++;
			i++;
		}
		if (input[i] == '(')//pull brackets to output array
		{
			b++;
			if (is_ident(input[i - 1]))
			{
				printf("Operator missed\n");
					return 0;
			}
			line[j].type = input[i];
			j++;
			i++;
		}
		if (input[i] == ')')//pull brackets to output array
		{
			b--;
			if (is_ident(input[i + 1]))
			{
				printf("Operator missed\n");
					return 0;
			}
			if (is_operator(input[i - 1]))
			{
				printf("Number missed\n");
					return 0;
			}
			line[j].type = input[i];
			j++;
			i++;
		}
		if (input[i] >= 'a'&&input[i] <= 'z' || input[i] >= 'A'&&input[i] <= 'Z')//Print error if restricted symbols on queue
		{
			printf("restricted symbols\n");
			if (getchar())
				return 0;
		}


	}
	if (b != 0)//Print error if bracket missed
	{
		if (b < 0)
		{
			printf("missed '('\n");//'('
				return 0;
		}
		if (b > 0)
		{
			printf("missed ')'\n");//')'
				return 0;
		}

	}
	line[j].type = 'e';
	return 1;
}

double solve(conveer *line)
{
	double res = 0;
	conveer stack[128];
	int inposs = 0, stposs = 0;
	double p1 = 0, p2 = 0, g=0;

	while (line[inposs].type != ' ')
	{


		if (line[inposs].type == 'n')//Numbers pulls to 'stack'
		{
			stack[stposs] = line[inposs];
			stposs++;
			inposs++;
		}
		if (line[inposs].type == '+')// +
		{
			if (stposs - 2 == -1)
			{
				p1 = 0;
				p2 = stack[stposs - 1].value;
				stack[stposs - 1].value = p1 + p2;
				inposs++;

			}
			else
			{
				p1 = stack[stposs - 2].value;
				p2 = stack[stposs - 1].value;
				stack[stposs - 2].value = p1 + p2;
				stack[stposs - 1].type = ' ';
				stposs--;
				inposs++;

			}
		}
		if (line[inposs].type == '-')// -
		{

			if (stposs - 2 == -1)
			{
				p1 = 0;
				p2 = stack[stposs - 1].value;
				stack[stposs - 1].value = p1 - p2;
				inposs++;

			}
			else
			{
				p1 = stack[stposs - 2].value;
				p2 = stack[stposs - 1].value;
				stack[stposs - 2].value = p1 - p2;
				stack[stposs - 1].type = ' ';
				stposs--;
				inposs++;

			}



		}
		if (line[inposs].type == '*')// *
		{
			if (stposs - 2 == -1)
			{
				printf("'*' is 2-operand operation\n");
					return 0;
			}
			else
				p1 = stack[stposs - 2].value;
			p2 = stack[stposs - 1].value;
			stack[stposs - 2].value = p1 * p2;
			stack[stposs - 1].type = ' ';
			stposs--;
			inposs++;
		}
		if (line[inposs].type == '/')// divide
		{
			
				
			
				if (stposs - 2 == -1)
				{
					printf("'/' is 2-operand operation\n");
						return 0;
				}
				else
					p1 = stack[stposs - 2].value;
				p2 = stack[stposs - 1].value;
				
				if (p2 == 0) {
						printf("Divide by zero\n");//Print error if divide by zero
						return 0;
				}
					
				stack[stposs - 2].value = p1 / p2;
				stack[stposs - 1].type = ' ';
				stposs--;
				inposs++;
				
		}
	}
	res = stack[stposs - 1].value;
	return res;
}