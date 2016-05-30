#ifndef PA9_H
#define PA9_H

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 50

#define STACK_BOTTOM 1

#define STACK_PRINT_STR "------STACK INFORMATION------\n"\
                        "Number of elements in the stack:\t%d\n"\
                        "Index of the top of the stack:\t\t%d\n"\
                        "Number of operations since initialized:\t%d\n"\
                        "-----------------------------\n"
#define STR_PRINT_WORDS "\nWord(s) stored in the stack are:"
#define STR_PRINT_NO_WORDS "\nThere is no word in the stack!\n"

#define STR_ERR_SYNTAX "\nSyntax error\n"
#define STR_ERR_MEM "\nMemory is not available:(\n"
#define STR_ERR_UNKNOWN "\nUnknown operation\n"

#define STR_PUSH_SUCCESS "\nSuccessfully pushed %s\n"
#define STR_PUSH_FAILURE "\nFailed to push to stack\n"

#define STR_POP_SUCCESS "\n%s\n"
#define STR_POP_FAILURE "\nFailed to pop from stack\n"

#define STR_PEEK_SUCCESS "\n%s\n"
#define STR_PEEK_FAILURE "\nFailed to peek stack\n"

#define STR_CHECK_SUCCESS "\n%s is valid\n"
#define STR_CHECK_FAILURE "\n%s is not valid\n"

#define STR_WELCOME "\tPA9! Use push(string), pop(), peek(), print(), "\
                    "or check(string)\n"\
                    "\tto manipulate stack. Ctrl+D to exit\n"
#define STR_PROMPT "> "

typedef char* string;

/*
 * Struct to store information of a function
 */
typedef struct {
	int func;
	char * word;
} FuncInfo;

typedef struct {
	int numElems;
	int nextIndex;
	int numSuccess;
	void** array[STACK_SIZE];
} Stack;

/*
 * Initializes a stack
 * Return:
 *   Normal: An empty stack
 *   When there is no memory available to allocate: null pointer
 */
Stack * stack_init();

/*
 * Pushes to a stack
 * Param:
 *   item - the stuff to be pushed
 */
void push(char * str);

/*
 * Pops from a stack
 */
char * pop();

/*
 * Returns top element of stack
 */
char * peek();

/*
 * Destructs a stack
 */
void stack_delete();

/*
 * Prints out the information of a stack
 */
void print();

/*
 * Checks parenthsis for validity
 */
void check(char * strt);

/*
 * Parse a function (as string) to a frame
 * Param:
 *   func - the function string
 * Returns:
 *	 -1 - invalid parse
 *	  1 - valid parse
 */
int parse_input(FuncInfo * funcInfo, const char * func);


#endif /* PA9_H */
