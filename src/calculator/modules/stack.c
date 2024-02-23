#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_calculator.h"

// Function to create a new stack
stack* createStack() {
  stack* newStack = (stack*)malloc(sizeof(stack));
  newStack->top = NULL;
  return newStack;
}

// Function to check if the stack is empty
int isEmpty(stack* s) { return (s->top == NULL); }

// Function to push a new element onto the stack
void push(stack* s, double value, int priority, int element_type) {
  stack_element* newElement = (stack_element*)malloc(sizeof(stack_element));

  newElement->value = value;
  newElement->priority = priority;
  newElement->element_type = element_type;
  newElement->next = s->top;
  s->top = newElement;
}
// void push_element(stack* s, stack_element* element) {
//     stack_element* newElement =
//     (stack_element*)malloc(sizeof(stack_element));
//
//     newElement->value = element->value;
//     newElement->priority = element->priority;
//     newElement->element_type = element->element_type;
//     newElement->next = s->top;
//     s->top = newElement;
// }

// Function to pop the top element from the stack
stack_element* pop(stack* s) {
  if (s == NULL || s->top == NULL) {
    return NULL;
  }

  stack_element* topElement = s->top;  // Сохраняем указатель на верхний элемент
  s->top = s->top->next;  // Перемещаем указатель на следующий элемент в стеке
  topElement->next = NULL;  // Отсоединяем верхний элемент от стека

  return topElement;  // Возвращаем удаленный верхний элемент стека
}
// void print_stack(const stack* s) {
//     stack_element* current = s->top;
//     printf("Printing Stack Elements ->>>>:\n");
//     while (current != NULL) {
//         printf("Value: %f, Priority: %d, Element Type: %d\n", current->value,
//         current->priority, current->element_type); current = current->next;
//     }
// }
// void print_stack_in_line(const stack* s) {
//     stack_element* current = s->top;
//     printf("Printing Stack Elements ->>>:\n");
//     while (current != NULL) {
//         enum element_type type = current->element_type;
//        // char str[256*3];
//         char* str = (char*)calloc(MAX_LEN * 2 + 1, sizeof(char));
//         memset(str, '\0', MAX_LEN * 2 + 1); // очищение массива
//
//         if (type == numb) {
//             sprintf(str, "%.f", current->value);
//         } else if (type == x_value) {
//             strcat(str,"x");
//         } else if (type == plus) {
//             strcat(str,"+");
//         } else if (type == minus) {
//             strcat(str,"-");
//         } else if (type == open_brackets) {
//             strcat(str,"(");
//         } else if (type == close_brackets) {
//             strcat(str,")");
//         } else if (type == multiply) {
//             strcat(str,"*");
//         } else if (type == divide) {
//             strcat(str,"/");
//         } else if (type == degree) {
//             strcat(str,"^");
//         } else if (type == mod_sign) {
//             strcat(str,"mod");
//         } else if (type == cosine) {
//             strcat(str,"cos");
//         } else if (type == sine) {
//             strcat(str,"sin");
//         } else if (type == tangent) {
//             strcat(str,"tan");
//         } else if (type == arc_cosine) {
//             strcat(str,"acos");
//         } else if (type == arc_sine) {
//             strcat(str,"asin");
//         } else if (type == arc_tangent) {
//             strcat(str,"atan");
//         } else if (type == sqrt_sign) {
//             strcat(str,"sqrt");
//         } else if (type == natural_logarithm) {
//             strcat(str,"ln");
//         } else if (type == logarithm) {
//             strcat(str,"log");
//         }
//         printf("%s ", str);
//         current = current->next;
//         free(str);
//     }
//     printf("\n");
// }
stack* reverse_stack(stack* s) {
  stack* reversed_stack = (stack*)malloc(sizeof(stack));
  reversed_stack->top = NULL;

  stack_element* prev = NULL;
  stack_element* current = s->top;
  stack_element* next;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  reversed_stack->top = prev;  // Update the top of the reversed stack

  return reversed_stack;  // Return the reversed stack
}

// Function to get the value of the top element of the stack
// double top(stack* s) {
//    if (isEmpty(s)) {
//        return -1; // Return some error value
//    } else {
//        return s->top->value;
//    }
//}
// stack_element* peek_st_element(stack* s) {
//    if (s == NULL || s->top == NULL) {
//        return NULL;
//    }
//    return s->top;
//}
void freeStack(stack* s) {
  while (s->top != NULL) {
    stack_element* temp = s->top;
    s->top = s->top->next;
    free(temp);
  }
  // Optionally, free the stack structure itself if dynamically allocated
  free(s);
}