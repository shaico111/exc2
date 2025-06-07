#include "Headers.h"
#include "ex3.h"

/**
 * Handles Exercise 3:
 * 1. Defines the encoded string.
 * 2. Decodes the string using the decode function.
 * 3. Prints the decoded result.
 */
void Ex3() {
    char str[] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
    decode(str);
    puts(str);
}

/**
 * Decodes an encoded string based on a character replacement rule.
 * Iterates over each character, applying the CHAR_REPLACE macro/function 
 * based on its position within the word.
 * 
 * @param text Pointer to the null-terminated string to decode.
 */
void decode(char* text) {
    int location = 0;       // Current index in the text string.
    int word_location = 1;  // Position of the character within the current word.

    while (text[location] != '\0') {
        if (text[location] != ' ') {
            text[location] = CHAR_REPLACE(text[location], word_location);
            word_location++;
        } else {
            word_location = 1;
        }
        location++;
    }
}
