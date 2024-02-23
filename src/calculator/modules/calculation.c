#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_calculator.h"

void replace_xValue_in_stack(stack* s, double x) {
  stack_element* current = s->top;

  while (current != NULL) {
    if (current->element_type == x_value) {
      current->value = x;
      current->element_type = numb;
    }
    current = current->next;
  }
}

// double calculate(stack* s) {
//     stack* calc_stack = createStack();
//     int error  = 0;
//
//     // Process each element in the stack
//     while (s->top != NULL) {
//         stack_element* current = pop(s);
//         int token_type = current->element_type;
//         double result = 0.0;
//
//         // If the element is a number or x_value, push it onto the
//         calculation stack if (token_type == numb || token_type == x_value) {
//             push(calc_stack, current->value, current->priority,
//             current->element_type);
//         }
//             // If the element is an operator, perform the operation
//         else {
//             // Check if the calculation stack has enough elements
//             if (calc_stack->top == NULL) {
//                 //printf("Error: Not enough operands.\n");
//                 error = 1;
//                 break;
//             }
//
//             // For binary operators, pop two elements from the calculation
//             stack if (token_type >= plus && token_type <= mod_sign) {
//                 double operand2 = pop(calc_stack)->value;
//                 double operand1 = pop(calc_stack)->value;
//
//                 switch (token_type) {
//                     case plus:
//                         result = operand1 + operand2;
//                         break;
//                     case minus:
//                         result = operand1 - operand2;
//                         break;
//                     case multiply:
//                         result = operand1 * operand2;
//                         break;
//                     case divide:
//                         if (operand2 != 0) {
//                             result = operand1 / operand2;
//                         } else {
//                             printf("Error: Division by zero.\n");
//                             exit(1);
//                         }
//                         break;
//                     case degree:
//                         result = pow(operand1, operand2);
//                         break;
//                     case mod_sign:
//                         result = fmod(operand1, operand2);
//                         break;
//                     default:
//                         printf("Error: Unknown binary operation.\n");
//                         exit(1);
//                 }
//             } else if (token_type > mod_sign) {
//                 double operand = pop(calc_stack)->value;
//
//                 switch (token_type) {
//                     case cosine:
//                         result = cos(operand);
//                         break;
//                     case sine:
//                         result = sin(operand);
//                         break;
//                     case tangent:
//                         result = tan(operand);
//                         break;
//                     case arc_cosine:
//                         result = acos(operand);
//                         break;
//                     case arc_sine:
//                         result = asin(operand);
//                         break;
//                     case arc_tangent:
//                         result = atan(operand);
//                         break;
//                     case sqrt_sign:
//                         if (operand >= 0) {
//                             result = sqrt(operand);
//                         } else {
//                             printf("Error: Square root of negative
//                             number.\n"); exit(1);
//                         }
//                         break;
//                     case natural_logarithm:
//                         if (operand > 0) {
//                             result = log(operand);
//                         } else {
//                             printf("Error: Logarithm of non-positive
//                             number.\n"); exit(1);
//                         }
//                         break;
//                     case logarithm:
//                         if (operand > 0) {
//                             result = log10(operand);
//                         } else {
//                             printf("Error: Logarithm of non-positive
//                             number.\n"); exit(1);
//                         }
//                         break;
//                     default:
//                         printf("Error: Unknown unary operation.\n");
//                         exit(1);
//                 }
//             }
//
//             // Push the result onto the calculation stack
//             push(calc_stack, result, undef, numb);
//         }
//     }
//
//     // If the calculation stack is empty, there's been an error
//     if (calc_stack->top == NULL) {
//         printf("Error: Stack underflow.\n");
//         exit(1);
//     }
//
//     // The final result is the last element on the calculation stack
//     return pop(calc_stack)->value;
// }
double calculate(stack* s, enum error_type* error) {
  stack* calc_stack = createStack();
  enum error_type err = no_error;
  double final_result = 0.0;

  while (s->top != NULL) {
    stack_element* current = pop(s);
    int token_type = current->element_type;
    double result = 0.0;

    if (token_type == numb || token_type == x_value) {
      push(calc_stack, current->value, current->priority,
           current->element_type);
    } else {
      //            if (calc_stack->top == NULL) {
      //                err = undef_error;
      //                break;
      //            }

      if (token_type >= plus && token_type <= mod_sign) {
        double operand2 = pop(calc_stack)->value;
        double operand1 = pop(calc_stack)->value;

        switch (token_type) {
          case plus:
            result = operand1 + operand2;
            break;
          case minus:
            result = operand1 - operand2;
            break;
          case multiply:
            result = operand1 * operand2;
            break;
          case divide:
            if (operand2 != 0) {
              result = operand1 / operand2;
            } else {
              err = dividing_by_zero;
              break;
            }
            break;
          case degree:
            result = pow(operand1, operand2);
            break;
          case mod_sign:
            result = fmod(operand1, operand2);
            break;
        }
      } else if (token_type > mod_sign) {
        double operand = pop(calc_stack)->value;

        switch (token_type) {
          case cosine:
            result = cos(operand);
            break;
          case sine:
            result = sin(operand);
            break;
          case tangent:
            result = tan(operand);
            break;
          case arc_cosine:
            result = acos(operand);
            break;
          case arc_sine:
            result = asin(operand);
            break;
          case arc_tangent:
            result = atan(operand);
            break;
          case sqrt_sign:
            if (operand >= 0) {
              result = sqrt(operand);
            } else {
              err = negative_sqrt;
            }
            break;
          case natural_logarithm:
            if (operand > 0) {
              result = log(operand);
            } else {
              err = negative_ln;
            }
            break;
          case logarithm:
            if (operand > 0) {
              result = log10(operand);
            } else {
              err = negative_log;
            }
            break;
            //                    default:
            //                        err = undef_error;
            //                        break;
        }
      }

      if (err != no_error && error != NULL) {
        *error = err;
        break;
      }
      push(calc_stack, result, undef, numb);
    }
  }

  if (err != no_error || calc_stack->top == NULL) {
    printf("Error occurred during calculation.\n");
    // Clean up and free resources if needed
  } else {
    final_result = pop(calc_stack)->value;
  }

  // Clean up and free resources if needed

  return final_result;
}
