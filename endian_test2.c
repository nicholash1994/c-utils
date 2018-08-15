#include <stdio.h>
#include <stdint.h>

int main() {
	uint16_t i = 1;
	char* p;
	
	p = (char*)&i;
	
	if (*p == 1)
		printf("Little endian\n");
	else
		printf("Big endian\n");

	return 0;
}
