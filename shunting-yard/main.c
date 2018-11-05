#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX_STACK_SIZE 50
#define MAX_TOKEN_NUM 50
#define MAX_LITERAL_LENGTH 50
#define MAX_INPUT_LENGTH 100

typedef int TokenType;
const TokenType TOKEN_OP = 1;
const TokenType TOKEN_NUM = 2;

typedef int Op;
const Op OP_ADD = 1;
const Op OP_SUB = 2;
const Op OP_MUL = 3;
const Op OP_DIV = 4;

typedef struct {
  TokenType type;
  int op;
} TokenOp;

typedef struct {
  TokenType type;
  int num;
} TokenNum;

typedef union {
  TokenOp op;
  TokenNum num;
} Token;

typedef struct {
  const char *source;
  char *literal;
} Tokenizer;

Tokenizer *TokenizerNew(const char *source) {
  Tokenizer *t = (Tokenizer *)malloc(sizeof(Tokenizer));
  t->source = source;
  t->literal = NULL;
  return t;
}

// Peek the source at the current char.
char TokenizerPeek(Tokenizer *t) { return *t->source; }

// Advance the source to the next char.
void TokenizerAdvance(Tokenizer *t) { t->source = &t->source[1]; }

// Returns the next token.
Token *TokenizerNext(Tokenizer *t) {
  if (TokenizerPeek(t) == '\0') {
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

    Tokenizer *t = TokenizerNew(source);
    printf("%d\n", TokenizerNext(t));
  }

  return 0;
}
