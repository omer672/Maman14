#include "fileCreator.h"
/*The function creates .ob file*/

void createObjFile(char *fileName)
{
    int i;
    char lineBuffer[8];
    char code[3];
    char address[3];
    char finalFileName[MAX_FILE_LENGTH+3];
    FILE* file;
    strcpy(finalFileName,fileName); /* creates the file */
    strcat(finalFileName,".ob");
    if((file = fopen(finalFileName ,"w")) != NULL)
    {
        for(i = 0; i< IC; i++)
        {
            ConvertBinTo32(instructionsArray[i],code);
            ConvertBinTo32(START_ADDRESS+i,address);
            sprintf(lineBuffer,"%s\t%s\n",address,code);
            fputs(lineBuffer,file);
        }
        for(i = 0; i< DC; i++)
        {
            ConvertBinTo32(dataArray[i],code);
            ConvertBinTo32(START_ADDRESS+i+IC,address);
            sprintf(lineBuffer,"%s\t%s\n",address,code);
            fputs(lineBuffer,file);
        }
        fclose(file);
    }
    else
    {
        fprintf(stderr,"File cannot be open, moving on. %s",finalFileName);
    }
}
/*The function creates .ext file
 * Input: extern file name
 * Output: creates the file at the project directory*/
void createExternFile(char *fileName)
{
    char lineBuffer[LINE_LENGTH];
    char* name;
    char address[3];
    char finalFileName[MAX_FILE_LENGTH+4];
    Symbol* head;
    Symbol* curr;
    FILE* file;
    strcpy(finalFileName,fileName); /* creates the file */
    strcat(finalFileName,".ext");
    if((file = fopen(finalFileName ,"w")) != NULL)
    {
        head = getHead();
        curr = head;
        while(curr)
        {
            if(curr->type == external)
            {
                name = curr->name;
                ConvertBinTo32(curr->value,address);
                sprintf(lineBuffer,"%s\t%s\n",name,address);
                fputs(lineBuffer,file);
            }
            curr = curr->next;
        }
        fclose(file);
    }
    else
    {
        fprintf(stderr,"File cannot be open, moving on. %s",finalFileName);
    }
}
/*The function creates .ent file
 * Input: entry file name
 * Output: creates the file at the project directory*/
void createEntryFile(char *fileName)
{
    char lineBuffer[LINE_LENGTH];
    char* name;
    char address[3];
    char finalFileName[MAX_FILE_LENGTH+4];
    Symbol* head;
    Symbol* curr;
    FILE* file;
    strcpy(finalFileName,fileName); /* creates the file */
    strcat(finalFileName,".ent");
    if((file = fopen(finalFileName ,"w")) != NULL)
    {
        head = getHead();
        curr = head;
        while(curr)
        {
            if(curr->isEntry)
            {
                name = curr->name;
                ConvertBinTo32(curr->value,address);
                sprintf(lineBuffer,"%s\t%s\n",name,address);
                fputs(lineBuffer,file);
            }
            curr = curr->next;
        }
        fclose(file);
    }
    else
    {
        fprintf(stderr,"File cannot be open, moving on. %s",finalFileName);
    }
}
/*The function creates all requested files to create
 * Input: file name
 * Output: .ob , .ext, .ent files*/
void createOutputFiles(char *fileName)
{
    createObjFile(fileName);
    createExternFile(fileName);
    createEntryFile(fileName);
}


