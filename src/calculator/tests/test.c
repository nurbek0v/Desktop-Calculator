#include <check.h>
#include <stdio.h>

#include "../s21_calculator.h"

START_TEST(input_validation_opt_1) {
  char* sample = "2+2*2+log(10)";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_2) {
  char* sample = "2^2^3";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_3) {
  char* sample = "cos(4)*sin(3)";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_4) {
  char* sample = "3.1415-21/42+12tan(5)";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_5) {
  char* sample = "19e+6-659.129+x(tan(cos(x)))";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_6) {
  char* sample = "kakayatonesurazica";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_7) {
  char* sample = "3..15";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_8) {
  char* sample = "1e--16";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_9) {
  char* sample = "29ep+cos(4)";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_10) {
  char* sample = "atan(5)+ln(3)+mod(4)+sqrb()";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_11) {
  char* sample = "atan(5)+ln(3)+mod(4)+sqrt())";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_12) {
  char* sample = "";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_13) {
  int res = is_valid_input(NULL);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_14) {
  char* sample = "1234.234.23 + 2";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_15) {
  char* sample = "a23.45f45\0";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_16) {
  char* sample = "344e\0";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_17) {
  char* sample = "e3";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_18) {
  char* sample = "1e12313d";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_19) {
  char* sample = "p";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_20) {
  char* sample = "cat";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_21) {
  char* sample = "lat";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_22) {
  char* sample = "sat";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_23) {
  char* sample = "sqrt()";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_24) {
  char* sample = "tat";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_25) {
  char* sample = "mom";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_26) {
  char* sample = "2 + k";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST
START_TEST(input_validation_opt_27) {
  char* sample = "1e1.1";
  int res = is_valid_input(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

// CALCULATION
START_TEST(calc_1) {
  enum error_type error;
  char* sample = "2+2";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  if (error == no_error) {
    ck_assert_double_eq(res, 4);
  }
}
END_TEST
START_TEST(calc_2) {
  stack* sample_stack = createStack();
  int res = isEmpty(sample_stack);
  stack_element* sample_el = pop(sample_stack);
  // double top_value = top(sample_stack);
  // ck_assert_double_eq(top_value, -1);
  ck_assert_ptr_eq(sample_el, NULL);
  ck_assert_double_eq(res, SUCCESS);

  push(sample_stack, 2, zero, numb);
  freeStack(sample_stack);
}
END_TEST
START_TEST(calc_3) {
  enum error_type error;
  char* sample = "(-2+x)-1*2/(2^1) + 3mod2";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  replace_xValue_in_stack(sample_rpn, 2);
  double res = calculate(sample_rpn, &error);
  double expected = (-2 + 2) - 1 * 2 / (pow(2, 1)) + 3 % 2;
  if (error == no_error) {
    ck_assert_double_eq(res, expected);
  }
}
END_TEST
START_TEST(calc_4) {
  enum error_type error;
  char* sample = "sin(45) + cos(45) - tan(45) + sqrt(4)";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  double expected = sin(45) + cos(45) - tan(45) + sqrt(4);
  if (error == no_error) {
    ck_assert_double_eq(res, expected);
  }
}
END_TEST
START_TEST(calc_5) {
  enum error_type error;
  char* sample = "-asin(1) + acos(45) - atan(45) + ln(45) + log(45)";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  double expected = -asin(1) + acos(45) - atan(45) + log10(45) + log(45);
  if (error == no_error) {
    ck_assert_double_ne(res, expected);
  }
}
END_TEST
START_TEST(calc_6) {
  enum error_type error;
  char* sample = "22245e-2";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  double expected = 22245e-2;
  if (error == no_error) {
    ck_assert_double_eq(res, expected);
  }
}
END_TEST
START_TEST(calc_7) {
  enum error_type error;
  char* sample = "-(476567mod693)+1/ln(x)+sin(x)+(3-3)*1+(3^(4^4))";
  double x = 18.17;
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  replace_xValue_in_stack(sample_rpn, x);
  double res = calculate(sample_rpn, &error);
  double expected =
      -(476567 % 693) + 1 / log(x) + sin(x) + (3 - 3) * 1 + pow(3, pow(4, 4));
  if (error == no_error) {
    ck_assert_double_eq(res, expected);
  }
}
END_TEST
START_TEST(calc_8) {
  enum error_type error;
  char* sample = "-4^2^2";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  double expected = -pow(4, pow(2, 2));
  if (error == no_error) {
    ck_assert_double_eq(res, expected);
  }
}
END_TEST
START_TEST(calc_9) {
  enum error_type error;
  char* sample = "1 / 0";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  if (error == no_error) {
    ck_assert_double_eq(res, FAILURE);
  }
}
END_TEST
START_TEST(calc_10) {
  enum error_type error;
  char* sample = "sqrt(-19)";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  if (error == no_error) {
    ck_assert_double_eq(res, FAILURE);
  }
}
END_TEST
START_TEST(calc_11) {
  enum error_type error;
  char* sample = "ln(-19)";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  if (error == no_error) {
    ck_assert_double_eq(res, FAILURE);
  }
}
END_TEST
START_TEST(calc_12) {
  enum error_type error;
  char* sample = "log(-19)";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  if (error == no_error) {
    ck_assert_double_eq(res, FAILURE);
  }
}
END_TEST
START_TEST(calc_13) {
  int res = exponent_notation_length(NULL);
  ck_assert_double_eq(res, FAILURE);
  res = exponent_notation_handler(NULL);
  ck_assert_double_eq(res, FAILURE);
  res = function_key_handler(NULL);
  ck_assert_double_eq(res, FAILURE);
  res = function_key_handler("d");
  ck_assert_double_eq(res, FAILURE);
  double res1 = convert_str_to_double("4\n");
  ck_assert_double_eq(res1, FAILURE);
}
END_TEST
START_TEST(calc_14) {
  enum error_type error;
  char* sample = "2e-2 + 32e3";
  char* sample_div = divided_by_tokens(sample);
  stack* sample_stack = parsing_elements(sample_div);
  stack* sample_rpn = convert_to_R_P_N(sample_stack);
  double res = calculate(sample_rpn, &error);
  double exp = 2e-2 + 32e3;
  if (error == no_error) {
    ck_assert_double_eq(res, exp);
  }
}

// Loan Calculation
START_TEST(loan_calc_1) {
  long double amount = 1000;
  long double rate = 12;
  double term = convert_years_to_month(5);
  long double total = total_payment_differentiated(amount, term, rate);
  long double month = monthly_payment_differentiated(total, term);
  long double overpay = overpayment(amount, total);
  ck_assert_int_eq((int)total, 1305);
  ck_assert_int_eq((int)month, 21);
  ck_assert_int_eq((int)overpay, 305);
}
START_TEST(loan_calc_2) {
  long double amount = 1000;
  long double rate = 12;
  double term = convert_years_to_month(5);
  long double month = monthly_payment_annuity(amount, rate, term);
  long double total = total_payment_annuity(month, term);
  long double overpay = overpayment(amount, total);
  ck_assert_int_eq((int)month, 22);
  ck_assert_int_eq((int)total, 1334);
  ck_assert_int_eq((int)overpay, 334);
}
START_TEST(deposit_calc_1) {
  long double deposit_amount = 100000;
  long double result = get_total_earned(&deposit_amount, 12, 5, 0, false, 0, 0);
  ck_assert_ldouble_eq(result, 5000);
}
END_TEST
START_TEST(deposit_calc_2) {
  long double res = get_tax_amount(104850, 3);
  int test_res = fabsl(res - (3145.500000)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST
START_TEST(deposit_calc_3) {
  long double res = get_total_amount(100000, 5000, 3);
  int test_res = fabsl(res - (104997.000000)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST
START_TEST(deposit_calc_4) {
  long double deposit_amount = 100000;
  long double res = get_total_earned(&deposit_amount, 12, 5, 1, true, 0, 0);
  ck_assert_ldouble_eq(res, 5000);
}
END_TEST

START_TEST(calc_usual_1) {
  char* input = "5+10+97";
  char* input1 = "5+10+97++";
  long double res = 0;
  calculate_usual(input, &res);
  ck_assert_ldouble_eq(res, 112.000000);
  enum error_type error = calculate_usual(NULL, NULL);
  enum error_type error1 = calculate_usual(input1, &res);
  ck_assert_int_eq(error, undef_error);
  ck_assert_int_eq(error1, invalid_input);
}
END_TEST

START_TEST(calc_usual_2) {
  char* input = "2^(2^3)";
  long double res = 0;
  calculate_usual(input, &res);
  ck_assert_ldouble_eq(res, 256.000000);
}
END_TEST
START_TEST(calc_with_x_1) {
  char* input = "x+x+x";
  long double res = 0;
  calculate_with_x_value(input, -2, &res);
  enum error_type error = calculate_with_x_value(NULL, -2, NULL);
  ck_assert_int_eq(error, undef_error);
  ck_assert_ldouble_eq(res, -6.000000);
}
END_TEST

START_TEST(calc_with_x_2) {
  char* input = "2+3*x";
  char* input2 = "2+3*x++";
  long double res = 0;
  calculate_with_x_value(input, -2, &res);
  ck_assert_ldouble_eq(res, -4.000000);
  enum error_type error = calculate_with_x_value(input2, -2, &res);
  ck_assert_int_eq(error, invalid_input);
  char* sample_div = divided_by_tokens(input);
  stack* sample_stack = parsing_elements(sample_div);
  bool contains = contains_x_val(sample_stack);
  ck_assert_int_eq(contains, 1);
}
END_TEST
Suite* s21_calc_suite(void) {
  Suite* s;
  TCase* tc_validation;
  TCase* tc_calculation;
  TCase* tc_loan_calc;
  TCase* tc_deposit_calc;
  TCase* tc_controller;
  s = suite_create("s21_smart_calc");
  tc_validation = tcase_create("Input Validation");
  tc_calculation = tcase_create("Calculation");
  tc_loan_calc = tcase_create("Loan Calculation");
  tc_deposit_calc = tcase_create("Deposit calc");
  tc_controller = tcase_create("Controller test");
  // Validation tests
  tcase_add_test(tc_validation, input_validation_opt_1);
  tcase_add_test(tc_validation, input_validation_opt_2);
  tcase_add_test(tc_validation, input_validation_opt_3);
  tcase_add_test(tc_validation, input_validation_opt_4);
  tcase_add_test(tc_validation, input_validation_opt_5);
  tcase_add_test(tc_validation, input_validation_opt_6);
  tcase_add_test(tc_validation, input_validation_opt_7);
  tcase_add_test(tc_validation, input_validation_opt_8);
  tcase_add_test(tc_validation, input_validation_opt_9);
  tcase_add_test(tc_validation, input_validation_opt_10);
  tcase_add_test(tc_validation, input_validation_opt_11);
  tcase_add_test(tc_validation, input_validation_opt_12);
  tcase_add_test(tc_validation, input_validation_opt_13);
  tcase_add_test(tc_validation, input_validation_opt_14);
  tcase_add_test(tc_validation, input_validation_opt_15);
  tcase_add_test(tc_validation, input_validation_opt_16);
  tcase_add_test(tc_validation, input_validation_opt_17);
  tcase_add_test(tc_validation, input_validation_opt_18);
  tcase_add_test(tc_validation, input_validation_opt_19);
  tcase_add_test(tc_validation, input_validation_opt_20);
  tcase_add_test(tc_validation, input_validation_opt_21);
  tcase_add_test(tc_validation, input_validation_opt_22);
  tcase_add_test(tc_validation, input_validation_opt_23);
  tcase_add_test(tc_validation, input_validation_opt_24);
  tcase_add_test(tc_validation, input_validation_opt_25);
  tcase_add_test(tc_validation, input_validation_opt_26);
  tcase_add_test(tc_validation, input_validation_opt_27);

  tcase_add_test(tc_calculation, calc_1);
  tcase_add_test(tc_calculation, calc_2);
  tcase_add_test(tc_calculation, calc_3);
  tcase_add_test(tc_calculation, calc_4);
  tcase_add_test(tc_calculation, calc_5);
  tcase_add_test(tc_calculation, calc_6);
  tcase_add_test(tc_calculation, calc_7);
  tcase_add_test(tc_calculation, calc_8);
  tcase_add_test(tc_calculation, calc_9);
  tcase_add_test(tc_calculation, calc_10);
  tcase_add_test(tc_calculation, calc_11);
  tcase_add_test(tc_calculation, calc_12);
  tcase_add_test(tc_calculation, calc_13);
  tcase_add_test(tc_calculation, calc_14);

  tcase_add_test(tc_loan_calc, loan_calc_1);
  tcase_add_test(tc_loan_calc, loan_calc_2);

  tcase_add_test(tc_loan_calc, deposit_calc_1);
  tcase_add_test(tc_loan_calc, deposit_calc_2);
  tcase_add_test(tc_loan_calc, deposit_calc_3);
  tcase_add_test(tc_loan_calc, deposit_calc_4);

  tcase_add_test(tc_controller, calc_usual_1);
  tcase_add_test(tc_controller, calc_usual_2);
  tcase_add_test(tc_controller, calc_with_x_1);
  tcase_add_test(tc_controller, calc_with_x_2);
  // tcase_add_test(tc_loan_calc, deposit_calc_4);
  // tcase_add_test(tc_loan_calc, deposit_calc_4);

  // tcase_add_test(tc_core, ADD);
  // tcase_add_test(tc_core, UNARY_ADD);
  // tcase_add_test(tc_core, SUB);
  // tcase_add_test(tc_core, UNARY_SUB);
  // tcase_add_test(tc_core, MULT);
  // tcase_add_test(tc_core, DIV);
  // tcase_add_test(tc_core, POW);
  // tcase_add_test(tc_core, SIN);
  // tcase_add_test(tc_core, COS);
  // tcase_add_test(tc_core, TAN);
  // tcase_add_test(tc_core, ASIN);
  // tcase_add_test(tc_core, ACOS);
  // tcase_add_test(tc_core, ATAN);
  //    tcase_add_test(tc_core, LN);
  //    tcase_add_test(tc_core, LOG);
  //    tcase_add_test(tc_core, SQRT);

  suite_add_tcase(s, tc_validation);
  suite_add_tcase(s, tc_calculation);
  suite_add_tcase(s, tc_loan_calc);
  suite_add_tcase(s, tc_deposit_calc);
  suite_add_tcase(s, tc_controller);

  return s;
}

int main() {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = s21_calc_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}