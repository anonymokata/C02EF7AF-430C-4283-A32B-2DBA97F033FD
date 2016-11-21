#include <stdio.h>
#include <memory.h>
#include "infixrpnconv.h"
#include "stackstring.h"

int validateInput(const char *originalExpression, const char *validInputChars);

int infixToRPN(const char *originalExpression, char *outputExpression, size_t outBufferSz) {
    int ret = 0;
    memset(outputExpression, 0, outBufferSz);
    int expressionLength = strlen(originalExpression);
    if (outBufferSz >= (expressionLength + 1)) {
        const char validInputChars[] = "qwertyuioplkjhgfdsazxcvbnm^/*-+()";
        ret = validateInput(originalExpression, validInputChars);
        if (ret == 0) {

        }
    }
    else
        ret = 0x01<<7;
    return ret;
}

int rpnToInfix(const char *originalExpression, char *outputExpression, size_t outBufferSz) {
    int ret = 0;
    memset(outputExpression, 0, outBufferSz);
    int expressionLength = strlen(originalExpression);
    if (outBufferSz > (expressionLength + 1)) {
        const char validInputChars[] = "qwertyuioplkjhgfdsazxcvbnm^/*-+";
        ret = validateInput(originalExpression, validInputChars);
        if (ret == 0) {

        }
    }
    else
        ret = 0x01<<7;
    return ret;
}

int validateInput(const char *originalExpression, const char *validInputChars) {
    int ret = 0;
    int expressionLength = strlen(originalExpression);
    for (int j = 0; j != expressionLength; j++) {
        char currentTokenString[2];
        sprintf(currentTokenString, "%c", originalExpression[j]);
        if (!strstr(validInputChars, currentTokenString)) {
            ret = 0x01<<6;
            break;
        }
    }
    return ret;
}
