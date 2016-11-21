#include <stdlib.h>
#include <check.h>
#include "infixrpnconv.h"
#include "stackstring.h"

START_TEST (infixtorpn_outputbufferatleastaslongasinputstring)
{
    char outputExpression[INFIXRPN_OUTBUFFERSIZE];
    const char inputExpr[] = "l/m^n*o-p";
    int ret = infixToRPN(inputExpr, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0);

    char outputExpression2[2]; // output buffer could be smaller than input but let's not take any chances.
    ret = infixToRPN(inputExpr, outputExpression2, 2);
    ck_assert_int_eq(ret, 0x01<<7);

}
END_TEST

START_TEST (rpntoinfix_outputbufferatleastaslongasinputstring)
{
    char outputExpression[INFIXRPN_OUTBUFFERSIZE];
    const char inputExpr[] = "ag+ba-c+cedf^*+^*";
    int ret = rpnToInfix(inputExpr, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0);

    char outputExpression2[2]; //output buffer smaller than input unacceptable. infix output could be way larger than rpn input.
    ret = rpnToInfix(inputExpr, outputExpression2, 2);
    ck_assert_int_eq(ret, 0x01<<7);
}
END_TEST


START_TEST (infixtorpn_validateinputexprlowercaselettersandvalidoperatorsonly)
{
    char outputExpression[INFIXRPN_OUTBUFFERSIZE];
    const char inputExpr[] = "l/m^n*o-p";
    int ret = infixToRPN(inputExpr, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0);
    //
    const char inputExpr2[] = "L/M^n*o-p";
    ret = infixToRPN(inputExpr2, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);
    //
    const char inputExpr3[] = "l/m^n*o-123";
    ret = infixToRPN(inputExpr3, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);    
    //
    const char inputExpr4[] = "l /m^ n*o-p"; // white space in between the expression
    ret = rpnToInfix(inputExpr4, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);

}
END_TEST

START_TEST (rpntoinfix_validateinputexprlowercaselettersandvalidoperatorsonly)
{
    char outputExpression[INFIXRPN_OUTBUFFERSIZE];
    const char inputExpr[] = "ag+ba-c+cedf^*+^*";
    int ret = rpnToInfix(inputExpr, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0);
    //
    const char inputExpr2[] = "AG+ba-c+cedf^*+^*";
    ret = rpnToInfix(inputExpr2, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);
    //
    const char inputExpr3[] = "123+ba-c+cedf^*+^*";
    ret = rpnToInfix(inputExpr3, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);
    //
    const char inputExpr4[] = "(ag)+ba-c+cedf^*+^*"; // input is rpn so no ()
    ret = rpnToInfix(inputExpr4, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);
    //
    const char inputExpr5[] = "a g +ba-c+cedf^*+^*"; // white space in between the expression
    ret = rpnToInfix(inputExpr5, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0x01<<6);

}
END_TEST

START_TEST (stack_operations)
{
    /*static*/ Stack operandTokens; // the static declaration avoids segmentation fault if we try to use the stack without first calling initStack. but for this test we'll properly initialize the stack.
    // only testing stack functionality
    //
    char token[50];
    int ret;
    //ret = topStack(&operandTokens, token); commented out on purpose
    //ck_assert_int_ne(ret, 0);
    //
    initStack(&operandTokens);
    ck_assert(isEmptyStack(&operandTokens) == true);
    //
    memset(token, 0, 50);
    sprintf(token, "(%s)", "test");
    ret = pushStack(&operandTokens, token);
    ck_assert_int_eq(ret, 0);

    ck_assert((!isEmptyStack(&operandTokens)) == true);

    memset(token, 0, 50);
    ret = pushStack(&operandTokens, token); //should fail. trying to push empty token
    ck_assert_int_ne(ret, 0);

    memset(token, 0, 50);
    ret = popStack(&operandTokens, token);
    ck_assert_int_eq(ret, 0);
    ck_assert_str_eq(token, "(test)");

    ck_assert(isEmptyStack(&operandTokens) == true);

    memset(token, 0, 50);
    ret = popStack(&operandTokens, token); // should fail
    ck_assert_int_ne(ret, 0);

}
END_TEST

Suite * infixrpnconv_suite (void)
{
  Suite *s = suite_create ("infixrpnconv");

    /* Validation test case */
    TCase *tc_val = tcase_create ("Validation");
    tcase_add_test (tc_val, infixtorpn_outputbufferatleastaslongasinputstring);
    tcase_add_test (tc_val, rpntoinfix_outputbufferatleastaslongasinputstring);
    tcase_add_test (tc_val, infixtorpn_validateinputexprlowercaselettersandvalidoperatorsonly);
    tcase_add_test (tc_val, rpntoinfix_validateinputexprlowercaselettersandvalidoperatorsonly);
    suite_add_tcase (s, tc_val);

    TCase *tc_stk = tcase_create ("Stack");
    tcase_add_test (tc_stk, stack_operations);
    suite_add_tcase (s, tc_stk);

    return s;
}

int main (void)
{
    int number_failed;
    Suite *s = infixrpnconv_suite ();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
