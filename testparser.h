/*
 * testparser.h
 *
 *  Created on: 8. okt. 2015
 *      Author: larso
 */

#ifndef TESTPARSER_H_
#define TESTPARSER_H_

/*
 * This is a test parser for mathematical expressions
 *
 * Numbers are following these production rules:
 * <Int> ::= <Digit> | <Digit> <Int>
 * <Float> ::= <Int>.<Int> | .<Int>
 * <Number> ::= <Int> | <Float>
 *
 * Numerical expressions
 * <Expr> ::= <P1>
 * <P1> ::= <P1>+<P2> | <P1>-<P2> | <P2>
 * <P2> ::= <P2>*<P3> | <P2>/<P3> | <P3>
 * <P3> ::= (<Expr>) | <UnaryExpr> | <Number>
 * <UnaryExpr> ::= -<Expr>
 *
 */

#include <stdlib.h>

typedef struct ast
{
    enum
    {
        NUMBER_EXPR,
        UNARY_EXPR,
        BINARY_EXPR
    } tag;
    union
    {
        float number_expr;
        struct
        {
            char* operator;
            struct ast* operand;
        } unary_expr;
        struct
        {
            char* operator;
            struct ast* left;
            struct ast* right;
        } binary_expr;
    } op;
} ast;

ast* make_number_expr(float value);
ast* make_unary_expr(char* operator, size_t len, ast* operand);
ast* make_binary_expr(char* operator, size_t len, ast* left, ast* right);
void free_ast(ast* obj);

typedef struct
{
    ast* result;
    char* rest_tokens;
    char* error;
} parse_data;

parse_data* make_parse_data(ast* result, char* rest_tokens, char* error);
void free_parse_data(parse_data* data);
void parse_error(parse_data* data, char* error);

parse_data* expect_token(char* tokens, char* token);
parse_data* parse_expr(char* tokens);
parse_data* parse_number(char* tokens);

#endif /* TESTPARSER_H_ */
