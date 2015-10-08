/*
 * test.c
 *
 *  Created on: 8. okt. 2015
 *      Author: larso
 */

#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char str[] = "(double x) + 5";
    char tokens[] = "()+-*/";
    char delims[] = " \t\r\n";

    char* beg = NULL;
    char* end = str;
    while(beg = token_begin(end, delims))
    {
        end = token_end(beg, delims, tokens);
        printf("%.*s\n", (int)(end-beg), beg);
    }
}
