#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void) {

	char *url = "http://flux/status?test=123&pretty=1";
	char *query = NULL;
	CURLU *handle;
        CURLUcode url_code;

	handle = curl_url();

	curl_url_set(handle, CURLUPART_URL, url, 0);
	url_code = curl_url_get(handle, CURLUPART_QUERY, &query, 0);
	if (!url_code) {
		printf("Query fields: %s\n", query);
	}
	else {
		return 1;
	}
	return 0;

}
