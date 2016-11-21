#include <stdlib.h>
#include <check.h>
#include "infixrpnconv.h"

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


START_TEST (infixtorpn_validateinputexprlowercaselettersonly)
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

}
END_TEST

START_TEST (rpntoinfix_validateinputexprlowercaselettersonly)
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

}
END_TEST

Suite * infixrpnconv_suite (void)
{
  Suite *s = suite_create ("infixrpnconv");

    /* Core test case */
    TCase *tc_core = tcase_create ("Validation");
    tcase_add_test (tc_core, infixtorpn_outputbufferatleastaslongasinputstring);
    tcase_add_test (tc_core, rpntoinfix_outputbufferatleastaslongasinputstring);
    tcase_add_test (tc_core, infixtorpn_validateinputexprlowercaselettersonly);
    tcase_add_test (tc_core, rpntoinfix_validateinputexprlowercaselettersonly);
    suite_add_tcase (s, tc_core);

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
