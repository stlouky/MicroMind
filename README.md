``` plaintext
MicroMind/
├── src/
│   ├── main.c
│   ├── orchestrator.c
│   ├── logger.c
│   ├── preprocess/
│   │   ├── preprocessor.c
│   │   └── preprocessor.h
│   ├── tokenizer/
│   │   ├── tokenizer.c
│   │   └── tokenizer.h
│   ├── classifier/
│   │   ├── classifier.c
│   │   └── classifier.h
│   ├── utils/
│   │   ├── utils.c
│   │   └── utils.h
│   └── thread_pool/
│       ├── thread_pool.c
│       └── thread_pool.h
├── include/
│   ├── orchestrator.h
│   ├── logger.h
│   └── module_interface.h
├── modules/
│   ├── preprocessor/
│   │   ├── preprocessor.c
│   │   └── preprocessor.h
│   ├── tokenizer/
│   │   ├── tokenizer.c
│   │   └── tokenizer.h
│   ├── classifier/
│   │   ├── classifier.c
│   │   └── classifier.h
│   └── ner/
│       ├── ner.c
│       └── ner.h
├── tests/
│   ├── test_framework.h
│   ├── test_framework.c
│   ├── test_preprocessor.c
│   ├── test_tokenizer.c
│   ├── test_classifier.c
│   ├── test_orchestrator.c
│   └── Makefile
├── docs/
│   ├── README.md
│   ├── architecture.md
│   └── usage.md
├── config/
│   └── orchestrator_config.json
├── build/
│   └── (build artifacts)
├── scripts/
│   └── build.sh
├── logs/
│   └── microMind.log
├── Makefile
├── .gitignore
├── README.md
└── TODO.md

Popis Klíčových Adresářů a Souborů:

src/: Obsahuje zdrojové kódy hlavních komponent projektu, včetně orchestrátoru, loggeru, a jednotlivých modulů.

preprocess/, tokenizer/, classifier/, ner/: Každý z těchto podsložek obsahuje zdrojové kódy a hlavičkové soubory pro konkrétní modul.
thread_pool/: Implementace thread poolu pro paralelní zpracování.
include/: Globální hlavičkové soubory, které jsou sdíleny mezi různými částmi projektu.

module_interface.h: Definuje standardizovaná rozhraní, která musí všechny moduly implementovat.
modules/: Obsahuje dynamicky načítatelné moduly implementované jako sdílené knihovny (.so soubory).

ner/: Nově přidaný modul pro rozpoznávání entit (NER).
tests/: Obsahuje jednotkové a integrační testy pro různé moduly a hlavní orchestrátor.

docs/: Dokumentace projektu, včetně přehledu, architektury a návodu k použití.

config/: Konfigurační soubory pro orchestrátora a moduly.

build/: Místo pro ukládání kompilovaných objektů a binárních souborů.

scripts/: Skripty pro automatizaci build procesu, testování a nasazení.

logs/: Logovací soubory pro sledování událostí a chyb v systému.

