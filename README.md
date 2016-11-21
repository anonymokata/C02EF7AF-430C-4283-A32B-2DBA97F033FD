Reverse Polish Notation Converter

Problem to Solve:

Take a mathematical expression in infix notation (operator between operands; ex. a+b) and convert it to reverse polish notation (operator follows operands; ex. ab+) and be able to do the reverse conversion as well; take a mathematical expression in rpn notation and convert it to infix notation.

Assumptions:

The mathematical expression to convert is based on variables, not numbers. Hence, no calculations will be performed. The exercise will thus focus on rearranging the given variable expression in such a way as to comply with the rules of the target notation. The only characters allowed in the input expression are lowercase letters, the operators ^/*-+ (listed from left to right in order of precedence) and in the case of an input infix expression to convert to rpn, the parentheses characters ().
 

Algorithm Strategy:

A. Infix to RPN conversion

For this particular type of conversion, we use a stack ADT as temporary storage for operators (and left parenthesis) that are encountered while traversing each character of the input expression.

As an example, let's parse the input infix expression a+b-c, whose equivalent rpn notation is abc-+

First token is the letter a, so add it to the output buffer. 

outbuf--->    a
stack --->   
inputbuf ---> +b-c

next token is operator +, so add it to the stack.

outbuf--->    a
stack --->    +
inputbuf ---> b-c  

next token is the letter b, so add it to the output buffer.

outbuf--->    ab
stack --->    +
inputbuf ---> -c

next token is operator -, so add it to the stack since it has higher precedence than the stack's current top operator + (if it would have been otherwise, then the stack's current top operator would have been popped and added to the output buffer. This process of popping from the stack would have continued until either a parenthesis would have been found or an operator of lower precedence than the current token operator would have been hit)

outbuf--->    ab
stack --->    +-
inputbuf ---> c     

next token is the letter c, so add it to the output buffer.

outbuf--->    abc
stack --->    +-
inputbuf ---> 

We've run out of input tokens to process, so since the stack is not empty, dump its contents into the output buffer (in iterative fashion, pop first from the stack, followed by an add to output. Repeat until stack is empty)

outbuf--->    abc-+
stack --->    
inputbuf --->

When encountering a parenthesis during traversal, if it is a '(', then add it to the stack. Later on, when we hit the next ')' from the input stream (hopefully the input is properly balanced. The conversion will fail otherwise, as it should) we pop from the stack and add each popped operator to the output buffer until the previously stored '(' is popped, at which point we stop popping from the stack and dump the popped '('.   
 					
 
B. RPN to Infix conversion

For this particular type of conversion, we use a stack ADT as temporary storage for operands that are encountered while traversing each character of the input expression.

As an example, let's parse the input RPN expression abc-+, whose equivalent infix notation is a+b-c or (a+(b-c)) 

First token is the letter a, so add it to the stack. 

stack --->    a
inputbuf ---> bc-+

next token is the letter b, so add it to the stack.

stack --->    a,b
inputbuf ---> c-+

next token is the letter c, so add it to the stack.

stack --->    a,b,c
inputbuf ---> -+

next token is operator -, so pop the top two letters from the stack (c and b) and concatenate the three tokens involved, surrounding the new expression between () parentheses as so:

(b-c)

then, push the new expression onto the stack. the state of affairs now looks as follows;

stack --->    a,(b-c)
inputbuf ---> +

next token is operator +, so repeating the same procedure from the previous step, we arrive at the following state of affairs:

stack --->    (a+(b-c))
inputbuf ---> 

Notice that unlike with the infix to RPN conversion, there was no use for an output buffer during this procedure as tokens were being already aggregated to the expression at the top of the stack. This procedure should always end with one element remaining on the stack, containing the entire converted output expression. As a last step, this last remaining stack item is popped and copied over to the output buffer.
   

Deliverables:

The solution is provided in static library form in order to facilitate integration into other client code bases. To build the library, run the typical make or make all target. No additional steps should be necessary. As the make file currently stands, it compiles and links with the gcc toolchain for Ubuntu Linux (4.8.4 and above) using the -std=c99 flag. Once the build completes, the libinfixrpnconv.a archive should appear in the root directory of this repository. This archive's corresponding header file path is the following: 
./src/infixrpnconv.h 

A test executable which runs a battery of unit tests may also be generated at your discretion. To build and automatically run such tests via this executable, you may issue the make test command. An optional target named resettarget also appears in the make file in order to streamline the edit, build, test workflow in case you would like to make further changes to the library.

Library Interface (API):

A. infixToRPN - Method Signature
	
int infixToRPN(const char *originalExpression, char *outputExpression, size_t outBufferSz);

1. Input/Output Parameters

	- originalExpression: Input string containing the infix notation to convert.
	- outputExpression: The client-supplied output buffer where the results of the conversion to RPN notation will be written to.
	- outBufferSz: The size of the outputExpression buffer. In order to standardize this buffer size, it is recommended to use the define constant INFIXRPN_OUTBUFFERSIZE defined in header file infixrpnconv.h

2. Return value

	An integer value of 0 is returned upon successful completion of the conversion operation. A return value of non-zero would indicate that a problem occurred during the parsing operation. Such problems may be attributed to input expression validation errors for the most part as system-related issues might be minimal to come about.  

B. rpnToInfix - Method Signature

int rpnToInfix(const char *originalExpression, char *outputExpression, size_t outBufferSz);

1. Input/Output Parameters

	- originalExpression: Input string containing the RPN notation to convert.
	- outputExpression: The client-supplied output buffer where the results of the conversion to infix notation will be written to.
	- outBufferSz: The size of the outputExpression buffer. In order to standardize this buffer size, it is recommended to use the define constant INFIXRPN_OUTBUFFERSIZE defined in header file infixrpnconv.h

2. Return value

	An integer value of 0 is returned upon successful completion of the conversion operation. A return value of non-zero would indicate that a problem occurred during the parsing operation. Such problems may be attributed to input expression validation errors for the most part as system-related issues might be minimal to come about. 

It is advised that the infixrpnconv.h header file be used as is when attempting to use the library in client code as it already contains the specifiers and preprocessing directives required to use the library under either C or C++-based client code bases.


Other considerations:

Although used for sizing output buffers, the INFIXRPN_OUTBUFFERSIZE define constant in a certain way also limits the length of the input string expression to be converted, but it is assumed that the predefined value of 1024 provides for a sufficiently large expression to process.

The unit test suite which the test executable runs is based on an open-source unit testing framework named Check. Please refer to the source code under the tests folder for learning more about how to use such a framework and also for learning about the internals of the libinfixrpnconv library.     