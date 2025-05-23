#include "ex2.h"

/**
 * Returns the alphabetical index (0–25) of a letter.
 * If the character is not an English letter, returns -1.
 *
 * @param c The character to evaluate.
 * @return Index of the letter (0–25), or -1 if not a letter.
 */
int letter_idx(char c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a';
    return -1;
}

void manuallyCleanBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // clean buffer
}

/**
 * Handles Exercise 2:
 * 1. Prompts the user to enter input.
 * 2. Stores the input in a file.
 * 3. Analyzes the file to find the most frequent English letter.
 */
void Ex2()
{
    const char filename[] = "D:\\test\\input.txt";

    // Prompt user for input
    printf("Enter the text that should go into input.txt\n");
    printf("Press Enter when done\n");

    // Write the input to a file
    createFile(filename);

    // Find and print the most frequent letter
    char most = commonestLetter(filename);
    if (most)
        printf("\nMost frequent letter: %c\n", most);
    else
        printf("\nNo English letters were found in the file.\n");
}

/**
 * Reads user input character-by-character and writes it to a file.
 * Ends on EOF (Ctrl+Z in Windows).
 *
 * @param filename Path to the file where input should be stored.
 */
void createFile(char* filename)
{
    manuallyCleanBuffer();
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("createFile – cannot open output file\n");
        return;
    }

    int current = getchar();
    if (current == EOF) {
        fclose(fp);
        return;
    }

    int next = getchar();
    while (next != EOF) {
        fputc(current, fp);
        current = next;
        next = getchar();
    }

    fclose(fp);
}


/**
 * Reads a file and determines the most frequent English letter (case-insensitive).
 *
 * @param filename Path to the input file to analyze.
 * @return The uppercase letter with the highest frequency, or '\0' if none.
 */
char commonestLetter(char* filename)
{
    int freq[26] = { 0 };
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Issue with reading input file\n");
        return '\0';
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        int idx = letter_idx((char)ch);
        if (idx != -1)
            ++freq[idx];
    }
    fclose(fp);

    int bestIdx = -1, bestCount = 0;
    for (int i = 25; i >= 0; i--) {
        if (freq[i] > bestCount) {
            bestCount = freq[i];
            bestIdx = i;
        }
    }
    return bestIdx == -1 ? '\0' : (char)('A' + bestIdx);
}
