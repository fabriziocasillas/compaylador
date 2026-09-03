#include "lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

int simple_token_type(int c, TokenType *type) {
    if (type == NULL) {
        return 0;
    }

    switch (c) {
        case '+':
            *type = PLUS;
            return 1;

        case '-':
            *type = MINUS;
            return 1;

        case '*':
            *type = STAR;
            return 1;

        case '/':
            *type = SLASH;
            return 1;

        case '=':
            *type = ASSIGN;
            return 1;

        case '<':
            *type = LESS;
            return 1;

        case '>':
            *type = GREATER;
            return 1;

        case '(':
            *type = LPAREN;
            return 1;

        case ')':
            *type = RPAREN;
            return 1;

        case '{':
            *type = LBRACE;
            return 1;

        case '}':
            *type = RBRACE;
            return 1;

        case ';':
            *type = SEMICOLON;
            return 1;

        default:
            return 0;
    }
}

static int is_ignored_space(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int is_digit(int c) {
    return c >= '0' && c <= '9';
}

static void advance_position(int c, FILE *file, size_t *line, size_t *column) {
    if (c == '\r') {
        int next = fgetc(file);

        if (next != '\n' && next != EOF) {
            ungetc(next, file);
        }

        (*line)++;
        *column = 0;
    } else if (c == '\n'){
        (*line)++;
        *column = 0;
    } else  {
        (*column)++;
    }
}
int lexer_scan(FILE *file) {
    size_t line = 1;
    size_t column = 0;
    int c;

    if (file == NULL) {
        return 2;
    }

    while ((c = fgetc(file)) != EOF) {
        size_t token_line = line;
        size_t token_column = column;
        TokenType type;

        advance_position(c, file, &line, &column);

        if (is_ignored_space(c)) {
            continue;
        }

        if(is_digit(c)) {
            size_t capacity = 16;
            size_t length = 0;
            char *lexeme = malloc(capacity);

            if (lexeme == NULL) {
                fprintf(stderr, "Error: no se pudo reservar memoria.\n");
                return 2;
            }

            lexeme[length++] = (char)c;

            while (1) {
                c = fgetc(file);

                if (c == EOF) {
                    break;
                }

                if(!is_digit(c)) {
                    ungetc(c, file);
                    break;
                }

                if (length + 1 >= capacity) {
                    char *new_lexeme;

                    capacity *= 2;
                    new_lexeme = realloc(lexeme, capacity);

                    if (new_lexeme == NULL) {
                        free(lexeme);
                        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
                        return 2;
                    }

                    lexeme = new_lexeme;
                }

                lexeme[length++] = (char)c;
                column++;
            }

            lexeme[length] = '\0';

            {
                Token token;

                if (!token_init(&token, INTEGER, lexeme, token_line, token_column)) {
                    fprintf(stderr, "Error: no se pudo reservar memoria.\n");
                    return 2;
                }

                token_print(&token);
                token_destroy(&token);
            }

            free(lexeme);
            continue;
        }

        if (simple_token_type(c, &type)) {
            char lexeme[2] = {(char)c, '\0'};
            Token token;

            if (!token_init(&token, type, lexeme,
                            token_line, token_column)) {
                fprintf(stderr, "Error: no se pudo reservar memoria.\n");
                return 2;
            }

            token_print(&token);
            token_destroy(&token);
            continue;
        }

        {
            char lexeme[2] = {(char)c, '\0'};
            Token token;

            if (!token_init(&token, ERROR, lexeme, token_line, token_column)) {
                fprintf(stderr, "Error: no se pudo reservar memoria.\n");
                return 2;
            }

            token_print(&token);
            token_destroy(&token);
        }
    }

    if (ferror(file)) {
        fprintf(stderr, "Error: no se pudo leer el archivo.\n");
        return 2;
    }

    Token token;

    if (!token_init(&token, TOKEN_EOF, "", line, column)){
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        return 2;
    }

    token_print(&token);
    token_destroy(&token);

    return 0;
}
