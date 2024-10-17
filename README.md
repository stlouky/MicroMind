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
