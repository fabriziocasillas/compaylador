#include "lexer/token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* pues esta funcion basicmanete te da el nombre del tipo
 * del token que le estas dando, en base en el tipo mismo del token, 
 * el tipo error que se encarga de todos los demas caracteres, esta esto dentro
 * de la logia, y si por algun motivo logra saltarse eso simplemente regresa UNKNOWN
*/
const char *token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "TOKEN_EOF";
        case ERROR: return "ERROR";
        case IDENTIFIER: return "IDENTIFIER";
        case INTEGER: return "INTEGER";
        case INT: return "INT";
        case BOOL: return "BOOL";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case PRINT: return "PRINT";
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case ASSIGN: return "ASSIGN";
        case EQUAL: return "EQUAL";
        case NOT_EQUAL: return "NOT_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case AND: return "AND";
        case OR: return "OR";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case SEMICOLON: return "SEMICOLON";
    }

    return "UNKNOWN";
}

/**
 * inicializas un token, primero checas que el token o supongo
 * la extension de memoria que te dan existe, despues tratas de hacer malloc
 * y si puedes, pues ya cpias el lexema y guardas el resto
 * 
 * 
 */
int token_init(Token *token, TokenType type, const char *lexeme,
               size_t line, size_t column) {
    size_t length;

    if (token == NULL || lexeme == NULL) {
        return 0;
    }

    length = strlen(lexeme);
    token->lexeme = malloc(length + 1);
    if (token->lexeme == NULL) {
        return 0;
    }

    memcpy(token->lexeme, lexeme, length + 1);
    token->type = type;
    token->line = line;
    token->column = column;
    return 1;
}


/**
 * Imprime un token utilizando el formato especificado
 *
 * Los tokens TOKEN_EOF se imprimen sin lexema.
 *
 * @param token token a imprimir
 */
void token_print(const Token *token) {
    if (token == NULL) {
        return;
    }

    if (token->type == TOKEN_EOF) {
        printf("%zu:%zu %s\n",
               token->line,
               token->column,
               token_type_name(token->type));
        return;
    }

    printf("%zu:%zu %s %s\n",
           token->line,
           token->column,
           token_type_name(token->type),
           token->lexeme);
}


/**
 * liberas la memoria
 *
 * no usamos free y creamos eta funcion porque puede haber sido
 * almacenado en memoria automática por el llamador.
 *
 * @param token Token cuyos recursos serán liberados.
 */
void token_destroy(Token *token) {
    if (token == NULL) {
        return;
    }

    free(token->lexeme);
    token->lexeme = NULL;
}
