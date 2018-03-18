#include "main.h"
#include "helper.h"
#include "symbolTable.h"
#include "fileCreator.h"
#include "commandsToBinary.h"
#include "errorPrinter.h"
/*Second iterate runs over the file after symbols table created on first iterate
 * will create Output files by definition.
 * handles Errors through the run*/
void secondIterate(FILE* file, char *fileName);
