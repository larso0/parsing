/*
 * tokens.c
 *
 *  Created on: 8. okt. 2015
 *      Author: larso
 */

#include "tokens.h"
#include <stdlib.h>
#include <string.h>

char* token_begin(char* str, char* delims)
{
    if(str == NULL
       || delims == NULL
       || *str == '\0')
    {
        return NULL;
    }
    for(; strchr(delims, *str); str++);
    return str;
}

char* token_end(char* str, char* delims, char* tokens)
{
    if(str == NULL
       || delims == NULL
       || tokens == NULL)
    {
        return NULL;
    }
    if(*str == '\0') return str;
    if(strchr(tokens, *str)) return str+1;
    for(; *str != '\0'
          && !strchr(tokens, *str)
          && !strchr(delims, *str); str++);
    return str;
}
