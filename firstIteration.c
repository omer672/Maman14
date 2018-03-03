#include "helper.h"
#include "symbolTable.h"
#define MAX_PARAMS 256
/*another comment check*/
void iterate(FILE* file)
{
    IC = 0;
    DC = 0;
    int j,i,numberOfParams = 0;
    int foundSymbol = 0;
    int numberOfLines = 0;
    int lineLength = LINE_LENGTH;
    char* symbolPos;
    char* lineParams[MAX_PARAMS];
    char* delimit = " \t";
    char lineBuffer[LINE_LENGTH];
    char value[MAX_DIGITS];
    while(getline(&lineBuffer,&lineLength,file) != EOF)
    {
        /* Get all parameters on a line */
        lineParams[numberOfParams] = strtok(lineBuffer,delimit);
        while(lineParams[numberOfParams])
        { //TODO: fix me, maybe use scanf
          i++;
          lineParams[numberOfParams]=strtok(NULL,delimit);
        }
        /* Iterate them */
        if(symbolPos = strchr(lineParams[0],':'))
        {
            foundSymbol = 1;
        }
        for(i=foundSymbol;i<numberOfParams;i++)
        {
            if(isDataType(lineParams[i]))
            {
                if(foundSymbol)
                {
                    sprintf(value,"%d",DC);
                    setSymbol(strtok(lineParams[0],":"),value,Types.relocatable);
                }
                insertData(lineParams[i],lineParams,i+1,numberOfParams);
                break;
            }
            else
            {
                if(isExtern(lineParams[i]) || isEntry(lineParams[i]))
                {
                    if(isExtern(lineParams[i]))
                        for(j=i+1;j<numberOfParams;j++)
                        {
                            setSymbol(lineParams[j],'0',Types.external);
                        }
                    break;
                }
                else
                {
                    if(foundSymbol)
                    {
                        sprintf(value,"%d",IC);
                        setSymbol(strtok(lineParams[0],":"),value,Types.relocatable);
                    }
                    if(isInstuction(lineParams[i]))
                        //build it
                        ;
                    //calc L
                    break;

                }
            }
        }
        numberOfLines++;
    }
    if(numberOfLines == 0)
        printf("Empty file, moving on");
}
