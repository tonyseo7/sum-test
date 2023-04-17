#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint> 
#include <sys/types.h> /* For system call open */
#include <sys/stat.h>  /* For system call open */
#include <fcntl.h>     /* For system call open */

#include "add-nbo.h"
#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf

void dump(void* p, size_t n) {
	uint8_t* u8 = static_cast<uint8_t*>(p);
	size_t i = 0;
	while (true) {
		printf("%02X ", *u8++);
		if (++i >= n) break;
		if (i % 8 == 0)
			printf("\n");
	}
	printf("\n");
}



//상위 8bit와 하위 8bit 바꿈
uint16_t my_ntohs(uint16_t n){

	uint16_t a=0;
	uint16_t b=0;
	uint16_t result;


	a = n>>8;
	a = a & 0x00ff;

	b = n<<8;
	b = b & 0xff00;
	result = a | b;


	return result;
}

void write_4660() {
	uint16_t port = 4660; // 0x1234
	printf("port number = %d\n", port);
	dump(&port, sizeof(port));
}

void  write_0x1234() {
	uint8_t network_buffer[] = { 0x12, 0x34 };
	uint16_t* p = reinterpret_cast<uint16_t*>(network_buffer);
	uint16_t n = my_ntohs(*p); // TODO
	printf("16 bit number=0x%x\n", n);
}

void  write_0x12345678() {
	uint8_t network_buffer[] = { 0x12, 0x34, 0x56, 0x78 };
	uint32_t* p = reinterpret_cast<uint32_t*>(network_buffer);
	uint32_t n = *p; // TODO
	printf("32 bit number=0x%x\n", n);
}

int main(int argc, char **argv) {


	int file;
	uint16_t result1;
	uint16_t result2;


	if(argc == 3)
		printf("Reading: %s, %s\n",argv[1], argv[2]);
	else
		printf("Check, Arguments Are Not Correct!\n");
	
	
	printf("fopen test\n");

	result1 = GetBinFileData(argv[1]);
	
	printf("%s binary data: %x\n", argv[1], result1);

	result2 = GetBinFileData(argv[2]);
	
	printf("%s binary data: %x\n", argv[2], result2);
	
	printf("%x + %x = %x\n", result1, result2, result1+result2);

		
	return 0;

}

uint16_t GetBinFileData(char *fileName)
{
	uint32_t file=0;
	uint16_t result=0;
	uint16_t data=0;

	file = open(fileName, O_RDONLY);
	printf("file open\n");
		
	while(read(file,&data,sizeof(uint16_t)))
	{
		//printf("%x\n", data1);
	} 
	
	result = my_ntohs(data);
	
	printf("%x\n", result);
		
	close(file);

	return result;
}
