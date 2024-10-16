/* SPDX-License-Identifier: GPL-2.0-only */
#include "../include/parser.h"
#include "../include/test_framework.h" 
#include "../include/common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>


#define INITIAL_ALLOCATION_SIZE 10

/* Funkce pro logování chyb */
void log_error(const char* func, const char* msg) {
    fprintf(stderr, "[ERROR] %s: %s (errno: %d - %s)\n", func, msg, errno, strerror(errno));
}

/**
 * @brief Určuje typ tokenu.
 *
 * @param token Řetězec představující token, jehož typ má být určen.
 * @return Typ tokenu jako celé číslo (např. 0 pro čísla, 1 pro operátory, 2 pro identifikátory, atd.).
 */
int determine_token_type(const char* token) {
    if (token == NULL) {
        return -1; // Chyba: neplatný token
    }

    // Kontrola, zda je token číslo (celé nebo desetinné)
    char* endptr;
    errno = 0;
    strtod(token, &endptr);
    if (errno == 0 && endptr != token && *endptr == '\0') {
        return 0; // Typ: číslo
    }

    // Kontrola operátorů
    const char* operators[] = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">="};
    int num_operators = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < num_operators; ++i) {
        if (strcmp(token, operators[i]) == 0) {
            return 1; // Typ: operátor
        }
    }

    // Jinak předpokládáme, že jde o identifikátor
    return 2; // Typ: identifikátor
}

/* Statická funkce pro uvolnění částečně alokovaných pamětí */
static void free_partial_results(ParseResult* results, int count) {
    for (int i = 0; i < count; i++) {
        SAFE_FREE(results[i].value);
    }
    SAFE_FREE(results);
}

/**
 * @brief Analyzuje vstupní tokeny a generuje strukturu ParseResult.
 *
 * @param tokens Pole ukazatelů na tokeny, které mají být analyzovány.
 * @param token_count Počet tokenů v poli.
 * @param result_count Ukazatel na int, kam bude uložen počet výsledků analýzy.
 * @return Pole struktur ParseResult nebo NULL v případě chyby.
 */
ParseResult* parse_tokens(char** tokens, int token_count, int* result_count) {
    if (tokens == NULL || result_count == NULL) {
        log_error("parse_tokens", "Invalid input: tokens or result_count is NULL");
        return NULL;
    }

    if (token_count <= 0) {
        log_error("parse_tokens", "Invalid input: token_count is non-positive");
        return NULL;
    }

    int allocated_size = token_count;
    ParseResult* results = (ParseResult*)malloc(allocated_size * sizeof(ParseResult));
    if (results == NULL) {
        log_error("parse_tokens", "Memory allocation failed for results array");
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < token_count; i++) {
        results[count].value = strdup(tokens[i]);
        if (results[count].value == NULL) {
            log_error("parse_tokens", "Memory allocation failed for result value");
            free_partial_results(results, count);
            return NULL;
        }
        results[count].type = determine_token_type(tokens[i]);
        count++;
    }

    *result_count = count;
    return results;
}

/**
 * @brief Uvolní paměť použitou pro výsledky analýzy.
 *
 * @param results Pole struktur ParseResult, které mají být uvolněny.
 * @param result_count Počet výsledků v poli.
 */
void free_parse_results(ParseResult* results, int result_count) {
    if (results == NULL) {
        return;
    }
    for (int i = 0; i < result_count; i++) {
        SAFE_FREE(results[i].value);
    }
    SAFE_FREE(results);
}