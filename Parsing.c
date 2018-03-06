
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*string to binary - > binary -> strange base*/
/*check if negative -> use two complements*/
/*DOESNOT WORK YET*/

int stringToBinary(char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    size_t i;
    int j;
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(i = 0; i < len; ++i) {
        char ch = s[i];
        for(j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}


/***** Need to be done - how to combine these functions in*****/
/* Two Complement Method in order to avoid negative numbers
 * The func will get number(binary)
 * The func will return integer presented as binary number
 *         in case of failure return -1 and print an error message*/
int TwosComplements(int number)
{
    int numArray[10];						/*initialize array of integers(will only has 0 and 1 values)*/
    int number_copy;
    int temp;
    int base;
    int sumOne;
    int i;
    int ArrI;							/*size of binary number*/
    int twoCompBin;			        	/*two complemented binary number*/
    char intArr[10];					/*array of chars to switch into two's complement binary*/

    base = 2;
    sumOne = 0;
    number_copy = ~number;					/*replace all num from 1 to 0 and 0 to 1*/
    number_copy = number_copy+1;			/*will add 1 to number*/
    ArrI = 9;
    /*initialize array*/
    for(i=0;i<10;i++)
    {
        numArray[i]=0;
    }
    /*Convert positive integer to binary and save it in array of integers by dividing on base 2 */
    while(number_copy != 0)
    {
        temp = (number_copy%base);
        number_copy = (number_copy/base);
        numArray[ArrI] = temp;
        ArrI--;
    }

/* Switch all ones to zeros and all zeros to ones in binary number presented by array of integers(0 or 1)
 * But start switching only after first non zero bit(1)
 * Example 1010 --> 0110*/
    for(ArrI = 9;ArrI >= 0;ArrI--)
    {
        /*If number equal to 1 and not first*/
        if(numArray[ArrI] == 1 && sumOne == 1)
        {
            numArray[ArrI] = 0;
        }
            /*If number equal to 0 and not first*/
        else if(numArray[ArrI] == 0 && sumOne == 1)
        {
            numArray[ArrI] = 1;
        }
            /*If number equal to 1 and first one*/
        else if(numArray[ArrI] == 1 && sumOne == 0)
        {
            sumOne++;
        }
    }

    /*parse array of integers into array of characters*/
    for(ArrI = 0;ArrI < 10;ArrI++)
    {
        if(numArray[ArrI] == 0)
        {
            intArr[ArrI] = '0';
        }
        else
        {
            intArr[ArrI] = '1';
        }
    }

    /*parse array of chars into int*/
    twoCompBin = atoi(intArr);

    if(!twoCompBin)
    {
        fprintf(stderr,"Array had not been converted to integer");
        return -1;
    }
    else
    {
        return twoCompBin;
    }
}

/*the function takes binary number(integer) to base 32 number in letters(!,@,#...,v)
 * the func will get integer binary number
 * the func will return array of characters by strange base 32*/
char* ConvertBinTo32(int number)
{
    /*Define auxiliary integers*/
    int number_copy;
    int base = 32;
    int count=0;
    int i=0;
    int j;

    int *numArray; /*define pointer to array of integers*/
    char *reqBase; /*pointer to the requested base(32 strange)*/
    int temp;

    number_copy=number;
    do
    {
        temp=number_copy % base;
        number_copy=number_copy / base;
        count++;
    }

    while(number_copy!=0);
    {
        /* Allocate memory to array*/
        numArray = malloc(count * sizeof(int));
    }

    if(numArray == NULL)
    {
        fprintf(stderr,"Failed to allocate memory for a new integer array");
        return 0;
    }

    /*Convert binary number to base 32(as defined up)*/
    while(i<count)
    {
        temp = (number%base);
        number = (number/base);
        numArray[i]=temp;
        i++;

    }

    if((reqBase= malloc(count * sizeof(char)))==NULL)
    {
        fprintf(stderr,"Failed to allocate memory for a new integer array");
        return 0;
    }

    j=0;
    i=count-1;
    /*Go over numArray array and replace 32 base numbers with letters
     * if number is 0 - replace with ! letter
     * if number is 1 - replace with @ letter
     * if number is 2 - replace with # letter and so further until 32 */
    while(j<count)
    {
        switch(numArray[i])
        {
            case 0:
                reqBase[j]='!';
                j++;
                i--;
                break;
            case 1:
                reqBase[j]='@';
                j++;
                i--;
                break;
            case 2:
                reqBase[j]='#';
                j++;
                i--;
                break;
            case 3:
                reqBase[j]='$';
                j++;
                i--;
                break;
            case 4:
                reqBase[j]='%';
                j++;
                i--;
                break;
            case 5:
                reqBase[j]='^';
                j++;
                i--;
                break;
            case 6:
                reqBase[j]='&';
                j++;
                i--;
                break;
            case 7:
                reqBase[j]='*';
                j++;
                i--;
                break;
            case 8:
                reqBase[j]='<';
                j++;
                i--;
                break;
            case 9:
                reqBase[j]='>';
                j++;
                i--;
                break;
            case 10:
                reqBase[j]='a';
                j++;
                i--;
                break;
            case 11:
                reqBase[j]='b';
                j++;
                i--;
                break;
            case 12:
                reqBase[j]='c';
                j++;
                i--;
                break;
            case 13:
                reqBase[j]='d';
                j++;
                i--;
                break;
            case 14:
                reqBase[j]='e';
                j++;
                i--;
                break;
            case 15:
                reqBase[j]='f';
                j++;
                i--;
                break;
            case 16:
                reqBase[j]='g';
                j++;
                i--;
                break;
            case 17:
                reqBase[j]='h';
                j++;
                i--;
                break;
            case 18:
                reqBase[j]='i';
                j++;
                i--;
                break;
            case 19:
                reqBase[j]='j';
                j++;
                i--;
                break;
            case 20:
                reqBase[j]='k';
                j++;
                i--;
                break;
            case 21:
                reqBase[j]='l';
                j++;
                i--;
                break;
            case 22:
                reqBase[j]='m';
                j++;
                i--;
                break;
            case 23:
                reqBase[j]='n';
                j++;
                i--;
                break;
            case 24:
                reqBase[j]='o';
                j++;
                i--;
                break;
            case 25:
                reqBase[j]='p';
                j++;
                i--;
                break;
            case 26:
                reqBase[j]='q';
                j++;
                i--;
                break;
            case 27:
                reqBase[j]='r';
                j++;
                i--;
                break;
            case 28:
                reqBase[j]='s';
                j++;
                i--;
                break;
            case 29:
                reqBase[j]='t';
                j++;
                i--;
                break;
            case 30:
                reqBase[j]='u';
                j++;
                i--;
                break;
            case 31:
                reqBase[j]='v';
                j++;
                i--;
                break;
            default:
                fprintf(stderr,"Wrong number\n");
                break;
        }
    }

    return reqBase;
}
