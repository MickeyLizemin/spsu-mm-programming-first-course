#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	int counter;
	double array[3];
	double side1, side2, side3;

	printf("Enter the 3 positive numbers you want to check for the formation of a non-degenerate triangle:\n");

	for(counter = 0; counter < 3; counter++)
	{
		char end_of_line = 0;

		printf("Side %d: ", counter + 1);

		if(scanf("%lf%c", &array[counter], &end_of_line) != 2 || end_of_line != '\n' || array[counter] <= 0)
		{
			printf("The last data you entered is incorrect.\nPlease check it for correctness and re-enter.\n");
			fseek(stdin, 0, SEEK_END);
			counter--;
		}
	}

	side1 = array[0];
	side2 = array[1];
	side3 = array[2];

	if(side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2)
	{
		double angle1, angle2, angle3;
		double from_radians_to_degrees = 180 / 3.141592;

		angle1 = acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side2 * side3)) * from_radians_to_degrees;
		angle2 = acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side1 * side3)) * from_radians_to_degrees;
		angle3 = acos((side1 * side1 + side2 * side2 - side3 * side3) / (2 * side1 * side2)) * from_radians_to_degrees;

		printf("From the sides you entered, you can build a non-degenerate triangle.\nHere are its angles:\n");
		printf("The angle lying opposite the first side will be %d degrees, %d minutes, %d seconds.\n", \
			(int) angle1, (int) ((angle1 - (int) angle1) * 60), (int) (((angle1 - (int) angle1) * 60 - (int) ((angle1 - (int) angle1) * 60)) * 60));
		printf("The angle lying opposite the second side will be %d degrees, %d minutes, %d seconds.\n", \
			(int) angle2, (int) ((angle2 - (int) angle2) * 60), (int) (((angle2 - (int) angle2) * 60 - (int) ((angle2 - (int) angle2) * 60)) * 60));
		printf("The angle lying opposite the third side will be %d degrees, %d minutes, %d seconds.\n", \
			(int) angle3, (int) ((angle3 - (int) angle3) * 60), (int) (((angle3 - (int) angle3) * 60 - (int) ((angle3 - (int) angle3) * 60)) * 60));
	}
	else
	{
		printf("From the sides you entered, you can't build a non-degenerate triangle.\n");
	}

	return(0);
}