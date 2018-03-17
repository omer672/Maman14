#include "fileCreator.h"

void createObjFile(char *fileName)
{
    int i;
    int instructionsArray[MAX_FILE_LENGTH];
    char lineBuffer[8];
    char code[2];
    char address[2];
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

void createExternFile(char *fileName)
{
    char lineBuffer[LINE_LENGTH];
    char* name;
    char address[2];
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

void createEntryFile(char *fileName)
{
    char lineBuffer[LINE_LENGTH];
    char* name;
    char address[2];
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

void createOutputFiles(char *fileName)
{
    createObjFile(fileName);
    createExternFile(fileName);
    createEntryFile(fileName);
}


