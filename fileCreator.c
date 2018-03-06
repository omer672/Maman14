#include "fileCreator.h"

void createObjFile(char *fileName)
{
    int i;
    int IC,DC;
    int dataArray[MAX_FILE_LENGTH];
    int instructionsArray[MAX_FILE_LENGTH];
    char lineBuffer[5];
    char* code, address;
    char finalFileName[strlen(fileName)+3];

    FILE* file;
    strcat(finalFileName,fileName); /* creates the file */
    strcat(finalFileName,".ob");
    if(file = fopen(finalFileName ,"w"))
    {
        for(i = 0; i< IC; i++)
        {
            code = ConvertBinTo32(instructionsArray[i]);
            address = ConvertBinTo32(START_ADDRESS+i);
            sprintf(lineBuffer,"%s\t%s",address,code);
            fputs(lineBuffer,file);
        }
        for(i = 0; i< DC; i++)
        {
            code = ConvertBinTo32(dataArray[i]);
            address = ConvertBinTo32(START_ADDRESS+i+IC);
            sprintf(lineBuffer,"%s\t%s",address,code);
            fputs(lineBuffer,file);
        }
        fclose(file);
    }
    else
    {
        /* ERROR */
    }
}

void createExternFile(char *fileName)
{
    int i = 0;
    char lineBuffer[LINE_LENGTH];
    char* address,name;
    char finalFileName[strlen(fileName)+4];
    Symbol* head;
    Symbol* curr;
    FILE* file;
    strcat(finalFileName,fileName); /* creates the file */
    strcat(finalFileName,".ext");
    if(file = fopen(finalFileName ,"w"))
    {
        head = getHead();
        curr = head;
        while(curr)
        {
            if(curr->type == external)
            {
                name = curr->name;
                address = ConvertBinTo32(curr->value);
                sprintf(lineBuffer,"%s\t%s",name,address);
                fputs(lineBuffer,file);
            }
            curr = curr->next;
        }
        fclose(file);
    }
    else
    {
        /* ERROR */
    }
}

void createEntryFile(char *fileName)
{

}

void createOutputFiles(char *fileName)
{
    createObjFile(fileName);
    createExternFile(fileName);
    createEntryFile(fileName);
}


