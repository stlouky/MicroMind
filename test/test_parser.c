/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * test_parser.c - Testovací soubor pro testování funkcí z parser.c pomocí testovacího rámce
 *
 * Tento soubor obsahuje testy pro funkce z parser.c, jako je funkce pro parsování vstupního textu.
 */

#include "test_framework.h"
#include "parser.h"
#include <stdlib.h>

/**
 * test_parse_text - Testuje funkci parse_text
 *
 * Testuje různé vstupní scénáře pro funkci parse_text a ověřuje správné výsledky.
 */
void test_parse_tokens() {
    // Test 1: Platný vstupní text
    char* tokens1[] = {"Toto", "je", "test"};
    int result_count1 = 0;
    ParseResult* results1 = parse_tokens(tokens1, 3, &result_count1);
    RUN_TEST("Parse valid input", results1 != NULL && result_count1 == 3);
    free_parse_results(results1, result_count1);

    // Test 2: Prázdný vstupní text
    char* tokens2[] = {};
    int result_count2 = 0;
    ParseResult* results2 = parse_tokens(tokens2, 0, &result_count2);
    RUN_TEST("Parse empty input", results2 == NULL && result_count2 == 0);

    // Test 3: NULL jako vstupní text
    int result_count3 = 0;
    ParseResult* results3 = parse_tokens(NULL, 3, &result_count3);
    RUN_TEST("Parse NULL input", results3 == NULL && result_count3 == 0);
}

/**
 * main - Hlavní funkce pro spuštění všech testů
 *
 * Spouští všechny testy definované v tomto souboru.
 */
int main() {
    printf("\nSpouštění testů pro parser.c:\n\n");

    test_parse_tokens();

    printf("\nTesty dokončeny\n");
    printf("\nCelkové shrnutí: %d/%d testů úspěšných.\n", passed_tests, total_tests);

    return 0;
}