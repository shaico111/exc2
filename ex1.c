#include "Headers.h"
#include "ex1.h"
#include <ctype.h>
#include <string.h>


/*
* this function will prompt the user to enter a string and a starting letter,
* then it will find and print all words in the string that start with the given letter.
* if no such words are found, it will notify the user.
*/
void Ex1() {
    char letter, str[100] = "";
    char** words_found;
    int array_size = 0;
    // asking the user to enter a string with a length between 1-99 characters
    printf("hello! please enter your string, its length should be between 1-99 characters\n");
    gets_s(str, sizeof(str));

    // asking the user to enter the starting letter for the words they wish us to find
    printf("now what is the starting letter for all the words you want to find? ");
    getchar(letter);

	// getting an array of words that start with the letter given by the user using the split function
    words_found = split(letter, str, &array_size);

	// checking if the split function found any words
    if (words_found == NULL)
        printf("no words that start with %c were found", letter);
    else
    {
        printf("here are all the words that start with %c: \n", letter);
        printStringsArray(words_found, array_size);
    }

    freeMatrix(words_found, array_size);
}

/*
* this function will create an array that will contain all the words from a given string that start with a specific letter,
* supplied by the user.
* this function will also return the size of said array by reference/
*/
char** split(char letter, char* str, int* p_size) {
    // creating the initial array and setting its size to 1
    *p_size = 1;
    char** ArrayOfWords = malloc(sizeof(char*) * 1);
    ArrayOfWords[0] = NULL;
    int i = 0, counter = 0;
    char curr = str[i];

    // a loop that goes through every single word and makes a decision on how to proccess it base on three cases:
    // 1) this word starts with the corect letter 
    // 2) this word does not start with the corect letter 
    // 3) we are in the space between words
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

    //checking if we found any words
    if (ArrayOfWords[0] == NULL)
    {
        // setting the size to 0, freeing the unused memory and returning that no word was found (return NULL)
        *p_size = 0;
        free (ArrayOfWords[0]);
        return NULL;
    }

    // getting rid of any unused memory space in the array and returning the array
    *p_size = counter;
    realloc(ArrayOfWords, sizeof(char*) * *p_size);

    return ArrayOfWords;
}


/*
* this function will input a word into the array from the split function
*/
void input_word(int* i, int* counter, char* str, char** ArrayOfWords, int* p_size)
{
    int j = *i, word_len = 1;
    // check if there is a space to input a word into the array, if not double the size of the array
    if (*counter > *p_size)
    {
        *p_size = 2 * *p_size;
        realloc(ArrayOfWords, sizeof(char*) * *p_size);
    }

    // check inside the string how long is the word we wish to input and save the length + a space for the null char '\0'
    while (str[j] != ' ' && str[j] != '\0')
        word_len++;

    // input the found word into the array and update the location to one character before the next space in our string
    ArrayOfWords[*counter] = malloc(word_len);
    for (j = 0;j < word_len - 1;j++)
        ArrayOfWords[*counter][j] = str[*i++];

    // add the null character '\0' in the end of the word and update the counter and location of the next space in the string
    ArrayOfWords[*counter][j] = '\0';
    *counter += 1;
    *i += 1;
}

/*
* this function will skip all the spaces that seperate two words 
* until it encounters the next word or the end of the string
*/
void skip_spaces(int* i, char* str)
{
    while (str[*i] == ' ' && str[*i] != '\0')
        *i += 1;
}

/*
* this function will skip the word that doesnt start with the letter given by the user 
* until it encounters a space or the end of the string
*/
void skip_word(int* i, char* str)
{
    while (str[*i] != ' ' && str[*i] != '\0')
        *i += 1;
}

/*
* this function will print ll of the words that the split function found
*/
void printStringsArray(char** str_arr, int size) {
    for (int i = 0; i < size; i++)
        puts(str_arr[i]);
}

/*
* this function will free all the memory allocated for the array of strings and set the pointer to NULL
*/
void freeMatrix(void** A, int rows) {
    for (int i = 0; i < rows; i++)
        free(A[i]);
    free(A);
    A = NULL;
}
