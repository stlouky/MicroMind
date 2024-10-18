# Makefile pro MindFrame Framework

# -------------------------------------------------------------------
# **Nastavení Kompilátoru a Nástrojů**
# -------------------------------------------------------------------
CC := gcc
AR := ar
RM := rm -f
MKDIR := mkdir -p
CFLAGS_COMMON := -I./include -Wall -Wextra -std=c11 -MMD -MP

# -------------------------------------------------------------------
# **Adresářová Struktura**
# -------------------------------------------------------------------
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := lib
BUILD_DIR := build
TEST_DIR := tests

# -------------------------------------------------------------------
# **Build Konfigurace**
# -------------------------------------------------------------------
# Výchozí build typ je debug, lze přepsat pomocí `make BUILD=release`
BUILD ?= debug

ifeq ($(BUILD), debug)
    CFLAGS := $(CFLAGS_COMMON) -g -DDEBUG
    LDFLAGS :=
    TARGET := $(BIN_DIR)/libmindframe.a
    SHARED_LIB := $(BIN_DIR)/libmindframe.so
else ifeq ($(BUILD), release)
    CFLAGS := $(CFLAGS_COMMON) -O2
    LDFLAGS :=
    TARGET := $(BIN_DIR)/libmindframe.a
    SHARED_LIB := $(BIN_DIR)/libmindframe.so
else
    $(error Neznámý typ buildu: $(BUILD))
endif

# -------------------------------------------------------------------
# **Seznam Soubory**
# -------------------------------------------------------------------
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# -------------------------------------------------------------------
# **Název Knihovny**
# -------------------------------------------------------------------
LIB_NAME := libmindframe.a
LIB := $(BIN_DIR)/$(LIB_NAME)

# -------------------------------------------------------------------
# **Sdílená Knihovna**
# -------------------------------------------------------------------
SHARED_LIB_NAME := libmindframe.so
SHARED_LIB := $(BIN_DIR)/$(SHARED_LIB_NAME)
SHARED_CFLAGS := -fPIC
SHARED_LDFLAGS := -shared

# -------------------------------------------------------------------
# **Hlavní Cíle**
# -------------------------------------------------------------------
.PHONY: all shared install uninstall clean test docs

all: $(TARGET)

# Cíl pro statickou knihovnu
$(TARGET): $(OBJS)
	@$(MKDIR) $(BIN_DIR)
	$(AR) rcs $@ $^

# Cíl pro sdílenou knihovnu
shared: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	@$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(SHARED_CFLAGS) -o $@ $^ $(SHARED_LDFLAGS)

# -------------------------------------------------------------------
# **Komplikace Zdrojových Souborů na Objektové**
# -------------------------------------------------------------------
# Kompilace .c na .o s generováním závislostí
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Vytvoření adresáře pro objekty, pokud neexistuje
$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# -------------------------------------------------------------------
# **Zahrnutí Závislostí**
# -------------------------------------------------------------------
-include $(DEPS)

# -------------------------------------------------------------------
# **Instalace Knihovny a Hlaviček**
# -------------------------------------------------------------------
install: all shared
	@$(MKDIR) $(DESTDIR)/usr/local/lib
	cp $(TARGET) $(SHARED_LIB) $(DESTDIR)/usr/local/lib/
	@$(MKDIR) $(DESTDIR)/usr/local/include/mindframe
	cp $(INC_DIR)/*.h $(DESTDIR)/usr/local/include/mindframe/

# -------------------------------------------------------------------
# **Odinstalace Knihovny a Hlaviček**
# -------------------------------------------------------------------
uninstall:
	rm -f $(DESTDIR)/usr/local/lib/$(LIB_NAME) $(DESTDIR)/usr/local/lib/$(SHARED_LIB_NAME)
	rm -rf $(DESTDIR)/usr/local/include/mindframe

# -------------------------------------------------------------------
# **Čištění Build Artefaktů**
# -------------------------------------------------------------------
clean:
	$(RM) -r $(OBJ_DIR) $(BIN_DIR) $(BUILD_DIR)

# -------------------------------------------------------------------
# **Generování Testů**
# -------------------------------------------------------------------
test: all
	@$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_DIR)/*.c -L$(BIN_DIR) -lmindframe -o $(BUILD_DIR)/test_mindframe
	./$(BUILD_DIR)/test_mindframe

# -------------------------------------------------------------------
# **Generování Dokumentace**
# -------------------------------------------------------------------
docs:
	doxygen Doxyfile
