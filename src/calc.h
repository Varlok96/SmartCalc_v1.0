#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_tag {
  char value;
  int priority;
  struct Node_tag *next;
} Node_t;

typedef struct Node_num {
  double value;
  struct Node_num *next;
} Node_n;

int priority(char elem);
void pars(char *infix, char *postfix);
int is_digit(char infix);
int is_operand(char infix);
void push(Node_t **head, char value);
char pop(Node_t **head);
void push_n(Node_n **head, double value);
double pop_n(Node_n **head);
char trigonometric(char *infix, int *i);
int math_operations(double x, char *postfix, double *res);
int result_operand(char postfix, double r1, double r2, double *result);
double result_trigonometric(char postfix, double r1);
double digit_reform(char *c1);