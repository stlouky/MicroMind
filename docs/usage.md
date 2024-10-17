# Usage Guide for MicroMind

## **1. Předpoklady**

Než začnete s instalací a používáním **MicroMind**, ujistěte se, že máte na vašem systému nainstalované následující nástroje a knihovny:

- **Jazyk C a Kompilátor**
  - GCC nebo Clang
- **Make**
- **cJSON** pro parsování JSON konfigurací
  - Instalace na Ubuntu:
    ```bash
    sudo apt-get update
    sudo apt-get install libcjson-dev
    ```
- **Pthread** pro multithreading
  - Obvykle je součástí standardní knihovny C

## **2. Instalace**

### **2.1. Klonování Repozitáře**

Nejprve naklonujte repozitář **MicroMind** z GitHubu:

```bash
git clone https://github.com/vaše-uživatelské-jméno/MicroMind.git
cd MicroMind
