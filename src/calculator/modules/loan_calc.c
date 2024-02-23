#include <math.h>

#include "../s21_calculator.h"

/*Формула расчета аннуитетного платежа
Х = С * К
где X — аннуитетный платеж,
С — сумма кредита,
К — коэффициент аннуитета.
Коэффициент аннуитета считается так:
К = (М * (1 + М) ^ S) / ((1 + М) ^ S — 1)
где М — месячная процентная ставка по кредиту,
S — срок кредита в месяцах.
Допустим, вы берете в кредит 2 млн ₽ на 5 лет по ставке 15% годовых. Сначала
подсчитаем коэффициент аннуитета. К = (0,0125 * (1 + 0,0125) ^ 60) / ((1 +
0,0125) ^ 60 — 1) Получаем коэффициент 0,02379. Подставляем значения в формулу:
Х = 2 000 000 * К
Получаем ежемесячный платеж, равный 47 580 ₽.
 */

long double monthly_payment_annuity(long double loan_amount,
                                    long double interest_rate, double term) {
  long double monthly_interest = interest_rate / 12 / 100;
  long double annuity_coefficiant = monthly_interest *
                                    pow(1 + monthly_interest, term) /
                                    (pow(1 + monthly_interest, term) - 1);
  long double annuity = annuity_coefficiant * loan_amount;
  return annuity;
}
long double total_payment_annuity(long double annuity, double term) {
  return annuity * term;
}
long double monthly_payment_differentiated(long double total_payment,
                                           double term) {
  return total_payment / term;
}

long double total_payment_differentiated(long double loan_amount, double term,
                                         long double interest_rate) {
  long double payment_without_rate = loan_amount / term;
  long double total_payment = 0;

  for (int month = 0; month < term; month++) {
    long double remainder = loan_amount - (payment_without_rate * month);
    long double interest_payment = remainder * (interest_rate / 100 / 12);
    long double monthly_payment = payment_without_rate + interest_payment;
    total_payment += monthly_payment;
  }
  return total_payment;
}
double overpayment(long double loan_amount, long double total_payment) {
  return total_payment - loan_amount;
}
double convert_years_to_month(double years) { return years * 12; }
