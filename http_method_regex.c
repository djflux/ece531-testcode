#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

int main (void)
{
	int match;
	int err;
	regex_t preg;
	regmatch_t pmatch[5]; // We have 4 capturing groups + the whole match group
	size_t nmatch = 5; // Same as above
	char *str_request = (char *)malloc(104857600 * sizeof(char));
	// char *buffer = "GET /status?pretty=1 HTTP/1.1#015#012Host: localhost:8088#015#012User-Agent: curl/7.81.0#015#012Accept: */*#015#012#015#012";
	//char *buffer = "GET /status HTTP/1.1#015#012Host: localhost:8088#015#012User-Agent: curl/7.81.0#015#012Accept: */*#015#012#015#012";
	char *buffer = "GET /status HTTP/1.1#015#012Host: localhost:8088#015#012User-Agent: curl/7.81.0#015#012Accept: */*#015#012#015#012";



	snprintf(str_request, strlen(buffer), "%s", buffer);
	//const char *str_regex = "([A-Za-z]+) +(/.*)?+(.*) +(HTTP/[0-9][.][0-9])";
	const char *str_regex = "([A-Za-z]+) +(/[A-Za-z0-9]+)\???+(.*) +(HTTP/[0-9][.][0-9])";

	char *method = (char *)malloc(104857600 * sizeof(char));
	char *query  = (char *)malloc(104857600 * sizeof(char));
	err = regcomp(&preg, str_regex, REG_EXTENDED);
	if (err == 0)
	{
		match = regexec(&preg, str_request, nmatch, pmatch, 0);
		nmatch = preg.re_nsub;
		regfree(&preg);
		if (match == 0)
		{
			printf("Number of match groups: %ld\n", nmatch);
			printf("\"%.*s\"\n", pmatch[1].rm_eo - pmatch[1].rm_so, &str_request[pmatch[1].rm_so]);
			printf("\"%.*s\"\n", pmatch[2].rm_eo - pmatch[2].rm_so, &str_request[pmatch[2].rm_so]);
			printf("\"%.*s\"\n", pmatch[3].rm_eo - pmatch[3].rm_so, &str_request[pmatch[3].rm_so]);
			printf("\"%.*s\"\n", pmatch[4].rm_eo - pmatch[4].rm_so, &str_request[pmatch[4].rm_so]);

			snprintf(method, (pmatch[1].rm_eo - pmatch[1].rm_so)+1, "%s", &str_request[pmatch[1].rm_so]);
			snprintf(query, (pmatch[3].rm_eo - pmatch[3].rm_so)+1, "%s", &str_request[pmatch[3].rm_so]);
			printf("method: %s\n", method);
			if (method == "GET") {
				printf("standard compare worked\n");
			}

			if (strcmp(method, "GET") == 0) {
				printf("strcmp worked.\n");
			}


			printf("query:  %s\n", query);

		}
		else if (match == REG_NOMATCH)
		{
			printf("unmatch\n");
		}
	}
	return 0;
}
