#ifndef STACKSTRING_H
#define STACKSTRINGCAPACITY 256 // up to this many number of strings in the stack

#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus

extern "C" {

#endif

        struct StackOfStrings {
                char* items[STACKSTRINGCAPACITY];
                size_t size;
        };

        typedef struct StackOfStrings Stack;

        // implement typical stack operations --> push pop isEmpty and top

        extern void initStack(Stack *stk);

        extern int topStack(Stack *stk, char *item);

        extern int popStack(Stack *stk, char *item);

        extern int pushStack(Stack *stk, const char *item);

        extern bool isEmptyStack(Stack *stk);


#ifdef __cplusplus

}

#endif

#endif // STACKSTRING_H
