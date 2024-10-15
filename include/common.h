#ifndef COMMON_H
#define COMMON_H

#include <pthread.h>

// Úrovně logování
/**
 * @brief Úrovně logování pro různé typy zpráv.
 */
typedef enum {
    LOG_LEVEL_DEBUG,   /**< Podrobné ladící zprávy */
    LOG_LEVEL_INFO,    /**< Obecné informační zprávy */
    LOG_LEVEL_WARNING, /**< Varovné zprávy */
    LOG_LEVEL_ERROR    /**< Chybové zprávy */
} LogLevel;

// Proměnná pro aktuální úroveň logování
/**
 * @brief Aktuální úroveň logování, která určuje, jaké zprávy se budou zobrazovat.
 */
extern LogLevel current_log_level;

// Funkce pro nastavení a získání úrovně logování
/**
 * @brief Nastaví aktuální úroveň logování.
 *
 * @param level Úroveň logování, která má být nastavena.
 */
void set_log_level(LogLevel level);

/**
 * @brief Získá aktuální úroveň logování.
 *
 * @return Aktuální úroveň logování.
 */
LogLevel get_log_level(void);

// Funkce pro logování zpráv
/**
 * @brief Vypíše logovací zprávu na základě úrovně logování.
 *
 * @param level Úroveň logování zprávy.
 * @param func Název funkce, která generuje zprávu.
 * @param format Formátovací řetězec ve stylu printf pro zprávu.
 * @param ... Další parametry pro formátování zprávy.
 */
void log_message(LogLevel level, const char* func, const char* format, ...);

// Funkce pro bezpečné uvolnění paměti
/**
 * @brief Bezpečně uvolní alokovanou paměť a nastaví ukazatel na NULL.
 *
 * @param ptr Ukazatel na ukazatel na paměť, která má být uvolněna.
 */
void safe_free(void **ptr);

// Definice makra pro bezpečné uvolnění paměti
/**
 * @brief Makro pro bezpečné uvolnění paměti a nastavení ukazatele na NULL.
 *
 * Toto makro volá funkci safe_free, aby zajistilo, že uvolněná paměť nebude dále používána.
 */
#define SAFE_FREE(ptr) do { safe_free((void**)&(ptr)); } while(0)

// Barvy pro výstup v terminálu
/**
 * @brief Resetuje barvu terminálu na výchozí hodnotu.
 */
#define RESET_COLOR   "\033[0m"

/**
 * @brief Nastaví barvu textu na červenou (používá se typicky pro chyby).
 */
#define RED_COLOR     "\033[31m"

/**
 * @brief Nastaví barvu textu na zelenou (používá se typicky pro úspěšné zprávy).
 */
#define GREEN_COLOR   "\033[32m"

/**
 * @brief Nastaví barvu textu na modrou (používá se pro informační zprávy).
 */
#define BLUE_COLOR    "\033[34m"

// Funkce pro získání barvy logování
/**
 * @brief Vrací barvu pro výstup v terminálu podle úrovně logování.
 *
 * @param level Úroveň logování.
 * @return Řetězec obsahující ANSI kód barvy.
 */
const char* get_log_color(LogLevel level);

#endif // COMMON_H