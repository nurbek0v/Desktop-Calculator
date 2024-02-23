#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_calculator.h"

stack* parsing_elements(char* string) {
  stack* main_stack = createStack();
  if (main_stack == NULL || string == NULL) {
    return NULL;
  }

  const char* delimiter = " ";  // Определение разделителей для токенизации
  char* first_token = strtok(string, delimiter);  // Получение первого токена
  // char* second_token = strtok(NULL, delimiter);  // Получение второго токена

  while (first_token != NULL) {
    if (*first_token == 'x') {
      push(main_stack, 777, zero, x_value);
      first_token = strtok(NULL, delimiter);
    } else if (strchr("1234567890.", *first_token)) {
      double number = convert_str_to_double(first_token);
      push(main_stack, number, zero, numb);
      first_token = strtok(NULL, delimiter);
    } else if (strchr(OPERATORS, *first_token)) {
      switch (*first_token) {
        case '+':
          push(main_stack, 777, one, plus);
          first_token = strtok(NULL, delimiter);
          break;
        case '-':
          push(main_stack, 777, one, minus);
          first_token = strtok(NULL, delimiter);
          break;
        case '*':
          push(main_stack, 777, two, multiply);
          first_token = strtok(NULL, delimiter);
          break;
        case '/':
          push(main_stack, 777, two, divide);
          first_token = strtok(NULL, delimiter);
          break;
        case '^':
          push(main_stack, 777, three, degree);
          first_token = strtok(NULL, delimiter);
          break;
      }
    } else if (strchr("()", *first_token)) {
      switch (*first_token) {
        case '(':
          push(main_stack, 777, undef, open_brackets);
          first_token = strtok(NULL, delimiter);
          break;
        case ')':
          push(main_stack, 777, undef, close_brackets);
          first_token = strtok(NULL, delimiter);
          break;
      }
    } else if (strcmp(first_token, "tan") == 0) {
      push(main_stack, 777, four, tangent);
      first_token = strtok(NULL, delimiter);
      // tan
    } else if (strcmp(first_token, "sin") == 0) {
      push(main_stack, 777, four, sine);
      first_token = strtok(NULL, delimiter);
      // sin
    } else if (strcmp(first_token, "cos") == 0) {
      push(main_stack, 777, four, cosine);
      first_token = strtok(NULL, delimiter);
      // cos
    } else if (strcmp(first_token, "atan") == 0) {
      push(main_stack, 777, four, arc_tangent);
      first_token = strtok(NULL, delimiter);
      // atan
    } else if (strcmp(first_token, "asin") == 0) {
      push(main_stack, 777, four, arc_sine);
      first_token = strtok(NULL, delimiter);
      // asin
    } else if (strcmp(first_token, "acos") == 0) {
      push(main_stack, 777, four, arc_cosine);
      first_token = strtok(NULL, delimiter);
      // acos
    } else if (strcmp(first_token, "sqrt") == 0) {
      push(main_stack, 777, four, sqrt_sign);
      first_token = strtok(NULL, delimiter);
      // sqrt
    } else if (strcmp(first_token, "ln") == 0) {
      push(main_stack, 777, four, natural_logarithm);
      first_token = strtok(NULL, delimiter);
      // ln
    } else if (strcmp(first_token, "log") == 0) {
      push(main_stack, 777, four, logarithm);
      first_token = strtok(NULL, delimiter);
      // log
    } else if (strcmp(first_token, "mod") == 0) {
      push(main_stack, 777, two, mod_sign);
      first_token = strtok(NULL, delimiter);
      // mod
    } else {
      char* value_str = scientificToMath(first_token);
      double value = convert_str_to_double(value_str);
      push(main_stack, value, zero, numb);
      first_token = strtok(NULL, delimiter);
    }
  }

  return reverse_stack(main_stack);
}
double convert_str_to_double(char* str) {
  char* endptr;  // Pointer to character that stops conversion
  double result = strtod(str, &endptr);  // Convert string to double

  if (*endptr != '\0') {
    // If endptr points to a non-null character, the conversion was not
    // successful
    // printf("Error: Invalid input for conversion to double: %s\n", str);
    return FAILURE;  // Terminate the program or handle the error as appropriate
  }

  return result;
}
char* scientificToMath(const char* scientificStr) {
  double number;
  sscanf(scientificStr, "%lf",
         &number);  // Считывание числа из строки научной записи

  char mathStr[50];  // Буфер для хранения математического выражения
  sprintf(mathStr, "%.10f",
          number);  // Форматирование числа в математическое выражение

  return strdup(mathStr);  // Возвращает динамически выделенную строку с
                           // математическим выражением
}
//
// char* unary_sign_handler(char* input_string) {
//    char* unary_sign_handled_string = (char*)calloc(MAX_LEN * 3 + 1,
//    sizeof(char)); // memset(unary_sign_handled_string, '\0', MAX_LEN * 2 +
//    1);
//
//    const char *delimiter = " ";  // Определение разделителей для токенизации
//    char* first_token = strtok(input_string, delimiter);  // Получение первого
//    токена char* second_token = strtok(NULL, delimiter);  // Получение второго
//    токена
//
//
//    int tokens_count = 0;
//    while (second_token != NULL) {
////        tokens_count++;
////        printf("Token%d: %s\n", tokens_count, token);  // Обработка текущего
/// токена (в данном случае, просто вывод на экран) /        token =
/// strtok(NULL, delimiter);  // Получение следующего токена
//            if ((*first_token == '-') && (tokens_count == 0)) {
//                strcat(unary_sign_handled_string, "0");
//                strcat(unary_sign_handled_string, " ");
//                strcat(unary_sign_handled_string, first_token);
//                strcat(unary_sign_handled_string, " ");
//                first_token = second_token;
//                second_token = strtok(NULL, delimiter);
//                tokens_count++;
//            } else if ((*second_token == '-') && (*first_token == '(')) {
//                strcat(unary_sign_handled_string, first_token);
//                strcat(unary_sign_handled_string, " ");
//                strcat(unary_sign_handled_string, "0");
//                strcat(unary_sign_handled_string, " ");
//                first_token = second_token;
//                second_token = strtok(NULL, delimiter);
//                tokens_count++;
//            } else {
//                //printf("%s\n", strcat(unary_sign_handled_string,
//                first_token)); strcat(unary_sign_handled_string, first_token);
//                strcat(unary_sign_handled_string, " ");
//                strcat(unary_sign_handled_string, second_token);
//                first_token = strtok(NULL, delimiter);
//                second_token = strtok(NULL, delimiter);
//                if (second_token != NULL) {
//                    strcat(unary_sign_handled_string, " ");
//                }
//                tokens_count++;
//            }
//    }
//    strcat(unary_sign_handled_string, " ");
//    strcat(unary_sign_handled_string, first_token);
//
//    // todo delete func bellow
////    int token_count_after = 0;
////    char* operate_string = strdup(unary_sign_handled_string);
////    char* curr_token = strtok(operate_string, delimiter);
////    while (curr_token != NULL) {
////        token_count_after++;
////        curr_token = strtok(NULL, delimiter);
////    }
////
////    printf("%d Total tokens\n",token_count_after);
//
//    return unary_sign_handled_string;
//}
char* unary_sign_handler(const char* input_string) {
  // Allocate memory for the handled string
  char* unary_sign_handled_string =
      (char*)calloc(strlen(input_string) * 3 + 1, sizeof(char));
  if (unary_sign_handled_string == NULL) {
    fprintf(stderr, "Memory allocation failed");
    return NULL;
  }

  const char* delimiter = " ";
  char* token = strtok((char*)input_string, delimiter);  // Get the first token
  char* prev_token = NULL;
  while (token != NULL) {
    if ((token[0] == '-' || token[0] == '+') &&
        (prev_token == NULL)) {  // Check for unary negative sign
      // Handle the unary sign by inserting '0' before the negative sign
      strcat(unary_sign_handled_string, "0 ");
      strcat(unary_sign_handled_string, token);
      prev_token = token;
    } else if ((token[0] == '-' || token[0] == '+') &&
               (prev_token[0] ==
                '(')) {  // Check for negative sign within parentheses
      // Handle the negative sign within parentheses by inserting '0' after the
      // opening parenthesis
      strcat(unary_sign_handled_string, " 0 ");
      strcat(unary_sign_handled_string, token);
      prev_token = token;
    } else {
      // Copy the token as is
      strcat(unary_sign_handled_string, token);
      prev_token = token;
    }

    // Append a space after each token
    strcat(unary_sign_handled_string, " ");

    // Get the next token
    token = strtok(NULL, delimiter);
  }

  return unary_sign_handled_string;
}
char* divided_by_tokens(char* string) {
  char* divided_str = (char*)calloc(MAX_LEN * 2 + 1, sizeof(char));
  if (string == NULL || divided_str == NULL) {
    return NULL;
  }

  memset(divided_str, '\0', MAX_LEN * 2 + 1);  // очищение массива

  for (char* ptr = string; *ptr != '\0'; ptr++) {
    char current_char = *ptr;
    char current_token[MAX_LEN] = {'\0'};
    int step = 0;

    if (current_char == '.' || strchr("1234567890", (int)current_char)) {
      bool is_exponent_notation = exponent_notation_handler(ptr);
      if (is_exponent_notation) {
        step = exponent_notation_length(ptr) - 1;  // шаг до след ключа
        strncpy(current_token, ptr, step + 1);
      } else {
        step = strspn(ptr, "1234567890.") - 1;  // // шаг до след ключа
        strncpy(current_token, ptr, step + 1);
      }
    } else if (current_char == 'e') {
    } else if (strchr(OPERATORS, (int)current_char) ||
               strchr("()", (int)current_char) || current_char == 'x') {
      strncpy(current_token, ptr, 1);
    } else if (strchr(FUNC_KEYS, (int)current_char)) {
      step = function_key_handler(ptr) - 1;
      strncpy(current_token, ptr, step + 1);
    }
    ptr += step;
    strcat(divided_str, current_token);
    strcat(divided_str, " ");
  }

  return unary_sign_handler(divided_str);
}

int exponent_notation_length(const char* string) {
  if (string == NULL) {
    return FAILURE;
  }

  bool has_sign = false;
  size_t real_part = strspn(string, "1234567890.");

  const char* exp_string = string + real_part + 1;
  if (*exp_string == '+' || *exp_string == '-') {
    has_sign = true;
    exp_string++;
  }
  size_t exp_part = strspn(exp_string, "1234567890");

  return (int)(real_part + has_sign + exp_part + 1);
}

bool exponent_notation_handler(char* string) {
  if (string == NULL) {
    return false;
  }

  bool is_exponent_notation = false;
  bool is_number_end = false;

  for (char* ptr = string; *ptr != '\0' && !is_number_end; ptr++) {
    if (*ptr == 'e') {
      is_exponent_notation = true;
    } else if (!strchr("1234567890.", (int)*ptr)) {
      is_number_end = true;
    }
  }

  return is_exponent_notation;
}

int function_key_handler(const char* ptr) {
  if (ptr == NULL) {
    return FAILURE;
  }

  int key_size = 0;
  char str_to_analyze[6] = {'\0'};
  strncat(str_to_analyze, ptr, 5);

  switch (*ptr) {
    case 'a':
      if (strstr(str_to_analyze, "asin") || strstr(str_to_analyze, "acos") ||
          strstr(str_to_analyze, "atan")) {
        key_size = 4;
      }
      break;
    case 'c':
      if (strstr(str_to_analyze, "cos")) {
        key_size = 3;
      }
      break;
    case 'l':
      if (strstr(str_to_analyze, "ln")) {
        key_size = 2;
      } else if (strstr(str_to_analyze, "log")) {
        key_size = 3;
      }
      break;
    case 'm':
      if (strstr(str_to_analyze, "mod")) {
        key_size = 3;
      }
      break;
    case 's':
      if (strstr(str_to_analyze, "sin")) {
        key_size = 3;
      } else if (strstr(str_to_analyze, "sqrt")) {
        key_size = 4;
      }
      break;
    case 't':
      if (strstr(str_to_analyze, "tan")) {
        key_size = 3;
      }
      break;
    default:
      break;
  }

  return key_size;
}
stack* convert_to_R_P_N(stack* token_stack) {
  stack* rpn_stack = createStack();
  stack* operator_stack = createStack();

  // Process each token in the input stack
  while (token_stack->top != NULL) {
    // Get the next token
    stack_element* current = pop(token_stack);
    int token_type = current->element_type; /* Determine the type of token
                                               (number, operator, etc.) */
    ;

    if (token_type == numb || token_type == x_value) {
      // If it's a number, push it onto the RPN stack
      push(rpn_stack, current->value, current->priority, current->element_type);
    } else if (token_type >= plus && token_type <= logarithm) {
      // If it's an operator, handle operator precedence
      while (operator_stack->top != NULL &&
             current->priority <= operator_stack->top->priority) {
        stack_element* op = pop(operator_stack);
        push(rpn_stack, op->value, op->priority, op->element_type);
      }
      // Push the current operator onto the operator stack
      push(operator_stack, current->value, current->priority,
           current->element_type);
      // push(operator_stack, token_value, get_operator_priority(/* Get the
      // operator from the token */), /* Set the element type for operators */);
    } else if (token_type == open_brackets) {
      // Push it onto the operator stack
      push(operator_stack, current->value, current->priority,
           current->element_type);
    } else if (token_type == close_brackets) {
      // Pop operators from the operator stack until an opening parenthesis is
      // encountered
      while (operator_stack->top != NULL &&
             operator_stack->top->element_type != open_brackets) {
        stack_element* op = pop(operator_stack);
        push(rpn_stack, op->value, op->priority, op->element_type);
        // push(rpn_stack, op, op_priority, /* Set the element type for
        // operators */);
      }
      // Pop the opening parenthesis
      pop(operator_stack);
    }
  }

  // Pop any remaining operators from the operator stack
  while (operator_stack->top != NULL) {
    stack_element* op = pop(operator_stack);
    push(rpn_stack, op->value, op->priority, op->element_type);
    // push(rpn_stack, op, op_priority, /* Set the element type for operators
    // */);
  }

  // Return the RPN stack
  return reverse_stack(rpn_stack);
}
// stack* convert_to_R_P_N(stack* s) {
//     stack* output_stack = createStack();
//     stack* operator_stack = createStack();
//
//     stack_element* current = s->top;
//
//     while (current != NULL) {
//         if (current->element_type == numb || current->element_type ==
//         x_value) {
//             push_element(output_stack, current);
//         } else if (current->element_type >= open_brackets &&
//         current->element_type <= logarithm) {
//             while (operator_stack->top != NULL &&
//             operator_stack->top->priority >= current->priority) {
//                 push_element(output_stack, pop(operator_stack));
//             }
//             push_element(operator_stack, current);
//         } else if (current->element_type == close_brackets) {
//             while (operator_stack->top != NULL &&
//             operator_stack->top->element_type != open_brackets) {
//                 push_element(output_stack, pop(operator_stack));
//             }
//             if (operator_stack->top != NULL &&
//             operator_stack->top->element_type == open_brackets) {
//                 pop(operator_stack);
//             }
//         }
//         current = current->next;
//     }
//
//     while (operator_stack->top != NULL) {
//         push_element(output_stack, pop(operator_stack));
//     }
//
//     freeStack(operator_stack);  // Free the memory allocated for the operator
//     stack
//
//     return output_stack;
// }
// stack* convert_to_R_P_N(stack* s) {
//     stack* output_stack = createStack();
//     stack* operator_stack = createStack();
//
//     stack_element* current = s->top;
//
//     while (current != NULL) {
//         if (current->element_type == numb || current->element_type ==
//         x_value) {
//             push(output_stack,current->value,current->priority,current->element_type);
//         } else if (current->element_type >= open_brackets &&
//         current->element_type <= logarithm) {
//             while (operator_stack->top != NULL &&
//             operator_stack->top->priority >= current->priority) {
//                 push_element(output_stack,pop(operator_stack));
//             }
//             push_element(operator_stack,current);
//         } else if (current->element_type == close_brackets) {
//             while (operator_stack->top != NULL &&
//             operator_stack->top->element_type != open_brackets) {
//                 push_element(output_stack,pop(operator_stack));
//             }
//             if (operator_stack->top != NULL &&
//             operator_stack->top->element_type == open_brackets) {
//                 pop(operator_stack);
//
//             }
//         }
//         current = current->next;
//     }
//
//     while (operator_stack->top != NULL) {
//         push_element(output_stack,pop(operator_stack));
//     }
//
//     free(operator_stack);  // Free the memory allocated for the operator
//     stack
//
//     return output_stack;
// }
