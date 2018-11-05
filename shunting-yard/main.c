#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 50
#define MAX_TOKEN_NUM 50
#define MAX_LITERAL_LENGTH 50
#define MAX_INPUT_LENGTH 100

typedef int TokenType;
const TokenType TOKEN_OP = 1;
const TokenType TOKEN_NUMBER = 2;

typedef int Op;
const Op OP_ADD = 1;
const Op OP_SUB = 2;
const Op OP_MUL = 3;
const Op OP_DIV = 4;

typedef struct {
  TokenType type;
  int number;
  char *literal;
} Token;

typedef struct {
  const char *source;
  char *literal;
  char *peek;
} Tokenizer;

Tokenizer TokenizerMake(const char *source) { return {source, NULL}; }

Token TokenizerNext(Tokenizer *t) {}

char *TokenizerPeek(Tokenizer *t) {}

void TokenizerAdvance(Tokenizer *t) { t->source = &t->source[1]; }

int main() {
  while (true) {
    printf("> ");

    // Read in the source.
    char source[MAX_INPUT_LENGTH];
    fgets(source, MAX_INPUT_LENGTH, stdin);
    source[strlen(source) - 1] = '\0';

    printf("%s\n", source);
  }

  return 0;
}
