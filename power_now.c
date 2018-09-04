#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	FILE* current_f;
	FILE* voltage_f;
	double current;
	double voltage;

	current_f = fopen("/sys/class/power_supply/BAT0/current_now", "r");
	voltage_f = fopen("/sys/class/power_supply/BAT0/voltage_now", "r");
	
	if (current_f == NULL || voltage_f == NULL) {
		fprintf(stderr, "Error: couldn't get current and voltage info!\n");
		return -1;
	}

	fscanf(current_f, "%lf", &current);
	fscanf(voltage_f, "%lf", &voltage);

	printf("%lf W\n", (current/1000000)*(voltage/1000000));

	fclose(current_f);
	fclose(voltage_f);

	return 0;

}
