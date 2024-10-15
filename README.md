# MicroMind
# MicroMind

MicroMind je modulární projekt v jazyce C, jehož cílem je vytvořit malé AI modely ("micromodely"), které lze kombinovat do větších a robustnějších systémů podle potřeby. Tyto mikromodely umožňují jednodušší přístup k umělé inteligenci díky modulárnímu a škálovatelnému přístupu. MicroMind se zaměřuje na efektivní řešení specifických problémů s možností kombinování jednotlivých mikromodelů pro dosažení složitějších cílů.

## Cíle projektu

- **Modulární design**: Každý modul v projektu představuje specifickou funkcionalitu, která může být samostatně využívána nebo kombinována s jinými moduly pro vytvoření složitějších AI modelů.
- **Přizpůsobivost**: Kombinací různých mikromodelů lze přizpůsobit chování AI pro specifické úlohy.
- **Škálovatelnost**: Moduly jsou navrženy tak, aby byly lehké a efektivní, což umožňuje jejich snadné rozšiřování.
- **Jednoduchá údržba**: Modulární struktura umožňuje snadnou správu a aktualizaci jednotlivých částí projektu bez nutnosti zásahu do celého systému.

## Struktura projektu

```
MicroMind/
├── include/
│   ├── common.h
│   ├── config.h
│   ├── sentiment.h
│   ├── markov_chain.h
│   ├── tokenizer.h
│   ├── parser.h
│   └── ngrams.h
├── src/
│   ├── common.c
│   ├── config.c
│   ├── sentiment.c
│   ├── markov_chain.c
│   ├── tokenizer.c
│   ├── parser.c
│   └── ngrams.c
├── libs/
│   ├── libstemmer_c/   # Knihovna Snowball stemmer
│   └── uthash.h        # Knihovna UTHash
├── data/
│   ├── positive_words.txt
│   ├── negative_words.txt
│   └── ...             # Další datové soubory
├── tests/
│   ├── test_sentiment.c
│   ├── test_markov_chain.c
│   ├── test_tokenizer.c
│   ├── test_parser.c
│   ├── test_ngrams.c
│   └── unity/          # Testovací framework Unity
│       ├── unity.c
│       └── unity.h
├── config.ini
├── Makefile
└── README.md
```

- **include/**: Obsahuje hlavičkové soubory definující rozhraní jednotlivých modulů.
- **src/**: Obsahuje zdrojové kódy jednotlivých modulů, které implementují specifické funkce.
- **libs/**: Externí knihovny pro specifické funkce jako je stemming nebo hashovací tabulky.
- **data/**: Datové soubory potřebné pro moduly (např. sentiment analýza).
- **tests/**: Testy pro jednotlivé moduly, používající testovací framework Unity.
- **config.ini**: Konfigurační soubor pro nastavení parametrů projektu.
- **Makefile**: Soubor pro automatizaci kompilace projektu.

## Instalace

### Závislosti

- **GCC**: Pro kompilaci projektu.
- **Make**: Pro automatizaci kompilace pomocí Makefile.
- **Unity**: Testovací framework, který je součástí projektu v adresáři `tests/unity`.

### Kompilace

Pro kompilaci projektu použijte následující příkazy:

```sh
make all
```

Pro spuštění testů:

```sh
make test
```

### Konfigurace

Nastavení projektu lze přizpůsobit pomocí souboru `config.ini`. Tento soubor obsahuje parametry, jako jsou cesty k datovým souborům nebo specifické parametry pro chování jednotlivých modulů.

## Použití

MicroMind je navržen jako stavebnice pro tvorbu AI systémů, kde jednotlivé moduly lze volně kombinovat.

- **Sentiment analýza**: Pomocí `sentiment.c` můžete provádět analýzu nálady textu na základě seznamu pozitivních a negativních slov.
- **Markovovy řetězce**: `markov_chain.c` umožňuje generování textu na základě Markovova modelu.
- **Tokenizace textu**: `tokenizer.c` poskytuje nástroje pro rozdělení textu na jednotlivé tokeny.
- **N-gramy**: `ngrams.c` umožňuje vytváření a analýzu n-gramů, což je užitečné pro analýzu jazykových vzorců a predikce.
- **Parser**: `parser.c` poskytuje základní syntaktickou analýzu textu, což umožňuje extrakci strukturovaných informací z textu.

Příklady použití:

### Analýza sentimentu

```c
#include "include/sentiment.h"
#include "include/tokenizer.h"

int main() {
    char* text = "Toto je testovací text.";
    size_t token_count = 0;
    char** tokens;

    // Tokenizace textu
    tokenize_text(text, &tokens, &token_count);

    // Analýza sentimentu
    int sentiment = analyze_sentiment(tokens, token_count);

    // Výsledek sentimentu
    printf("Sentiment: %d\n", sentiment);

    return 0;
}
```

### Generování textu pomocí Markovova řetězce

```c
#include "include/markov_chain.h"

int main() {
    char* text = "Toto je příklad tréninkového textu.";
    MarkovChain* chain = create_markov_chain();

    // Trénování Markovova řetězce
    train_markov_chain(chain, text);

    // Generování nového textu
    char* generated_text = generate_text(chain, 10);
    printf("Generovaný text: %s\n", generated_text);

    // Uvolnění paměti
    free(generated_text);
    destroy_markov_chain(chain);

    return 0;
}
```

### Spojování modelů

MicroMind umožňuje spojování několika mikromodelů dohromady, což zvyšuje jejich schopnosti a umožňuje složitější analýzy. Například lze kombinovat tokenizaci, sentiment analýzu a Markovův řetězec pro vytvoření systému, který nejprve zanalyzuje text a následně vygeneruje podobný text se stejným sentimentem.

```c
#include "include/tokenizer.h"
#include "include/sentiment.h"
#include "include/markov_chain.h"

int main() {
    char* text = "Toto je příklad textu se smíšeným sentimentem.";
    size_t token_count = 0;
    char** tokens;

    // Tokenizace textu
    tokenize_text(text, &tokens, &token_count);

    // Analýza sentimentu
    int sentiment = analyze_sentiment(tokens, token_count);
    printf("Sentiment původního textu: %d\n", sentiment);

    // Trénování Markovova řetězce
    MarkovChain* chain = create_markov_chain();
    train_markov_chain(chain, text);

    // Generování nového textu
    char* generated_text = generate_text(chain, 15);
    printf("Generovaný text: %s\n", generated_text);

    // Uvolnění paměti
    free(generated_text);
    destroy_markov_chain(chain);

    return 0;
}
```

V tomto příkladu je text nejprve tokenizován a zanalyzován pomocí sentiment analýzy. Poté se stejný text použije k trénování Markovova řetězce a k generování nového textu, který odpovídá původnímu sentimentu. Tímto způsobem lze kombinovat různé mikromodely pro dosažení složitějšího chování.

## Možný budoucí vývoj projektu

Projekt MicroMind je v neustálém vývoji, s cílem rozšiřovat jeho schopnosti a přidávat nové moduly pro zpracování specifických úloh. Některé z možných budoucích směrů vývoje zahrnují:

- **Rozpoznávání vzorů**: Přidání modulu pro rozpoznávání specifických vzorů v datech, což by umožnilo lepší analýzu a predikci.
- **Přírodní jazyk**: Další rozšíření funkcí pro práci s přirozeným jazykem, jako je složitější syntaktická analýza nebo generování odpovědí.
- **Optimalizace výkonu**: Zaměření na optimalizaci stávajících modulů pro vyšší efektivitu a rychlost zpracování.
- **Podpora dalších formátů dat**: Rozšíření o podporu práce s dalšími typy datových vstupů, jako jsou obrázky nebo zvuk, pomocí kombinace s dalšími knihovnami.

Cílem je udržet projekt otevřený pro nové nápady a inovace, aby mohl růst a vyvíjet se podle potřeb uživatelů a výzkumu v oblasti umělé inteligence.

## Licence

Tento projekt je licencován pod licencí MIT. Podrobnosti naleznete v souboru `LICENSE`.

## Kontakt
>w3men@protonmail.com
Pokud máte otázky nebo návrhy, můžete mě kontaktovat prostřednictvím GitHub Issues nebo e-mailu.
