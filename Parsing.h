#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_NUM 1<<10
#define MASK_10_BITS ((1<<9) - 1) /* 511, maximum allowed integer */

/* Two Complement Method in order to avoid negative numbers
 * The func will get number(binary)
 * The func will return integer presented as binary number
 *         in case of failure return -1 and print an error message*/
int twosComplements(int number);

/*the function takes binary number(integer) to base 32 number in letters(!,@,#...,v)
 * the func will get integer binary number
 * the func will return array of characters by strange base 32*/
void ConvertBinTo32(int number, char* newNumber);

