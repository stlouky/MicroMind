/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * common.c - Implementace společných utilit pro projekt MicroMind
 *
 * Tento soubor obsahuje implementace funkcí pro logování a práci s pamětí,
 * které jsou využívány napříč projektem MicroMind.
 */

#include "../include/common.h"
#include "../include/test_framework.h"
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
 * @brief Logovací funkce pro zaznamenání chybové zprávy.
 *
 * Tato funkce vypíše chybovou zprávu na standardní chybový výstup spolu s názvem funkce,
 * ve které k chybě došlo.
 *
 * @param func Název funkce, ve které došlo k chybě.
 * @param message Text chybové zprávy, která má být zaznamenána.
 */
void log_error(const char* func, const char* message) {
    fprintf(stderr, "[ERROR] %s: %s\n", func, message);
}
