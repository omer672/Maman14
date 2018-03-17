#include "secondIteration.h"

void secondIterate(FILE* file, char* fileName)
{
    int numberOfLines = 0;          /*Auxiliary integer - counts lines*/
    char* symbolPos;               /*Auxiliary pointer - to position of symbol*/
    char command[LINE_LENGTH];
    char restOfLine[LINE_LENGTH];
    char* delimit = " \t";          /*Auxiliary flag for tabs*/
    char lineBuffer[LINE_LENGTH];
    char linebufferCopy[LINE_LENGTH]; /*Copy of the line buffer because strtok destroys the string*/
    StatusCode code;

    IC = 0;
    rewind(file); /* read file again */
    while(fgets(lineBuffer,LINE_LENGTH,file) != NULL)
    {
        numberOfLines++;
        if(!(isWhitespace(lineBuffer) || (unsigned char)(*lineBuffer) == ';')) /* Checking for empty line or comment line */
        {
            strcpy(linebufferCopy,lineBuffer);
            strcpy(command, strtok(lineBuffer, delimit));
            if ((symbolPos = strchr(command, ':')) != NULL)	/*Checks if there is a symbol */
                strcpy(command, strtok(NULL, delimit));	/*Should contain instruction/data command */
            strcpy(restOfLine, strtok(NULL, ""));	/*Gets the rest of the line */
            if(!(isDataType(command) || isExtern(command))) /*Data type or extern*/
            {
                if(isEntry(command)) /*Entry*/
                {
                    if((code = markEntry(restOfLine)) < 0)
                    {
                        printError(code,numberOfLines,fileName);
                        errorsFound = 1;
                    }
                }
                else /*Instruction*/
                {
                    if((code = insertInstruction(command,restOfLine, 1)) < 0)
                    {
                        printError(code,numberOfLines,fileName);
                        errorsFound = 1;
                    }
                }
            }
        }
    }
    if(!errorsFound)
    {
        createOutputFiles(fileName);
    }
}
