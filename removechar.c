#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void testslash(char* string) {

	int i = 0;
	while(string[i] != '\0')
	{
		i++;

	}
	printf("%d\n", i);
	printf("%c\n", string[i-1]);
	string[i-1] = '\0';
	printf("string: %s\n",string);
}



int main() {
	char *test1 = "http://loclahost:8989/";
	char *test2 = "http://loclahost:8989/";

	testslash(test1);
	testslash(test2);

	return 0;
}
