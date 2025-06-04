#include "Headers.h"
#include "ex3.h"

void Ex3() {
    char str[] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
    decode(str);
    puts(str);
}

void decode(char* text) {
    int location = 0;
    int word_location = 1;
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
