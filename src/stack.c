#include "calc.h"

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

void push(Node_t **head, char value) {
  Node_t *tmp = malloc(sizeof(Node_t));
  if (tmp == NULL) {
    exit(STACK_OVERFLOW);
  }
  tmp->next = *head;
  tmp->value = value;
  *head = tmp;
}

char pop(Node_t **head) {
  Node_t *out;
  char value;
  if (*head == NULL) {
    exit(STACK_UNDERFLOW);
  }
  out = *head;
  *head = (*head)->next;
  value = out->value;
  free(out);
  return value;
}

void printStack(const Node_n *head) {
  printf("stack >");
  while (head) {
    printf("%lf ", head->value);
    head = head->next;
  }
}

void push_n(Node_n **head, double value) {
  Node_n *tmp = malloc(sizeof(Node_n));
  if (tmp == NULL) {
    exit(STACK_OVERFLOW);
  }
  tmp->next = *head;
  tmp->value = value;
  *head = tmp;
}

double pop_n(Node_n **head) {
  Node_n *out;
  double value;
  if (*head == NULL) {
    exit(STACK_UNDERFLOW);
  }
  out = *head;
  *head = (*head)->next;
  value = out->value;
  free(out);
  return value;
}