#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa9.h"

static Stack* stackpointer;

Stack* stack_init() {
    Stack *pointer = malloc(sizeof(Stack));
    pointer->nextIndex = 0;
    pointer->numElems = 0;
    pointer->numSuccess = 0;
    return pointer;
}

void push(char * str) {
    int pos = stackpointer->nextIndex;
    if (pos > 49) {
        printf(STR_POP_FAILURE);
        return;
    }
    stackpointer->array[pos] = (void*) str;
    stackpointer->nextIndex += 1;
    stackpointer->numElems += 1;
    stackpointer->numSuccess += 1;
    printf(STR_PUSH_SUCCESS, "Success");
}

char* pop() {
    int pos = stackpointer->nextIndex - 1;
    if (pos < 0) {
        printf(STR_POP_FAILURE);
        return NULL;
    }
    char* pulledString = (char*) stackpointer->array[pos];
    stackpointer->nextIndex -= 1;
    stackpointer->numElems -= 1;
    stackpointer->numSuccess += 1;
    printf(STR_POP_SUCCESS, "Success");
    printf(pulledString);
    free(pulledString);
    return pulledString;
}

char* peek() {
    int pos = stackpointer->nextIndex - 1;
    //int *p = &pos;
    if (pos < 0) {
        printf(STR_PEEK_FAILURE);
        return NULL;
    }
    char* pulledString = (char*) stackpointer->array[pos];
    printf(STR_PEEK_SUCCESS, "Success");
    //free(p);
    return pulledString;
}

void stack_delete() {
    free(stackpointer);
}

void print() {

}

void check(char * str) {

}

int parse_input(FuncInfo * funcInfo, const char * func) {

    if (strcmp(func, "pop()\n") == 0) {
        funcInfo->func = 2;
        return 1;
    }
    if (strcmp(func, "peek()\n") == 0) {
        funcInfo->func = 3;
        return 1;
    }
    if (strcmp(func, "print()\n") == 0) {
        funcInfo->func = 4;
        return 1;
    }
    int length = strlen(func);
    if (((strchr(func, '(')) == NULL) || ((strchr(func, ')')) == NULL)) {
        printf(STR_ERR_SYNTAX);
        return -1;
    }

    //check for push
    if (length >= 10) {
        if (func[0] == 'p' && func[1] == 'u' && func[2] == 's' && func[3] == 'h'
                && func[4] == '(' && func[5] == '"' && func[length - 3] == '"'
                && func[length - 2] == ')') {
            int i = 6;
            char* word = malloc(length-9+1);
            char* wordptr = word;
            while (i < length - 3) {
                char c = func[i];
                if (isalpha(c)) {
                    *wordptr = c;
                    wordptr++;
                    i++;
                    continue;
                } else {
                    printf(STR_ERR_SYNTAX);
                    return -1;
                }
            }
            *wordptr = '\0';
            funcInfo->func = 1;
            funcInfo->word = word;
            //something to capture word?
            return 1;
        } else {
            printf(STR_ERR_SYNTAX);
            return -1;
        }
    }
    printf(STR_ERR_UNKNOWN);
    return -1;
}

//will not compile till you provide a declaration for stack

int main(int argc, char * argv[]) {

    setvbuf(stdout, NULL, _IONBF, 0);
    //will not compile till you provide a declaration for stack
    Stack* stack = stack_init();

    if (stack == NULL) {
        fprintf(stderr, STR_ERR_MEM);
        return EXIT_FAILURE;
    }

    stackpointer = stack;

    //to pass into parse_input
    FuncInfo funcInfo;

    printf(STR_WELCOME);
    printf(STR_PROMPT);

    //to store strings from stdin
    char readin[BUFSIZ];

    while (fgets(readin, BUFSIZ, stdin) != NULL) {

        if (feof(stdin)) {
            break;
        }

        //parse input
        int r = parse_input(&funcInfo, readin);

        //input could not be parsed, continue to next iteation
        if (r == -1) {
            printf("\n");
            printf(STR_PROMPT);
            continue;
        }

        //call appropriate function
        switch (funcInfo.func) {
            case 1:
                push(funcInfo.word);
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                print();
                break;
            case 5:
                check(funcInfo.word);
                break;
            default:
                printf(STR_ERR_UNKNOWN);
        }
        printf("\n");

        printf(STR_PROMPT);
    }

    //destruct stack
    stack_delete();

    printf("quit\n");

    return EXIT_SUCCESS;

    return 0;
}
