#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *stringRemoveNonAlphaNum(char *str)
{
	unsigned long i = 0;
	unsigned long j = 0;
	char c;
	char *tmp = malloc(sizeof(str) + 1);

	while ((c = str[i]) != '\0') {
		if (isalnum(c)) {
			tmp[j] = str[i];
			i++;
			j++;
		} else {
			i++;
		}
	}

	tmp[j] = '\0';

	return tmp;
}

int main(void) {

	char *z = "\"flux\"";

	char *alphanum = stringRemoveNonAlphaNum(z);

	printf("no special chars: %s\n", alphanum);

	free(alphanum);


	return 0;
}
