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
    char letter = '-', str[100];
    char** words_found;
    int array_size = 0;
    // asking the user to enter a string with a length between 1-99 characters
    printf("hello! please enter your string, its length should be between 1-99 characters\n");
    scanf(" %99[^\n]", str);

    // asking the user to enter the starting letter for the words they wish us to find
    printf("now what is the starting letter for all the words you want to find? ");
    scanf(" %c", &letter);

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

    freeMatrix((void**)words_found, array_size);
}

/*
 * this function will create an array that will contain all the words
 * from a given string that start with a specific letter supplied by the user.
 * this function will also return the size of said array by reference
 *
 * @param letter  the letter every returned word must start with (case-insensitive)
 * @param str     input string to scan
 * @param p_size  [output variable] will be updated to number of matching words
 *
 * @return  a dynamic array of strings (each word malloc’ed separately);
 *          NULL if no matching words were found
 */
char** split(char letter, char* str, int* p_size) {
    // creating the initial array
    *p_size = 0;
    char** ArrayOfWords = NULL;
    int i = 0, counter = 0;
    char curr = str[i];

    // loop through the spaces and initials of each word in str
    while (curr)
    {
        if (tolower(curr) == tolower(letter))
            // current letter is equal to the given letter
            input_word(&i, &counter, &str, &ArrayOfWords, p_size);
        else if (curr == ' ')
            // current letter is a space
            skip_spaces(&i, str);
        else
            // current letter isn't a space or the given letter
            skip_word(&i, str);

        // get the next space or initial of the next word
        curr = str[i];
    }

    //if we didn't find any words
    if (counter == 0)
    {
        // free the array and return null
        free(ArrayOfWords);
        *p_size = 0;
        return NULL;
    }

    
    // getting rid of any unused memory space in the array and returning the array
    *p_size = counter;
    char** temp = realloc(ArrayOfWords, sizeof(char*) * (*p_size));

    ArrayOfWords = temp;

    return ArrayOfWords;
}


/*
 * this function will input a word into the array from the split function
 *
 * @param i           [input&output variable] index in the string, updated to point after the inserted word
 * @param counter     [input&output variable] current number of words inserted into the array
 * @param str         pointer to the input string (NUL-terminated)
 * @param ArrayOfWords [input&output variable] pointer to the dynamic array of words, may be reallocated
 * @param p_size      [input&output variable] current allocated size of ArrayOfWords, updated if reallocation occurs
 * 
 */
void input_word(int* i, int* counter, char** str, char*** ArrayOfWords, int* p_size)
{
    int j = *i, word_len = 0;
    // check if there is a space to input a word into the array, if not double the size of the array
    if (*counter >= *p_size)
    {
        *p_size = (*p_size == 0) ? 2 : 2 * (*p_size);
        char** temp = realloc(*ArrayOfWords, sizeof(char*) * (*p_size));
        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        *ArrayOfWords = temp;
    }

    // check inside the string how long is the word we wish to input and save the length + a space for the null char '\0'
    while ((*str)[j] != ' ' && (*str)[j] != '\0')
    {
        word_len++;
        j++;
    }

    // input the found word into the array and update the location to  the next space in our string
    (*ArrayOfWords)[*counter] = (char*)malloc((word_len + 1) * sizeof(char));
    if ((*ArrayOfWords)[*counter] == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (j = 0;j < word_len - 1;j++)
        (*ArrayOfWords)[*counter][j] = (*str)[(*i)++];

    // add the null character '\0' in the end of the word and update the counter
    (*ArrayOfWords)[*counter][j] = '\0';
    *counter += 1;
}

/*
 * this function will skip all the spaces that separate two words
 * until it encounters the next word or the end of the string
 *
 * @param i   [input&output variable] current index in the string
 * @param str input string
 */
void skip_spaces(int* i, char* str)
{
    while (str[*i] == ' ' && str[*i] != '\0')
        *i += 1;
}

/*
* this function will skip the word that doesnt start with the letter given by the user 
* until it encounters a space or the end of the string
* 
* @param i   [input&output variable] current index in the string
* @param str input string
*/
void skip_word(int* i, char* str)
{
    while (str[*i] != ' ' && str[*i] != '\0')
        *i += 1;
}

/*
* this function will print all of the words that the split function found
* 
* @param str_arr  array of words
* @param size     number of words in the array
*/
void printStringsArray(char** str_arr, int size) {
    for (int i = 0; i < size; i++)
        puts(str_arr[i]);
}

/*
* this function will free all the memory allocated for the array of strings and set the pointer to NULL
* 
* @param A     array of pointers (each pointing to allocated memory)
* @param rows  number of elements in the array
*/
void freeMatrix(void** A, int rows) {
    for (int i = 0; i < rows; i++)
        free(A[i]);

    free(A);
    A = NULL;
}