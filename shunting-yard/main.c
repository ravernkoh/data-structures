#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define MAX_STACK_LEN 20
#define MAX_LITERAL_LEN 20
#define MAX_INPUT_LEN 200
#define MAX_ERROR_LEN 30

bool is_digit(char c) { return c >= '0' && c <= '9'; }
bool is_space(char c) { return c == '\t' || c == ' '; }

////////////////////////////
////////// TOKEN ///////////
////////////////////////////

typedef int op_assoc_t;
const op_assoc_t OP_ASSOC_ERROR = 0;
const op_assoc_t OP_ASSOC_LEFT = 1;
const op_assoc_t OP_ASSOC_RIGHT = 2;

typedef char op_kind_t;
const op_kind_t OP_ERROR = 0;
const op_kind_t OP_ADD = '+';
const op_kind_t OP_SUB = '-';
const op_kind_t OP_MUL = '*';
const op_kind_t OP_DIV = '/';
const op_kind_t OP_POW = '^';

int op_prec(op_kind_t op) {
  switch (op) {
  case OP_ADD:
  case OP_SUB:
    return 1;
  case OP_MUL:
  case OP_DIV:
    return 2;
  case OP_POW:
    return 3;
  }
  return 0;
}

op_assoc_t op_assoc(op_kind_t op) {
  switch (op) {
  case OP_ERROR:
  case OP_ADD:
  case OP_SUB:
  case OP_MUL:
  case OP_DIV:
    return OP_ASSOC_LEFT;
  case OP_POW:
    return OP_ASSOC_RIGHT;
  }
  return 0;
}

typedef int token_kind_t;
const token_kind_t TOKEN_ERROR = 0;
const token_kind_t TOKEN_OP = 1;
const token_kind_t TOKEN_NUM = 2;

typedef union {
  op_kind_t op;
  int num;
} token_value_t;

// Creates a new op value.
token_value_t token_value_make_op(op_kind_t op) {
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

// Creates a new error token.
token_t token_make_error() {
  token_value_t v;
  return token_make(TOKEN_ERROR, v);
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
    char *num = (char *)malloc(sizeof(char) * MAX_LITERAL_LEN);
    sprintf(num, "%i", t.value.num);
    return num;
  }
  }
  return "ERROR";
}

////////////////////////////
///////// SCANNER //////////
////////////////////////////

typedef struct {
  const char *source;
  char *error;
  char *literal;
} scanner_t;

// Creates a new scanner.
scanner_t *scanner_make(const char *source) {
  scanner_t *s = (scanner_t *)malloc(sizeof(scanner_t));
  s->source = source;
  s->literal = (char *)malloc(sizeof(char) * MAX_LITERAL_LEN);
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

    if (len == MAX_LITERAL_LEN) {
      printf("error: exceeded max literal length\n");
      exit(1);
    }
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
      return token_make_error();
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
    } else if (peek == OP_POW) {
      scanner_advance(s);
      return token_make(TOKEN_OP, token_value_make_op(OP_POW));
    }

    s->error = (char *)malloc(sizeof(char) * MAX_ERROR_LEN);
    sprintf(s->error, "unexpected char '%c'", peek);
    return token_make_error();
  }
}

////////////////////////////
/////////// AST ////////////
////////////////////////////

typedef int expr_kind_t;
const expr_kind_t EXPR_BIN_OP = 1;
const expr_kind_t EXPR_NUM = 2;

// Forward declaration of `expr_t`.
struct expr_t;

typedef struct {
  op_kind_t op;
  struct expr_t *left;
  struct expr_t *right;
} bin_op_t;

bin_op_t bin_op_make(op_kind_t op, struct expr_t *left, struct expr_t *right) {
  bin_op_t bin_op;
  bin_op.op = op;
  bin_op.left = left;
  bin_op.right = right;
  return bin_op;
}

typedef union {
  bin_op_t bin_op;
  int num;
} expr_value_t;

expr_value_t expr_value_make_bin(bin_op_t bin_op) {
  expr_value_t v;
  v.bin_op = bin_op;
  return v;
}

expr_value_t expr_value_make_num(int num) {
  expr_value_t v;
  v.num = num;
  return v;
}

typedef struct {
  expr_kind_t kind;
  expr_value_t value;
} expr_t;

expr_t *expr_make(expr_kind_t kind, expr_value_t value) {
  expr_t *e = (expr_t *)malloc(sizeof(expr_t));
  e->kind = kind;
  e->value = value;
  return e;
}

////////////////////////////
////////// STACKS //////////
////////////////////////////

typedef struct {
  int len;
  op_kind_t *stack;
} op_stack_t;

// Creates a new operator stack.
op_stack_t op_stack_make() {
  op_stack_t s;
  s.len = 0;
  s.stack = (op_kind_t *)malloc(sizeof(op_kind_t) * MAX_STACK_LEN);
  return s;
}

// Peeks the stack.
op_kind_t op_stack_peek(op_stack_t *s) {
  if (s->len == 0) {
    return OP_ERROR;
  }
  return s->stack[s->len - 1];
}

// Pushes a new operator onto the stack.
void op_stack_push(op_stack_t *s, op_kind_t op) {
  if (s->len > MAX_STACK_LEN) {
    printf("error: exceeded max stack length\n");
    exit(1);
  }
  s->stack[s->len++] = op;
}

// Pops an operator off the stack.
op_kind_t op_stack_pop(op_stack_t *s) {
  if (s->len == 0) {
    return OP_ERROR;
  }
  return s->stack[--s->len];
}

typedef struct {
  int len;
  expr_t **stack;
} expr_stack_t;

// Creates a new expression stack.
expr_stack_t expr_stack_make() {
  expr_stack_t s;
  s.len = 0;
  s.stack = (expr_t **)malloc(sizeof(expr_t *) * MAX_STACK_LEN);
  return s;
}

// Peeks the stack.
expr_t *expr_stack_peek(expr_stack_t *s) {
  if (s->len == 0) {
    return NULL;
  }
  return s->stack[s->len - 1];
}

// Pushes a new expression onto the stack.
void expr_stack_push(expr_stack_t *s, expr_t *e) {
  if (s->len > MAX_STACK_LEN) {
    printf("error: exceeded max stack length\n");
    exit(1);
  }
  s->stack[s->len++] = e;
}

// Pops an expression off the stack.
expr_t *expr_stack_pop(expr_stack_t *s) {
  if (s->len == 0) {
    return NULL;
  }
  return s->stack[--s->len];
}

////////////////////////////
////////// PARSER //////////
////////////////////////////

typedef struct {
  scanner_t *scanner;
  token_t peek;
  char *error;
} parser_t;

// Creates a new parser.
parser_t *parser_make(scanner_t *scanner) {
  parser_t *p = (parser_t *)malloc(sizeof(parser_t));
  p->scanner = scanner;
  p->peek = token_make_error();
  p->error = NULL;
  return p;
}

// Peek the scanner at the current token.
token_t parser_peek(parser_t *p) {
  if (p->peek.kind == TOKEN_ERROR) {
    p->peek = scanner_next(p->scanner);
  }
  return p->peek;
}

// Advances the scanner to the next token.
void parser_advance(parser_t *p) {
  if (p->peek.kind == TOKEN_ERROR) {
    parser_peek(p);
  }
  p->peek = token_make_error();
}

// Build an expression from the operator and the expression stack.
expr_t *parser_build_bin_op(parser_t *p, op_kind_t op, expr_stack_t *exprs) {
  struct expr_t *left = (struct expr_t *)expr_stack_pop(exprs);
  struct expr_t *right = (struct expr_t *)expr_stack_pop(exprs);
  if (left == NULL || right == NULL) {
    p->error = (char *)malloc(sizeof(char) * MAX_ERROR_LEN);
    sprintf(p->error, "unexpected operator '%c'", op);
    return NULL;
  }

  bin_op_t bin_op = bin_op_make(op, left, right);
  return expr_make(EXPR_BIN_OP, expr_value_make_bin(bin_op));
}

// Parses an expression using the shunting-yard algorithm.
expr_t *parser_parse(parser_t *p) {
  expr_t *expr = NULL;

  expr_stack_t exprs = expr_stack_make();
  op_stack_t ops = op_stack_make();

  while (TRUE) {
    token_t peek = parser_peek(p);
    if (peek.kind == TOKEN_ERROR) {
      while (ops.len > 0) {
        op_kind_t op = op_stack_pop(&ops);

        expr_t *e = parser_build_bin_op(p, op, &exprs);
        if (e == NULL) {
          return NULL;
        }

        expr = e;
      }
      break;
    }
    parser_advance(p);

    // Perform some operator magic.
    if (peek.kind == TOKEN_OP) {
      while (TRUE) {
        op_kind_t op = op_stack_peek(&ops);
        if (op == OP_ERROR) {
          break;
        }

        bool end;
        if (op_assoc(op) == OP_ASSOC_LEFT) {
          end = op_prec(op_stack_peek(&ops)) < op_prec(peek.value.op);
        } else {
          end = op_prec(op_stack_peek(&ops)) <= op_prec(peek.value.op);
        }

        if (end) {
          break;
        }

        op = op_stack_pop(&ops);

        expr_t *e = parser_build_bin_op(p, op, &exprs);
        if (e == NULL) {
          return NULL;
        }

        expr = e;
      }

      op_stack_push(&ops, peek.value.op);
      continue;
    }

    // Push the number as an expression.
    if (peek.kind == TOKEN_NUM) {
      expr_t *e = expr_make(EXPR_NUM, expr_value_make_num(peek.value.num));
      expr_stack_push(&exprs, e);
      continue;
    }

    printf("error: invalid token type\n");
    exit(1);
  }

  if (exprs.len > 0) {
    p->error = (char *)malloc(sizeof(char) * MAX_ERROR_LEN);
    sprintf(p->error, "unbalanced binary operations");
    return NULL;
  }

  return expr;
}

int main() {
  while (TRUE) {
    printf("> ");

    // Read in the source.
    char source[MAX_INPUT_LEN];
    fgets(source, MAX_INPUT_LEN, stdin);
    source[strlen(source) - 1] = '\0';

    // Create the scanner around the source.
    scanner_t *s = scanner_make(source);

    // Create the parser around the scanner.
    parser_t *p = parser_make(s);
    parser_parse(p);

    // Check for parser error.
    if (p->error != NULL) {
      printf("error: %s\n", p->error);
      continue;
    }

    // Check for scanner error.
    if (s->error != NULL) {
      printf("error: %s\n", s->error);
    }
  }
}
