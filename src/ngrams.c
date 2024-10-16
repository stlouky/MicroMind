#include "../include/ngrams.h"
#include "../include/common.h" // Přidání common.h pro použití log_error a SAFE_FREE
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/**
 * Funkce generate_ngrams generuje n-gramy ze zadaných tokenů.
 * 
 * @param tokens Pole tokenů získaných z textu.
 * @param token_count Počet tokenů ve vstupním poli.
 * @param n Velikost n-gramu, například 2 pro bigram nebo 3 pro trigram.
 * @param ngram_count Ukazatel na proměnnou, kam bude uložen počet generovaných n-gramů.
 * @return Pole struktur NGram, které obsahují všechny n-gramy vytvořené z tokenů.
 *         Pokud dojde k chybě, vrátí NULL a ngram_count bude nastaveno na 0.
 */
NGram* generate_ngrams(char** tokens, int token_count, int n, int* ngram_count) {
    // Zkontrolujeme, zda jsou vstupy platné
    if (tokens == NULL || token_count < n || ngram_count == NULL || n <= 0) {
        if (ngram_count != NULL) {
            *ngram_count = 0;
        }
        log_error(__func__, "Invalid input: tokens, token_count, or ngram_count is NULL or invalid");
        return NULL;
    }

    // Počet n-gramů, které mohou být vytvořeny
    *ngram_count = token_count - n + 1;
    if (*ngram_count <= 0) {
        *ngram_count = 0;
        return NULL;
    }

    // Alokace paměti pro n-gramy
    NGram* ngramArray = (NGram*)malloc(*ngram_count * sizeof(NGram));
    if (ngramArray == NULL) {
        log_error(__func__, "Memory allocation failed for ngramArray");
        *ngram_count = 0;
        return NULL;
    }

    // Generování n-gramů
    for (int i = 0; i < *ngram_count; i++) {
        ngramArray[i].size = n;
        ngramArray[i].words = (char**)malloc(n * sizeof(char*));
        if (ngramArray[i].words == NULL) {
            log_error(__func__, "Memory allocation failed for ngramArray element");
            free_allocated_ngrams_on_failure(ngramArray, i);
            SAFE_FREE(ngramArray);  // Použití SAFE_FREE z common.c
            *ngram_count = 0;
            return NULL;
        }

        // Kopírování ukazatelů na slova do n-gramu pomocí pointerové aritmetiky
        for (int j = 0; j < n; j++) {
            ngramArray[i].words[j] = *(tokens + i + j);
        }
    }

    return ngramArray;
}

/**
 * Funkce free_allocated_ngrams_on_failure uvolní paměť alokovanou pro částečně vytvořené n-gramy.
 * 
 * @param ngramArray Pole n-gramů, které byly částečně vytvořeny.
 * @param count Počet n-gramů, které byly alokovány a je třeba je uvolnit.
 */
void free_allocated_ngrams_on_failure(NGram* ngramArray, int count) {
    // Uvolnění paměti pro částečně vytvořené n-gramy
    for (int j = 0; j < count; j++) {
        SAFE_FREE(ngramArray[j].words); // Použití SAFE_FREE
    }
    SAFE_FREE(ngramArray);  // Zajištění uvolnění pole n-gramů
}

/**
 * Funkce free_ngrams uvolní paměť alokovanou pro všechny n-gramy.
 * 
 * @param ngramArray Pole n-gramů, které byly vytvořeny funkcí generate_ngrams.
 * @param ngram_count Počet n-gramů v poli ngramArray.
 */
void free_ngrams(NGram* ngramArray, int ngram_count) {
    if (ngramArray == NULL) {
        return;
    }

    // Uvolnění paměti pro každé slovo v každém n-gramu
    for (int i = 0; i < ngram_count; i++) {
        SAFE_FREE(ngramArray[i].words);  // Použití SAFE_FREE pro slova
    }

    // Uvolnění paměti pro pole n-gramů
    SAFE_FREE(ngramArray);  // Použití SAFE_FREE pro celé pole
}
