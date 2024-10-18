#include "../include/error_handling.h"

/**
 * @brief Zpracuje chybu s možností ukončení programu.
 *
 * Loguje chybovou zprávu, uzavírá logger a bezpečně ukončuje program s daným kódem.
 *
 * @param message Chybová zpráva.
 * @param exit_code Kód, s jakým se program ukončí.
 * @return Nekonečný návratový typ, funkce nikdy nevrátí.
 */
int handle_error(const char *message, int exit_code) {
    LOG_MESSAGE(LOG_ERROR, "Chyba: %s", message);
    framework_logger_close();
    exit(exit_code);
    return -1; // Tato řádka nebude nikdy dosažena, ale je zde pro úplnost
}
