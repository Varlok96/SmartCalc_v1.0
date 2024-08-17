#include "calc.h"

int priority(char elem) {
  int priority = 0;
  switch (elem) {
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case 'k':
    case 's':  // sin
    case 'c':  // cos
    case 't':  // tg
    case 'S':  // asin
    case 'C':  // acos
    case 'T':  // atg
    case 'l':  // ln
    case 'L':  // log
      priority = 4;
      break;
  }
  return priority;
}

void pars(char *infix, char *postfix) {
  int i = 0, j = 0, tmp_priority = 0;
  Node_t *list = NULL;
  while (infix[i]) {
    char trigonometric_elem = 0;
    if (infix[i] == '(') {
      push(&list, infix[i]);
      list->priority = priority(infix[i++]);
      continue;
    }
    if (is_digit(infix[i])) {
      postfix[j++] = infix[i++];
      while (is_digit(infix[i])) {
        postfix[j++] = infix[i++];
      }
      postfix[j++] = ' ';
      continue;
    }
    if (infix[i] == ')') {
      while (list) {
        if (list->value == '(') {
          pop(&list);
          break;
        }
        postfix[j++] = pop(&list), postfix[j++] = ' ';
      }
    }
    if (is_operand(infix[i])) {
      tmp_priority = priority(infix[i]);
      if ((i == 0 && infix[i] == '-') ||
          (infix[i - 1] == '(' && infix[i] == '-')) {
        postfix[j++] = '0', postfix[j++] = ' ';
      }
      if (list) {
        if (tmp_priority < list->priority) {
          while (list) {
            if (list->value == '(') {
              break;
            }
            postfix[j++] = pop(&list), postfix[j++] = ' ';
          }
        } else if (tmp_priority == list->priority && list->value != '(') {
          postfix[j++] = pop(&list), postfix[j++] = ' ';
        }
      }
      trigonometric_elem = trigonometric(infix, &i);
      push(&list, trigonometric_elem);
      list->priority = tmp_priority;
    }
    i++;
  }
  while (list) {
    postfix[j++] = pop(&list), postfix[j++] = ' ';
  }
}

char trigonometric(char *infix, int *i) {
  char result = infix[*i];
  if (infix[*i] == 's') {
    if (infix[*i + 1] == 'i') {
      result = 's', *i += 2;
    } else {
      result = 'k', *i += 3;
    }
  } else if (infix[*i] == 'c') {
    result = 'c', *i += 2;
  } else if (infix[*i] == 't') {
    *i += 1, result = 't';
  } else if (infix[*i] == 'l') {
    if (infix[*i + 1] == 'o') {
      result = 'L', *i += 2;
    } else {
      *i += 1, result = 'l';
    }
  } else if (infix[*i] == 'a') {
    if (infix[*i + 1] == 's') {
      *i += 3, result = 'S';
    } else if (infix[*i + 1] == 'c') {
      result = 'C', *i += 3;
    } else if (infix[*i + 1] == 't') {
      *i += 2, result = 'T';
    }
  }
  return result;
}

int is_digit(char infix) {
  int result = 0;
  if ((infix >= 48 && infix <= 57) || infix == 46 || infix == 120 ||
      infix == 44) {
    result = 1;
  }
  return result;
}

int is_operand(char infix) {
  int result = 0;
  char *str = "+-*/%^ksctal";
  char *ach = NULL;
  ach = strchr(str, infix);
  if (ach != NULL) {
    result = 1;
  }
  return result;
}

int math_operations(double x, char *postfix, double *res) {
  Node_n *stack = NULL;
  int error = 0, i = 0, j = 0;
  double r1 = 0.0, r2 = 0.0, result = 0.0;
  char *operand = "+-*/%^";
  char *trigonometric = "sctSCTlLk";
  while (postfix[i] != '\0') {
    char c1[255] = {0};
    r1 = 0.0;
    r2 = 0.0;
    if (postfix[i] == 'x') {
      push_n(&stack, x);
      i++;
      continue;
    }
    if (is_digit(postfix[i])) {
      j = 0;
      while (postfix[i] != ' ') {
        c1[j++] = postfix[i++];
      }
      push_n(&stack, digit_reform(c1));
    }
    if (strchr(operand, postfix[i])) {
      r2 = pop_n(&stack);
      if (stack) {
        r1 = pop_n(&stack);
      } else {
        r1 = r2, r2 = 0.0;
      }
      result = 0.0;
      error = result_operand(postfix[i], r1, r2, &result);
      push_n(&stack, result);
    }
    if (strchr(trigonometric, postfix[i])) {
      r1 = pop_n(&stack);
      push_n(&stack, result_trigonometric(postfix[i], r1));
    }
    i++;
  }
  *res = pop_n(&stack);
  return error;
}

int result_operand(char postfix, double r1, double r2, double *result) {
  int error = 0;
  switch (postfix) {
    case '+':
      *result = r1 + r2;
      break;
    case '-':
      *result = r1 - r2;
      break;
    case '*':
      *result = r1 * r2;
      break;
    case '/':
      *result = r1 / r2;
      if (r2 == 0) {
        error = 1;
      }
      break;
    case '%':
      *result = fmod(r1, r2);
      break;
    case '^':
      *result = pow(r1, r2);
      break;
  }
  return error;
}

double result_trigonometric(char postfix, double r1) {
  double result = 0;
  switch (postfix) {
    case 's':  // sin
      result = sin(r1);
      break;
    case 'c':  // cos
      result = cos(r1);
      break;
    case 't':  // tan
      result = tan(r1);
      break;
    case 'S':  // asin
      result = asin(r1);
      break;
    case 'C':  // acos
      result = acos(r1);
      break;
    case 'T':  // atg
      result = atan(r1);
      break;
    case 'l':  // log
      result = log(r1);
      break;
    case 'L':  // log10
      result = log10(r1);
      break;
    case 'k':  // sqrt
      result = sqrt(r1);
      break;
  }
  return result;
}

double digit_reform(char *c1) {
  double digit = 0.0;
  int flag_digit = 1;
  int n = 0;
  int m = 0;
  while (c1[n] != '\0') {
    if (c1[n] == ',' || c1[n] == '.') {
      flag_digit = 0;
      n++;
      continue;
    }
    if (flag_digit) {
      digit = digit * 10 + (c1[n] - 48);
    } else {
      digit = digit + (c1[n] - 48) / pow(10, m + 1);
      m++;
    }
    n++;
  }
  return digit;
}