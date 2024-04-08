#include <inttypes.h>
#include <stdio.h>
int main()
{
int num = 0xFFBB7688; //32 bits or 4 bytes
uint8_t *ptr = (uint8_t*)&num; //8 bit pointer or 1 byte
printf("num: %X\n", num);
printf("first byte: %X\n", *ptr); // 0x88 because it is the LEAST significant

ptr++; //move the ptr along by 1 byte (move past 0x88)
uint16_t *two_bytes = (uint16_t*)ptr;
printf("one byte at ptr after add: %X\n", *ptr);
printf("two bytes at ptr after add: %X\n", *two_bytes);
//-----------------------------------------------------
int numbers[2];
numbers[0] = num;
numbers[1] = 0x11223344;
// numbers = { 0xFFBB7688, 0x11223344 }
uint64_t* big_ptr = (uint64_t*) numbers;
printf("bytes 0x%lX\n", *big_ptr);
return 0;
}
