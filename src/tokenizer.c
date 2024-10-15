#include "../include/tokenizer.h"
#include "../include/common.h"
#include "../include/test_framework.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define DEFAULT_DELIMITERS " \t\n"

/* Statická funkce pro uvolnění částečně alokovaných tokenů */
static void free_partial_tokens(char** tokens, int count) {
    for (int i = 0; i < count; i++) {
        SAFE_FREE(tokens[i]);
    }
    SAFE_FREE(tokens);
}

/**
 * @brief Rozdělí vstupní text na tokeny podle zadaných oddělovačů.
 * 
 * @param text Vstupní řetězec, který má být tokenizován.
 * @param token_count Ukazatel na int, kam bude uložen počet nalezených tokenů.
 * @param delimiters Řetězec obsahující oddělovače. Pokud je NULL, použijí se výchozí oddělovače.
 * @return Pole ukazatelů na tokeny nebo NULL v případě chyby.
 */
char** tokenize(const char* text, int* token_count, const char* delimiters) {
    if (text == NULL || token_count == NULL) {
        log_error(__func__, "Invalid input: text or token_count is NULL");
        return NULL;
    }

    /* Pokud nejsou zadány oddělovače, použijeme výchozí */
    if (delimiters == NULL) {
        delimiters = DEFAULT_DELIMITERS;
    }

    /* Vytvoření kopie vstupního textu pro tokenizaci */
    char* text_copy = strdup(text);
    if (text_copy == NULL) {
        log_error(__func__, "Memory allocation failed for text copy");
        return NULL;
    }

    int count = 0;
    char* saveptr;
    char* token = strtok_r(text_copy, delimiters, &saveptr);
    char** tokens = NULL;

    while (token != NULL) {
        /* Realokace pole ukazatelů na tokeny */
        char** new_tokens = realloc(tokens, (count + 1) * sizeof(char*));
        if (new_tokens == NULL) {
            log_error(__func__, "Memory allocation failed for tokens array");
            free_partial_tokens(tokens, count);
            SAFE_FREE(text_copy);
            return NULL;
        }
        tokens = new_tokens;

        /* Uložení tokenu do pole */
        tokens[count] = strdup(token);
        if (tokens[count] == NULL) {
            log_error(__func__, "Memory allocation failed for token");
            free_partial_tokens(tokens, count);
            SAFE_FREE(text_copy);
            return NULL;
        }
        count++;
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    SAFE_FREE(text_copy);
    *token_count = count;
    return tokens;
}

/**
 * @brief Uvolní paměť použitou pro tokeny.
 * 
 * @param tokens Pole ukazatelů na tokeny, které mají být uvolněny.
 * @param token_count Počet tokenů v poli.
 */
void free_tokens(char** tokens, int token_count) {
    if (tokens == NULL) {
        return;
    }
    for (int i = 0; i < token_count; i++) {
        SAFE_FREE(tokens[i]);
    }
    SAFE_FREE(tokens);
}