#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "calculator.h"






void main()
{
	
	
	char input[64];
	while (1) 
	{
	printf("Insert expression ('~' to exit): ");
	fgets(input,64,stdin);
	if (input[0] == '~')
		break;
	printf("%.2f\n",calculator(input));
	}
	system("pause");
}



