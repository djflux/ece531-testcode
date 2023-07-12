#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define URL	"http://localhost:8989/schedule_clean"

typedef struct memory {
	char *response;
	size_t size;
} memory;

static size_t cb(void *data, size_t size, size_t nmemb, void *clientp)
{
	size_t realsize = size * nmemb;
	memory *mem = (memory *)clientp;

	char *ptr = realloc(mem->response, mem->size + realsize + 1);
	if(ptr == NULL)
		return 0;  /* out of memory! */

	mem->response = ptr;
	memcpy(&(mem->response[mem->size]), data, realsize);
	mem->size += realsize;
	mem->response[mem->size] = 0;

	return realsize;
}

int main(void) {

	CURL *curl;
	CURLcode res;

	memory chunk = {0};
	curl = curl_easy_init();

	if (curl) {

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION ,1L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		res = curl_easy_perform(curl);
	
		printf("response: %s\n", chunk.response);


	}

}
