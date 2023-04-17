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

uint32_t my_ntohs(uint32_t n){

	uint32_t a=0;
	uint32_t b=0;
	uint32_t c=0;
	uint32_t d=0;
	uint32_t result;


	a = n & 0xff000000;
	a = a>>24;
	a = a & 0x000000ff;
	//printf("a:%x\n", a);

	b = n & 0x00ff0000;
	b = b>>8;
	b = b & 0x0000ff00;
	//printf("b:%x\n", b);
	
	c = n & 0x0000ff00;
	c = c<<8;
	c = c & 0x00ff0000;
	//printf("c:%x\n", c);

	d = n & 0x000000ff;
	d = d<<24;
	d = d & 0xff000000;
	//printf("d:%x\n", d);	
	
	result = a|b|c|d;


	return result;
}

int main(int argc, char **argv) {


	int file;
	uint32_t result1;
	uint32_t result2;


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

uint32_t GetBinFileData(char *fileName)
{
	uint32_t file=0;
	uint32_t result=0;
	uint32_t data=0;

	file = open(fileName, O_RDONLY);

		
	while(read(file,&data,sizeof(uint32_t)))
	{
		printf("%x\n", data);
	} 
	
	result = my_ntohs(data);
	
		
	close(file);

	return result;
}
