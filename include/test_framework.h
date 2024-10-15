#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Barvy pro výstup
#define TEST_PASSED_COLOR "\033[32m" /**< ANSI kód pro zelenou barvu, použitou při úspěšném testu */
#define TEST_FAILED_COLOR "\033[31m"  /**< ANSI kód pro červenou barvu, použitou při neúspěšném testu */
#define TEST_RESET_COLOR  "\033[0m"  /**< ANSI kód pro reset barevného výstupu */

// Počítadla testů
extern int total_tests;  /**< Celkový počet spuštěných testů */
extern int passed_tests; /**< Počet úspěšně prošlých testů */

// Makro pro snadné testování podmínky
/**
 * @brief Makro pro spuštění testu.
 *
 * @param test_name Název testu, který se provádí.
 * @param condition Podmínka, která určuje, zda test prošel nebo selhal.
 *
 * Toto makro volá funkci run_test s názvem testu a podmínkou.
 */
#define RUN_TEST(test_name, condition) do { \
    run_test((test_name), (condition)); \
} while (0)

// Funkce pro spouštění testů
/**
 * @brief Spustí jeden test a vypíše výsledek.
 *
 * @param test_name Název testu, který se provádí.
 * @param condition Podmínka, která určuje, zda test prošel nebo selhal.
 *
 * Tato funkce zvyšuje počítadlo celkových testů a v závislosti na výsledku podmínky
 * také počítadlo úspěšných testů. Vypisuje výsledek testu do konzole.
 */
void run_test(const char* test_name, bool condition);

#endif // TEST_FRAMEWORK_H