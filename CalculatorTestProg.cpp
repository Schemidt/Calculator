#include "calculator.h"

int main(void)
{
	if (calculator("1+2\n") == 3)//1+2=3
		printf("1+2 = 3 - OK\n");
	else
		printf("1+2 != 3 - FAULT\n");

	if (calculator("3-1\n") == 2)//3-1=2
		printf("3-1 = 2 - OK\n");
	else
		printf("3-1 != 2 - FAULT\n");

	if (calculator("3*1\n") == 3)//3*1=3
		printf("3*1 = 3 - OK\n");
	else
		printf("3*1 != 3 - FAULT\n");

	if (calculator("1/2\n") == 0.5)//1/2=0.5
		printf("1/2 = 0.5 - OK\n");
	else
		printf("1/2 != 0.5 - FAULT\n");

	if (calculator("(1)\n") == 1)//(1)=1
		printf("(1) = 1 - OK\n");
	else
		printf("(1) != 1 - FAULT\n");

	if (calculator("(-1)\n") == -1)//(-1)=-1
		printf("(-1) = -1 - OK\n");
	else
		printf("(-1) = -1 - FAULT\n");

	if (calculator(" - 1 + 5 - 3\n") == 1)//-1 + 5 - 3 = 1
		printf("-1 + 5 - 3 = 1 - OK\n");
	else
		printf("-1 + 5 - 3 != 1 - FAULT\n");

	if (calculator("-10 + (8 * 2.5) - (3 / 1, 5)\n") == 8)//-10 + (8 * 2.5) - (3 / 1, 5) = 8
		printf("-10 + (8 * 2.5) - (3 / 1, 5) = 8 - OK\n");
	else
		printf("-10 + (8 * 2.5) - (3 / 1, 5) != 8 - FAULT\n");

	if (calculator("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)\n") == 11)//1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5) = 11
		printf("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5) = 11 - OK\n");
	else
		printf("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5) != 11 - FAULT\n");



	return 0;
}

