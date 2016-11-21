#ifndef INFIXRPNKATA_H
#define INFIXRPNKATA_H

#include <stdlib.h>

#define INFIXRPN_OUTBUFFERSIZE 1024

#ifdef __cplusplus

extern "C" {

#endif


extern int infixToRPN(const char *originalExpression, char *outputExpression, size_t outBufferSz);

extern int rpnToInfix(const char *originalExpression, char *outputExpression, size_t outBufferSz);


#ifdef __cplusplus

}

#endif

#endif // INFIXRPNKATA_H
