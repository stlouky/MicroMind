 /* SPDX-License-Identifier: GPL-2.0-only */
/*
 * test_common.c - Testovací soubor pro testování funkcí z common.c pomocí testovacího rámce
 *
 * Tento soubor obsahuje testy pro funkce z common.c, jako jsou logování a bezpečné uvolňování paměti.
 */

#include "test_framework.h"
#include "common.h"
#include <stdlib.h>
#include <pthread.h>

/**
 * test_set_log_level - Testuje funkci set_log_level
 *
 * Nastaví různé úrovně logování a ověřuje, že jsou správně nastaveny.
 */
void test_set_log_level() {
    set_log_level(LOG_LEVEL_DEBUG);
    RUN_TEST("Set log level to DEBUG", get_log_level() == LOG_LEVEL_DEBUG);

    set_log_level(LOG_LEVEL_INFO);
    RUN_TEST("Set log level to INFO", get_log_level() == LOG_LEVEL_INFO);

    set_log_level(LOG_LEVEL_WARNING);
    RUN_TEST("Set log level to WARNING", get_log_level() == LOG_LEVEL_WARNING);

    set_log_level(LOG_LEVEL_ERROR);
    RUN_TEST("Set log level to ERROR", get_log_level() == LOG_LEVEL_ERROR);
}

/**
 * test_safe_free - Testuje funkci safe_free
 *
 * Alokuje paměť, uvolní ji pomocí safe_free a ověří, že ukazatel je nastaven na NULL.
 */
void test_safe_free() {
    // Test 1: Bezpečné uvolnění alokované paměti
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    SAFE_FREE(ptr);
    RUN_TEST("SAFE_FREE sets pointer to NULL", ptr == NULL);

    // Test 2: Uvolnění již uvolněného ukazatele
    SAFE_FREE(ptr);
    RUN_TEST("SAFE_FREE handles double free without crash", ptr == NULL);

    // Test 3: Uvolnění NULL ukazatele
    int *null_ptr = NULL;
    SAFE_FREE(null_ptr);
    RUN_TEST("SAFE_FREE handles NULL pointer without crash", null_ptr == NULL);
}

/**
 * test_log_message - Testuje funkci log_message
 *
 * Zavolá funkci log_message a ověří, že se provede bez pádu.
 */
void test_log_message() {
    // Test 1: Logování s úrovní INFO
    log_message(LOG_LEVEL_INFO, "test_log_message", "Test logovací zprávy s úrovní INFO\n");
    RUN_TEST("Log message with INFO level executes without crash", true);

    // Test 2: Logování s úrovní DEBUG (která nemusí být zobrazena)
    set_log_level(LOG_LEVEL_WARNING);
    log_message(LOG_LEVEL_DEBUG, "test_log_message", "Test logovací zprávy s úrovní DEBUG\n");
    RUN_TEST("Log message with DEBUG level does not crash when log level is WARNING", true);

    // Test 3: Logování s úrovní ERROR
    set_log_level(LOG_LEVEL_ERROR);
    log_message(LOG_LEVEL_ERROR, "test_log_message", "Test logovací zprávy s úrovní ERROR\n");
    RUN_TEST("Log message with ERROR level executes without crash", true);
}


/**
 * test_multithreaded_safe_free - Testuje funkci safe_free ve vícevláknovém prostředí
 *
 * Vytvoří několik vláken, která paralelně volají safe_free a ověřuje, že nedochází k pádům.
 */
void* thread_safe_free_test(void* arg) {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    SAFE_FREE(ptr);
    return NULL;
}

void test_multithreaded_safe_free() {
    const int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_safe_free_test, NULL) != 0) {
            RUN_TEST("Multithreaded SAFE_FREE - thread creation", false);
            return;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    RUN_TEST("Multithreaded SAFE_FREE executes without crash", true);
}

/**
 * main - Hlavní funkce pro spuštění všech testů
 *
 * Spouští všechny testy definované v tomto souboru.
 */
int main() {
    printf("\nSpouštění testů pro common.c:\n\n");

    test_set_log_level();
    test_safe_free();
    test_log_message();
    test_multithreaded_safe_free();

    printf("\nTesty dokončeny\n");
    printf("\nCelkové shrnutí: %d/%d testů úspěšných.\n", passed_tests, total_tests);

    return 0;
}