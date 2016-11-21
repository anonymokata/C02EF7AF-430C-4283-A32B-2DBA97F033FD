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
            Stack operandTokens;
            initStack(&operandTokens);
            const char operators[] = "^/*-+";
            for (int j = 0; j != expressionLength; j++) {
                char currentTokenString[2];
                sprintf(currentTokenString, "%c", originalExpression[j]);
                const char *operatorPtr = strstr(operators, currentTokenString);
                if (operatorPtr) {
                    char rightOperandToken[outBufferSz/2];
                    char leftOperandToken[outBufferSz/2];
                    popStack(&operandTokens, rightOperandToken);
                    popStack(&operandTokens, leftOperandToken);
                    // write to buffer and then put back into operand stack
                    char operandTokenString[outBufferSz];  // 50*2 + 2() + 1^ + 1\0
                    sprintf(operandTokenString, "(%s%s%s)", leftOperandToken, currentTokenString, rightOperandToken);
                    pushStack(&operandTokens, operandTokenString);
                }
                else {
                    pushStack(&operandTokens, currentTokenString);
                }
            }	//
            // copy operandTokens into outputExpression buffer. Fill buffer in reverse order
            while (!isEmptyStack(&operandTokens)) {
                char operandTokenString[outBufferSz];
                popStack(&operandTokens, operandTokenString);
                int currentLength = strlen(outputExpression);
                int spacesToMove = strlen(operandTokenString);
                if (currentLength > 0) {
                    memmove(outputExpression + spacesToMove, outputExpression, currentLength);
                }
                memcpy(outputExpression, operandTokenString, spacesToMove);
            }
            //
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
