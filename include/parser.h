#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

// Struktura pro uložení výsledků parsování
typedef struct {
    char* value;
    int type;
} ParseResult;

// Funkce pro analýzu tokenů
ParseResult* parse_tokens(char** tokens, int token_count, int* result_count);

// Funkce pro uvolnění paměti použitou pro výsledky analýzy
void free_parse_results(ParseResult* results, int result_count);

// Funkce pro určení typu tokenu
int determine_token_type(const char* token);

// Funkce pro tokenizaci vstupního textu
char** tokenize(const char* text, int* token_count, const char* delimiters);

// Funkce pro uvolnění paměti použitou pro tokeny
void free_tokens(char** tokens, int token_count);

#endif // PARSER_H