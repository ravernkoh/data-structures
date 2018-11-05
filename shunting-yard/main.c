#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX_STACK_SIZE 50
#define MAX_TOKEN_NUM 50
#define MAX_LITERAL_LENGTH 50
#define MAX_INPUT_LENGTH 100

typedef int token_kind_t;
const token_kind_t TOKEN_INVALID = 0;
const token_kind_t TOKEN_OP = 1;
const token_kind_t TOKEN_NUM = 2;

typedef int op_t;
const op_t OP_ADD = 1;
const op_t OP_SUB = 2;
const op_t OP_MUL = 3;
const op_t OP_DIV = 4;

// Display the op.
const char *op_disp(op_t op) {
  switch (op) {
  case OP_ADD:
    return "+";
  case OP_SUB:
    return "-";
  case OP_MUL:
    return "*";
  case OP_DIV:
    return "/";
  }
  return "INVALID";
}

typedef union {
  op_t op;
  int num;
} token_value_t;

// Creates a new op value.
token_value_t token_value_make_op(op_t op) {
  token_value_t v;
  v.op = op;
  return v;
}

// Creates a new num value.
token_value_t token_value_make_num(int num) {
  token_value_t v;
  v.num = num;
  return v;
}

typedef union {
  token_kind_t kind;
  token_value_t value;
} token_t;

// Creates a new token.
token_t token_make(token_kind_t kind, token_value_t value) {
  token_t t;
  t.kind = kind;
  t.value = value;
  return t;
}

// Creates a new invalid token.
token_t token_make_invalid() {
  token_t t;
  t.kind = TOKEN_INVALID;
  return t;
}

// Displays the token.
const char *token_disp(token_t t) {
  switch (t.kind) {
  case TOKEN_OP:
    return op_disp(t.value.op);
  case TOKEN_NUM: {
    char *num = (char *)malloc(sizeof(char) * MAX_LITERAL_LENGTH);
    sprintf(num, "%i", t.value.num);
    return num;
  }
  }
  return "INVALID";
}

typedef struct {
  const char *source;
  char *literal;
} scanner_t;

// Creates a new scanner.
scanner_t *scanner_make(const char *source) {
  scanner_t *t = (scanner_t *)malloc(sizeof(scanner_t));
  t->source = source;
  t->literal = NULL;
  return t;
}

// Peek the source at the current char.
char scanner_peek(scanner_t *t) { return *t->source; }

// Advance the source to the next char.
void scanner_advance(scanner_t *t) { t->source = &t->source[1]; }

// Returns the next token.
token_t scanner_next(scanner_t *t) {
  if (scanner_peek(t) == '\0') {
    return token_make_invalid();
  }
  return token_make(TOKEN_OP, token_value_make_op(OP_ADD));
}

int main() {
  while (TRUE) {
    printf("> ");

    // Read in the source.
    char source[MAX_INPUT_LENGTH];
    fgets(source, MAX_INPUT_LENGTH, stdin);
    source[strlen(source) - 1] = '\0';

    // Create the scanner around the source.
    scanner_t *t = scanner_make(source);
    printf("%s\n", token_disp(scanner_next(t)));
  }

  return 0;
}
