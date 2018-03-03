#include "main.h"
#include "firstIteration.c"
/*Global variables*/
char* instructions[] = {"mov", "cmp", "add", "sub", "lea","not","clr","inc","dec", "jmp", "bne", "red", "prn", "jsr","rts", "stop"};
char* dataTypes[] = {"data","string","struct"};
char* registers[] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

int main(int argc, char *argv[])
{
    int i;
    for(i = 1; i < argc; i++)
    {
        runProg(argv[i]);
    }
    return 0;
}
/*runProg - Consider Copying it outside main*/
void runProg(char* fileName)
{
    FILE* file;
    if(file = fopen(fileName,"r"))
    {
        iterate(file);
    }
    else
        printf("File cannot be open, moving on");
}

