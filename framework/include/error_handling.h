#ifndef MINDFRAME_ERROR_HANDLING_H
#define MINDFRAME_ERROR_HANDLING_H

#include "mindframe.h"

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

#endif // MINDFRAME_ERROR_HANDLING_H
