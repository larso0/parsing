/*
 * tokens.h
 *
 *  Created on: 8. okt. 2015
 *      Author: larso
 */

#ifndef TOKENS_H_
#define TOKENS_H_

/**
 * Finds the beginning of a token.
 * Skips delimiter characters.
 * Returns pointer to beginning of the next token in the string.
 * Returns NULL if there are no more tokens.
 * Returns NULL if any of the parameters are NULL.
 */
char* token_begin(char* str, char* delims);

/**
 * Finds the end of a token.
 * Stops on a delimiter or a single character token.
 * Returns pointer to the rest of the string after the token,
 * so a pointer to the first character after the token.
 * Returns NULL if any of the parameters are NULL.
 */
char* token_end(char* str, char* delims, char* tokens);

#endif /* TOKENS_H_ */
