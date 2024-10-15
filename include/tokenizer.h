#ifndef TOKENIZER_H
#define TOKENIZER_H

/**
 * @brief Rozdělí vstupní text na tokeny podle zadaných oddělovačů.
 * 
 * @param text Vstupní řetězec, který má být tokenizován.
 * @param token_count Ukazatel na int, kam bude uložen počet nalezených tokenů.
 * @param delimiters Řetězec obsahující oddělovače. Pokud je NULL, použijí se výchozí oddělovače " \t\n".
 * @return Pole ukazatelů na tokeny nebo NULL v případě chyby.
 */
char** tokenize(const char* text, int* token_count, const char* delimiters);

/**
 * @brief Uvolní paměť použitou pro tokeny.
 * 
 * @param tokens Pole ukazatelů na tokeny, které mají být uvolněny.
 * @param token_count Počet tokenů v poli.
 */
void free_tokens(char** tokens, int token_count);

#endif // TOKENIZER_H
