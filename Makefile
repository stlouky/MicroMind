# Makefile pro MicroMind Framework

# Kompilátor a linker
CC := gcc
CXX := g++
AR := ar
RM := rm -f
MKDIR := mkdir -p

# Cesta k adresářům
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
BUILD_DIR := build
TEST_DIR := tests
DOCS_DIR := docs/html

# Cíle
TARGET := $(BIN_DIR)/micro_mind
LIB_NAME := libmicro_mind.a
LIB := $(BIN_DIR)/$(LIB_NAME)
SHARED_LIB_NAME := libmicro_mind.so
SHARED_LIB := $(BIN_DIR)/$(SHARED_LIB_NAME)

# Soubory zdrojového kódu
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Příznaky kompilátoru
CFLAGS_COMMON := -I$(INC_DIR) -Wall -Wextra -std=c11 -MMD -MP

# Výběr build režimu
BUILD ?= debug

ifeq ($(BUILD), debug)
    CFLAGS := $(CFLAGS_COMMON) -g -DDEBUG
    LDFLAGS := 
else ifeq ($(BUILD), release)
    CFLAGS := $(CFLAGS_COMMON) -O2 -DNDEBUG
    LDFLAGS := 
else
    $(error Neznámý typ buildu: $(BUILD))
endif

# Phony cíle
.PHONY: all debug release shared install uninstall clean test docs

# Výchozí cíl
all: $(LIB)

# Cíl pro sestavení statické knihovny
$(LIB): $(OBJS)
	@$(MKDIR) $(BIN_DIR)
	$(AR) rcs $@ $^

# Cíl pro sestavení sdílené knihovny
shared: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	@$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(LDFLAGS)

# Cíl pro instalaci knihovny a hlaviček
install: all shared
	@$(MKDIR) $(DESTDIR)/usr/local/lib
	cp $(LIB) $(SHARED_LIB) $(DESTDIR)/usr/local/lib/
	@$(MKDIR) $(DESTDIR)/usr/local/include/micro_mind
	cp $(INC_DIR)/*.h $(DESTDIR)/usr/local/include/micro_mind/

# Cíl pro odinstalaci knihovny a hlaviček
uninstall:
	rm -f $(DESTDIR)/usr/local/lib/$(LIB_NAME) $(DESTDIR)/usr/local/lib/$(SHARED_LIB_NAME)
	rm -rf $(DESTDIR)/usr/local/include/micro_mind

# Cíl pro čištění build artefaktů
clean:
	$(RM) -r $(OBJ_DIR) $(BIN_DIR) $(BUILD_DIR) $(DOCS_DIR)

# Cíl pro sestavení projektu
build: all

# Cíl pro spuštění testů
test: all
	@$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_DIR)/*.c -L$(BIN_DIR) -lmicro_mind -o $(BUILD_DIR)/test_micro_mind
	./$(BUILD_DIR)/test_micro_mind

# Cíl pro kontrolu paměťových úniků pomocí Valgrind
memcheck: all
	valgrind --leak-check=full --error-exitcode=1 ./$(TARGET)

# Cíl pro generování dokumentace pomocí Doxygen
docs: 
	doxygen Doxyfile

# Automatické zahrnutí závislostí
-include $(DEPS)
