#include "Headers.h"
#include "ex1.h"
#include <ctype.h>
#include <string.h>


void Ex1() {
    char letter, str[100] = "";
    char** words_found;
    int array_size = 0;
    printf("hello! please enter your string, its length should be between 1-99 characters\n");
    gets_s(str, sizeof(str));
    printf("now what is the starting letter for all the words you want to find? ");
    getchar(letter);

    words_found = split(letter, str, &array_size);
    if (words_found == NULL)
        printf("no words that start with %c were found", letter);
    else
    {
        printf("here are all the words that start with %c: \n", letter);
        printStringsArray(words_found, array_size);
    }

    freeMatrix(words_found, array_size);
}

char** split(char letter, char* str, int* p_size) {
    *p_size = 1;
    char** ArrayOfWords = malloc(sizeof(char*) * 1);
    ArrayOfWords[0] = NULL;
    int i = 0, counter = 0;
    char curr = str[i];
    while (curr)
    {
        if (tolower(curr) == tolower(letter))
            input_word(&i, &counter, str, ArrayOfWords, p_size);
        else if (curr == ' ')
            skip_spaces(&i, str);
        else
            skip_word(&i, str);
        curr = str[i];
    }

    if (ArrayOfWords[0] == NULL)
    {
        *p_size = 0;
        free (ArrayOfWords[0]);
        return NULL;
    }

    //fit the size of the array to the actual space that is used
    *p_size = counter;
    realloc(ArrayOfWords, sizeof(char*) * *p_size);

    return ArrayOfWords;
}

void input_word(int* i, int* counter, char* str, char** ArrayOfWords, int* p_size)
{
    int j = *i, word_len = 1;
    // check if there is a space to input a word into the array, if not double the size and realloc
    if (*counter > *p_size)
    {
        *p_size = 2 * *p_size;
        realloc(ArrayOfWords, sizeof(char*) * *p_size);
    }

    // scan the word until you see a space and save the size of the word
    while (str[j] != ' ' && str[j] != '\0')
        word_len++;

    // input the word into the array and update 'i'
    ArrayOfWords[*counter] = malloc(word_len);
    for (j = 0;j < word_len - 1;j++)
        ArrayOfWords[*counter][j] = str[*i++];

    ArrayOfWords[*counter][j] = '\0';
    *counter += 1;
    *i += 1;
}

void skip_spaces(int* i, char* str)
{
    while (str[*i] == ' ' && str[*i] != '\0')
        *i += 1;
}

void skip_word(int* i, char* str)
{
    while (str[*i] != ' ' && str[*i] != '\0')
        *i += 1;
}

void printStringsArray(char** str_arr, int size) {
    for (int i = 0; i < size; i++)
        puts(str_arr[i]);
}

void freeMatrix(void** A, int rows) {
    for (int i = 0; i < rows; i++)
        free(A[i]);
    free(A);
    A = NULL;
}
