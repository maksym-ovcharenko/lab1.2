#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint_..t
#include <math.h>   // pow ()
#include <conio.h>  // system ("SLC")

void compare(double inputX1, double inputX2, double* X1, double* X2)
{
	if (inputX1 > inputX2)
	{
		*X2 = inputX1;
		*X1 = inputX2;
	}
	else
	{
		*X2 = inputX2;
		*X1 = inputX1;
	}
}
void inputArguments(double* inputX1, double* inputX2)
{
	double decoyX1, decoyX2;
	printf("\nEnter your start-argument : ");
	scanf("%lf", &decoyX1);

	printf("\nEnter your start-argument : ");
	scanf("%lf", &decoyX2);

	*inputX1 = decoyX1;
	*inputX2 = decoyX2;
}
void checkValueDelta(double* delta)
{
	double decoyDelta;
	do
	{
		printf("\nEnter your delta > 1.0      : ");
		scanf("%lf", &decoyDelta);
		if (decoyDelta < 1.0)
		{
			printf("\nTry again \n");
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF)
				;
		}
	} while (decoyDelta < 1.0);
	*delta = decoyDelta;
}
void checkValueNum(uint32_t* N)
{
	uint32_t decoyN;
	do
	{
		printf("\nEnter number of points    : ");
		scanf("%u", &decoyN);
		if (decoyN < 1.0)
		{
			printf("\nTry again \n");
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF)
				;
		}
	} while (decoyN < 1.0);
	*N = decoyN;
}
void drawPlusMinusLine( int width, int nColWidth,  int xColWidth,  int fColWidth)
{
	for (int i = 1; i <= width; i++)
	{
		if (i == 1 || i == (nColWidth + 2) || i == (xColWidth + nColWidth + 3) || i == (xColWidth + nColWidth + fColWidth + 4))
			printf("+");
		else
			printf("-");
	}
	printf("\n");
}
void drawStarLine(int width)
{
	for (int i = 1; i <= width; i++)
		printf("*");
	printf("\n");
}
void drawHeader(int width)
{
	// draw star-line function
	drawStarLine(width);
	// end of the star-line
	printf("*  N  *          X          *          F(X)           *\n");

	for (int i = 1; i <= width; i++)
		printf("*");
	printf("\n");
}
int main()
{
	// variables used for computing
	uint32_t variant, N;
	uint32_t n = 1;
	double inputX1, X1, inputX2, X2, delta, F;

	// flag for do while
	int flag;

	// columns width
    int width = 55;
	int nColWidth = 5;
    int xColWidth = 21;
    int fColWidth = 25;

	// enter variant and init variables
	do
	{
		flag = 0;
		// variant
		printf("Enter your variant (1 or 2) : ");
		scanf("%u", &variant);

		// two cases
		if (variant == 1)
		{
			inputArguments(&inputX1, &inputX2);

			compare(inputX1, inputX2, &X1, &X2);

			checkValueNum(&N);

			delta = (X2 - X1) / (double)(N);
		}
		else if (variant == 2)
		{
			inputArguments(&inputX1, &inputX2);

			compare(inputX1, inputX2, &X1, &X2);

			checkValueDelta(&delta);

			N = (uint32_t)(X2 - X1) / delta;
		}
		else
		{
			flag = 1;
			printf("\tTry again\n");
		}
	} while (flag);

	F = (pow(X1, 3)) / 3 - 5 * (pow(X1, 2)) + 1000;

	system("CLS");
	// display x1, x2, delta
	printf("X1 =  %4.2lf, X2 = %4.2lf, delta = %4.2lf\n", X1, X2, delta);

	// draw header (including two lines)
	// draw star-line function
	drawHeader(width);
	// end of the star-line
	// end of the header
	// calculate and display N X F(X) and plus-minus line
	while (X1 <= X2)
	{
		// draw plus-minus line
		drawPlusMinusLine(width, nColWidth, xColWidth, fColWidth);
		// end of the plus-minus line

		F = (pow(X1, 3)) / 3 - 5 * (pow(X1, 2)) + 1000;

		printf("|%5u|           %10.2lf|               %10.2lf|\n", n, X1, F);

		// increment
		X1 += delta;
		n++;

		if ((n % 9) == 0)
		{
			printf("Press any key to continue...");
			getch();
			system("CLS");
		}
	}
	// end
	return 0;
}

