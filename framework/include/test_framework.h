#ifndef MINDFRAME_TEST_FRAMEWORK_H
#define MINDFRAME_TEST_FRAMEWORK_H

#include "mindframe.h"

/**
 * @brief Inicializuje počitadla testů.
 *
 * Nastaví počitadla spuštěných a úspěšných testů na nulu.
 */
void initialize_test_counters();

/**
 * @brief Vypíše shrnutí výsledků testů.
 *
 * Vypíše celkový počet spuštěných a úspěšných testů na konci testovacího běhu.
 */
void print_test_summary();

#endif // MINDFRAME_TEST_FRAMEWORK_H
