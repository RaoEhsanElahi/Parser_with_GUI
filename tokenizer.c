#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include "grammar.h"

#define MAX_TOKEN_LENGTH 32

typedef struct Token {
  TokenType type;
  char value[MAX_TOKEN_LENGTH + 1];
} Token;

int is_keyword(const char* str) {
  return strcmp(str, KEYWORD_INPUT) == 0 || strcmp(str, KEYWORD_OUTPUT) == 0;
}

TokenType get_token_type(const char* str) {
  if (isdigit(*str)) {
    return TOKEN_NUMBER;
  } else if (isalpha(*str)) {
    return TOKEN_IDENTIFIER;
  } else if (is_keyword(str)) {
    return TOKEN_KEYWORD;
  } else if (*str == '+') {
    return TOKEN_PLUS;
  } else if (*str == '-') {
    return TOKEN_MINUS;
  } else if (*str == '*') {
    return TOKEN_MULTIPLY;
  } else if (*str == '/') {
    return TOKEN_DIVIDE;
  } else if (*str == '(') {
    return TOKEN_LPAREN;
  } else if (*str == ')') {
    return TOKEN_RPAREN;
  } else if (*str == ';') {
    return TOKEN_SEMICOLON;
  } else {
    return TOKEN_ERROR;
  }
}

Token* tokenize(const char* input_string) {
  int num_tokens = 0;
  int max_tokens = 10;
  Token* tokens = malloc(sizeof(Token) * max_tokens);

  const char* current_char = input_string;
  while (*current_char != '\0') {
    // Skip whitespace
    while (isspace(*current_char)) {
      current_char++;
    }

    if (*current_char == '\0') {
      break;
    }

    int token_length = 0;
    while (*current_char != '\0' && !isspace(*current_char) && token_length < MAX_TOKEN_LENGTH) {
      if (*current_char == '+' || *current_char == '-' || *current_char == '*' || *current_char == '/' ||
          *current_char == '(' || *current_char == ')' || *current_char == ';') {
        if (token_length > 0) {
          // If we have characters accumulated in the token buffer, create a token with them first
          tokens[num_tokens].value[token_length] = '\0'; // Null terminate
          tokens[num_tokens].type = get_token_type(tokens[num_tokens].value);
          num_tokens++;
          token_length = 0;
          if (num_tokens == max_tokens) {
            max_tokens *= 2;
            tokens = realloc(tokens, sizeof(Token) * max_tokens);
          }
        }
        // Create a token for the operator or delimiter
        tokens[num_tokens].value[0] = *current_char;
        tokens[num_tokens].value[1] = '\0'; // Null terminate
        tokens[num_tokens].type = get_token_type(tokens[num_tokens].value);
        num_tokens++;
        if (num_tokens == max_tokens) {
          max_tokens *= 2;
          tokens = realloc(tokens, sizeof(Token) * max_tokens);
        }
        current_char++;
      } else {
        // Accumulate characters into the token buffer
        tokens[num_tokens].value[token_length++] = *current_char++;
      }
    }

    if (token_length > 0) {
      // If we have characters accumulated in the token buffer, create a token with them
      tokens[num_tokens].value[token_length] = '\0'; // Null terminate
      tokens[num_tokens].type = get_token_type(tokens[num_tokens].value);
      num_tokens++;
      if (num_tokens == max_tokens) {
        max_tokens *= 2;
        tokens = realloc(tokens, sizeof(Token) * max_tokens);
      }
    }
  }

  // Resize tokens array to actual number of tokens
  tokens = realloc(tokens, sizeof(Token) * (num_tokens + 1));
  tokens[num_tokens].type = TOKEN_ERROR; 
  // Mark end of tokens

  return tokens;
}

// Example usage (can be removed)
int main() { 
  char input_string[] = "INPUT x; OUTPUT x + 2 * (y - 3);";
  Token* tokens = tokenize(input_string);

  int i = 0;
  while (tokens[i].type != TOKEN_ERROR) {
    printf("Token %d: type=%d, value=%s\n", i + 1, tokens[i].type, tokens[i].value);
    i++;
  }

  free(tokens);
  return 0;
}
