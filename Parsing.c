#include "Parsing.h"

char get32FromDigit(int digit)
{
    char returnVal;
    switch(digit)
    {
    case 0:
        returnVal='!';
        break;
    case 1:
        returnVal='@';
        break;
    case 2:
        returnVal='#';
        break;
    case 3:
        returnVal='$';
        break;
    case 4:
        returnVal='%';
        break;
    case 5:
        returnVal='^';
        break;
    case 6:
        returnVal='&';
        break;
    case 7:
        returnVal='*';
        break;
    case 8:
        returnVal='<';
        break;
    case 9:
        returnVal='>';
        break;
    case 10:
        returnVal='a';
        break;
    case 11:
        returnVal='b';
        break;
    case 12:
        returnVal='c';
        break;
    case 13:
        returnVal='d';
        break;
    case 14:
        returnVal='e';
        break;
    case 15:
        returnVal='f';
        break;
    case 16:
        returnVal='g';
        break;
    case 17:
        returnVal='h';
        break;
    case 18:
        returnVal='i';
        break;
    case 19:
        returnVal='j';
        break;
    case 20:
        returnVal='k';
        break;
    case 21:
        returnVal='l';
        break;
    case 22:
        returnVal='m';
        break;
    case 23:
        returnVal='n';
        break;
    case 24:
        returnVal='o';
        break;
    case 25:
        returnVal='p';
        break;
    case 26:
        returnVal='q';
        break;
    case 27:
        returnVal='r';
        break;
    case 28:
        returnVal='s';
        break;
    case 29:
        returnVal='t';
        break;
    case 30:
        returnVal='u';
        break;
    case 31:
        returnVal='v';
        break;
    default:
        break;
    }
    return returnVal;
}

/* Two Complement Method in order to avoid negative numbers
 * The func will get number(binary)
 * The func will return integer presented as binary number
 *         in case of failure return -1 and print an error message*/
int twosComplements(int number, int numberOfBits)
{
    int mask = ((1<<numberOfBits) - 1); /* maximum allowed integer */
    int isNegetive = number < 0;
    int base = 1<<numberOfBits;
    int cutNum = abs(number) & mask; /* cutting excess bits (more than 10) */
    return isNegetive ? (base - cutNum) : cutNum; /* if the number was negetive return the twos complement, otherwise return it back */
}

/*the function takes binary number(integer) to base 32 number in letters(!,@,#...,v)
 * the func will get integer binary number
 * the func will return array of characters by strange base 32*/
void ConvertBinTo32(int number, char* newNumber)
{
    char resultString[3];
    int mask = (1<<5) - 1; /* 31 or 11111 in binary */
    int firstDigit = number & mask; /* get first 5 digits */
    int secondDigit = (number & (mask << 5)) >> 5; /* get 5 last digits by masking and pushing back */

    resultString[0] = get32FromDigit(secondDigit); /* opposite order because left-to-right ordering */
    resultString[1] = get32FromDigit(firstDigit);
    resultString[2] = '\0';
    strcpy(newNumber,resultString);
}
