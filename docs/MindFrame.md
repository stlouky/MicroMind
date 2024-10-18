# MindFrame Framework Documentation

## **Obsah**

1. [Úvod](#úvod)
2. [Funkce Frameworku](#funkce-frameworku)
3. [Instalace](#instalace)
4. [Začínáme](#začínáme)
5. [API Reference](#api-reference)
    - [Makra](#makra)
    - [Funkce](#funkce)
6. [Příklady Použití](#příklady-použití)
    - [Logování](#logování)
    - [Správa Paměti](#správa-paměti)
    - [Jednotkové Testování](#jednotkové-testování)
    - [Error Handling](#error-handling)
7. [CI/CD Integrace](#cicd-integrace)
8. [Generování Dokumentace pomocí Doxygenu](#generování-dokumentace-pomocí-doxygenu)
9. [Best Practices](#best-practices)
10. [Závěr](#závěr)

---

## **Úvod**

**MindFrame** je robustní a flexibilní framework navržený pro usnadnění vývoje softwarových aplikací v jazyce C. Framework poskytuje základní nástroje a makra pro správu paměti, logování, testování a zpracování chyb, což výrazně zvyšuje efektivitu a kvalitu vývoje.

---

## **Funkce Frameworku**

- **Bezpečná Správa Paměti:** Makra jako `SAFE_ALLOC` a `SAFE_FREE` pro bezpečnou alokaci a uvolňování paměti.
- **Pokročilé Logování:** Makro `LOG_MESSAGE` pro jednotné logování s různými úrovněmi (DEBUG, INFO, WARN, ERROR).
- **Jednotkové Testování:** Makro `RUN_TEST` pro jednoduché a efektivní psaní testů.
- **Error Handling:** Funkce `handle_error` pro konzistentní zpracování chyb a bezpečné ukončení programu.
- **Modularita:** Strukturální podpora pro snadné rozšiřování o nové moduly a funkce.

---

## **Instalace**

1. **Klonování Repozitáře:**

    ```bash
    git clone https://github.com/yourusername/mindframe.git
    cd mindframe
    ```

2. **Kompilace Frameworku:**

    ```bash
    cd framework
    make
    cd ..
    ```

---

## **Začínáme**

### **Inicializace Loggeru**

Před použitím logovacích funkcí je nutné inicializovat logger.

```c
#include "mindframe.h"
#include "logger.h"

int main() {
    // Inicializace loggeru
    if (framework_logger_init("logs/mindframe.log") != 0) {
        fprintf(stderr, "Nepodařilo se inicializovat MindFrame logger.\n");
        return EXIT_FAILURE;
    }

    LOG_MESSAGE(LOG_INFO, "Aplikace byla spuštěna.");

    // Vaše logika zde

    // Uzavření loggeru
    framework_logger_close();
    return EXIT_SUCCESS;
}

Výstup v logovacím souboru (logs/mindframe.log):

```css
[2024-04-27 10:00:00] [INFO] (main.c:10) Aplikace byla spuštěna.
```

## API Reference
### Makra
SAFE_FREE(ptr)
Bezpečné uvolnění paměti a nastavení ukazatele na NULL.

```c
SAFE_FREE(buffer);
```
Popis: Toto makro zajišťuje, že uvolňovaná paměť je správně uvolněna a ukazatel je nastaven na NULL, což zabraňuje přístupům k již uvolněné paměti.

SAFE_ALLOC(ptr, size)
Bezpečná alokace paměti s kontrolou úspěšnosti. Pokud alokace selže, dojde k logování chyby a ukončení programu.

```c
SAFE_ALLOC(buffer, sizeof(char) * 100);
```
Popis: Makro alokuje paměť a pokud alokace selže, loguje chybu a bezpečně ukončí program.

LOG_MESSAGE(level, format, ...)
Jednotné logování zpráv s různými úrovněmi.

```c
LOG_MESSAGE(LOG_INFO, "Informační zpráva: %s", info);
```
Popis: Makro pro logování zpráv na různých úrovních (DEBUG, INFO, WARN, ERROR) spolu s informacemi o souboru a řádku.

RUN_TEST(description, condition)
Makro pro psaní jednotkových testů, které zjednodušuje sledování a reportování výsledků testů.

```c
RUN_TEST("Testování funkce add", add(2, 3) == 5);
```
Popis: Spustí test s popisem a podmínkou. Výsledek testu je automaticky zaznamenán a zobrazen.

### Funkce
void log_message(LogLevel level, const char *file, int line, const char *format, ...);
Funkce pro logování zpráv.

Popis: Loguje zprávy na základě zadané úrovně. Zprávy jsou zapisovány do logovacího souboru a zobrazovány v terminálu s barevným výstupem.

void initialize_test_counters();
Inicializuje počitadla testů.

Popis: Inicializuje globální proměnné pro sledování počtu spuštěných a úspěšných testů.

void print_test_summary();
Vypíše shrnutí výsledků testů.

Popis: Vypíše celkový počet spuštěných a úspěšných testů na konci testovacího běhu.

int handle_error(const char *message, int exit_code);
Zpracuje chybu s možností ukončení programu.

Popis: Loguje chybovou zprávu, uzavírá logger a bezpečně ukončuje program s daným kódem.

## Příklady Použití
**Logování**
Ukázka logování různých úrovní zpráv.

```c
#include "mindframe.h"
#include "logger.h"

int main() {
    framework_logger_init("logs/mindframe.log");

    LOG_MESSAGE(LOG_DEBUG, "Toto je debug zpráva.");
    LOG_MESSAGE(LOG_INFO, "Toto je informační zpráva.");
    LOG_MESSAGE(LOG_WARN, "Toto je varovná zpráva.");
    LOG_MESSAGE(LOG_ERROR, "Toto je chybová zpráva.");

    framework_logger_close();
    return 0;
}
```
Výstup v terminálu:

```less
Zkopírovat kód
[2024-04-27 10:05:00] [DEBUG] (example.c:6) Toto je debug zpráva.
[2024-04-27 10:05:00] [INFO] (example.c:7) Toto je informační zpráva.
[2024-04-27 10:05:00] [WARN] (example.c:8) Toto je varovná zpráva.
[2024-04-27 10:05:00] [ERROR] (example.c:9) Toto je chybová zpráva.
```
Výstup v logovacím souboru (logs/mindframe.log):

```less
[2024-04-27 10:05:00] [DEBUG] (example.c:6) Toto je debug zpráva.
[2024-04-27 10:05:00] [INFO] (example.c:7) Toto je informační zpráva.
[2024-04-27 10:05:00] [WARN] (example.c:8) Toto je varovná zpráva.
[2024-04-27 10:05:00] [ERROR] (example.c:9) Toto je chybová zpráva.
```
### Správa Paměti
Ukázka bezpečné alokace a uvolnění paměti pomocí makra SAFE_ALLOC a SAFE_FREE.

```c
#include "mindframe.h"

int main() {
    framework_logger_init("logs/mindframe.log");

    char *buffer = NULL;
    SAFE_ALLOC(buffer, sizeof(char) * 256);
    strcpy(buffer, "Toto je testovací řetězec.");

    LOG_MESSAGE(LOG_INFO, "Buffer obsahuje: %s", buffer);

    SAFE_FREE(buffer);

    framework_logger_close();
    return 0;
}
```
Výstup v logovacím souboru (logs/mindframe.log):

```less
Zkopírovat kód
[2024-04-27 10:10:00] [INFO] (memory_example.c:8) Buffer obsahuje: Toto je testovací řetězec.
```
### Jednotkové Testování
Ukázka psaní a spuštění jednotkového testu pomocí RUN_TEST.

```c
#include "mindframe.h"
#include "test_framework.h"

// Příklad funkce pro testování
int add(int a, int b) {
    return a + b;
}

int main() {
    framework_logger_init("logs/mindframe.log");
    initialize_test_counters();

    RUN_TEST("Test add(2, 3) == 5", add(2, 3) == 5);
    RUN_TEST("Test add(-1, 1) == 0", add(-1, 1) == 0);
    RUN_TEST("Test add(0, 0) == 0", add(0, 0) == 0);

    print_test_summary();
    framework_logger_close();
    return (tests_passed == tests_run) ? 0 : 1;
}
```
Výstup v terminálu:

```scss
Zkopírovat kód
[PASS] Test add(2, 3) == 5
[PASS] Test add(-1, 1) == 0
[PASS] Test add(0, 0) == 0

Shrnutí testů: 3/3 testů prošlo.
```
### Error Handling
Ukázka konzistentního zpracování chyb pomocí handle_error.

```c
#include "mindframe.h"
#include "logger.h"

int main() {
    framework_logger_init("logs/mindframe.log");

    FILE *file = fopen("non_existent_file.txt", "r");
    if (!file) {
        handle_error("Nepodařilo se otevřít soubor.", EXIT_FAILURE);
    }

    // Další logika zde

    framework_logger_close();
    return 0;
}
```
Výstup v logovacím souboru (logs/mindframe.log):

```less
[2024-04-27 10:15:00] [ERROR] (error_handling_example.c:7) Nepodařilo se otevřít soubor.
```
Program se ukončí s chybovým kódem 1.

