#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


FILE *_openfile(char *filename, char *mode) {

	FILE *file = fopen(filename, mode);

	if (!file) {
		printf("Couldn't open %s\n", filename);
		return NULL;
	}

	return file;
}

char *_readfile(FILE *file) {
	char *buf;
	long len;

	fseek(file, 0L, SEEK_END);
	len = ftell(file);
	rewind(file);

	buf = calloc(1, len+1);
	if (!buf) {
		fclose(file);
		printf("Couldn't allocate memory.\n");
		exit(1);
	}

	if ( fread(buf, len, 1, file) != 1 ) {
                fclose(file);
                printf("Couldn't read file.\n");
                exit(12);
	}

	return buf;
}



void _turn_heater_on(FILE *file) {

}

int main(void) {

	char *temperature, *status;
	char *tempfile = "/tmp/temp";
	char *statusfile = "/tmp/status";
	FILE *temp, *heater_status;

	temp = _openfile(tempfile, "r");
	heater_status = _openfile(statusfile, "r+");


	if (!temp) {
		return 187;
	} else {
		temperature = _readfile(temp);
		printf("Temperature: %.2f\n", atof(temperature));
	}

        if (!heater_status) {
		printf("Could not open %s\n. Turning heater OFF.", statusfile);
		return 99;
        } else {
                status = _readfile(heater_status);
                printf("Heater status is: %s", status);
                return 0;
        }

}
