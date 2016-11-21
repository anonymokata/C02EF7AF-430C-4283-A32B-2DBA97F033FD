#include <stdio.h>
#include "infixrpnconv.h"


int infixToRPN(const char *originalExpression, char *outputExpression, size_t outBufferSz) {
        int ret = 0;
	memset(outputExpression, 0, outBufferSz);
	if ((strlen(originalExpression) + 1) <= outBufferSz)
        	memcpy(outputExpression, originalExpression, strlen(originalExpression));
	else 
		ret = 0x01<<7;
        return ret;
}

int rpnToInfix(const char *originalExpression, char *outputExpression, size_t outBufferSz) {
        int ret = 0;
        memset(outputExpression, 0, outBufferSz);
	if ((strlen(originalExpression) + 1) <= outBufferSz)
        	memcpy(outputExpression, originalExpression, strlen(originalExpression));
	else 
		ret = 0x01<<7;
        return ret;
}
