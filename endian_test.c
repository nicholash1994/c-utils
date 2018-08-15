#include <stdint.h>
#include <stdio.h>

union endian_test {
	uint32_t a;
	unsigned char b[4];
};

int main(int argc, char** argv) {
	union endian_test my_test;

	my_test.a = 0x00aabbcc;

	printf("0x%x 0x%x 0x%x 0x%x\n", my_test.b[0], my_test.b[1],
									my_test.b[2], my_test.b[3]);

	if (my_test.b[0] == 0xcc)
		printf("This machine is little endian!\n");
	else
		printf("This machine is big endian!\n");
	
	return 0;
}
