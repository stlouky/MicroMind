# MindFrame Framework Documentation

## **Obsah**

1. [Úvod](#úvod)
2. [Funkce Frameworku](#funkce-frameworku)
3. [Instalace](#instalace)
4. [Začínáme](#začínáme)
5. [API Reference](#api-reference)
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
Výstup:

css
Zkopírovat kód
[2024-04-27 10:00:00] [INFO] (main.c:10) Aplikace byla spuštěna.
API Reference
Makra
SAFE_FREE(ptr)
Bezpečné uvolnění paměti a nastavení ukazatele na NULL.

c
Zkopírovat kód
SAFE_FREE(buffer);
SAFE_ALLOC(ptr, size)
Bezpečná alokace paměti s kontrolou úspěšnosti. Pokud alokace selže, dojde k logování chyby a ukončení programu.

c
Zkopírovat kód
SAFE_ALLOC(buffer, sizeof(char) * 100);
LOG_MESSAGE(level, format, ...)
Jednotné logování zpráv s různými úrovněmi.

c
Zkopírovat kód
LOG_MESSAGE(LOG_INFO, "Informational message: %s", info);
RUN_TEST(description, condition)
Makro pro psaní jednotkových testů, které zjednodušuje sledování a reportování výsledků testů.

c
Zkopírovat kód
RUN_TEST("Testování funkce x", x == expected);
Funkce
void log_message(LogLevel level, const char *file, int line, const char *format, ...);
Funkce pro logování zpráv.

void initialize_test_counters();
Inicializuje počitadla testů.

void print_test_summary();
Vypíše shrnutí výsledků testů.

int handle_error(const char *message, int exit_code);
Zpracuje chybu s možností ukončení programu.

Příklady Použití
Logování
Ukázka logování různých úrovní zpráv.

c
Zkopírovat kód
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
Výstup v terminálu:

less
Zkopírovat kód
[2024-04-27 10:05:00] [DEBUG] (example.c:6) Toto je debug zpráva.
[2024-04-27 10:05:00] [INFO] (example.c:7) Toto je informační zpráva.
[2024-04-27 10:05:00] [WARN] (example.c:8) Toto je varovná zpráva.
[2024-04-27 10:05:00] [ERROR] (example.c:9) Toto je chybová zpráva.
Výstup v logovacím souboru (logs/mindframe.log):

less
Zkopírovat kód
[2024-04-27 10:05:00] [DEBUG] (example.c:6) Toto je debug zpráva.
[2024-04-27 10:05:00] [INFO] (example.c:7) Toto je informační zpráva.
[2024-04-27 10:05:00] [WARN] (example.c:8) Toto je varovná zpráva.
[2024-04-27 10:05:00] [ERROR] (example.c:9) Toto je chybová zpráva.
Správa Paměti
Ukázka bezpečné alokace a uvolnění paměti pomocí makra SAFE_ALLOC a SAFE_FREE.

c
Zkopírovat kód
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
Výstup:

less
Zkopírovat kód
[2024-04-27 10:10:00] [INFO] (memory_example.c:8) Buffer obsahuje: Toto je testovací řetězec.
Jednotkové Testování
Ukázka psaní a spuštění jednotkového testu pomocí RUN_TEST.

c
Zkopírovat kód
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
Výstup:

scss
Zkopírovat kód
[PASS] Test add(2, 3) == 5
[PASS] Test add(-1, 1) == 0
[PASS] Test add(0, 0) == 0

Shrnutí testů: 3/3 testů prošlo.
Error Handling
Ukázka konzistentního zpracování chyb pomocí handle_error.

c
Zkopírovat kód
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
Výstup:

less
Zkopírovat kód
[2024-04-27 10:15:00] [ERROR] (error_handling_example.c:7) Nepodařilo se otevřít soubor.
Program se ukončí s chybovým kódem 1.

CI/CD Integrace
Co je CI/CD?
CI/CD (Continuous Integration/Continuous Deployment) je soubor praktik a nástrojů, které automatizují procesy vývoje softwaru, zajišťují rychlejší a spolehlivější dodávku kódu do produkčního prostředí.

Continuous Integration (CI): Pravidelné integrace kódu do společného repozitáře s automatizovaným buildem a testováním.
Continuous Deployment/Delivery (CD): Automatické nasazení kódu do produkčního prostředí po úspěšném průchodu CI procesem.
Příklad GitHub Actions Workflow (.github/workflows/ci.yml)
Níže je příklad konfigurace CI/CD pipeline pomocí GitHub Actions, která automaticky sestaví projekt, spustí testy a zkontroluje paměťové úniky pomocí Valgrind.

yaml
Zkopírovat kód
name: CI

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build-and-test:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout Kódu
      uses: actions/checkout@v2

    - name: Instalace Závislostí
      run: sudo apt-get update && sudo apt-get install -y gcc make valgrind

    - name: Sestavení Frameworku
      run: |
        cd framework
        make
        cd ..

    - name: Sestavení Projektu
      run: make

    - name: Spuštění Testů
      run: make test

    - name: Kontrola Paměťových Úniků
      run: valgrind --leak-check=full ./build/main
Vysvětlení Kroků:
Checkout Kódu: Stáhne aktuální kód z repozitáře.
Instalace Závislostí: Nainstaluje potřebné nástroje jako GCC, Make a Valgrind.
Sestavení Frameworku: Sestaví MindFrame framework.
Sestavení Projektu: Sestaví hlavní program.
Spuštění Testů: Spustí jednotkové testy.
Kontrola Paměťových Úniků: Provádí kontrolu paměťových úniků pomocí Valgrind.
Generování Dokumentace pomocí Doxygenu
Co je Doxygen?
Doxygen je nástroj pro generování dokumentace z komentářů v kódu. Umožňuje automaticky vytvářet přehlednou a strukturovanou dokumentaci ve formátech jako HTML, LaTeX, PDF atd.

Příklad Použití Doxygenu s MindFrame
1. Instalace Doxygenu
Pro instalaci Doxygenu použijte následující příkaz (na Ubuntu):

bash
Zkopírovat kód
sudo apt-get install doxygen doxygen-gui graphviz
2. Vytvoření Konfiguračního Souboru
V kořenovém adresáři projektu vytvořte konfigurační soubor Doxyfile pomocí příkazu:

bash
Zkopírovat kód
doxygen -g Doxyfile
3. Úprava Konfiguračního Souboru
Otevřete Doxyfile a upravte následující položky:

ini
Zkopírovat kód
# Projektové informace
PROJECT_NAME           = "MindFrame"
OUTPUT_DIRECTORY       = "docs"
GENERATE_HTML          = YES
GENERATE_LATEX         = NO
INPUT                  = framework/include framework/src
FILE_PATTERNS          = *.h *.c
RECURSIVE              = YES
4. Přidání Komentářů do Kódu
Přidejte komentáře ve formátu Doxygen k vašim funkcím a makrám.

c
Zkopírovat kód
/**
 * @brief Bezpečné uvolnění paměti a nastavení ukazatele na NULL.
 *
 * Tento makro zajišťuje, že uvolňovaná paměť je správně uvolněna a ukazatel je nastaven na NULL, což zabraňuje přístupům k již uvolněné paměti.
 *
 * @param ptr Ukazatel na paměť, která má být uvolněna.
 */
#define SAFE_FREE(ptr) do { \
    if (ptr) { \
        free(ptr); \
        ptr = NULL; \
    } \
} while(0)
5. Generování Dokumentace
Spusťte Doxygen s konfigurací Doxyfile:

bash
Zkopírovat kód
doxygen Doxyfile
Dokumentace bude vygenerována v adresáři docs/html. Otevřete soubor index.html v prohlížeči pro zobrazení dokumentace.

Best Practices
Konzistentní Styl Kódu:

Dodržujte jednotný styl kódu napříč celým projektem. Používejte nástroje jako clang-format pro automatické formátování.
Příklad .clang-format:

yaml
Zkopírovat kód
BasedOnStyle: LLVM
IndentWidth: 4
ColumnLimit: 100
Modularita:

Udržujte kód modulární, aby byly jednotlivé komponenty snadno znovu použitelné a nezávislé na ostatních částech systému.
Dokumentace Kódu:

Dokumentujte klíčové funkce a struktury kódu pomocí komentářů, což usnadní pochopení a údržbu kódu.
c
Zkopírovat kód
/**
 * @brief Inicializuje orchestrátor.
 *
 * @return Pointer na orchestrátor, nebo NULL v případě chyby.
 */
Orchestrator* create_orchestrator();
Automatizované Testování:

Rozšiřujte sadu jednotkových testů a integrujte je do CI/CD pipeline pro rychlou detekci chyb.
Správa Paměti:

Používejte nástroje jako Valgrind pro detekci paměťových úniků a dalších chyb ve správě paměti.
bash
Zkopírovat kód
valgrind --leak-check=full ./build/main
Bezpečnostní Praktiky:

Implementujte robustní validaci a sanitaci všech vstupů ve všech modulech, aby se zabránilo potenciálním bezpečnostním útokům.
c
Zkopírovat kód
void safe_function(const char *input) {
    ASSERT(input != NULL, "Input cannot be NULL");

    // Další bezpečnostní kontroly...
}
Monitorování Výkonu:

Pravidelně profilujte aplikaci pomocí nástrojů jako gprof nebo perf a optimalizujte identifikovaná úzká místa.
bash
Zkopírovat kód
gcc -pg -o build/main src/main.c src/orchestrator.c -L./framework -lmindframe $(CFLAGS) $(LDFLAGS)
./build/main
gprof build/main gmon.out > analysis.txt
Závěr
Framework MindFrame poskytuje silný a flexibilní základ pro vývoj softwarových aplikací v jazyce C. Díky bezpečné správě paměti, pokročilému logování, jednotkovému testování a konzistentnímu zpracování chyb výrazně zvyšuje efektivitu a kvalitu vývoje. Dodržováním doporučených best practices zajistíte, že váš projekt bude robustní, rozšiřitelný a snadno udržitelný.

Pokud budete potřebovat další pomoc nebo konzultaci ohledně konkrétních částí frameworku, neváhejte se na mě obrátit!

