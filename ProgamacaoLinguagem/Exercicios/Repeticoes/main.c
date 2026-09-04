#include <stdio.h>

int main()
{
	for (int i = 0; i <= 10; i++) {
		printf("For: %d \n", i);
	}
	
	int i = 11;
	while (i <= 20) {
		printf("While: %d \n", i);
	    i++;
	}
	
	do {
		printf("Do While: %d \n", i);
		i++;
	} while (i <= 30);

	return 0;
}
