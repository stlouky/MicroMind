# TODO List for MicroMind Project

## **1. Implementace a Rozšíření Modulů**
- [ ] **Rozpoznávání Entit (NER) Modul**
  - [ ] Definovat rozhraní pro NER modul v `module_interface.h`
  - [ ] Implementovat základní NER funkcionalitu v `modules/ner/ner.c` a `modules/ner/ner.h`
  - [ ] Přidat NER modul do orchestrátoru
  - [ ] Vytvořit jednotkové testy pro NER modul

- [ ] **Sentimentální Analýza Modul**
  - [ ] Definovat rozhraní pro sentimentální analýzu v `module_interface.h`
  - [ ] Implementovat základní sentimentální analýzu v `modules/sentiment/sentiment.c` a `modules/sentiment/sentiment.h`
  - [ ] Přidat sentimentální modul do orchestrátoru
  - [ ] Vytvořit jednotkové testy pro sentimentální modul

- [ ] **Generování Textu Modul**
  - [ ] Definovat rozhraní pro generování textu v `module_interface.h`
  - [ ] Implementovat základní generování textu v `modules/generator/generator.c` a `modules/generator/generator.h`
  - [ ] Přidat generátor textu do orchestrátoru
  - [ ] Vytvořit jednotkové testy pro generátor textu

## **2. Vylepšení Orchestrátoru**
- [ ] **Načítání Konfigurace z JSON**
  - [ ] Implementovat načítání konfigurace v `src/orchestrator.c` pomocí `cJSON`
  - [ ] Aktualizovat `config/orchestrator_config.json` s novými moduly a nastaveními

- [ ] **Dynamické Přidávání a Odstraňování Modulů**
  - [ ] Implementovat funkce pro dynamické přidávání modulů za běhu
  - [ ] Implementovat funkce pro odstraňování modulů za běhu

- [ ] **Optimalizace Paralelizace**
  - [ ] Integrace thread poolu pro efektivnější využití vláken
  - [ ] Optimalizovat kritické sekce pro minimalizaci blokování

## **3. Testování a Validace**
- [ ] **Rozšíření Jednotkových Testů**
  - [ ] Přidat více testovacích případů pro stávající moduly
  - [ ] Vytvořit testy pro nové moduly (NER, sentimentální analýza, generátor textu)

- [ ] **Implementace Integračních Testů**
  - [ ] Vytvořit integrační testy pro nové moduly
  - [ ] Ověřit správnou integraci všech modulů s orchestrátorem

- [ ] **Pokrytí Kódu a Reportování**
  - [ ] Implementovat pokrytí kódu pomocí `gcov`
  - [ ] Generovat reporty pokrytí kódu

## **4. Dokumentace**
- [ ] **Architektonická Dokumentace (`architecture.md`)**
  - [ ] Popis celkové architektury systému
  - [ ] Diagramy interakcí mezi moduly a orchestrátorem

- [ ] **Návod k Použití (`usage.md`)**
  - [ ] Instrukce pro instalaci a kompilaci projektu
  - [ ] Příklady konfigurace a spuštění systému
  - [ ] Návody pro přidávání nových modulů

- [ ] **API Reference (`api_reference.md`)**
  - [ ] Detailní popis všech funkcí a struktur používaných v projektu
  - [ ] Příklady použití API pro vývojáře

## **5. Optimalizace a Výkon**
- [ ] **Profilování Aplikace**
  - [ ] Použít `gprof` pro identifikaci úzkých míst výkonu
  - [ ] Optimalizovat identifikovaná úzká místa

- [ ] **Optimalizace Správy Paměti**
  - [ ] Minimalizovat dynamické alokace paměti
  - [ ] Implementovat efektivní buffer management

## **6. CI/CD Pipeline**
- [ ] **Rozšíření GitHub Actions Workflow**
  - [ ] Přidat kroky pro kompilaci a testování nových modulů
  - [ ] Implementovat automatické nasazení po úspěšném buildnutí a testování

- [ ] **Integrace s Nástroji pro Kontinuální Integraci**
  - [ ] Nastavit Jenkins nebo GitLab CI pro pokročilejší CI/CD procesy

## **7. Logging a Monitoring**
- [ ] **Rozšíření Logování**
  - [ ] Přidat více úrovní logování (např. TRACE)
  - [ ] Implementovat rotaci logovacích souborů pro lepší správu diskového prostoru

- [ ] **Integrace s Monitorovacími Nástroji**
  - [ ] Nastavit Prometheus pro sběr metrik
  - [ ] Vytvořit dashboardy v Grafana pro vizualizaci výkonu a chyb

## **8. Správa Konfigurace**
- [ ] **Validace Konfigurace**
  - [ ] Implementovat validaci konfigurace při načítání z JSON
  - [ ] Poskytovat užitečné chybové zprávy při neplatné konfiguraci

- [ ] **Uživatelské Rozhraní pro Konfiguraci**
  - [ ] Vytvořit jednoduché CLI nástroje pro úpravu konfigurace
  - [ ] Implementovat webové rozhraní pro správu konfigurace (budoucí rozšíření)

## **9. Bezpečnostní Vylepšení**
- [ ] **Bezpečnostní Audity Kódu**
  - [ ] Pravidelně provádět bezpečnostní audity kódu
  - [ ] Opravit nalezené bezpečnostní chyby

- [ ] **Validace a Sanitace Vstupů**
  - [ ] Implementovat validaci vstupních dat ve všech modulech
  - [ ] Přidat sanitaci vstupů pro ochranu proti injekcím a dalším útokům

## **10. Uživatelské Rozhraní (Budoucí Rozšíření)**
- [ ] **CLI Rozhraní**
  - [ ] Navrhnout a implementovat jednoduché CLI pro interakci s orchestrátorem
  - [ ] Přidat příkazy pro správu modulů a konfigurace

- [ ] **Webové Rozhraní**
  - [ ] Navrhnout webové rozhraní pro monitorování a konfiguraci systému
  - [ ] Implementovat backend API pro komunikaci s orchestrátorem

