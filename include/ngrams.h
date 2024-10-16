#ifndef NGRAMS_H
#define NGRAMS_H

#include <stddef.h>

/**
 * Struktura pro n-gram.
 * 
 * Struktura NGram reprezentuje jeden n-gram, což je posloupnost slov ze vstupního textu.
 * - words: Pole slov, která tvoří n-gram.
 * - size: Velikost n-gramu, například 2 pro bigram nebo 3 pro trigram.
 */
typedef struct {
    char** words; // Pole slov, které tvoří n-gram
    int size;     // Velikost n-gramu (např. 2 pro bigram, 3 pro trigram)
} NGram;

/**
 * Generuje n-gramy ze zadaných tokenů.
 * 
 * @param tokens Pole tokenů získaných z textu.
 * @param token_count Počet tokenů ve vstupním poli.
 * @param n Velikost n-gramu, například 2 pro bigram nebo 3 pro trigram.
 * @param ngram_count Ukazatel na proměnnou, kam bude uložen počet generovaných n-gramů.
 * @return Pole struktur NGram, které obsahují všechny n-gramy vytvořené z tokenů.
 */
NGram* generate_ngrams(char** tokens, int token_count, int n, int* ngram_count);

/**
 * Uvolní paměť alokovanou pro n-gramy.
 * 
 * @param ngrams Pole n-gramů, které byly vytvořeny funkcí generate_ngrams.
 * @param ngram_count Počet n-gramů v poli ngrams.
 */
void free_ngrams(NGram* ngrams, int ngram_count);

/**
 * Uvolní paměť alokovanou pro n-gramy v případě selhání.
 * 
 * Tato funkce se používá k uvolnění paměti alokované pro n-gramy, když dojde k chybě
 * během generování n-gramů. Zajišťuje, že nedojde k úniku paměti uvolněním všech
 * n-gramů, které byly úspěšně alokovány před selháním.
 * 
 * @param ngramArray Ukazatel na pole n-gramů, které mají být uvolněny.
 * @param count Počet n-gramů, které byly úspěšně alokovány před selháním.
 */
void free_allocated_ngrams_on_failure(NGram* ngramArray, int count);

#endif // NGRAMS_H