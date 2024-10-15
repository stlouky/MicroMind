#include "../include/tokenizer.h"
#include "../include/test_framework.h"
#include "../include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definice barev pro výstup v terminálu
#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define BLUE_COLOR    "\033[34m"


void test_basic_tokenization() {
    const char* text = "Toto je jednoduchý test tokenizeru.";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Basic tokenization - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Basic tokenization - token count should be 5", token_count == 5);
    if (tokens != NULL) {
        RUN_TEST("Basic tokenization - first token should be 'Toto'", strcmp(tokens[0], "Toto") == 0);
        RUN_TEST("Basic tokenization - second token should be 'je'", strcmp(tokens[1], "je") == 0);
        RUN_TEST("Basic tokenization - third token should be 'jednoduchý'", strcmp(tokens[2], "jednoduchý") == 0);
        RUN_TEST("Basic tokenization - fourth token should be 'test'", strcmp(tokens[3], "test") == 0);
        RUN_TEST("Basic tokenization - fifth token should be 'tokenizeru.'", strcmp(tokens[4], "tokenizeru.") == 0);
        free_tokens(tokens, token_count);
    }
}

void test_custom_delimiters() {
    const char* text = "Jedna, dvě, tři, čtyři, pět";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, ", ");

    RUN_TEST("Custom delimiters - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Custom delimiters - token count should be 5", token_count == 5);
    if (tokens != NULL) {
        RUN_TEST("Custom delimiters - first token should be 'Jedna'", strcmp(tokens[0], "Jedna") == 0);
        RUN_TEST("Custom delimiters - second token should be 'dvě'", strcmp(tokens[1], "dvě") == 0);
        RUN_TEST("Custom delimiters - third token should be 'tři'", strcmp(tokens[2], "tři") == 0);
        RUN_TEST("Custom delimiters - fourth token should be 'čtyři'", strcmp(tokens[3], "čtyři") == 0);
        RUN_TEST("Custom delimiters - fifth token should be 'pět'", strcmp(tokens[4], "pět") == 0);
        free_tokens(tokens, token_count);
    }
}

void test_empty_string() {
    const char* text = "";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Empty string - token count should be 0", token_count == 0);
    free_tokens(tokens, token_count);
}

void test_null_input() {
    int token_count = 0;
    char** tokens = tokenize(NULL, &token_count, NULL);
    RUN_TEST("Null input - tokens should be NULL", tokens == NULL);
}

void test_null_token_count() {
    const char* text = "Test bez token_count";
    char** tokens = tokenize(text, NULL, NULL);
    RUN_TEST("Null token count - tokens should be NULL", tokens == NULL);
}

void test_long_text() {
    const char* text = "Toto je dlouhý text, který obsahuje mnoho slov a slouží k otestování tokenizeru s větším množstvím dat.";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Long text - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Long text - token count should be 17", token_count == 17);
    free_tokens(tokens, token_count);
}

void test_special_characters() {
    const char* text = "Speciální znaky: !@#$%^&*()_+{}|:\"<>?";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, " ");

    RUN_TEST("Special characters - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Special characters - token count should be 3", token_count == 3);
    if (tokens != NULL) {
        RUN_TEST("Special characters - first token should be 'Speciální'", strcmp(tokens[0], "Speciální") == 0);
        RUN_TEST("Special characters - second token should be 'znaky:'", strcmp(tokens[1], "znaky:") == 0);
        free_tokens(tokens, token_count);
    }
}

void test_unicode_characters() {
    const char* text = "Příliš žluťoučký kůň úpěl ďábelské ódy.";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Unicode characters - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Unicode characters - token count should be 6", token_count == 6);
    free_tokens(tokens, token_count);
}

void test_repeated_delimiters() {
    const char* text = "Slovo1   Slovo2\t\tSlovo3\n\nSlovo4";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Repeated delimiters - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Repeated delimiters - token count should be 4", token_count == 4);
    free_tokens(tokens, token_count);
}

void test_leading_trailing_delimiters() {
    const char* text = "  Slovo1 Slovo2 Slovo3  ";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Leading and trailing delimiters - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Leading and trailing delimiters - token count should be 3", token_count == 3);
    free_tokens(tokens, token_count);
}

void test_long_words() {
    const char* text = "Superkalifragilistikexpialidocious";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Long words - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Long words - token count should be 1", token_count == 1);
    if (tokens != NULL) {
        RUN_TEST("Long words - token should be 'Superkalifragilistikexpialidocious'", strcmp(tokens[0], "Superkalifragilistikexpialidocious") == 0);
        free_tokens(tokens, token_count);
    }
}

void test_mixed_delimiters() {
    const char* text = "Slovo1,Slovo2;Slovo3:Slovo4.Slovo5";
    int token_count = 0;
    const char* delimiters = ",;:.";
    char** tokens = tokenize(text, &token_count, delimiters);

    RUN_TEST("Mixed delimiters - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Mixed delimiters - token count should be 5", token_count == 5);
    free_tokens(tokens, token_count);
}

void test_multilingual_text() {
    const char* text = "Привет мир こんにちは世界 مرحبا بالعالم";
    int token_count = 0;
    char** tokens = tokenize(text, &token_count, NULL);

    RUN_TEST("Multilingual text - tokens should not be NULL", tokens != NULL);
    RUN_TEST("Multilingual text - token count should be 5", token_count == 5);
    free_tokens(tokens, token_count);
}

int main() {
    test_basic_tokenization();
    test_custom_delimiters();
    test_empty_string();
    test_null_input();
    test_null_token_count();
    test_long_text();
    test_special_characters();
    test_unicode_characters();
    test_repeated_delimiters();
    test_leading_trailing_delimiters();
    test_long_words();
    test_mixed_delimiters();
    test_multilingual_text();

    print_test_summary();
    return 0;
}