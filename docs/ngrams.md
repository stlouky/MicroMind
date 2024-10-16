# Manuál pro soubor `ngrams.c`

Soubor `ngrams.c` je součástí projektu MicroMind a je určen k generování n-gramů ze zadaného textu. N-gramy jsou skupiny slov v textu, které mají pevnou velikost a jsou používány například při analýze jazykových vzorců. Tento modul umožňuje vytvořit n-gramy libovolné velikosti (bigramy, trigramy atd.) a poskytuje funkce pro jejich generování i bezpečné uvolnění paměti.

## Funkce souboru `ngrams.c`

### 1. `generate_ngrams(char** tokens, int token_count, int n, int* ngram_count)`

Funkce `generate_ngrams` generuje n-gramy ze zadaných tokenů.

- **Parametry**:
  - `tokens`: Pole tokenů (slov) získaných z textu.
  - `token_count`: Počet tokenů ve vstupním poli.
  - `n`: Velikost n-gramu, například 2 pro bigram nebo 3 pro trigram.
  - `ngram_count`: Ukazatel na proměnnou, kam bude uložen počet generovaných n-gramů.
- **Návratová hodnota**: Vrací pole struktur `NGram`, které obsahují všechny n-gramy vytvořené z tokenů. Pokud dojde k chybě, vrátí `NULL` a `ngram_count` bude nastaveno na `0`.
- **Využití**: Funkce se používá pro analýzu textu, kde je potřeba rozdělit text na menší části, aby bylo možné analyzovat jejich vzájemné vztahy.

Tato funkce zahrnuje několik kroků:

1. **Kontrola vstupů**: Nejprve se ověřuje, zda jsou všechny vstupy platné (např. že `tokens` není `NULL`, že `token_count` a `n` jsou platné hodnoty).
2. **Alokace paměti**: Paměť je alokována pro pole n-gramů, kde každý n-gram obsahuje `n` slov.
3. **Generování n-gramů**: Pro každý n-gram se nastaví ukazatele na příslušná slova v původním poli tokenů.
4. **Ošetření chyb**: Pokud dojde k chybě během alokace paměti, funkce uvolní již alokovanou paměť a vrátí `NULL`.

### 2. `free_allocated_ngrams_on_failure(NGram* ngramArray, int count)`

Funkce `free_allocated_ngrams_on_failure` uvolňuje paměť alokovanou pro částečně vytvořené n-gramy, pokud dojde k chybě během jejich generování.

- **Parametry**:
  - `ngramArray`: Pole n-gramů, které byly částečně vytvořeny.
  - `count`: Počet n-gramů, které byly alokovány a je třeba je uvolnit.
- **Využití**: Používá se interně funkcí `generate_ngrams`, aby se zajistilo správné uvolnění paměti při neúspěšném generování n-gramů.

### 3. `free_ngrams(NGram* ngramArray, int ngram_count)`

Funkce `free_ngrams` uvolňuje paměť alokovanou pro všechny n-gramy, které byly vytvořeny funkcí `generate_ngrams`.

- **Parametry**:
  - `ngramArray`: Pole n-gramů, které byly vytvořeny.
  - `ngram_count`: Počet n-gramů v poli `ngramArray`.
- **Využití**: Tato funkce by měla být volána vždy, když již n-gramy nejsou potřeba, aby se zabránilo únikům paměti.

## Předpokládané využití

Modul `ngrams.c` lze využít v různých scénářích, zejména při analýze textu a zpracování přirozeného jazyka. To zahrnuje například:

1. **Analýza jazykových vzorců**: N-gramy mohou být využity k analýze jazykových vzorců a frekvencí, což může být užitečné při strojovém překladu nebo vytváření jazykových modelů.
2. **Klasifikace textu**: N-gramy lze použít jako atributy pro klasifikaci textu, například při detekci spamu nebo analýze sentimentu.
3. **Generování textu**: N-gramy mohou být využity k prediktivnímu generování textu, kde se na základě předchozích slov snaží předpovědět následující slovo nebo frázi.
4. **Předzpracování dat**: Před použitím jinými AI moduly mohou být n-gramy použity k lepšímu pochopení struktury a kontextu textu.

## Použití

1. **Generování n-gramů**: Použijte funkci `generate_ngrams` pro vytvoření n-gramů z tokenizovaného textu.
2. **Zpracování n-gramů**: Následně můžete pracovat s vytvořenými n-gramy, například je použít pro analýzu nebo jako vstup pro další AI moduly.
3. **Uvolnění paměti**: Po dokončení práce s n-gramy nezapomeňte zavolat funkci `free_ngrams` pro uvolnění alokované paměti.

### Příklad kódu 1: Základní generování n-gramů

```c
#include "../include/ngrams.h"
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"Tento", "projekt", "je", "velmi", "zajímavý"};
    int token_count = 5;
    int n = 2;  // Generování bigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy\n");
        return 1;
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("\n");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

### Příklad kódu 2: Generování trigramů a práce s více sadami tokenů

```c
#include "../include/ngrams.h"
#include <stdio.h>

int main() {
    // Příklad tokenů pro dvě různé sady
    char* tokens1[] = {"Tento", "kód", "generuje", "n-gramy"};
    char* tokens2[] = {"Další", "sada", "tokenů", "pro", "testování"};
    int token_count1 = 4;
    int token_count2 = 5;
    int n = 3;  // Generování trigramů
    int ngram_count1, ngram_count2;

    // Generování n-gramů pro první sadu
    NGram* ngrams1 = generate_ngrams(tokens1, token_count1, n, &ngram_count1);
    if (ngrams1 == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy pro první sadu\n");
        return 1;
    }

    // Generování n-gramů pro druhou sadu
    NGram* ngrams2 = generate_ngrams(tokens2, token_count2, n, &ngram_count2);
    if (ngrams2 == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy pro druhou sadu\n");
        free_ngrams(ngrams1, ngram_count1);
        return 1;
    }

    // Výpis n-gramů pro obě sady
    printf("N-gramy první sady:\n");
    for (int i = 0; i < ngram_count1; i++) {
        for (int j = 0; j < ngrams1[i].size; j++) {
            printf("%s ", ngrams1[i].words[j]);
        }
        printf("\n");
    }

    printf("\nN-gramy druhé sady:\n");
    for (int i = 0; i < ngram_count2; i++) {
        for (int j = 0; j < ngrams2[i].size; j++) {
            printf("%s ", ngrams2[i].words[j]);
        }
        printf("\n");
    }

    // Uvolnění paměti
    free_ngrams(ngrams1, ngram_count1);
    free_ngrams(ngrams2, ngram_count2);

    return 0;
}
```

### Příklad kódu 3: Integrace s MicroMind AI mikromoduly

```c
#include "../include/ngrams.h"
#include "micromind_module.h"  // Fiktivní knihovna pro integraci s MicroMind
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"MicroMind", "umožňuje", "generování", "n-gramů", "pro", "AI", "moduly"};
    int token_count = 7;
    int n = 2;  // Generování bigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy");
        return 1;
    }

    // Předání n-gramů do dalšího AI modulu pro analýzu
    for (int i = 0; i < ngram_count; i++) {
        micromind_process_ngram(&ngrams[i]);  // Fiktivní funkce pro zpracování n-gramu v MicroMind AI
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

### Příklad kódu 4: Využití n-gramů v jazykovém modelu pro predikci dalšího slova

Tento příklad ukazuje, jak lze n-gramy použít k predikci následujícího slova v textu. Generujeme trigramy (n = 3) a využíváme je v jazykovém modulu MicroMind pro predikci dalšího slova. Každý n-gram je zpracován pomocí funkce `micromind_predict_next_word`, která se pokouší určit následující slovo na základě předchozích tří slov.

```c
#include "../include/ngrams.h"
#include "micromind_language_model.h"  // Fiktivní knihovna pro jazykové modelování v MicroMind
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"Tento", "jazykový", "model", "využívá", "n-gramy", "k", "predikci"};
    int token_count = 7;
    int n = 3;  // Generování trigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy");
        return 1;
    }

    // Použití n-gramů pro predikci v jazykovém modelu
    for (int i = 0; i < ngram_count; i++) {
        micromind_predict_next_word(&ngrams[i]);  // Fiktivní funkce pro predikci následujícího slova
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

### Příklad kódu 5: Využití n-gramů k rozpoznávání kontextu v konverzaci

Tento příklad ukazuje, jak lze n-gramy použít k rozpoznávání kontextu v konverzaci. Generujeme bigramy (n = 2) a používáme je v konverzačním modulu MicroMind, který se snaží určit, o čem se diskutuje, a přizpůsobit odpovědi kontextu. Každý n-gram je zpracován pomocí funkce `micromind_analyze_conversation_context`, která pomáhá rozpoznat aktuální téma konverzace.

```c
#include "../include/ngrams.h"
#include "micromind_conversation.h"  // Fiktivní knihovna pro konverzační AI v MicroMind
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"Jak", "se", "dnes", "cítíš", "?"};
    int token_count = 5;
    int n = 2;  // Generování bigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy");
        return 1;
    }

    // Použití n-gramů k analýze kontextu v konverzaci
    for (int i = 0; i < ngram_count; i++) {
        micromind_analyze_conversation_context(&ngrams[i]);  // Fiktivní funkce pro rozpoznání kontextu
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

### Příklad kódu 6: Využití n-gramů pro klasifikaci typu textu

Tento příklad ukazuje, jak lze n-gramy využít k automatické klasifikaci typu textu. Generujeme bigramy (n = 2) a používáme je v modulu MicroMind pro klasifikaci textu, například k určení, zda je text technický, obchodní nebo společenský. Každý n-gram je zpracován pomocí funkce `micromind_classify_text_type`, která přiřazuje typu textu odpovídající kategorii.

```c
#include "../include/ngrams.h"
#include "micromind_text_classification.h"  // Fiktivní knihovna pro klasifikaci textu v MicroMind
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"Tento", "dokument", "obsahuje", "informace", "o", "bezpečnosti"};
    int token_count = 6;
    int n = 2;  // Generování bigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy");
        return 1;
    }

    // Použití n-gramů pro klasifikaci typu textu
    for (int i = 0; i < ngram_count; i++) {
        micromind_classify_text_type(&ngrams[i]);  // Fiktivní funkce pro klasifikaci textu
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

### Příklad kódu 5: Využití n-gramů k rozpoznávání kontextu v konverzaci

```c
#include "../include/ngrams.h"
#include "micromind_conversation.h"  // Fiktivní knihovna pro konverzační AI v MicroMind
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"Jak", "se", "dnes", "cítíš", "?"};
    int token_count = 5;
    int n = 2;  // Generování bigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy");
        return 1;
    }

    // Použití n-gramů k analýze kontextu v konverzaci
    for (int i = 0; i < ngram_count; i++) {
        micromind_analyze_conversation_context(&ngrams[i]);  // Fiktivní funkce pro rozpoznání kontextu
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

### Příklad kódu 6: Využití n-gramů pro klasifikaci typu textu

```c
#include "../include/ngrams.h"
#include "micromind_text_classification.h"  // Fiktivní knihovna pro klasifikaci textu v MicroMind
#include <stdio.h>

int main() {
    // Příklad tokenů získaných z textu
    char* tokens[] = {"Tento", "dokument", "obsahuje", "informace", "o", "bezpečnosti"};
    int token_count = 6;
    int n = 2;  // Generování bigramů
    int ngram_count;

    // Generování n-gramů
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    if (ngrams == NULL) {
        fprintf(stderr, "Chyba: Nepodařilo se vygenerovat n-gramy");
        return 1;
    }

    // Použití n-gramů pro klasifikaci typu textu
    for (int i = 0; i < ngram_count; i++) {
        micromind_classify_text_type(&ngrams[i]);  // Fiktivní funkce pro klasifikaci textu
    }

    // Výpis n-gramů
    for (int i = 0; i < ngram_count; i++) {
        printf("N-gram %d: ", i + 1);
        for (int j = 0; j < ngrams[i].size; j++) {
            printf("%s ", ngrams[i].words[j]);
        }
        printf("");
    }

    // Uvolnění paměti
    free_ngrams(ngrams, ngram_count);

    return 0;
}
```

Tento manuál poskytuje detailní náhled na funkce a jejich využití v souboru `ngrams.c` pro efektivní generování a práci s n-gramy.

