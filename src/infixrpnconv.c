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
            Stack operatorTokens;
            initStack(&operatorTokens);
            const char operators[] = "^/*-+";
            for (int j = 0; j != expressionLength; j++) {
                char currentTokenString[2];
                sprintf(currentTokenString, "%c", originalExpression[j]);
                //
                const char *operatorPtr = strstr(operators, currentTokenString);
                if (operatorPtr) {
                    char operatorStackTokenString[2];
                    if (!isEmptyStack(&operatorTokens)) {
                        int operatorCurrentTokenPos = (operatorPtr - operators);
                        topStack(&operatorTokens, operatorStackTokenString);
                        while ((!strstr(operatorStackTokenString, "(")) && (!isEmptyStack(&operatorTokens))) {
                            operatorPtr = strstr(operators, operatorStackTokenString);
                            int operatorStackTokenPos = (operatorPtr - operators);
                            if (operatorCurrentTokenPos < operatorStackTokenPos) { // determine operator precedence
                                break;
                            }
                            else {
                                popStack(&operatorTokens, operatorStackTokenString);
                                strcat(outputExpression, operatorStackTokenString);
                            }
                            topStack(&operatorTokens, operatorStackTokenString);
                        }

                    }
                    pushStack(&operatorTokens, currentTokenString);

                }
                else {
                    if (strstr(currentTokenString, "(")) {
                        pushStack(&operatorTokens, currentTokenString);
                    }
                    else {
                        if (strstr(currentTokenString, ")")) {
                            char operatorToken[2];
                            do {
                                popStack(&operatorTokens, operatorToken);
                                if (!strstr(operatorToken, "("))
                                    strcat(outputExpression, operatorToken);
                            } while ( (!strstr(operatorToken, "(")) && (!isEmptyStack(&operatorTokens)) );
                            if (!strstr(operatorToken, "(")) {
                                // at this point, we've popped all elements off the operator stack and still no '(' found. This means that parentheses are not balanced so quit with exit code != 0
                                ret = 0x01<<1;
                                break;
                            }

                        }
                        else {
                            strcat(outputExpression, currentTokenString);
                        }
                    }
                }
            }
            char operatorStackTokenString[2];
            while (!isEmptyStack(&operatorTokens)) {
                popStack(&operatorTokens, operatorStackTokenString);
                if (strstr(operatorStackTokenString, "(")) {
                        ret = 0x01 << 1;
                        // can't break here. need to keep emptying the stack in order to deallocate the rest of the elements from the heap.
                }
                strcat(outputExpression, operatorStackTokenString);
            }
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
