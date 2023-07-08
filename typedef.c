#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_SETPOINTS	3

int main(void) {

	typedef struct setpoint {
		int time;
		double temp;
	} setpoint;

	setpoint (*schedule)[] = malloc(NUMBER_OF_SETPOINTS * sizeof(setpoint));

	setpoint *item = malloc(sizeof(setpoint));

	item->time = 3600;
	item->temp = 20.0;
	(*schedule)[0] = *item;

	printf("time: %d\n", (*schedule)[0].time);
        printf("temp: %f\n", (*schedule)[0].temp);

	free(item);
	return 0;
}
