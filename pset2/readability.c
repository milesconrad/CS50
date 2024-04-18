#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *get_string(char prompt[]);

int main(void) {
    char *text = get_string("Text: ");
    int length = strlen(text);

    float L = 0;
    float S = 0;
    int words = 0;
    for (int i = 0; i < length; i++) {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)) {
            L++;
        }
        // punctuation marks the end of a sentence, but also the end of a word, so we skip over
        // the space that follows
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            i++;
            S++;
            words++;
        }
        else if (text[i] == ' ') {
            words++;
        }
    }
    // find 100-word averages for the number of letters and the number of sentences
    S = ((float) 100 / words) * S;
    L = ((float) 100 / words) * L;

    // the algorithm is not perfect, so we need to round to the nearest integer
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1) {
        printf("Before Grade 1\n");
    }
    else if (index > 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", index);
    }
}

char *get_string(char prompt[]) {
    // reserve space for input, then ask for input
    int string_size = 500;
    char *input = malloc(sizeof(char) * string_size);
    printf("%s", prompt);
    fgets(input, sizeof(char) * string_size, stdin);

    if (input[0] == 10) {
        return get_string(prompt);
    }
    else {
        return input;
    }
}