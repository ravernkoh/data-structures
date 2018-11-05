#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define MAX_STACK_SIZE 50
#define MAX_TOKEN_NUM 50
#define MAX_LITERAL_LENGTH 50
#define MAX_INPUT_LENGTH 100
#define MAX_ERROR_LENGTH 50

bool is_digit(char c) { return c >= '0' && c <= '9'; }
bool is_space(char c) { return c == '\t' || c == ' '; }

typedef int token_kind_t;
const token_kind_t TOKEN_END = 0;
const token_kind_t TOKEN_OP = 1;
const token_kind_t TOKEN_NUM = 2;

typedef char op_t;
const op_t OP_ADD = '+';
const op_t OP_SUB = '-';
const op_t OP_MUL = '*';
const op_t OP_DIV = '/';

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

typedef struct {
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
token_t token_make_end() {
  token_t t;
  t.kind = TOKEN_END;
  return t;
}

// Displays the token.
const char *token_disp(token_t t) {
  switch (t.kind) {
  case TOKEN_OP: {
    char *op = (char *)malloc(sizeof(char) * 4);
    sprintf(op, "%c", t.value.op);
    return op;
  }
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
  char *error;
  char *literal;
} scanner_t;

// Creates a new scanner.
scanner_t *scanner_make(const char *source) {
  scanner_t *s = (scanner_t *)malloc(sizeof(scanner_t));
  s->source = source;
  s->literal = (char *)malloc(sizeof(char) * MAX_LITERAL_LENGTH);
  s->error = NULL;
  return s;
}

// Peek the source at the current char.
char scanner_peek(scanner_t *s) { return *s->source; }

// Advance the source to the next char.
void scanner_advance(scanner_t *s) { s->source = &s->source[1]; }

// Returns the next number token.
token_t scanner_next_number(scanner_t *s) {
  int len = 0;

  while (TRUE) {
    char peek = scanner_peek(s);
    if (!is_digit(peek)) {
      break;
    }

    s->literal[len++] = peek;
    scanner_advance(s);
  }
  s->literal[len] = '\0';

  return token_make(TOKEN_NUM, token_value_make_num(atoi(s->literal)));
}

// Returns the next token.
token_t scanner_next(scanner_t *s) {
  while (TRUE) {
    char peek = scanner_peek(s);

    // Check for end or whitespace.
    if (peek == '\0') {
      return token_make_end();
    } else if (is_space(peek)) {
      scanner_advance(s);
      continue;
    }

    // Check for number.
    if (is_digit(peek)) {
      return scanner_next_number(s);
    }

    // Check for operators.
    if (peek == OP_ADD) {
      scanner_advance(s);
      return token_make(TOKEN_OP, token_value_make_op(OP_ADD));
    } else if (peek == OP_SUB) {
      scanner_advance(s);
      return token_make(TOKEN_OP, token_value_make_op(OP_SUB));
    } else if (peek == OP_MUL) {
      scanner_advance(s);
      return token_make(TOKEN_OP, token_value_make_op(OP_MUL));
    } else if (peek == OP_DIV) {
      scanner_advance(s);
      return token_make(TOKEN_OP, token_value_make_op(OP_DIV));
    }

    s->error = (char *)malloc(sizeof(char) * MAX_ERROR_LENGTH);
    sprintf(s->error, "unexpected char '%c'", peek);
    return token_make_end();
  }
}

int main() {
  while (TRUE) {
    printf("> ");

    // Read in the source.
    char source[MAX_INPUT_LENGTH];
    fgets(source, MAX_INPUT_LENGTH, stdin);
    source[strlen(source) - 1] = '\0';

    // Create the scanner around the source.
    scanner_t *s = scanner_make(source);
    while (TRUE) {
      token_t t = scanner_next(s);
      if (t.kind == TOKEN_END) {
        break;
      }
      printf("%s\n", token_disp(t));
    }

    // Check for scanner error.
    if (s->error != NULL) {
      printf("error: %s\n", s->error);
    }
  }
}
