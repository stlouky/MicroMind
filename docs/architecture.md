# Architecture of MicroMind

## **1. Úvod**

Architektura **MicroMind** je navržena tak, aby byla modulární, flexibilní a škálovatelná. Systém se skládá z několika klíčových komponent, které spolu komunikují prostřednictvím definovaných rozhraní. Tento dokument poskytuje detailní přehled o architektuře systému, jeho hlavních částech a jejich interakcích.

## **2. Hlavní Komponenty**

### **2.1. Orchestrátor**

**Orchestrátor** je centrální část systému, která řídí tok dat mezi jednotlivými moduly. Zodpovídá za:

- **Načítání Modulů**: Dynamické načítání a správa modulů pomocí sdílených knihoven (`.so`).
- **Řízení Toků Dat**: Předávání dat mezi moduly ve správném pořadí.
- **Monitoring a Logging**: Sledování výkonu modulů a zaznamenávání logů.

### **2.2. Moduly**

Moduly jsou samostatné komponenty implementující specifické funkce NLP. Každý modul je navržen tak, aby implementoval standardizované rozhraní definované v `module_interface.h`. Stávající moduly zahrnují:

- **Preprocessor**: Čistí a normalizuje vstupní text.
- **Tokenizer**: Rozděluje text na jednotlivé tokeny.
- **Classifier**: Klasifikuje text do předdefinovaných kategorií.

### **2.3. Logger**

**Logger** poskytuje mechanismus pro zaznamenávání zpráv a chyb v systému. Logy jsou zapisovány do souboru `logs/microMind.log` a rozlišují různé úrovně logování (DEBUG, INFO, WARN, ERROR).

### **2.4. Thread Pool**

**Thread Pool** umožňuje paralelní zpracování úkolů, což zvyšuje výkon systému při zpracování více vstupů současně. Implementace thread poolu je obsažena v `src/thread_pool/`.

## **3. Interakce Mezi Komponentami**

1. **Spuštění Systému**:
   - Uživatel spustí hlavní program `main.c`.
   - `main.c` inicializuje orchestrátor a načítá konfigurační soubor `config/orchestrator_config.json`.

2. **Načítání Modulů**:
   - Orchestrátor načte a inicializuje jednotlivé moduly podle konfigurace.
   - Každý modul je načten jako sdílená knihovna a jeho funkce jsou přiřazeny orchestrátoru.

3. **Zpracování Textu**:
   - Uživatel poskytne vstupní text.
   - Orchestrátor předá text do Preprocessor modulu pro čištění a normalizaci.
   - Vyčištěný text je předán do Tokenizer modulu pro rozdělení na tokeny.
   - Tokeny jsou znovu složeny a předány do Classifier modulu pro klasifikaci.
   - Výsledek klasifikace je vrácen uživateli.

4. **Logging a Monitoring**:
   - Během zpracování orchestrátor zaznamenává důležité události a chyby pomocí Logger komponenty.
   - Logy jsou ukládány do `logs/microMind.log` pro pozdější analýzu.

## **4. Diagram Architektury**

![Architecture Diagram](./images/architecture_diagram.png)

*(Poznámka: Přidejte diagram architektury do adresáře `docs/images/` a odkažte na něj)*

## **5. Rozhraní a Komunikace**

### **5.1. Modulové Rozhraní (`module_interface.h`)**

Definuje standardizovaná rozhraní, která musí všechny moduly implementovat. To zajišťuje konzistenci a umožňuje snadnou integraci nových modulů.

### **5.2. Dynamické Načítání Modulů**

Orchestrátor používá funkce `dlopen`, `dlsym` a `dlclose` pro dynamické načítání a správu modulů. Každý modul je implementován jako sdílená knihovna (`.so`), která exportuje potřebné funkce definované v rozhraní.

## **6. Paralelizace**

Pro zvýšení výkonu systému je implementován thread pool, který umožňuje paralelní zpracování více textových vstupů současně. Thread pool spravuje vlákna, která vykonávají úkoly z fronty, což umožňuje efektivní využití zdrojů systému.

## **7. Správa Paměti**

Jelikož je projekt implementován v jazyce C, je důležitá pečlivá správa paměti. Všechny dynamické alokace jsou řádně uvolňovány a používají se nástroje jako Valgrind pro detekci paměťových úniků.

## **8. Závěr**

Architektura **MicroMind** je navržena tak, aby byla flexibilní a snadno rozšiřitelná. Modularita systému umožňuje rychlé přidávání nových funkcionalit a optimalizaci stávajících komponent. Robustní orchestrátor a efektivní správa zdrojů zajišťují, že systém je připraven na náročné NLP úlohy.

