// gcc json-new00.c -ljson-c -o json-new00
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <json-c/json.h>

#define HTTP_BUFFER_SIZE	104857600

int main(void)
{
	const char *filename = "contact2.json";

	json_object *root = json_object_new_object();
	if (!root)
		return 1;
	json_object_object_add(root, "heaterStatus", json_object_new_string("ON"));
	json_object_object_add(root, "currentTemperature", json_object_new_string("74.0"));

	json_object *set_points = json_object_new_array();
	json_object_object_add(root, "setPoints", set_points);

	json_object *setpoint1 = json_object_new_object();
	json_object_object_add(setpoint1, "time", json_object_new_int(3600));
	json_object_object_add(setpoint1, "temp", json_object_new_double(78.0));
	json_object_array_add(set_points, setpoint1);

	json_object *setpoint2 = json_object_new_object();
	json_object_object_add(setpoint1, "time", json_object_new_int(3600));
	json_object_object_add(setpoint1, "temp", json_object_new_double(78.0));
	json_object_array_add(set_points, setpoint1);

	json_object *setpoint3 = json_object_new_object();
	json_object_object_add(setpoint3, "time", json_object_new_int(3600));
	json_object_object_add(setpoint3, "temp", json_object_new_double(78.0));
	json_object_array_add(set_points, setpoint3);

	char* header = "HTTP/1.1 200 OK\r\n"
		"Content-Type: application/json\r\n"
		"\r\n";

	const char* body = json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY);

	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	header = (char *)malloc(HTTP_BUFFER_SIZE * 2 * sizeof(char));
	int header_len = snprintf(header, 1024,
			"HTTP/1.1 200 OK\r\n"
			"Date: %s"
			"Content-Type: application/json\r\n"
			"Content-Length: %lu\r\n"
			"Connection: keep-alive\r\n"
			"Server: thermostatd/0.0.1\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Access-Control-Allow-Credentials: true\r\n", 
			asctime(timeinfo), strlen(body));

	printf("header: %s len: %d\n\n", header, header_len);

	char *response = (char *)malloc(HTTP_BUFFER_SIZE * 2 * sizeof(char));

	int temp_len = snprintf(response, HTTP_BUFFER_SIZE, header);
	snprintf(response + temp_len, HTTP_BUFFER_SIZE - temp_len, body);

	size_t *response_len = (size_t *)strlen(response);



	// print json
	printf("The json representation:\n\n%s\n\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PLAIN));

	printf("response:\n\n%s\n\n", response);

	free(response);

	return 0;
}
