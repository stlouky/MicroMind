/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * common.c - Implementace společných utilit pro projekt MicroMind
 *
 * Tento soubor obsahuje implementace funkcí pro logování a práci s pamětí,
 * které jsou využívány napříč projektem MicroMind.
 */

#include "common.h"
#include <unistd.h> // pro isatty
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdarg.h>

// Proměnná pro správu úrovně logování
/**
 * @brief Globální proměnná určující aktuální úroveň logování.
 *
 * Tato proměnná určuje, jaké zprávy budou logovány v závislosti na jejich úrovni.
 */
LogLevel current_log_level = LOG_LEVEL_INFO;
static pthread_mutex_t log_level_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t free_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Nastaví aktuální úroveň logování.
 *
 * Implementace funkce pro nastavení globální úrovně logování.
 *
 * @param level Úroveň logování, která má být nastavena.
 */
void set_log_level(LogLevel level) {
    pthread_mutex_lock(&log_level_mutex);
    current_log_level = level;
    pthread_mutex_unlock(&log_level_mutex);
}

/**
 * @brief Získá aktuální úroveň logování.
 *
 * @return Aktuální úroveň logování.
 */
LogLevel get_log_level(void) {
    pthread_mutex_lock(&log_level_mutex);
    LogLevel level = current_log_level;
    pthread_mutex_unlock(&log_level_mutex);
    return level;
}

/**
 * @brief Vrací barvu pro výstup v terminálu podle úrovně logování.
 *
 * Implementace funkce pro získání ANSI kódu barvy odpovídající úrovni logování.
 *
 * @param level Úroveň logování.
 * @return Řetězec obsahující ANSI kód barvy.
 */
const char* get_log_color(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG:
            return BLUE_COLOR;
        case LOG_LEVEL_INFO:
            return GREEN_COLOR;
        case LOG_LEVEL_WARNING:
            return "\033[33m"; // Žlutá
        case LOG_LEVEL_ERROR:
            return RED_COLOR;
        default:
            return RESET_COLOR;
    }
}

/**
 * @brief Bezpečné uvolnění alokované paměti.
 *
 * Implementace funkce pro bezpečné uvolnění paměti a nastavení ukazatele na NULL.
 *
 * @param ptr Ukazatel na ukazatel na paměť, která má být uvolněna.
 */
void safe_free(void **ptr) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }

    pthread_mutex_lock(&free_mutex);
    free(*ptr);
    *ptr = NULL;
    pthread_mutex_unlock(&free_mutex);
}

/**
 * @brief Vypíše logovací zprávu.
 *
 * Implementace funkce pro logování zpráv do standardního chybového výstupu.
 *
 * @param level Úroveň logování zprávy.
 * @param func Název funkce, která logovací zprávu generuje.
 * @param format Formátovací řetězec ve stylu printf.
 */
void log_message(LogLevel level, const char* func, const char* format, ...) {
    pthread_mutex_lock(&log_level_mutex);
    LogLevel current_level = current_log_level;
    pthread_mutex_unlock(&log_level_mutex);

    if (level < current_level) {
        return;
    }

    // Získání času pomocí thread-safe funkce
    time_t now = time(NULL);
    struct tm tstruct;
    char time_buffer[50];
    if (localtime_r(&now, &tstruct) == NULL) {
        strcpy(time_buffer, "[TIME ERROR]");
    } else {
        if (strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %X", &tstruct) == 0) {
            strcpy(time_buffer, "[TIME FORMAT ERROR]");
        }
    }

    // Kontrola, zda je stderr terminál
    bool use_color = isatty(fileno(stderr));

    // Výpis logovací zprávy
    va_list args;
    va_start(args, format);
    if (use_color) {
        fprintf(stderr, "%s [%s] %s", time_buffer, func, get_log_color(level));
    } else {
        fprintf(stderr, "%s [%s] ", time_buffer, func);
    }

    // Předpokládáme, že formátovací řetězec je důvěryhodný
    vfprintf(stderr, format, args);
    
    if (use_color) {
        fprintf(stderr, "%s\n", RESET_COLOR);
    } else {
        fprintf(stderr, "\n");
    }
    va_end(args);
}
