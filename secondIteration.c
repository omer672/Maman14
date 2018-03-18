#include "secondIteration.h"

/*Second iterate runs over the file after symbols table created on first iterate
 * will create Output files by definition.
 * handles Errors through the run*/
void secondIterate(FILE* file, char* fileName)
{
    int numberOfLines = 0;          /*Auxiliary integer - counts lines*/
    char* symbolPos;               /*Auxiliary pointer - to position of symbol*/
    char command[LINE_LENGTH];
    char restOfLine[LINE_LENGTH];
    char* delimit = " \t\n";          /*Auxiliary flag for tabs*/
    char* token;
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
            token = strtok(lineBuffer, delimit);
            strcpy(command,token);
            if ((symbolPos = strchr(command, ':')) != NULL)	/*Checks if there is a symbol */
            {
                token =  strtok(NULL, delimit);
                if(token == NULL)
                {
                    errorsFound = 1;
                    printError(unrecognized_command,numberOfLines,fileName);
                    continue;
                }
                strcpy(command, token);	/*Should contain instruction/data command */
            }
            token =  strtok(NULL, "");
            if(token != NULL)
                strcpy(restOfLine,token);	/*Gets the rest of the line */
            else
                restOfLine[0] = '\0';
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
    if(!errorsFound)/*case second iterate went successful, will create output files*/
    {
        createOutputFiles(fileName);
    }
}
