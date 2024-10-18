#include "test_framework.h"

/** @brief Globální proměnná pro sledování počtu spuštěných testů. */
int tests_run = 0;

/** @brief Globální proměnná pro sledování počtu úspěšných testů. */
int tests_passed = 0;

/**
 * @brief Inicializuje počitadla testů.
 *
 * Nastaví počitadla spuštěných a úspěšných testů na nulu.
 */
void initialize_test_counters() {
    tests_run = 0;
    tests_passed = 0;
}

/**
 * @brief Vypíše shrnutí výsledků testů.
 *
 * Vypíše celkový počet spuštěných a úspěšných testů na konci testovacího běhu.
 */
void print_test_summary() {
    printf("\nShrnutí testů: %d/%d testů prošlo.\n", tests_passed, tests_run);
}
