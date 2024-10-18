# Makefile pro MicroMind Projekt

# Phony cíle
.PHONY: all debug release shared install uninstall clean test memcheck docs

# Definice cest
FRAMEWORK_DIR := framework
INSTALL_DIR := install

# Cíle
all: debug shared

debug:
	@echo "Sestavení v Debug režimu..."
	$(MAKE) -C $(FRAMEWORK_DIR) BUILD=debug

release:
	@echo "Sestavení v Release režimu..."
	$(MAKE) -C $(FRAMEWORK_DIR) BUILD=release

shared: debug
	@echo "Sestavení sdílené knihovny..."
	$(MAKE) -C $(FRAMEWORK_DIR) shared

install: all
	@echo "Instalace knihoven a hlaviček..."
	$(MAKE) -C $(FRAMEWORK_DIR) install DESTDIR=$(INSTALL_DIR)

uninstall:
	@echo "Odinstalace knihoven a hlaviček..."
	$(MAKE) -C $(FRAMEWORK_DIR) uninstall DESTDIR=$(INSTALL_DIR)

clean:
	@echo "Čištění build artefaktů..."
	$(MAKE) -C $(FRAMEWORK_DIR) clean

test: all
	@echo "Spuštění testů..."
	$(MAKE) -C $(FRAMEWORK_DIR) test

memcheck: all
	@echo "Kontrola paměťových úniků pomocí Valgrind..."
	$(MAKE) -C $(FRAMEWORK_DIR) memcheck

docs: all
	@echo "Generování dokumentace pomocí Doxygen..."
	$(MAKE) -C $(FRAMEWORK_DIR) docs
