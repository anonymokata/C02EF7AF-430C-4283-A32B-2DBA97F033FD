#include <stdlib.h>
#include <check.h>
#include "infixrpnconv.h"

START_TEST (infixtorpn_passinputandreturnecho)
{
    char outputExpression[INFIXRPN_OUTBUFFERSIZE];
    const char inputExpr[] = "l/m^n*o-p";
    int ret = infixToRPN(inputExpr, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0);
    ck_assert_str_eq(outputExpression, "l/m^n*o-p");
    
}
END_TEST

START_TEST (rpntoinfix_passinputandreturnecho)
{
    char outputExpression[INFIXRPN_OUTBUFFERSIZE];
    const char inputExpr[] = "ag+ba-c+cedf^*+^*";
    int ret = rpnToInfix(inputExpr, outputExpression, INFIXRPN_OUTBUFFERSIZE);
    ck_assert_int_eq(ret, 0);
    ck_assert_str_eq(outputExpression, "ag+ba-c+cedf^*+^*");
}
END_TEST

Suite * infixrpnconv_suite (void)
{
  Suite *s = suite_create ("infixrpnconv");

  /* Core test case */
  TCase *tc_core = tcase_create ("Validation");
  tcase_add_test (tc_core, infixtorpn_passinputandreturnecho);
  tcase_add_test (tc_core, rpntoinfix_passinputandreturnecho);
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