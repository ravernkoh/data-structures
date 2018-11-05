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
const token_kind_t TOKEN_OP = 1;
const token_kind_t TOKEN_NUM = 2;

typedef int op_t;
const op_t OP_ADD = 1;
const op_t OP_SUB = 2;
const op_t OP_MUL = 3;
const op_t OP_DIV = 4;

typedef union {
  int op;
  int num;
} token_value_t;

typedef union {
  token_kind_t kind;
  token_value_t value;
} token_t;

typedef struct {
  const char *source;
  char *literal;
} scanner_t;

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
token_t *scanner_next(scanner_t *t) {
  if (scanner_peek(t) == '\0') {
    return NULL;
  }
  return NULL;
}

int main() {
  while (TRUE) {
    printf("> ");

    // Read in the source.
    char source[MAX_INPUT_LENGTH];
    fgets(source, MAX_INPUT_LENGTH, stdin);
    source[strlen(source) - 1] = '\0';

    scanner_t *t = scanner_make(source);
    printf("%d\n", scanner_next(t));
  }

  return 0;
}
