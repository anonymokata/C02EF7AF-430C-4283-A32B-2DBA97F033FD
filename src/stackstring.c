// implement typical stack operations --> push pop isEmpty
#include <memory.h>
#include "stackstring.h"

void initStack(Stack *stk) {
    stk->size = 0;
}

int topStack(Stack *stk, char *item)
{
    int ret = 0;

    if (stk->size == 0) {
        ret = 0x01;
    }
    else {
        char *entry = stk->items[stk->size - 1];
        memcpy(item, entry, strlen(entry) + 1);
    }

    return ret;
}

int popStack(Stack *stk, char *item)
{
    int ret = 0;

    if (stk->size == 0) {
        ret = 0x01;
    }
    else {
        char *entry = stk->items[stk->size - 1];
        memcpy(item, entry, strlen(entry) + 1);
        free(entry);
        stk->size--;
    }

    return ret;
}

int pushStack(Stack *stk, const char *item)
{
    int ret = 0;

    if (stk->size < STACKSTRINGCAPACITY) {
        if (strlen(item) > 0) {
            char *entry=(char*)malloc(strlen(item) + 1);
            memcpy(entry, item, strlen(item) + 1);
            stk->items[stk->size++] = entry;
        }
        else {
            ret = 0x01;
        }

    }
    else {
        ret = 0x01;
    }

    return ret;
}

bool isEmptyStack(Stack *stk) {
    return (stk->size == 0);
}
