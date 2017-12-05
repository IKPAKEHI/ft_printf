#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


int main()
{
	printf("m: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n", 
		BYTE_TO_BINARY(-42>>24), BYTE_TO_BINARY(-42>>16), BYTE_TO_BINARY(-42>>8), BYTE_TO_BINARY(-42));


	
	printf("m: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"	"BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
		 BYTE_TO_BINARY(-42l>>56), BYTE_TO_BINARY(-42l>>48), BYTE_TO_BINARY(-42l>>40), BYTE_TO_BINARY(-42l>>32),
		 BYTE_TO_BINARY(-42l>>24), BYTE_TO_BINARY(-42l>>16), BYTE_TO_BINARY(-42l>>8), BYTE_TO_BINARY(-42l));
	return 0;
}