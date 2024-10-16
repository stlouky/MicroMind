/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * test_parser.c - Testovací soubor pro testování funkcí z parser.c pomocí testovacího rámce
 *
 * Tento soubor obsahuje testy pro funkce z parser.c, jako je funkce pro parsování vstupního textu.
 */

#include "../include/parser.h"
#include "../include/test_framework.h"

#include <stdlib.h>
#include <string.h> // Přidáno kvůli strcmp
#include <errno.h>
#include <assert.h>

/**
 * test_parse_text - Testuje funkci parse_text
 *
 * Testuje různé vstupní scénáře pro funkci parse_text a ověřuje správné výsledky.
 */
void test_parse_tokens() {
    // Test 1: Platný vstupní text
    char* tokens1[] = {"Toto", "je", "test"};
    int result_count1 = 0;
    ParseResult* results1 = parse_tokens(tokens1, 3, &result_count1);
    RUN_TEST("Parse valid input", results1 != NULL && result_count1 == 3);
    free_parse_results(results1, result_count1);

    // Test 2: Prázdný vstupní text
    char* tokens2[] = {};
    int result_count2 = 0;
    ParseResult* results2 = parse_tokens(tokens2, 0, &result_count2);
    RUN_TEST("Parse empty input", results2 == NULL && result_count2 == 0);

    // Test 3: NULL jako vstupní text
    int result_count3 = 0;
    ParseResult* results3 = parse_tokens(NULL, 3, &result_count3);
    RUN_TEST("Parse NULL input", results3 == NULL && result_count3 == 0);

    printf("Running null tokens input test:\n");
    int result_count = 0;
    ParseResult* results = parse_tokens(NULL, 3, &result_count);
    RUN_TEST("Null tokens input test", results3 == NULL && result_count3 == 0);
}

void test_multilingual_text() {
    printf("Running null tokens input test\n");
    const char* text = "Привет мир こんにちは世界 مرحبا بالعالم";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Multilingual text - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Multilingual text - token count should be 5", token_count == 5);
    free_tokens(tokens, token_count);
}

void test_basic_parsing() {
    printf("Running basic parsing test:\n");

    char* tokens[] = {"token1", "token2", "token3"};
    int token_count = 3;
    int result_count = 0;

    // Zavolej funkci parse_tokens a získej výsledek
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);

    // Test 1: Kontrola, zda výsledky nejsou NULL
    RUN_TEST("Parse tokens - results are not NULL", results != NULL);

    // Test 2: Kontrola počtu výsledků
    if (results != NULL) {
        RUN_TEST("Parse tokens - result count matches token count", result_count == token_count);

        if (result_count == token_count) {
            int success_count = 0;

            // Test 3: Kontrola hodnot jednotlivých tokenů a typů
            for (int i = 0; i < result_count; i++) {
                if (strcmp(results[i].value, tokens[i]) == 0 && results[i].type == 2) {
                    success_count++;
                }
            }

            RUN_TEST("Parse tokens - all tokens processed successfully", success_count == result_count);
        }

        // Uvolnění výsledků
        free_parse_results(results, result_count);
    }
}


// Running null tokens input test:
void test_null_tokens_input() {
    printf("Running null tokens input test\n");
    int result_count = 0;
    ParseResult* results = parse_tokens(NULL, 3, &result_count);

    RUN_TEST(" Null tokens input test", results == NULL);
}

// Running null result count input test:
void test_null_result_count_input() {
    printf("Running null result count input test\n");
    char* tokens[] = {"token1", "token2"};
    ParseResult* results = parse_tokens(tokens, 2, NULL);

    RUN_TEST(" Null result count input test", results == NULL);
}

// Running negative token count test:
void test_negative_token_count() {
    printf("Running negative token count test:\n");
    char* tokens[] = {"token1", "token2"};
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, -1, &result_count);

    RUN_TEST("Negative token count test", results == NULL);
}

// Running empty token list test
void test_empty_token_list() {
    printf("Running empty token list test\n");
    int result_count = 0;
    ParseResult* results = parse_tokens(NULL, 0, &result_count);

    RUN_TEST("Empty token list test", results == NULL);
}

void test_long_token_list() {
    printf("Running long token list test:\n");
    char* long_tokens[1000];
    for (int i = 0; i < 1000; i++) {
        long_tokens[i] = "token";
    }
    int result_count = 0;
    ParseResult* results = parse_tokens(long_tokens, 1000, &result_count);

    RUN_TEST("Parse tokens - results not NULL", results != NULL);
    RUN_TEST("Parse tokens - correct result count", result_count == 1000);
    for (int i = 0; i < result_count; i++) {
        RUN_TEST("Parse tokens - value matches input", strcmp(results[i].value, "token") == 0);
        RUN_TEST("Parse tokens - type is identifier", results[i].type == 2);
    }
    free_parse_results(results, result_count);
}

void test_special_characters_in_tokens() {
    printf("Running special characters in tokens test:\n");
    char* special_tokens[] = {"!@#$", "%^&*", "()_+"};
    int result_count = 0;
    ParseResult* results = parse_tokens(special_tokens, 3, &result_count);

    RUN_TEST("Parse tokens - results not NULL", results != NULL);
    RUN_TEST("Parse tokens - correct result count", result_count == 3);
    for (int i = 0; i < result_count; i++) {
        RUN_TEST("Parse tokens - value matches input", strcmp(results[i].value, special_tokens[i]) == 0);
        RUN_TEST("Parse tokens - type is identifier", results[i].type == 2);
    }
    free_parse_results(results, result_count);
}

void test_mixed_tokens() {
    printf("Running mixed tokens test:\n");
    char* tokens[] = {"123", "+", "variable", "-", "3.14", "*", "=="};
    int token_count = 7;
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);

    RUN_TEST("Parse tokens - results not NULL", results != NULL);
    RUN_TEST("Parse tokens - correct result count", result_count == token_count);
    int expected_types[] = {0, 1, 2, 1, 0, 1, 1}; // Očekávané typy
    for (int i = 0; i < result_count; i++) {
        RUN_TEST("Parse tokens - value matches input", strcmp(results[i].value, tokens[i]) == 0);
        RUN_TEST("Parse tokens - type matches expected", results[i].type == expected_types[i]);
    }
    free_parse_results(results, result_count);
}

void test_mixed_delimiters() {
    printf("Running mixed delimiters test:\n");
    const char* text = "token1,token2 token3;token4";
    int token_count = 0;
    // Použijeme tokenizer s oddělovači ",; "
    char** tokens = tokenize(text, &token_count, ",; ");

    RUN_TEST("Tokenize - tokens not NULL", tokens != NULL);
    RUN_TEST("Tokenize - correct token count", token_count == 4);
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);

    RUN_TEST("Parse tokens - results not NULL", results != NULL);
    RUN_TEST("Parse tokens - correct result count", result_count == token_count);
    for (int i = 0; i < result_count; i++) {
        RUN_TEST("Parse tokens - value matches input", strcmp(results[i].value, tokens[i]) == 0);
        RUN_TEST("Parse tokens - type is identifier", results[i].type == 2);
    }
    free_parse_results(results, result_count);
    free_tokens(tokens, token_count);
}

// Funkce pro testování velmi dlouhého textového tokenu
void test_very_long_token() {
    printf("Running very long token test:\n");

    char long_token[10000];
    memset(long_token, 'a', sizeof(long_token) - 1);
    long_token[sizeof(long_token) - 1] = '\0';

    char* tokens[] = { long_token };
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, 1, &result_count);

    RUN_TEST("Very long token - results not NULL", results != NULL);
    RUN_TEST("Very long token - correct result count", result_count == 1);
    if (results != NULL) {
        RUN_TEST("Very long token - value matches input", strcmp(results[0].value, long_token) == 0);
        RUN_TEST("Very long token - type is identifier", results[0].type == 2);
    }
    free_parse_results(results, result_count);
}

// Funkce pro testování neplatných znaků v tokenu
void test_invalid_characters_in_token() {
    printf("Running invalid characters in token test:\n");

    char* tokens[] = { "token1", "\x01\x02\x03", "token3" };
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, 3, &result_count);

    RUN_TEST("Invalid characters in token - results not NULL", results != NULL);
    RUN_TEST("Invalid characters in token - correct result count", result_count == 3);
    if (results != NULL) {
        RUN_TEST("Invalid characters in token - value matches input", strcmp(results[1].value, "\x01\x02\x03") == 0);
        RUN_TEST("Invalid characters in token - type is identifier", results[1].type == 2);
    }
    free_parse_results(results, result_count);
}

// Funkce pro testování opakujících se tokenů
void test_repeated_tokens() {
    printf("Running repeated tokens test:\n");

    char* tokens[] = { "repeat", "repeat", "repeat" };
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, 3, &result_count);

    RUN_TEST("Repeated tokens - results not NULL", results != NULL);
    RUN_TEST("Repeated tokens - correct result count", result_count == 3);
    if (results != NULL) {
        for (int i = 0; i < result_count; i++) {
            RUN_TEST("Repeated tokens - value matches input", strcmp(results[i].value, "repeat") == 0);
            RUN_TEST("Repeated tokens - type is identifier", results[i].type == 2);
        }
    }
    free_parse_results(results, result_count);
}

// Funkce pro testování kombinace čísel, operátorů a identifikátorů
void test_combination_of_tokens() {
    printf("Running combination of tokens test:\n");

    char* tokens[] = { "123", "+", "variable", "-", "3.14", "*", "==" };
    int token_count = 7;
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);

    RUN_TEST("Combination of tokens - results not NULL", results != NULL);
    RUN_TEST("Combination of tokens - correct result count", result_count == token_count);

    if (results != NULL && result_count == token_count) {
        int success_count = 0;
        int expected_types[] = {0, 1, 2, 1, 0, 1, 1}; // Očekávané typy

        for (int i = 0; i < result_count; i++) {
            if (strcmp(results[i].value, tokens[i]) == 0 && results[i].type == expected_types[i]) {
                success_count++;
            }
        }

        RUN_TEST("Combination of tokens - all tokens processed successfully", success_count == result_count);
    }

    free_parse_results(results, result_count);
}


// Funkce pro testování smíšených datových typů
void test_mixed_data_types() {
    printf("Running mixed data types test:\n");

    char* tokens[] = { "42", "hello", "3.14", "true", "false" };
    int token_count = 5;
    int result_count = 0;
    ParseResult* results = parse_tokens(tokens, token_count, &result_count);

    RUN_TEST("Mixed data types - results not NULL", results != NULL);
    RUN_TEST("Mixed data types - correct result count", result_count == token_count);
    int expected_types[] = {0, 2, 0, 2, 2}; // Očekávané typy (číslo, identifikátor, číslo, boolean jako identifikátor)
    for (int i = 0; i < result_count; i++) {
        RUN_TEST("Mixed data types - value matches input", strcmp(results[i].value, tokens[i]) == 0);
        RUN_TEST("Mixed data types - type matches expected", results[i].type == expected_types[i]);
    }
    free_parse_results(results, result_count);
}

/**
 * main - Hlavní funkce pro spuštění všech testů
 *
 * Spouští všechny testy definované v tomto souboru.
 */
int main() {
    printf("\nSpouštění testů pro parser.c:\n\n");

  
    test_parse_tokens();
    test_multilingual_text();
    test_basic_parsing();
    test_null_tokens_input();
    test_null_result_count_input();
    test_negative_token_count();
    test_empty_token_list();
    test_long_token_list();
    test_special_characters_in_tokens();
    test_mixed_tokens();
    test_mixed_delimiters();
    test_very_long_token();
    test_invalid_characters_in_token();
    test_repeated_tokens();
    test_combination_of_tokens();
    test_mixed_data_types();

    printf("\nTesty dokončeny\n");
    printf("\nCelkové shrnutí: %d/%d testů úspěšných.\n", passed_tests, total_tests);

    return 0;
}