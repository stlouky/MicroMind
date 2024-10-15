/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * test_parser.c - Testovací soubor pro testování funkcí z parser.c pomocí testovacího rámce
 *
 * Tento soubor obsahuje testy pro funkce z parser.c, jako jsou logování a bezpečné uvolňování paměti.
 */

#include "../include/test_framework.h"
#include "../include/parser.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

// Definice barev pro výstup v terminálu
#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define BLUE_COLOR    "\033[34m"

#define SAFE_FREE(ptr) do { if ((ptr) != NULL) { free(ptr); (ptr) = NULL; } } while (0)

void test_basic_parsing() {
    printf("Running basic parsing test:\n");

    char* tokens[] = {"token1", "token2", "token3"};
    int token_count = 3;
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);

    assert(results != NULL);
    assert(result_count == token_count);
    for (int i = 0; i < result_count; i++) {
        assert(strcmp(results[i].value, tokens[i]) == 0);
        assert(results[i].type == 2); // Očekáváme typ identifikátor
    }
    free_parse_results(results, result_count);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Basic parsing test\n");
}

void test_null_tokens_input() {
    printf("Running null tokens input test:\n");
    int result_count = 0;
    ParseResult* results = parse_tokens(NULL, 3, &result_count);
    assert(results == NULL);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Null tokens input test\n");
}

void test_null_result_count_input() {
    printf("Running null result count input test:\n");
    char* tokens[] = {"token1", "token2"};
    ParseResult* results = parse_tokens(tokens, 2, NULL);
    assert(results == NULL);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Null result count input test\n");
}

void test_negative_token_count() {
    printf("Running negative token count test:\n");
    char* tokens[] = {"token1", "token2"};
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, -1, &result_count);
    assert(results == NULL);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Negative token count test\n");
}

void test_empty_token_list() {
    printf("Running empty token list test:\n");
    int result_count = 0;
    ParseResult* results = parse_tokens(NULL, 0, &result_count);
    assert(results == NULL);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Empty token list test\n");
}

void test_long_token_list() {
    printf("Running long token list test:\n");
    char* long_tokens[1000];
    for (int i = 0; i < 1000; i++) {
        long_tokens[i] = "token";
    }
    int result_count = 0;
    ParseResult* results = parse_tokens(long_tokens, 1000, &result_count);
    assert(results != NULL);
    assert(result_count == 1000);
    for (int i = 0; i < result_count; i++) {
        assert(strcmp(results[i].value, "token") == 0);
        assert(results[i].type == 2); // Očekáváme typ identifikátor
    }
    free_parse_results(results, result_count);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Long token list test\n");
}

void test_special_characters_in_tokens() {
    printf("Running special characters in tokens test:\n");
    char* special_tokens[] = {"!@#$", "%^&*", "()_+"};
    int result_count = 0;
    ParseResult* results = parse_tokens(special_tokens, 3, &result_count);
    assert(results != NULL);
    assert(result_count == 3);
    for (int i = 0; i < result_count; i++) {
        assert(strcmp(results[i].value, special_tokens[i]) == 0);
        assert(results[i].type == 2); // Očekáváme typ identifikátor
    }
    free_parse_results(results, result_count);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Special characters in tokens test\n");
}

void test_mixed_tokens() {
    printf("Running mixed tokens test:\n");
    char* tokens[] = {"123", "+", "variable", "-", "3.14", "*", "=="};
    int token_count = 7;
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);
    assert(results != NULL);
    assert(result_count == token_count);
    int expected_types[] = {0, 1, 2, 1, 0, 1, 1}; // Očekávané typy
    for (int i = 0; i < result_count; i++) {
        assert(strcmp(results[i].value, tokens[i]) == 0);
        assert(results[i].type == expected_types[i]);
    }
    free_parse_results(results, result_count);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Mixed tokens test\n");
}

void test_mixed_delimiters() {
    printf("Running mixed delimiters test:\n");
    const char* text = "token1,token2 token3;token4";
    int token_count = 0;
    // Použijeme tokenizer s oddělovači ",; "
    char** tokens = tokenize(text, &token_count, ",; ");
    assert(tokens != NULL);
    assert(token_count == 4);
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);
    assert(results != NULL);
    assert(result_count == token_count);
    for (int i = 0; i < result_count; i++) {
        // Ověříme hodnoty tokenů
        assert(strcmp(results[i].value, tokens[i]) == 0);
        // Očekáváme typ identifikátor pro všechny tokeny
        assert(results[i].type == 2);
    }
    free_parse_results(results, result_count);
    free_tokens(tokens, token_count);
    printf(GREEN_COLOR "[PASSED]" RESET_COLOR " Mixed delimiters test\n");
}

int main() {
    test_basic_parsing();
    test_null_tokens_input();
    test_null_result_count_input();
    test_negative_token_count();
    test_empty_token_list();
    test_long_token_list();
    test_special_characters_in_tokens();
    test_mixed_tokens();
    test_mixed_delimiters();
    printf(BLUE_COLOR "All tests passed successfully.\n" RESET_COLOR);
    return 0;
}