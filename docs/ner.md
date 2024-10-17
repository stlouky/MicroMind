# Dokumentace pro NER Modul v MicroMind

## Definice Rozhraní pro NER Modul v module\_interface.h

Aby byl modul pro rozpoznávání entit (NER) kompatibilní se systémem MicroMind, musí implementovat standardizované rozhraní definované v souboru `module_interface.h`. Toto rozhraní zajišťuje, že orchestrátor může správně načítat, inicializovat a komunikovat s modulem.

### 1. Původní `module_interface.h`

Nejprve se podíváme na existující `module_interface.h`, který definuje rozhraní pro již existující moduly jako Preprocessor, Tokenizer a Classifier.

```c
#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

// Preprocessor Module Interface
typedef struct {
    int (*preprocess_text)(const char *input, char *output);
} PreprocessorInterface;

// Tokenizer Module Interface
typedef struct {
    int (*tokenize_text)(const char *input, char ***tokens, int *count);
} TokenizerInterface;

// Classifier Module Interface
typedef struct {
    int (*classify_text)(const char *input, char *output);
} ClassifierInterface;

// Orchestrator's Module Interface
typedef struct {
    PreprocessorInterface preprocessor;
    TokenizerInterface tokenizer;
    ClassifierInterface classifier;
} ModuleInterface;

#endif // MODULE_INTERFACE_H
```

### 2. Rozšíření `module_interface.h` pro NER Modul

Pro přidání nového NER modulu je třeba rozšířit `module_interface.h` o definici rozhraní pro tento modul. To zahrnuje definici nového strukturovaného typu s funkcemi, které musí NER modul implementovat.

#### Definice Funkcí pro NER Modul

- `recognize_entities`: Funkce pro rozpoznávání entit v textu.
- `initialize` a `shutdown` (volitelné): Funkce pro inicializaci a ukončení modulu, pokud je to potřeba.

#### Rozšíření Struktury `ModuleInterface`

- Přidání nového rozhraní pro NER modul do hlavní struktury orchestrátoru.

Aktualizovaný `module_interface.h`:

```c
#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

// Preprocessor Module Interface
typedef struct {
    int (*preprocess_text)(const char *input, char *output);
} PreprocessorInterface;

// Tokenizer Module Interface
typedef struct {
    int (*tokenize_text)(const char *input, char ***tokens, int *count);
} TokenizerInterface;

// Classifier Module Interface
typedef struct {
    int (*classify_text)(const char *input, char *output);
} ClassifierInterface;

// NER Module Interface
typedef struct {
    int (*recognize_entities)(const char *input, char ***entities, int *count);
} NERInterface;

// Orchestrator's Module Interface
typedef struct {
    PreprocessorInterface preprocessor;
    TokenizerInterface tokenizer;
    ClassifierInterface classifier;
    NERInterface ner; // Přidání NER rozhraní
} ModuleInterface;

#endif // MODULE_INTERFACE_H
```

#### Popis Nového Rozhraní

- `NERInterface`: Struktura obsahující funkci `recognize_entities`, která přijímá vstupní text a vrací seznam rozpoznaných entit spolu s jejich počtem.

### 3. Přidání Nového Neznámého Modulu

Při přidání nového neznámého modulu do systému MicroMind je nutné, aby byl kompatibilní s existujícím rozhraním a strukturovaným přístupem. Tento proces zahrnuje definici nového rozhraní, implementaci modulu, integraci s orchestrátorem a vytvoření testů.

### 4. Implementace NER Modulu

Po definici rozhraní je třeba implementovat NER modul, který bude tento interface splňovat.

**`modules/ner/ner.h`**:

```c
#ifndef NER_H
#define NER_H

// Deklarace funkcí, které musí NER modul implementovat
int recognize_entities(const char *input, char ***entities, int *count);

#endif // NER_H
```

**`modules/ner/ner.c`**:

```c
#include "ner.h"
#include <stdlib.h>
#include <string.h>
#include "logger.h"

// Příklad jednoduché implementace rozpoznávání entit
int recognize_entities(const char *input, char ***entities, int *count) {
    if (!input || !entities || !count) {
        log_message(LOG_ERROR, "Invalid arguments to recognize_entities.");
        return -1;
    }

    // Příklad: Rozpoznání slov začínajících velkým písmenem jako entit
    int entity_count = 0;
    char **entity_list = NULL;

    const char *token = strtok((char *)input, " ");
    while (token != NULL) {
        if (token[0] >= 'A' && token[0] <= 'Z') {
            entity_list = realloc(entity_list, sizeof(char *) * (entity_count + 1));
            if (!entity_list) {
                log_message(LOG_ERROR, "Memory allocation failed in recognize_entities.");
                return -1;
            }
            entity_list[entity_count] = strdup(token);
            if (!entity_list[entity_count]) {
                log_message(LOG_ERROR, "Memory allocation failed for entity string.");
                return -1;
            }
            entity_count++;
        }
        token = strtok(NULL, " ");
    }

    *entities = entity_list;
    *count = entity_count;

    log_message(LOG_INFO, "Recognized %d entities.", entity_count);
    return 0;
}
```

### 5. Aktualizace Orchestrátoru pro NER Modul

Orchestrátor musí být aktualizován, aby načítal a spravoval nový NER modul stejně jako ostatní moduly.

**Aktualizace ****`orchestrator.h`**:

```c
#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H

#include "module_interface.h"

// Definice orchestrátoru
typedef struct {
    ModuleInterface modules;
    // Další stavové proměnné orchestrátoru
} Orchestrator;

// Funkce pro vytvoření orchestrátoru
Orchestrator* create_orchestrator();

// Funkce pro přidání modulu do orchestrátoru
int add_module(Orchestrator *orch, const char *module_path);

// Funkce pro zpracování textu
char* process_text(Orchestrator *orch, const char *input);

// Funkce pro uvolnění orchestrátoru
void free_orchestrator(Orchestrator *orch);

#endif // ORCHESTRATOR_H
```

### 6. Implementace Nového Modulu `example.c`

Pro přidání nového modulu, například `Example`, postupujte podle těchto kroků.

#### 6.1 Definice Rozhraní pro Example Modul

**`include/module_interface.h`**:

```c
#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

// Preprocessor Module Interface
typedef struct {
    int (*preprocess_text)(const char *input, char *output);
} PreprocessorInterface;

// Tokenizer Module Interface
typedef struct {
    int (*tokenize_text)(const char *input, char ***tokens, int *count);
} TokenizerInterface;

// Classifier Module Interface
typedef struct {
    int (*classify_text)(const char *input, char *output);
} ClassifierInterface;

// NER Module Interface
typedef struct {
    int (*recognize_entities)(const char *input, char ***entities, int *count);
} NERInterface;

// Example Module Interface
typedef struct {
    int (*example_function)(const char *input, char *output);
} ExampleInterface;

// Orchestrator's Module Interface
typedef struct {
    PreprocessorInterface preprocessor;
    TokenizerInterface tokenizer;
    ClassifierInterface classifier;
    NERInterface ner;
    ExampleInterface example; // Přidání Example rozhraní
} ModuleInterface;

#endif // MODULE_INTERFACE_H
```

#### 6.2 Implementace Example Modulu

**`modules/example/example.h`**:

```c
#ifndef EXAMPLE_H
#define EXAMPLE_H

// Deklarace funkcí, které musí Example modul implementovat
int example_function(const char *input, char *output);

#endif // EXAMPLE_H
```

**`modules/example/example.c`**:

```c
#include "example.h"
#include <stdlib.h>
#include <string.h>
#include "logger.h"

// Příklad jednoduché implementace funkce pro nový modul
int example_function(const char *input, char *output) {
    if (!input || !output) {
        log_message(LOG_ERROR, "Invalid arguments to example_function.");
        return -1;
    }

    // Příklad: Zkopírování vstupu do výstupu
    strcpy(output, input);
    log_message(LOG_INFO, "Example function executed successfully.");
    return 0;
}
```

### 7. Aktualizace Orchestrátoru pro Example Modul

Orchestrátor musí být aktualizován, aby načítal a spravoval nový modul stejně jako ostatní moduly.

**Aktualizace `orchestrator.c`** pro načítání nového modulu:

```c
#include "orchestrator.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#define MAX_OUTPUT_SIZE 1024

struct Orchestrator {
    ModuleInterface modules;
    // Další stavové proměnné orchestrátoru
};

// Funkce pro vytvoření orchestrátoru
Orchestrator* create_orchestrator() {
    Orchestrator *orch = (Orchestrator *)malloc(sizeof(Orchestrator));
    if (!orch) {
        log_message(LOG_ERROR, "Failed to allocate memory for orchestrator.");
        return NULL;
    }
    memset(orch, 0, sizeof(Orchestrator));
    log_message(LOG_INFO, "Orchestrator created successfully.");
    return orch;
}

// Funkce pro přidání modulu
int add_module(Orchestrator *orch, const char *module_path) {
    if (!orch || !module_path) return -1;

    void *handle = dlopen(module_path, RTLD_LAZY);
    if (!handle) {
        log_message(LOG_ERROR, "Cannot open module %s: %s", module_path, dlerror());
        return -1;
    }

    // Reset dlerror
    dlerror();

    // Načtení symbolů podle typu modulu
    if (strstr(module_path, "example.so")) {
        int (*example_func)(const char *, char *) = dlsym(handle, "example_function");
        char *error = dlerror();
        if (error != NULL) {
            log_message(LOG_ERROR, "Cannot load symbol example_function: %s", error);
            dlclose(handle);
            return -1;
        }
        orch->modules.example.example_function = example_func;
        log_message(LOG_INFO, "Example module loaded successfully.");
    }
    // Další moduly...

    return 0;
}
```

### 8. Testování Example Modulu

Vytvořte jednotkové testy pro nový modul v adresáři `tests/` a přidejte příslušná pravidla do `tests/Makefile`.

**`tests/test_example.c`**:

```c
#include "example.h"
#include "test_framework.h"
#include "logger.h"
#include <string.h>
#include <stdlib.h>

int main() {
    initialize_test_counters();

    const char *input = "Test input";
    char output[50];
    int result = example_function(input, output);

    RUN_TEST("Example - Return value should be 0", result == 0);
    RUN_TEST("Example - Output should match input", strcmp(output, input) == 0);

    print_test_summary();
    return (tests_passed == tests_run) ? 0 : 1;
}
```

Aktualizace `tests/Makefile` pro kompilaci a spuštění testu nového modulu:

```makefile
# Přidání pravidla pro testování Example modulu
test_example: test_example.c ../modules/example/example.c ../src/logger.c test_framework.o
	$(CC) -o test_example test_example.c ../modules/example/example.c ../src/logger.c test_framework.o $(CFLAGS) $(LDFLAGS)

all: test_preprocessor test_tokenizer test_classifier test_orchestrator test_ner test_example

clean:
	rm -f test_preprocessor test_tokenizer test_classifier test_orchestrator test_ner test_example *.o
```

Tímto způsobem lze nový modul `example` úspěšně přidat, implementovat, integrovat s orchestrátorem a otestovat.

