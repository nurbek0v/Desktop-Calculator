#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_calculator.h"

enum error_type calculate_usual(const char* string, long double* result) {
  enum error_type error = no_error;
  if (string == NULL || result == NULL) {
    error = undef_error;
  } else {
    *result = 0;
    char* modifiedInput = strdup(string);
    remove_spaces(modifiedInput);
    if (is_valid_input(modifiedInput)) {
      char* divided_str = divided_by_tokens(modifiedInput);
      stack* initial_stack = parsing_elements(divided_str);
      stack* rpn_stack = convert_to_R_P_N(initial_stack);
      double res = calculate(rpn_stack, &error);
      if (error == no_error) {
        *result = res;
      }
    } else {
      error = invalid_input;
    }
    free(modifiedInput);
  }

  return error;
}
bool contains_x_val(stack* s) {
  stack_element* current = s->top;
  bool result = false;
  while (current != NULL) {
    if (current->element_type == x_value) {
      result = true;
    }
    current = current->next;
  }
  return result;
}
enum error_type calculate_with_x_value(const char* string, long double x,
                                       long double* result) {
  enum error_type error = no_error;

  if (string == NULL || result == NULL) {
    error = undef_error;
  } else {
    *result = 0;
    char* modifiedInput = strdup(string);
    remove_spaces(modifiedInput);
    if (is_valid_input(modifiedInput)) {
      char* divided_str = divided_by_tokens(modifiedInput);
      stack* initial_stack = parsing_elements(divided_str);
      replace_xValue_in_stack(initial_stack, x);
      stack* rpn_stack = convert_to_R_P_N(initial_stack);
      double res = calculate(rpn_stack, &error);
      if (error == no_error) {
        *result = res;
      }
    } else {
      error = invalid_input;
    }
    free(modifiedInput);
  }
  return error;
}