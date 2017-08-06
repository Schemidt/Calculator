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

int loader(char *input, conveer *line);
bool leftlow(char op1, char op2);
int revpolsen(conveer *input, conveer *output);
double solve(conveer *line);//Вычисляет обратную польскую запись
double calculator(char *input);

void main()
{
	
	
	char input[64];
	while (1) 
	{
	printf("Insert sentence ('~' to exit): ");
	fgets(input,64,stdin);
	if (input[0] == '~')
		break;
	printf("%.2f\n",calculator(input));
	}
	system("pause");
}

double calculator(char *input)//функция вычисляющая значение выражения введенного пользователем
{
	conveer output[32], line[32];
	int i = 0;

	if (loader(input, line) == 0)
		return 0;
	revpolsen(line, output);

	while (line[i].type != 'e')
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
	fprintf(stdout, "\n");

	return solve(output);
}

int revpolsen(conveer *input, conveer *output)
{
	
	
	conveer stack[32];
	
	int inposs = 0, outposs = 0, stposs = 0;

	while (input[inposs].type != 'e')//Пока что-то есть на очереди
	{
		if (input[inposs].type=='n')//если число
		{
			output[outposs] = input[inposs];
			outposs++;
			inposs++;
		}
		if (is_operator(input[inposs].type))//если оператор
		{
			while(is_operator(stack[stposs].type))//перекладываем все операторы на выход пока на вершине стека оператор
			{
				if (leftlow(input[inposs].type, stack[stposs].type))//op2 из стека в выходную очередь
				{
					output[outposs] = stack[stposs];
					stack[stposs].type = ' ';
					if (stposs != 0)stposs--;
					outposs++;
				}
				else
					break;
			}
			if (stposs == 0 && stack[stposs].type== ' ')
			{
				stack[stposs] = input[inposs];//op1 в стек
				inposs++;
				

			}
			else
			{
				stack[stposs + 1] = input[inposs];//op1 в стек
				inposs++;
				stposs++;
			}

		}
		if (input[inposs].type == '(')//если открывающая скобка
		{
			if (input[inposs+1].type == '-')
			{
				output[outposs].value = 0;
				output[outposs].type = 'n';
				outposs++;
			}
			if (stposs == 0 && !is_operator(stack[stposs].type))
			{
				stack[stposs] = input[inposs];//скобка в стек
				inposs++;
				
			}
			else
			{
				stack[stposs + 1] = input[inposs];
				inposs++;
				stposs++;
			}

		}
		if (input[inposs].type == ')')//если закрывающая скобка
		{
			
			if (stack[stposs].type!= '(')//пока на вершине стека нет открывающей скобки перекладываем стек в вых очередь
			{
				output[outposs] = stack[stposs];
				stack[stposs].type = ' ';
				if (stposs != 0)stposs--;
				outposs++;

			}
			if (stack[stposs].type == '(')//выкинуть открывающую скобку из стека
			{
				stack[stposs].type = ' ';
				if (stposs != 0)stposs--;
				inposs++;
			}
			
		
		}
		
		
	}
	while (stposs != -1)//Когда входной поток закончился, продолжаем обрабатывать стек
	{
		
		output[outposs] = stack[stposs];
		stack[stposs].type = ' ';
		stposs--;
		outposs++;

	}
	return 1;
}

bool leftlow(char op1,char op2)//функция сравнения приоритетов
{
	// Операторы
	// Приоритет Оператор Ассоциативность
	// 3 * /  левая
	// 2 + - левая
	
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

int loader(char *input, conveer *line)//Разбивает входную строку на элементы и записывает в массив
{
	int b=0,i=0,j=0,pos=0;
	char box[10];
	

	while(input[i]!='\n')
	{
		while(is_ident(input[i])||input[i] == '.' || input[i] == ',')//Собираем число в контейнер
		{
			if (input[i] == ',')
				box[pos] = '.';
			else
			box[pos] = input[i];
			i++;
			pos++;
			
		}
		if (is_ident(input[i-1]))//если все число получено-сохраняем в выходной массив
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
		if(is_operator(input[i]))//операторы  сохраняем в вых массив
		{
			if (is_operator(input[i - 1]))
			{
				printf("One operator cant follow second");
				if (getchar())
					return 0;
			}
			line[j].type = input[i];
			j++;
			i++;
		}
		if (input[i] == '(')//скобки сохраняем в вых массив
		{
			b++;
			if (is_ident(input[i - 1]))
			{
				printf("operator missed");
				if (getchar())
					return 0;
			}
			line[j].type = input[i];
			j++;
			i++;
		}
		if (input[i] == ')')//скобки сохраняем в вых массив
		{
			b--;
			if (is_ident(input[i + 1]))
			{
				printf("operator missed");
				if (getchar())
					return 0;
			}
			if (is_operator(input[i - 1]))
			{
				printf("number missed");
				if (getchar())
					return 0;
			}
			line[j].type = input[i];
			j++;
			i++;
		}
		if (input[i] == ' ')
			i++;

		if (input[i]>='a'&&input[i]<='z'|| input[i] >= 'A'&&input[i] <= 'Z')//если введены недопустимые символы-вывести ошибку
		{
				printf("restricted symbols");
				if (getchar())
					return 0;
		}
		
		
	}
	if (b != 0)//Пропущена скобка
	{
		if (b < 0)
		{
			printf("missed '('");//открывающая
			if (getchar())
				return 0;
		}
		if (b > 0)
		{
			printf("missed ')'");//закрывающая
			if (getchar())
				return 0;
		}

	}
	line[j].type = 'e';
	return 1;
}

double solve(conveer *line)//Вычисляет обратную польскую запись
{
	double res = 0;
	conveer stack[128];
	int inposs = 0, stposs = 0;
	double p1 = 0, p2 = 0;

	while (line[inposs].type != ' ')
	{


		if (line[inposs].type == 'n')//числа кидаем  в стек
		{
			stack[stposs] = line[inposs];
			stposs++;
			inposs++;
		}
		if (line[inposs].type == '+')//обрабатываем сложение
		{
			if (stposs - 2 == -1)
				p1 = 0;
			else
				p1 = stack[stposs - 2].value;
			p2 = stack[stposs - 1].value;
			stack[stposs - 2].value = p1 + p2;
			stack[stposs - 1].type = ' ';
			stposs--;
			inposs++;
		}
		if (line[inposs].type == '-')//обрабатываем разность
		{
			if (line[inposs + 1].type == '-')
			{
				if (stposs - 2 == -1)
				{
					p1 = 0;
					p2 = stack[stposs - 1].value;
					stack[stposs - 1].value = p1 + p2;
					inposs += 2;

				}
					
				else
				{
					p1 = stack[stposs - 2].value;
					p2 = stack[stposs - 1].value;
					stack[stposs - 2].value = p1 + p2;
					stack[stposs - 1].type = ' ';
					stposs--;
					inposs += 2;

				}
				
			}
			else
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
			
				
		}
		if (line[inposs].type == '*')//обрабатываем произведение
		{
			if (stposs - 2 == -1)
			{
				printf(" '*' is 2-operand operation \n");
				if (getchar())
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
		if (line[inposs].type == '/')//обрабатываем деление
		{
			if (stposs - 2 == -1)
				p1 = 0;
			else
				p1 = stack[stposs - 2].value;
			p2 = stack[stposs - 1].value;
			if (p2 == 0)
			{
				printf("Divide by zero\n");
				if (getchar())
					return 0;

			}
			else
			stack[stposs - 2].value = p1 / p2;
			stack[stposs - 1].type = ' ';
			stposs--;
			inposs++;
		}
	}
	res = stack[stposs - 1].value;
	return res;
}

