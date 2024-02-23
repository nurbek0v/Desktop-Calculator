#ifndef S21_CALCULATOR_H
#define S21_CALCULATOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define MAX_LEN 255
#define OPERANDS "1234567890mcstalx.("
#define FUNC_KEYS "mcstal"
#define OPERATORS "+-*/^"
#define SUCCESS 1
#define FAILURE 0

typedef struct stack_element {
  double value;
  int priority;
  int element_type;
  struct stack_element* next;
} stack_element;

typedef struct stack {
  struct stack_element* top;
} stack;
enum priority { undef, zero, one, two, three, four };

enum element_type {
  numb,               // = 0
  x_value,            // =1
  open_brackets,      // 2
  close_brackets,     // 3
  plus,               // 4
  minus,              // 5
  multiply,           // 6
  divide,             // 7
  degree,             // 8
  mod_sign,           // 9
  cosine,             // 10
  sine,               // 11
  tangent,            // 12
  arc_cosine,         // 13
  arc_sine,           // 14
  arc_tangent,        // 15
  sqrt_sign,          // 16
  natural_logarithm,  // ln // 17
  logarithm           // log //  18
};
enum error_type {
  no_error,
  dividing_by_zero,
  negative_sqrt,
  negative_ln,
  negative_log,
  undef_error,
  invalid_input
};

stack* createStack();
int isEmpty(stack* s);
void push(stack* s, double value, int priority, int element_type);
void push_element(stack* s, stack_element* element);  // todo
stack_element* pop(stack* s);
stack* reverse_stack(stack* s);  // todo
double top(stack* s);
void print_stack(const stack* s);
void print_stack_in_line(const stack* s);  // todo
stack_element* peek_st_element(stack* s);  // todo
void freeStack(stack* s);

// validation input string
void remove_spaces(
    char* string);  // don't forget to use before "is_valid_input" function and
                    // also don't forget to free!
bool is_valid_input(char* string);     // main func for validation
bool is_valid_brackets(char* string);  // done
bool is_valid_character(char c);       // done
bool is_valid_number(char c);          // done
bool is_dot_valid(char* string);       // done
int handle_character(char* ptr);       // done
int handle_exponent(char* string);     // done

// Parsing String into stack by math elements
char* divided_by_tokens(
    char* string);  // Разделяет математические элементы пробелом в строке
int exponent_notation_length(const char* str);
bool exponent_notation_handler(char* str);
int function_key_handler(const char* ptr);
char* unary_sign_handler(const char* input_string);
stack* convert_to_R_P_N(stack* s);                  // todo
int get_operator_priority(stack_element* element);  // todo

stack* parsing_elements(char* string);              // todo
char* scientificToMath(const char* scientificStr);  // todo dont forget to free
double convert_str_to_double(char* str);            //

// Helpers
void missing_multiply_signs_handler(char* string);  // todo
void add_end_of_line_to(char* str);                 // todo

// calculation
// double calculate(stack* s); // todo
double calculate(stack* s, enum error_type* error);
void replace_xValue_in_stack(stack* s, double x);  // todo

// Loan Calculation
double convert_years_to_month(double years);
double overpayment(long double loan_amount, long double total_payment);
long double monthly_payment_annuity(long double loan_amount,
                                    long double interest_rate, double term);
long double total_payment_annuity(long double annuity, double term);
long double total_payment_differentiated(long double loan_amount, double term,
                                         long double interest_rate);
long double monthly_payment_differentiated(long double total_payment,
                                           double term);

// Deposit calculator
enum mode { MONTHLY, YEARLY };
long double get_total_earned(long double* deposit_amount, double term,
                             long double interest_rate, int MODE,
                             bool is_capitalization, long double replenishments,
                             long double withdraws);
long double get_tax_amount(long double total_amount, long double tax_rate);
long double get_total_amount(long double deposit_amount,
                             long double earned_money, long double tax_amount);

// controller Functions
bool contains_x_val(stack* s);  // todo
enum error_type calculate_usual(const char* string,
                                long double* result);  // todo
enum error_type calculate_with_x_value(const char* string, long double x,
                                       long double* result);  // todo
#ifdef __cplusplus
}
#endif
#endif  // S21_CALCULATOR_H