#include "../include/logger.h"
#include <time.h>
#include <stdarg.h>

// Barevné kódy pro terminál
#define COLOR_RESET   "\033[0m"
#define COLOR_DEBUG   "\033[36m" // Cyan
#define COLOR_INFO    "\033[32m" // Green
#define COLOR_WARN    "\033[33m" // Yellow
#define COLOR_ERROR   "\033[31m" // Red

/** @brief Otevřený logovací soubor. */
static FILE *log_file = NULL;

/**
 * @brief Inicializuje logger.
 *
 * Otevírá logovací soubor pro zápis logovacích zpráv.
 *
 * @param log_file_path Cesta k logovacímu souboru.
 * @return 0 při úspěchu, -1 při selhání.
 */
int framework_logger_init(const char *log_file_path) {
    log_file = fopen(log_file_path, "a");
    if (!log_file) {
        fprintf(stderr, "Nepodařilo se otevřít logovací soubor: %s\n", log_file_path);
        return -1;
    }
    return 0;
}

/**
 * @brief Uzavírá logger.
 *
 * Zavírá otevřený logovací soubor.
 */
void framework_logger_close() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

/**
 * @brief Implementace log_message s barevným výstupem do terminálu.
 *
 * Loguje zprávy na základě zadané úrovně. Zprávy jsou zapisovány do logovacího souboru a zobrazovány v terminálu s barevným výstupem.
 *
 * @param level Úroveň logování.
 * @param file Název souboru, odkud byla zpráva logována.
 * @param line Číslo řádku v souboru, odkud byla zpráva logována.
 * @param format Formátovací řetězec (podobný printf).
 * @param ... Proměnné argumenty pro formátovací řetězec.
 */
void log_message(LogLevel level, const char *file, int line, const char *format, ...) {
    if (!log_file) {
        fprintf(stderr, "Logger není inicializován.\n");
        return;
    }

    const char *level_str;
    const char *color;
    switch (level) {
        case LOG_DEBUG:
            level_str = "DEBUG";
            color = COLOR_DEBUG;
            break;
        case LOG_INFO:
            level_str = "INFO";
            color = COLOR_INFO;
            break;
        case LOG_WARN:
            level_str = "WARN";
            color = COLOR_WARN;
            break;
        case LOG_ERROR:
            level_str = "ERROR";
            color = COLOR_ERROR;
            break;
        default:
            level_str = "UNKNOWN";
            color = COLOR_RESET;
            break;
    }

    // Získání aktuálního času
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str)-1, "%Y-%m-%d %H:%M:%S", t);

    // Zpracování proměnných argumentů
    va_list args;
    va_start(args, format);

    // Logování do souboru
    fprintf(log_file, "[%s] [%s] (%s:%d) ", time_str, level_str, file, line);
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");
    fflush(log_file);

    // Logování do terminálu s barevným výstupem
    printf("%s[%s] [%s] (%s:%d) ", color, time_str, level_str, file, line);
    va_start(args, format); // Reset args
    vprintf(format, args);
    va_end(args);
    printf("%s\n", COLOR_RESET);
}
