
#include <stdio.h>

int main()
{
	int fd = open(0, O_RDONLY);
	char *tmp;
	char size = 10;

	getline(&tmp, &size, 0);
	printf("%s\n", tmp);
	
	getline(&tmp, &size, 0);
	printf("%s\n", tmp);
	/* code */
	return 0;
}