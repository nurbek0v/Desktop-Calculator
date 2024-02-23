#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_calculator.h"

bool is_valid_brackets(char* string) {
  int openCount = 0;
  int closeCount = 0;

  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] == '(') {
      openCount++;
    } else if (string[i] == ')') {
      closeCount++;
      if (closeCount > openCount) {
        return false;  // Return false if a closing bracket is encountered
                       // before an opening bracket
      }
    }
  }
  return openCount == closeCount;  // Return true if the count of open brackets
                                   // is equal to the count of closed brackets
}
void remove_spaces(char* string) {
  char* destination = string;
  while (*string) {
    if (*string != ' ') {
      *destination = *string;  // Copy non-space characters to the destination
      destination++;
    }
    string++;
  }
  *destination = '\0';  // Add null terminator at the end
}
bool is_valid_character(char c) {
  const char* PERMITTED_SYMBOLS = "1234567890()+-*/^mcstalx.e";
  return strchr(PERMITTED_SYMBOLS, c) != NULL;
}
bool is_valid_number(char c) {
  const char* NUMBERS = "0123456789x";
  return strchr(NUMBERS, c) != NULL;
}

bool is_dot_valid(char* string) {
  bool has_significant =
      strchr("0123456789", (int)*(string - 2)) ? true : false;
  bool is_dot_single =
      strchr("0123456789", *(string + 1)) != NULL || *(string + 1) == '\0';
  bool is_only_numbers = true;
  // now go to the next character and test after '.'
  string++;
  if (has_significant &&
      (!strchr("0123456789", (int)*(string)) || *(string) == '\0')) {
    is_dot_single = false;
  }
  for (char* ptr = string; *ptr != '\0' && is_dot_single && is_only_numbers;
       ptr++) {
    char cur_char = *ptr;
    if (!strchr("0123456789", (int)cur_char)) {
      is_only_numbers = false;
      if (cur_char == '.') {
        is_dot_single = false;
      }
    }
  }

  return is_dot_single;
}
int handle_exponent(char* string) {
  if (string == NULL || *(string + 1) == '\0' ||
      !strchr("0123456789", *(string - 1))) {
    return 0;
  }

  int valid_chars = 0;
  bool error = false;

  if (strchr("+-", *(string + 1)) != NULL) {
    if (strchr("0123456789", *(string + 2)) != NULL) {
      valid_chars += 2;
      string += 2;
    } else {
      error = true;
    }
  } else if (!strchr("0123456789", *(string + 1))) {
    error = true;
  } else {
    valid_chars++;
    string++;
  }

  if (!error) {
    bool is_num_end = false;
    for (char* ptr = string; *ptr != '\0' && !is_num_end && !error; ptr++) {
      if (strchr("0123456789", *ptr)) {
        valid_chars++;
      } else if (*ptr == 'e' || *ptr == '.') {
        error = true;
      } else {
        is_num_end = true;
      }
    }
  }
  return error ? 0 : valid_chars;
}
int handle_character(char* ptr) {
  //    if (ptr == NULL) {
  //        return 0;
  //    }

  int valid_chars = 0;
  char str_to_analyze[6] = {'\0'};
  strncat(str_to_analyze, ptr, 5);

  switch (*ptr) {
    case '(':
      valid_chars = 1;
      break;
    case ')':
      if (*(ptr - 1) != '(') {
        valid_chars = 1;
      }
      break;
    case '.':
      valid_chars = (int)is_dot_valid(ptr);
      break;
    case 'e':
      valid_chars = handle_exponent(ptr);
      break;
      // Handle other cases as needed
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      if (strchr(OPERANDS, *(ptr + 1)) && *(ptr + 1) != '\0') {
        return 1;
      }
      break;
    case 'a':
      if (strstr(str_to_analyze, "asin(") || strstr(str_to_analyze, "acos(") ||
          strstr(str_to_analyze, "atan(")) {
        return 5;
      }
      break;
    case 'c':
      if (strstr(str_to_analyze, "cos(")) {
        return 4;
      }
      break;
    case 'l':
      if (strstr(str_to_analyze, "ln(")) {
        return 3;
      } else if (strstr(str_to_analyze, "log(")) {
        return 4;
      }
      break;
    case 'm':
      if (strstr(str_to_analyze, "mod")) {
        return 3;
      }
      break;
    case 's':
      if (strstr(str_to_analyze, "sin(")) {
        return 4;
      } else if (strstr(str_to_analyze, "sqrt(")) {
        return 5;
      }
      break;
    case 't':
      if (strstr(str_to_analyze, "tan(")) {
        return 4;
      }
      break;
  }
  return valid_chars;
}
bool is_valid_input(char* string) {
  if (string == NULL || *string == 'e' || *string == ')' ||
      !is_valid_brackets(string)) {
    return false;
  } else if (strcmp(string, "") == 0) {
    return false;
  }
  char* modifiedInput = strdup(string);
  remove_spaces(modifiedInput);
  for (char* ptr = modifiedInput; *ptr != '\0'; ptr++) {
    if (!is_valid_character(*ptr)) {
      return false;
      // free(modifiedInput);
    } else if (!is_valid_number(*ptr)) {
      int step = handle_character(ptr);
      if (step) {
        ptr += step - 1;
      } else {
        return false;
        // free(modifiedInput);
      }
    }
  }

  free(modifiedInput);
  return true;
}

// int main() {
//     //-x+1.2-(ln(5)-log(10))*tan(5)/sin(45)+2
//     char* testInput = "-x+1.2-(ln(5)-log(10))*tan(5)/sin(45)+2";
//     char* modifiedInput = strdup(testInput); // Make a copy to avoid
//     modifying the original constant string remove_spaces(modifiedInput);
//     printf("String after removing spaces: %s\n", modifiedInput);
//     if (is_valid_input(modifiedInput)) {
//         printf("The input is valid.\n");
//         char* divided_str = divided_by_tokens(modifiedInput);
//         printf("divided_str: %s\n", divided_str);
//         stack* initial_stack = parsing_elements(divided_str);
//         print_stack_in_line(initial_stack);
//         stack* rpn_stack = convert_to_R_P_N(initial_stack);
//         print_stack_in_line(rpn_stack);
//         replace_xValue_in_stack(rpn_stack, 3);
//         print_stack_in_line(rpn_stack);
//         double res = calculate(rpn_stack);
//         printf("\nRESULT: %f\n", res);
//
//     } else {
//         printf("The input is not valid.\n");
//     }
//
//     free(modifiedInput); // Free the dynamically allocated memory
//     return 0;
// }
