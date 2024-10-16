# Manuál pro soubor `sentiment.c`

V MicroMind mikromodulech by mohly být tyto sentimentální analýzy využity k rozšíření schopností systému o pochopení emocionálního kontextu textových dat. Například:

1. **Interakce s uživatelem**: Modul sentimentální analýzy by mohl pomoci lépe reagovat na zprávy od uživatele na základě jejich emocionálního tónu. Pokud by uživatelův text vyjadřoval frustraci, mohl by MicroMind reagovat více empaticky a nabídnout lepší podporu.

2. **Předzpracování dat pro další modely**: Sentimentální skóre může sloužit jako dodatečný atribut, který se předává dalším AI mikromodulům v rámci rozhodovacích procesů. Tím by systém mohl brát v úvahu nejen faktickou stránku textu, ale také emocionální zabarvení při dalších úlohách, jako jsou doporučovací systémy.

3. **Monitorování změn nálady**: Modul může být využit k monitorování změn sentimentu v textu postupně od uživatele v různých časových obdobích, což může být užitečné například v aplikacích zaměřených na duševní zdraví.

4. **Analýza trendů v textových datech**: Sentimentální analýza může být použita ke sledování trendů v textových datech v čase. Například v marketingu lze sledovat, jak se mění sentiment zákazníků k určitému produktu po zavedení nové funkce.

5. **Automatické rozhodování**: Modul může být použit pro automatizované rozhodování na základě nálady v textu. Například v chatbotech lze určit, zda je vhodné předat konverzaci lidskému operátorovi na základě detekovaného negativního sentimentu.

6. **Zlepšení přesnosti jiných modelů**: Sentimentální skóre může sloužit jako další prvek pro vylepšení přesnosti jiných modelů strojového učení. Například při klasifikaci spokojenosti zákazníků by sentiment mohl zlepšit přesnost výsledků.

Přidáním tohoto modulu do MicroMind umožníte AI systému lépe pochopit, jaké emoce jsou vyjádřeny v textu, což povede k chytřejším interakcím a lepším rozhodnutím.

## Popis souboru `sentiment.c`

Soubor `sentiment.c` je navržen jako nástroj pro analýzu sentimentu textu v rámci systému MicroMind. Tento nástroj analyzuje vstupní text a určuje, zda obsahuje pozitivní, negativní nebo neutrální sentiment. Využívá dynamicky alokovanou strukturu pro správu slov a knihovnu `libstemmer` pro stemming. Sentiment je určen na základě skóre přiřazeného každému slovu - pozitivní slova mají kladné skóre, negativní slova záporné skóre. Během analýzy se text tokenizuje, každé slovo se normalizuje a porovná se se seznamem sentimentálních slov. Pokud je nalezeno odpovídající slovo, jeho skóre se přičte k celkovému skóre textu. Kromě toho se kontrolují negace, které mohou dočasně měnit polaritu skóre následujících slov. Tento kód může být využit v různých aplikacích MicroMind, jako jsou nástroje pro analýzu zpětné vazby, monitorování sentimentu na sociálních sítích nebo hodnocení recenzí.

## Funkce souboru `sentiment.c`

### 1. `add_sentiment_word(const char* word, int score)`

Tato funkce přidává nové sentimentální slovo do dynamického pole `sentiment_words` s jeho příslušným skóre.

- **Parametry**:
  - `word`: Slovo, které bude přidáno do seznamu.
  - `score`: Hodnota sentimentu spojená s tímto slovem (kladná pro pozitivní, záporná pro negativní).
- **Využití**: Používá se k dynamickému rozšiřování seznamu sentimentálních slov během jejich načítání ze souboru.

### 2. `compare_sentiment_words(const void* a, const void* b)`

Porovnává dvě sentimentální slova pro účely třídění nebo hledání.

- **Parametry**:
  - `a`, `b`: Ukazatele na sentimentální slova, která se mají porovnat.
- **Využití**: Používá se s funkcemi `qsort` a `bsearch` pro efektivní třídění a vyhledávání slov.

### 3. `get_sentiment_score(const char* word)`

Zjišťuje sentimentální skóre slova pomocí binárního vyhledávání.

- **Parametry**:
  - `word`: Slovo, jehož sentimentální skóre chceme zjistit.
- **Návratová hodnota**: Hodnota sentimentu slova (kladná, záporná nebo nulová).
- **Využití**: Používá se při analýze sentimentu textu.

### 4. `free_sentiment_table()`

Uvolňuje dynamicky alokované pole `sentiment_words`.

- **Využití**: Zajišťuje, že paměť alokovaná pro sentimentální slova bude uvolněna, když již není potřeba.

### 5. `load_sentiment_words(const char* filename, int score)`

Načítá sentimentální slova z určeného souboru a přidává je do dynamického pole s určeným skóre.

- **Parametry**:
  - `filename`: Cesta k souboru obsahujícímu sentimentální slova.
  - `score`: Hodnota sentimentu spojená se slovy v souboru.
- **Návratová hodnota**: 0 při úspěchu, -1 při chybě.
- **Využití**: Používá se k inicializaci seznamu sentimentálních slov.

### 6. `analyze_sentiment(const char* text, Config* config)`

Hlavní funkce pro analýzu sentimentu zadaného textu.

- **Parametry**:
  - `text`: Text, který má být analyzován.
  - `config`: Konfigurace obsahující cesty k souborům se sentimentálními slovy a další parametry, jako je rozsah negace.
- **Návratová hodnota**: Celkové sentimentální skóre textu (kladné, záporné nebo nulové). Na základě této hodnoty lze určit, zda má text celkově pozitivní, negativní nebo neutrální charakter. Pozitivní hodnoty indikují pozitivní sentiment, záporné hodnoty indikují negativní sentiment a hodnota blízká nule může značit neutrální nebo smíšený sentiment.
- **Využití**: Používá se k určení sentimentu celého textu.

Tato funkce zahrnuje několik kroků:

1. **Zamknutí Mutexu**: Zajišťuje synchronizaci při přístupu k seznamu sentimentálních slov, což je důležité při paralelním zpracování.
2. **Načtení slov**: Pokud sentimentální slova nejsou načtena, zavolá funkci `load_sentiment_words` pro načtení pozitivních a negativních slov.
3. **Inicializace Stemmeru**: Používá knihovnu `libstemmer` pro normalizaci (stemming) slov.
4. **Tokenizace a normalizace textu**: Text je rozdělen na jednotlivá slova, která jsou převedena na malá písmena.
5. **Vyhodnocení sentimentu**: Pro každé slovo se zjistí jeho sentimentální skóre. Pokud je detekována negace, změní se polarita skóre následujících slov po omezenou dobu.
6. **Uvolnění zdrojů**: Po skončení analýzy se uvolní paměť alokovaná pro textovou kopii a stemmer.

## Předpokládané využití

Soubor `sentiment.c` je vhodný pro různé aplikace, kde je třeba analyzovat textový obsah a zjistit jeho sentimentální hodnotu. To zahrnuje například:

- **Analýzu zpětné vazby od uživatelů**: Hodnocení sentimentu komentářů nebo recenzí produktů.
- **Monitorování sentimentu na sociálních sítích**: Automatická analýza příspěvků a komentářů.
- **Hodnocení obsahu**: Identifikace pozitivního nebo negativního sentimentu v textech, jako jsou recenze, blogové příspěvky nebo zprávy.
- **Analýza trendů v textových datech**: Sledování změn sentimentu v průběhu času, což může být využito v marketingu nebo průzkumu trhu.
- **Automatické rozhodování**: Použití sentimentu pro rozhodování o dalším postupu, například předání konverzace lidskému operátorovi, pokud je detekován negativní sentiment.
- **Personalizace obsahu**: Na základě sentimentální analýzy lze přizpůsobit obsah konkrétnímu uživateli. Například doporučovací systém může navrhnout pozitivní nebo relaxační obsah, pokud je u uživatele detekován negativní sentiment.
- **Emotionální analytika pro HR aplikace**: Pomocí sentimentální analýzy lze analyzovat zpětnou vazbu od zaměstnanců, což může pomoci HR oddělení lépe pochopit náladu a spokojenost zaměstnanců.
- **Zlepšení chatbotů a virtuálních asistentů**: Sentimentální analýza může pomoci chatbotům lépe přizpůsobit odpovědi na základě nálady uživatele, čímž se zvýší jejich účinnost a spokojenost uživatelů.
- **Predikce zákaznického chování**: Analýzou sentimentu v zákaznických komentářích a recenzích lze předvídat budoucí chování zákazníků, jako je nespokojenost nebo pravděpodobnost odchodu.
- **Detekce rizikových zpráv**: Sentimentální analýza může být použita pro identifikaci rizikových nebo potenciálně nebezpečných zpráv v rámci monitorovacích systémů, například pro bezpečnostní účely nebo při moderování obsahu.

## Použití

1. **Načtení sentimentu**: Nejprve zavolejte `load_sentiment_words` pro načtení pozitivních a negativních slov ze souborů.
2. **Analýza textu**: Použijte `analyze_sentiment` pro analýzu zadaného textu a zjištění jeho sentimentálního skóre.
3. **Uvolnění paměti**: Po dokončení analýzy nezapomeňte zavolat `free_sentiment_table` pro uvolnění dynamické paměti.

### Příklad kódu 1: Základní analýza sentimentu

```c
// Načtení sentimentu
if (load_sentiment_words("positive_words.txt", 1) != 0 ||
    load_sentiment_words("negative_words.txt", -1) != 0) {
    fprintf(stderr, "Chyba: Nepodařilo se načíst sentimentální slova\n");
    return 1;
}

// Analýza textu
const char* text = "Tento produkt je naprosto skvělý, ale občas má problémy.";
int score = analyze_sentiment(text, &config);
printf("Sentimentální skóre: %d\n", score);

// Uvolnění paměti
free_sentiment_table();
```

### Příklad kódu 2: Použití s více vlákny

```c
#include <pthread.h>
#include "../include/sentiment_analysis.h"

void* analyze_text_thread(void* arg) {
    const char* text = (const char*)arg;
    int score = analyze_sentiment(text, &config);
    printf("Sentimentální skóre vlákna: %d
", score);
    return NULL;
}

int main() {
    // Načtení sentimentu
    if (load_sentiment_words("positive_words.txt", 1) != 0 ||
        load_sentiment_words("negative_words.txt", -1) != 0) {
        fprintf(stderr, "Chyba: Nepodařilo se načíst sentimentální slova
");
        return 1;
    }

    // Vytvoření vláken pro paralelní analýzu
    pthread_t threads[2];
    const char* texts[] = {
        "Tento produkt je vynikající, doporučuji ho všem.",
        "Byl jsem velmi zklamán kvalitou tohoto produktu."
    };

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, analyze_text_thread, (void*)texts[i]);
    }

    // Čekání na dokončení vláken
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // Uvolnění paměti
    free_sentiment_table();

    return 0;
}
```

### Příklad kódu 3: Dynamické načítání sentimentálních slov

```c
#include <stdio.h>
#include <stdlib.h>
#include "../include/sentiment_analysis.h"

int main() {
    char filename[256];
    int score;

    printf("Zadejte cestu k souboru se sentimentálními slovy: ");
    scanf("%255s", filename);
    printf("Zadejte skóre pro slova v tomto souboru (1 pro pozitivní, -1 pro negativní): ");
    scanf("%d", &score);

    // Načtení sentimentálních slov
    if (load_sentiment_words(filename, score) != 0) {
        fprintf(stderr, "Chyba: Nepodařilo se načíst sentimentální slova
");
        return 1;
    }

    // Analýza textu
    const char* text = "Tento produkt je skvělý, ale má pár drobných chyb.";
    int sentiment_score = analyze_sentiment(text, &config);
    printf("Sentimentální skóre: %d
", sentiment_score);

    // Uvolnění paměti
    free_sentiment_table();

    return 0;
}
```

### Příklad kódu 4: Integrace sentimentálního modulu s MicroMind AI mikromoduly

```c
#include "../include/sentiment_analysis.h"
#include "micromind_module.h"  // Fiktivní knihovna pro integraci s MicroMind

void process_user_input(const char* user_input) {
    // Načtení sentimentu
    if (load_sentiment_words("positive_words.txt", 1) != 0 ||
        load_sentiment_words("negative_words.txt", -1) != 0) {
        fprintf(stderr, "Chyba: Nepodařilo se načíst sentimentální slova
");
        return;
    }

    // Analýza sentimentu uživatelského vstupu
    int sentiment_score = analyze_sentiment(user_input, &config);
    printf("Sentimentální skóre uživatelského vstupu: %d
", sentiment_score);

    // Integrace s MicroMind pro další zpracování
    if (sentiment_score > 0) {
        micromind_trigger_positive_response();  // Fiktivní funkce, která reaguje pozitivně
    } else if (sentiment_score < 0) {
        micromind_trigger_negative_response();  // Fiktivní funkce, která reaguje empaticky
    } else {
        micromind_trigger_neutral_response();  // Fiktivní funkce, která reaguje neutrálně
    }

    // Uvolnění paměti
    free_sentiment_table();
}

int main() {
    const char* user_input = "Tento nový produkt mě opravdu nadchnul, ale měl by být levnější.";
    process_user_input(user_input);
    return 0;
}
```

Tento manuál poskytuje detailní náhled na funkce a jejich využití v souboru `sentiment.c` pro efektivní analýzu sentimentu textu.

