#include "../include/test_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Počítadla testů
int total_tests = 0;  /**< Celkový počet spuštěných testů */
int passed_tests = 0; /**< Počet úspěšně prošlých testů */

// Pomocné funkce pro testování

/**
 * @brief Spustí jeden test a vypíše výsledek.
 *
 * @param test_name Název testu, který se provádí.
 * @param condition Podmínka, která určuje, zda test prošel nebo selhal.
 *
 * Tato funkce zvyšuje počítadlo celkových testů a v závislosti na výsledku podmínky
 * také počítadlo úspěšných testů. Vypisuje výsledek testu do konzole.
 */
void run_test(const char* test_name, bool condition) {
    total_tests++;
    printf("----------------------------------------\n");
    if (condition) {
        printf(TEST_PASSED_COLOR "[PASSED] %s\n" TEST_RESET_COLOR, test_name);
        passed_tests++;
    } else {
        printf(TEST_FAILED_COLOR "[FAILED] %s\n" TEST_RESET_COLOR, test_name);
    }
    printf("----------------------------------------\n");
}

/**
 * @brief Vytiskne souhrn výsledků testů.
 *
 * Tato funkce vypíše celkový počet testů a počet úspěšných testů.
 */
void print_test_summary() {
    printf("\nTesty dokončeny\n");
    printf("\nCelkové shrnutí: %d/%d testů úspěšných.\n", passed_tests, total_tests);
}