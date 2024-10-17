/**
 * @file orchestrator.c
 * @brief Orchestrator komponenta pro MicroMind - Modulární AI Framework
 *
 * Tento soubor obsahuje implementaci orchestrátoru, který řídí datový tok mezi moduly,
 * spravuje modulární architekturu, zajišťuje paralelní zpracování úloh a integruje REST API.
 *
 * @author
 * @date
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "microhttpd.h"

// Definice portu pro REST API
#define PORT 8888

// Maximální počet vláken v thread poolu
#define MAX_THREADS 10

/**
 * @struct Data
 * @brief Struktura pro data zpracovávaná frameworkem
 *
 * Tato struktura obsahuje vstupní text a výsledky z jednotlivých modulů,
 * jako je detekce jazyka, sentimentální analýza, detekce tématu a generování odpovědi.
 */
typedef struct {
    char *input_text;    /**< Vstupní text pro zpracování */
    char *language;      /**< Detekovaný jazyk */
    char *sentiment;     /**< Detekovaný sentiment */
    char *topic;         /**< Detekované téma */
    char *response;      /**< Generovaná odpověď */
} Data;

/**
 * @struct Module
 * @brief Struktura pro modul v frameworku
 *
 * Tato struktura definuje modul s názvem a funkčními ukazateli pro inicializaci,
 * zpracování dat a shutdown. Dále obsahuje ukazatel na další modul pro vytvoření
 * seznamu modulů.
 */
typedef struct Module {
    char name[50];                                  /**< Název modulu */
    int (*init)(struct Module *module);             /**< Funkční ukazatel pro inicializaci modulu */
    int (*process)(struct Module *module, Data *data); /**< Funkční ukazatel pro zpracování dat */
    int (*shutdown)(struct Module *module);         /**< Funkční ukazatel pro shutdown modulu */
    struct Module *next;                             /**< Ukazatel na další modul v seznamu */
} Module;

/**
 * @struct Orchestrator
 * @brief Struktura pro orchestrator
 *
 * Tato struktura spravuje seznam modulů, mutex a podmínku pro synchronizaci vláken,
 * thread pool a stav orchestratoru (spuštěn nebo zastaven).
 */
typedef struct {
    Module *modules;              /**< Ukazatel na seznam modulů */
    pthread_mutex_t lock;         /**< Mutex pro synchronizaci přístupu k modulům */
    pthread_cond_t cond;          /**< Podmínka pro signalizaci vláken o nových úlohách */
    pthread_t threads[MAX_THREADS]; /**< Pole vláken v thread poolu */
    int thread_count;             /**< Počet vláken v thread poolu */
    int stop;                     /**< Flag pro zastavení orchestratoru */
} Orchestrator;

// Globální instance orchestratoru
Orchestrator orchestrator;

/**
 * @brief Inicializace orchestratoru
 *
 * Inicializuje orchestrator, nastaví proměnné, inicializuje mutex a podmínku.
 * Spustí thread pool s definovaným počtem vláken.
 *
 * @param orch Ukazatel na orchestrator strukturu
 * @return 0 při úspěchu, -1 při chybě
 */
int orchestrator_init(Orchestrator *orch) {
    orch->modules = NULL;
    orch->thread_count = MAX_THREADS;
    orch->stop = 0;
    pthread_mutex_init(&orch->lock, NULL);
    pthread_cond_init(&orch->cond, NULL);

    // Inicializace thread poolu
    for(int i = 0; i < orch->thread_count; i++) {
        if(pthread_create(&orch->threads[i], NULL, &thread_worker, orch) != 0) {
            perror("Failed to create thread");
            return -1;
        }
    }

    return 0;
}

/**
 * @brief Přidání modulu do orchestratoru
 *
 * Přidá nový modul do seznamu modulů orchestratoru. Používá mutex pro zajištění
 * thread safety při přidávání modulu.
 *
 * @param orch Ukazatel na orchestrator strukturu
 * @param module Ukazatel na modul, který má být přidán
 * @return 0 při úspěchu, -1 při chybě
 */
int add_module(Orchestrator *orch, Module *module) {
    pthread_mutex_lock(&orch->lock);
    module->next = orch->modules;
    orch->modules = module;
    pthread_cond_signal(&orch->cond); // Signalizace vláknům o nové úloze
    pthread_mutex_unlock(&orch->lock);
    return 0;
}

/**
 * @brief Odstranění modulu z orchestratoru
 *
 * Odstraní modul ze seznamu modulů podle jeho názvu. Zavolá funkci shutdown modulu
 * a uvolní jeho paměť.
 *
 * @param orch Ukazatel na orchestrator strukturu
 * @param name Název modulu, který má být odstraněn
 * @return 0 při úspěchu, -1 pokud modul nebyl nalezen
 */
int remove_module(Orchestrator *orch, const char *name) {
    pthread_mutex_lock(&orch->lock);
    Module *current = orch->modules;
    Module *prev = NULL;

    while(current != NULL) {
        if(strcmp(current->name, name) == 0) {
            if(prev == NULL) {
                orch->modules = current->next;
            } else {
                prev->next = current->next;
            }
            current->shutdown(current);
            free(current);
            pthread_mutex_unlock(&orch->lock);
            return 0;
        }
        prev = current;
        current = current->next;
    }

    pthread_mutex_unlock(&orch->lock);
    return -1; // Modul nenalezen
}

/**
 * @brief Zpracování dat orchestratoru
 *
 * Prochází seznam modulů a volá jejich funkci process pro zpracování dat.
 *
 * @param orch Ukazatel na orchestrator strukturu
 * @param data Ukazatel na strukturu Data, která obsahuje data pro zpracování
 */
void process_data(Orchestrator *orch, Data *data) {
    pthread_mutex_lock(&orch->lock);
    Module *current = orch->modules;

    while(current != NULL) {
        current->process(current, data);
        current = current->next;
    }

    pthread_mutex_unlock(&orch->lock);
}

/**
 * @brief Funkce thread poolu pro zpracování úloh
 *
 * Každé vlákno v thread poolu čeká na úlohu. Jakmile je úloha dostupná,
 * zpracuje data pomocí process_data funkce a uvolní paměť.
 *
 * @param arg Ukazatel na orchestrator strukturu
 * @return NULL
 */
void *thread_worker(void *arg) {
    Orchestrator *orch = (Orchestrator *)arg;

    while(1) {
        pthread_mutex_lock(&orch->lock);

        // Čekání na úlohu
        while(!orch->stop && orch->modules == NULL) {
            pthread_cond_wait(&orch->cond, &orch->lock);
        }

        if(orch->stop) {
            pthread_mutex_unlock(&orch->lock);
            break;
        }

        // Získání dat pro zpracování (zjednodušený příklad)
        Data *data = malloc(sizeof(Data));
        if(data == NULL) {
            perror("Failed to allocate memory for data");
            pthread_mutex_unlock(&orch->lock);
            continue;
        }
        data->input_text = strdup("Příklad vstupního textu");
        data->language = NULL;
        data->sentiment = NULL;
        data->topic = NULL;
        data->response = NULL;

        pthread_mutex_unlock(&orch->lock);

        // Zpracování dat
        process_data(orch, data);

        // Uvolnění paměti
        free(data->input_text);
        free(data);
    }

    return NULL;
}

/**
 * @brief Shutdown orchestratoru
 *
 * Zastaví orchestrator, počká na ukončení všech vláken a zavolá shutdown funkce
 * všech modulů. Uvolní také veškeré alokované zdroje.
 *
 * @param orch Ukazatel na orchestrator strukturu
 * @return 0 při úspěchu, -1 při chybě
 */
int orchestrator_shutdown(Orchestrator *orch) {
    pthread_mutex_lock(&orch->lock);
    orch->stop = 1;
    pthread_cond_broadcast(&orch->cond);
    pthread_mutex_unlock(&orch->lock);

    // Čekání na ukončení vláken
    for(int i = 0; i < orch->thread_count; i++) {
        pthread_join(orch->threads[i], NULL);
    }

    // Shutdown všech modulů
    pthread_mutex_lock(&orch->lock);
    Module *current = orch->modules;
    while(current != NULL) {
        current->shutdown(current);
        Module *tmp = current;
        current = current->next;
        free(tmp);
    }
    orch->modules = NULL;
    pthread_mutex_unlock(&orch->lock);

    pthread_mutex_destroy(&orch->lock);
    pthread_cond_destroy(&orch->cond);

    return 0;
}

/* 
 * Příklad implementace modulu pro rozpoznání jazyka
 */

/**
 * @brief Inicializace modulu pro rozpoznání jazyka
 *
 * @param module Ukazatel na modul, který má být inicializován
 * @return 0 při úspěchu, -1 při chybě
 */
int language_detection_init(Module *module) {
    printf("Inicializace modulu: %s\n", module->name);
    // Inicializační kód
    return 0;
}

/**
 * @brief Zpracování dat modulů pro rozpoznání jazyka
 *
 * @param module Ukazatel na modul, který zpracovává data
 * @param data Ukazatel na strukturu Data obsahující data pro zpracování
 * @return 0 při úspěchu, -1 při chybě
 */
int language_detection_process(Module *module, Data *data) {
    printf("Zpracování modulu: %s\n", module->name);
    // Simulace detekce jazyka
    data->language = strdup("Czech");
    return 0;
}

/**
 * @brief Shutdown modulu pro rozpoznání jazyka
 *
 * @param module Ukazatel na modul, který má být ukončen
 * @return 0 při úspěchu, -1 při chybě
 */
int language_detection_shutdown(Module *module) {
    printf("Shutdown modulu: %s\n", module->name);
    // Cleanup kód
    return 0;
}

/* 
 * Příklad implementace modulu pro sentimentální analýzu
 */

/**
 * @brief Inicializace modulu pro sentimentální analýzu
 *
 * @param module Ukazatel na modul, který má být inicializován
 * @return 0 při úspěchu, -1 při chybě
 */
int sentiment_analysis_init(Module *module) {
    printf("Inicializace modulu: %s\n", module->name);
    // Inicializační kód
    return 0;
}

/**
 * @brief Zpracování dat modulů pro sentimentální analýzu
 *
 * @param module Ukazatel na modul, který zpracovává data
 * @param data Ukazatel na strukturu Data obsahující data pro zpracování
 * @return 0 při úspěchu, -1 při chybě
 */
int sentiment_analysis_process(Module *module, Data *data) {
    printf("Zpracování modulu: %s\n", module->name);
    // Simulace sentimentální analýzy
    data->sentiment = strdup("Positive");
    return 0;
}

/**
 * @brief Shutdown modulu pro sentimentální analýzu
 *
 * @param module Ukazatel na modul, který má být ukončen
 * @return 0 při úspěchu, -1 při chybě
 */
int sentiment_analysis_shutdown(Module *module) {
    printf("Shutdown modulu: %s\n", module->name);
    // Cleanup kód
    return 0;
}

/* 
 * REST API handler pro přijímání dat
 */

/**
 * @brief Handler pro REST API spojení
 *
 * Tento handler přijímá pouze POST požadavky a simuluje zpracování dat.
 * V reálném nasazení by zde bylo zpracování vstupních dat a jejich předání orchestratoru.
 *
 * @param cls Nepoužitý argument
 * @param connection Ukazatel na MHD_Connection strukturu
 * @param url URL požadavku
 * @param method HTTP metoda požadavku
 * @param version HTTP verze požadavku
 * @param upload_data Data přenášená v požadavku
 * @param upload_data_size Velikost dat přenášených v požadavku
 * @param con_cls Nepoužitý argument
 * @return MHD_YES při úspěšném zpracování, MHD_NO při neúspěchu
 */
int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "POST")) {
        // Pouze POST požadavky jsou přijímány
        return MHD_NO;
    }

    if (*con_cls == NULL) {
        // Přijetí nového spojení
        *con_cls = strdup("");
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        // Zpracování přijatých dat
        // Zjednodušený příklad: ignorování dat
        *upload_data_size = 0;
        return MHD_YES;
    }

    // Vytvoření odpovědi
    const char *response_str = "Data přijata a zpracována";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_str),
                                                                    (void *)response_str,
                                                                    MHD_RESPMEM_PERSISTENT);
    if (response == NULL) {
        return MHD_NO;
    }
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

/**
 * @brief Hlavní funkce orchestratoru
 *
 * Inicializuje orchestrator, přidává moduly, spouští REST API server a běží v hlavní smyčce
 * dokud není proces ukončen (např. Ctrl+C).
 *
 * @param argc Počet argumentů příkazové řádky
 * @param argv Pole argumentů příkazové řádky
 * @return EXIT_SUCCESS při úspěšném ukončení, EXIT_FAILURE při chybě
 */
int main(int argc, char *argv[]) {
    // Inicializace orchestratoru
    if (orchestrator_init(&orchestrator) != 0) {
        fprintf(stderr, "Chyba při inicializaci orchestratoru.\n");
        return EXIT_FAILURE;
    }

    // Vytvoření a přidání modulů

    // Modul pro rozpoznání jazyka
    Module *lang_module = malloc(sizeof(Module));
    if(lang_module == NULL) {
        perror("Failed to allocate memory for language_detection module");
        orchestrator_shutdown(&orchestrator);
        return EXIT_FAILURE;
    }
    strcpy(lang_module->name, "Language Detection");
    lang_module->init = language_detection_init;
    lang_module->process = language_detection_process;
    lang_module->shutdown = language_detection_shutdown;
    add_module(&orchestrator, lang_module);
    if(lang_module->init(lang_module) != 0) {
        fprintf(stderr, "Chyba při inicializaci Language Detection modulu.\n");
        orchestrator_shutdown(&orchestrator);
        return EXIT_FAILURE;
    }

    // Modul pro sentimentální analýzu
    Module *sentiment_module = malloc(sizeof(Module));
    if(sentiment_module == NULL) {
        perror("Failed to allocate memory for sentiment_analysis module");
        orchestrator_shutdown(&orchestrator);
        return EXIT_FAILURE;
    }
    strcpy(sentiment_module->name, "Sentiment Analysis");
    sentiment_module->init = sentiment_analysis_init;
    sentiment_module->process = sentiment_analysis_process;
    sentiment_module->shutdown = sentiment_analysis_shutdown;
    add_module(&orchestrator, sentiment_module);
    if(sentiment_module->init(sentiment_module) != 0) {
        fprintf(stderr, "Chyba při inicializaci Sentiment Analysis modulu.\n");
        orchestrator_shutdown(&orchestrator);
        return EXIT_FAILURE;
    }

    // Spuštění REST API serveru
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Chyba při spuštění REST API serveru.\n");
        orchestrator_shutdown(&orchestrator);
        return EXIT_FAILURE;
    }

    printf("MicroMind Orchestrator běží na portu %d.\n", PORT);
    printf("Stiskněte Ctrl+C pro ukončení.\n");

    // Hlavní smyčka
    while(1) {
        sleep(1);
    }

    // Shutdown orchestratoru a REST API serveru
    MHD_stop_daemon(daemon);
    orchestrator_shutdown(&orchestrator);

    return EXIT_SUCCESS;
}
