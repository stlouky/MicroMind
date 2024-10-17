#include "../include/ngrams.h"
#include "../include/test_framework.h"
#include <stdlib.h>
#include <string.h>

// Testy

void test_generate_ngrams_basic() {
    char* tokens[] = {"this", "is", "a", "test"};
    int token_count = 4;
    int n = 2;
    int ngram_count = 0;
    
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);

    RUN_TEST("Basic n-grams generation - ngram array should not be NULL", ngrams != NULL);
    RUN_TEST("Basic n-grams generation - ngram count should be 3", ngram_count == 3);

    for (int i = 0; i < ngram_count; i++) {
        RUN_TEST("Basic n-grams generation - ngram size should be 2", ngrams[i].size == n);
    }

    free_ngrams(ngrams, ngram_count);
}

void test_null_tokens_input() {
    int ngram_count = 0;
    NGram* ngrams = generate_ngrams(NULL, 0, 2, &ngram_count);
    RUN_TEST("Null tokens input - ngram array should be NULL", ngrams == NULL);
    RUN_TEST("Null tokens input - ngram count should be 0", ngram_count == 0);
}

void test_empty_token_list() {
    int ngram_count = 0;
    char* tokens[] = {};
    NGram* ngrams = generate_ngrams(tokens, 0, 2, &ngram_count);
    RUN_TEST("Empty token list - ngram array should be NULL", ngrams == NULL);
    RUN_TEST("Empty token list - ngram count should be 0", ngram_count == 0);
}

void test_long_tokens() {
    char* tokens[] = {"thisisaverylongtoken", "anotherlongtoken", "yetanotherlongtoken"};
    int token_count = 3;
    int n = 2;
    int ngram_count = 0;
    
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);

    RUN_TEST("Long tokens - ngram array should not be NULL", ngrams != NULL);
    RUN_TEST("Long tokens - ngram count should be 2", ngram_count == 2);
    
    free_ngrams(ngrams, ngram_count);
}

void test_special_characters() {
    char* tokens[] = {"hello!", "#world", "$money", "%percentage"};
    int token_count = 4;
    int n = 2;
    int ngram_count = 0;
    
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    
    RUN_TEST("Special characters - ngram array should not be NULL", ngrams != NULL);
    RUN_TEST("Special characters - ngram count should be 3", ngram_count == 3);
    
    free_ngrams(ngrams, ngram_count);
}

void test_mixed_languages() {
    char* tokens[] = {"こんにちは", "world", "你好", "hello"};
    int token_count = 4;
    int n = 2;
    int ngram_count = 0;
    
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    
    RUN_TEST("Mixed languages - ngram array should not be NULL", ngrams != NULL);
    RUN_TEST("Mixed languages - ngram count should be 3", ngram_count == 3);
    
    free_ngrams(ngrams, ngram_count);
}

void test_different_n_values() {
    char* tokens[] = {"this", "is", "a", "test", "of", "ngrams"};
    int token_count = 6;

    // Test pro bigram
    int ngram_count = 0;
    int n = 2;
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    RUN_TEST("Bigram - ngram count should be 5", ngram_count == 5);
    free_ngrams(ngrams, ngram_count);

    // Test pro trigram
    n = 3;
    ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    RUN_TEST("Trigram - ngram count should be 4", ngram_count == 4);
    free_ngrams(ngrams, ngram_count);

    // Test pro n větší než token_count
    n = 7;
    ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    RUN_TEST("n greater than token_count - ngram array should be NULL", ngrams == NULL);
    RUN_TEST("n greater than token_count - ngram count should be 0", ngram_count == 0);
}

void test_max_n_value() {
    char* tokens[] = {"this", "is", "a", "test"};
    int token_count = 4;
    int n = 4;  // n rovné počtu tokenů
    int ngram_count = 0;
    
    NGram* ngrams = generate_ngrams(tokens, token_count, n, &ngram_count);
    
    RUN_TEST("Max n value - ngram count should be 1", ngram_count == 1);
    RUN_TEST("Max n value - ngram array should not be NULL", ngrams != NULL);

    free_ngrams(ngrams, ngram_count);
}

void test_large_input() {
    // Generování velkého počtu tokenů
    int token_count = 10000;
    char** tokens = (char**)malloc(token_count * sizeof(char*));
    for (int i = 0; i < token_count; i++) {
        tokens[i] = (char*)malloc(20 * sizeof(char));
        sprintf(tokens[i], "token%d", i);
    }

    int ngram_count = 0;
    NGram* ngrams = generate_ngrams(tokens, token_count, 2, &ngram_count);
    
    RUN_TEST("Large input - ngram array should not be NULL", ngrams != NULL);
    RUN_TEST("Large input - ngram count should be 9999", ngram_count == 9999);

    free_ngrams(ngrams, ngram_count);
    
    // Uvolnění tokenů
    for (int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

// Hlavní funkce pro spuštění všech testů
int main() {
    test_generate_ngrams_basic();
    test_null_tokens_input();
    test_empty_token_list();
    test_long_tokens();
    test_special_characters();
    test_mixed_languages();
    test_different_n_values();
    test_max_n_value();
    test_large_input();

    print_test_summary();  // Výpis souhrnu výsledků testů
    return 0;
}
