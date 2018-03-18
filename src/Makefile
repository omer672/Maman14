####### Compiler, tools and options

CC            = gcc
CFLAGS        = -ansi -Wall -pedantic

####### Compile

assembler: firstIteration.o \
		main.o \
		helper.o \
		symbolTable.o \
		LinkedList.o \
		secondIteration.o \
		fileCreator.o \
		Parsing.o \
		commandsToBinary.o \
		errorPrinter.o
	$(CC) -g $(CFLAGS) firstIteration.o \
		main.o \
		helper.o \
		symbolTable.o \
		LinkedList.o \
		secondIteration.o \
		fileCreator.o \
		Parsing.o \
		commandsToBinary.o \
		errorPrinter.o -o assembler

main.o: main.c main.h
	$(CC) -c $(CFLAGS)  -o main.o main.c

firstIteration.o: firstIteration.c firstIteration.h \
		main.h \
		helper.h \
		symbolTable.h \
		LinkedList.h \
		Parsing.h \
		commandsToBinary.h \
		secondIteration.h \
		fileCreator.h \
		errorPrinter.h
	$(CC) -c $(CFLAGS)  -o firstIteration.o firstIteration.c

secondIteration.o: secondIteration.c secondIteration.h \
		main.h \
		helper.h \
		symbolTable.h \
		LinkedList.h \
		Parsing.h \
		commandsToBinary.h \
		fileCreator.h \
		errorPrinter.h
	$(CC) -c $(CFLAGS)  -o secondIteration.o secondIteration.c

symbolTable.o: symbolTable.c symbolTable.h \
		main.h \
		LinkedList.h \
		helper.h \
		Parsing.h \
		commandsToBinary.h
	$(CC) -c $(CFLAGS)  -o symbolTable.o symbolTable.c

helper.o: helper.c helper.h \
		main.h \
		symbolTable.h \
		LinkedList.h \
		Parsing.h \
		commandsToBinary.h
	$(CC) -c $(CFLAGS)  -o helper.o helper.c

LinkedList.o: LinkedList.c LinkedList.h \
		main.h
	$(CC) -c $(CFLAGS)  -o LinkedList.o LinkedList.c

Parsing.o: Parsing.c Parsing.h
	$(CC) -c $(CFLAGS)  -o Parsing.o Parsing.c

fileCreator.o: fileCreator.c fileCreator.h \
		symbolTable.h \
		main.h \
		LinkedList.h \
		helper.h \
		Parsing.h \
		commandsToBinary.h
	$(CC) -c $(CFLAGS)  -o fileCreator.o fileCreator.c

commandsToBinary.o: commandsToBinary.c commandsToBinary.h \
		main.h \
		symbolTable.h \
		LinkedList.h \
		helper.h \
		Parsing.h
	$(CC) -c $(CFLAGS)  -o commandsToBinary.o commandsToBinary.c

errorPrinter.o: errorPrinter.c errorPrinter.h \
		main.h
	$(CC) -c $(CFLAGS)  -o errorPrinter.o errorPrinter.c
