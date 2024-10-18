#ifndef MINDFRAME_LOGGER_H
#define MINDFRAME_LOGGER_H

#include "mindframe.h"

/**
 * @brief Inicializuje logger.
 *
 * Otevírá logovací soubor pro zápis logovacích zpráv.
 *
 * @param log_file_path Cesta k logovacímu souboru.
 * @return 0 při úspěchu, -1 při selhání.
 */
int framework_logger_init(const char *log_file_path);

/**
 * @brief Uzavírá logger.
 *
 * Zavírá otevřený logovací soubor.
 */
void framework_logger_close();

#endif // MINDFRAME_LOGGER_H
