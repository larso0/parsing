/*
 * testparser.c
 *
 *  Created on: 9. okt. 2015
 *      Author: larso
 */


#include "testparser.h"
#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

char token_characters[] = "()+-*/%";
char delimiter_characters[] = " \t\r\n";

ast* make_number_expr(float value)
{
    ast* expr = malloc(sizeof(ast));
    if(expr == NULL) return NULL;
    expr->tag = NUMBER_EXPR;
    expr->op.number_expr = value;
    return expr;
}

ast* make_unary_expr(char* operator, size_t len, ast* operand)
{
    if(operator == NULL || operand == NULL) return NULL;
    ast* expr = malloc(sizeof(ast));
    if(expr == NULL) return NULL;
    expr->tag = UNARY_EXPR;
    expr->op.unary_expr.operator = malloc(len+1);
    if(expr->op.unary_expr.operator == NULL)
    {
        free(expr);
        return NULL;
    }
    memcpy(expr->op.unary_expr.operator, operator, len);
    expr->op.unary_expr.operator[len] = '\0';
    expr->op.unary_expr.operand = operand;
    return expr;
}

ast* make_binary_expr(char* operator, size_t len, ast* left, ast* right)
{
    if(operator == NULL || left == NULL || right == NULL) return NULL;
    ast* expr = malloc(sizeof(ast));
    if(expr == NULL) return NULL;
    expr->tag = BINARY_EXPR;
    expr->op.binary_expr.operator = malloc(len+1);
    if(expr->op.binary_expr.operator == NULL)
    {
        free(expr);
        return NULL;
    }
    memcpy(expr->op.binary_expr.operator, operator, len);
    expr->op.binary_expr.operator[len] = '\0';
    expr->op.binary_expr.left = left;
    expr->op.binary_expr.right = right;
    return expr;
}

void free_ast(ast* obj)
{
    if(obj == NULL) return;
    switch(obj->tag)
    {
    case UNARY_EXPR:
        free(obj->op.unary_expr.operator);
        free_ast(obj->op.unary_expr.operand);
        break;
    case BINARY_EXPR:
        free(obj->op.binary_expr.operator);
        free_ast(obj->op.binary_expr.left);
        free_ast(obj->op.binary_expr.right);
        break;
    default:
        break;
    }
    free(obj);
}

parse_data* make_parse_data(ast* result, char* rest_tokens, char* error)
{
    parse_data* data = malloc(sizeof(parse_data));
    if(data == NULL) return NULL;
    data->result = result;
    data->rest_tokens = rest_tokens;
    if(error == NULL)
    {
        data->error = NULL;
        return data;
    }
    data->error = malloc(strlen(error)+1);
    if(data->error == NULL)
    {
        free(data);
        return NULL;
    }
    strcpy(data->error, error);
    return data;
}

void free_parse_data(parse_data* data)
{
    if(data == NULL) return;
    if(data->error != NULL)
    {
        free(data->error);
    }
    free(data);
}

void parse_error(parse_data* data, char* error)
{
    if(data == NULL || error == NULL) return;
    if(data->error == NULL)
    {
        data->error = malloc(strlen(error)+1);
        if(data->error == NULL) return;
        strcpy(data->error, error);
    }
    else
    {
        size_t len = strlen(data->error);
        data->error = realloc(data->error, len+strlen(error)+1);
        if(data->error == NULL) return;
        strcpy((data->error + len), error);
    }
}

parse_data* expect_token(char* tokens, char* token)
{
    if(token == NULL)
    {
        return NULL;
    }
    else if(tokens == NULL)
    {
        return make_parse_data(NULL, tokens,
                "Cannot expect a NULL pointer from tokenlist.");
    }
    else
    {
        char* end = token_end(tokens, delimiter_characters, token_characters);
        parse_data* data = make_parse_data(NULL, end, NULL);
        if(end == tokens)
        {
            parse_error(data, "Expected \"");
            parse_error(data, token);
            parse_error(data, "\", but out of tokens.");
        }
        else if(strncmp(tokens, token, (end-tokens)) != 0)
        {
            size_t len = end-tokens;
            parse_error(data, "Expected \"");
            parse_error(data, token);
            char* instead = malloc(len+1);
            if(instead != NULL)
            {
                parse_error(data, "\", got \"");
                memcpy(instead, tokens, len);
                instead[len] = '\0';
                parse_error(data, instead);
                free(instead);
                parse_error(data, "\".");
            }
        }

        return data;
    }
}

parse_data* parse_expr(char* tokens)
{
    if(tokens == NULL)
    {
        return make_parse_data(NULL, NULL,
                "Token string is a NULL pointer. - in parse_expr\n");
    }
    tokens = token_begin(tokens, delimiter_characters);
    if(tokens == NULL)
    {
        return make_parse_data(NULL, NULL,
                "Token string contains no tokens. - in parse_expr\n");
    }

    char* beg = NULL;
    char* end = tokens;
    while(beg = token_begin(end, delimiter_characters))
    {
        end = token_end(beg, delimiter_characters, token_characters);
        //TODO implement rest of shunting-yard algorithm
    }

}

parse_data* parse_number(char* tokens)
{
    if(tokens == NULL)
    {
        return make_parse_data(NULL, NULL,
                "Token string is a NULL pointer. - in parse_number\n");
    }
    tokens = token_begin(tokens, delimiter_characters);
    if(tokens == NULL)
    {
        return make_parse_data(NULL, NULL,
                "Token string contains no tokens. - in parse_number\n");
    }

    float number = 0.f;
    char* end = tokens;
    for(; '0' <= end[0] && end[0] <= '9'; end++);
    char* i = tokens;
    for(; i < end; i++)
    {
        number += (*i - '0') * pow(10, end - i - 1);
    }
    if(*end == '.')
    {
        end++;
        i++;
        for(; '0' <= end[0] && end[0] <= '9'; end++);
        char* j = i;
        for(; j < end; j++)
        {
            number += (*j - '0') * pow(10, -(j - i - 1));
        }
    }

    ast* num = make_number_expr(number);
    if(num == NULL)
    {
        return make_parse_data(NULL, end,
                "Could not allocate memory for ast. - in parse_number\n");
    }

    return make_parse_data(num, end, NULL);
}
