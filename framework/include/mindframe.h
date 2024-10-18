#ifndef MINDFRAME_H
#define MINDFRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 * @enum LogLevel
 * @brief Úrovně logování.
 */
typedef enum {
    LOG_DEBUG, /**< Debugovací zpráva */
    LOG_INFO,  /**< Informační zpráva */
    LOG_WARN,  /**< Varovná zpráva */
    LOG_ERROR  /**< Chybová zpráva */
} LogLevel;

/**
 * @brief Bezpečné uvolnění paměti a nastavení ukazatele na NULL.
 *
 * Toto makro zajišťuje, že uvolňovaná paměť je správně uvolněna a ukazatel je nastaven na NULL, což zabraňuje přístupům k již uvolněné paměti.
 *
 * @param ptr Ukazatel na paměť, která má být uvolněna.
 */
#define SAFE_FREE(ptr) do { \
    if (ptr) { \
        free(ptr); \
        ptr = NULL; \
    } \
} while(0)

/**
 * @brief Bezpečná alokace paměti s kontrolou úspěšnosti.
 *
 * Pokud alokace selže, dojde k logování chyby a bezpečnému ukončení programu.
 *
 * @param ptr Ukazatel, který bude alokován.
 * @param size Velikost paměti k alokaci v bytech.
 */
#define SAFE_ALLOC(ptr, size) do { \
    ptr = malloc(size); \
    if (!ptr) { \
        LOG_MESSAGE(LOG_ERROR, "Alokace paměti selhala pro %s", #ptr); \
        handle_error("Alokace paměti selhala", EXIT_FAILURE); \
    } \
} while(0)

/**
 * @brief Jednotné logování zpráv s různými úrovněmi.
 *
 * Toto makro volá funkci log_message s informacemi o souboru a řádku, odkud bylo makro zavoláno.
 *
 * @param level Úroveň logování (LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR).
 * @param format Formátovací řetězec (podobný printf).
 * @param ... Proměnné argumenty pro formátovací řetězec.
 */
#define LOG_MESSAGE(level, format, ...) \
    log_message(level, __FILE__, __LINE__, format, ##__VA_ARGS__)

/**
 * @brief Makro pro psaní jednotkových testů.
 *
 * Toto makro zjednodušuje sledování a reportování výsledků testů tím, že automaticky zvyšuje počitadla testů a vypisuje výsledky.
 *
 * @param description Popis testu.
 * @param condition Podmínka, která musí být splněna pro úspěch testu.
 */
#define RUN_TEST(description, condition) \
    do { \
        tests_run++; \
        if (condition) { \
            tests_passed++; \
            printf("[PASS] %s\n", description); \
        } else { \
            printf("[FAIL] %s\n", description); \
        } \
    } while(0)

/**
 * @brief Funkce pro logování zpráv.
 *
 * Loguje zprávy na základě zadané úrovně. Zprávy jsou zapisovány do logovacího souboru a zobrazovány v terminálu s barevným výstupem.
 *
 * @param level Úroveň logování.
 * @param file Název souboru, odkud byla zpráva logována.
 * @param line Číslo řádku v souboru, odkud byla zpráva logována.
 * @param format Formátovací řetězec (podobný printf).
 * @param ... Proměnné argumenty pro formátovací řetězec.
 */
void log_message(LogLevel level, const char *file, int line, const char *format, ...);

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

/**
 * @brief Zpracuje chybu s možností ukončení programu.
 *
 * Loguje chybovou zprávu, uzavírá logger a bezpečně ukončuje program s daným kódem.
 *
 * @param message Chybová zpráva.
 * @param exit_code Kód, s jakým se program ukončí.
 * @return Nekonečný návratový typ, funkce nikdy nevrátí.
 */
int handle_error(const char *message, int exit_code);

/** @brief Globální proměnná pro sledování počtu spuštěných testů. */
extern int tests_run;

/** @brief Globální proměnná pro sledování počtu úspěšných testů. */
extern int tests_passed;

#endif // MINDFRAME_H
