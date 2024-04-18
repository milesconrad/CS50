#include <stdio.h>
#include <stdlib.h>

int get_int(char prompt[]);

int main(void) {
    int depth = get_int("Please enter a number 1-8: ");
    char *line_string = malloc(sizeof(char) * depth);


    // have to start at 1 because we need the line number for some calculations
    for (int line = 1; line <= depth; line++) {
        for (int i = 0; i < depth; i++) {
            if (i < depth - line) {
                line_string[i] = ' ';
            }
            else {
                line_string[i] = '#';
            }
        }

        printf("%s\n", line_string);
    }
}

int get_int(char prompt[]) {
    // reserve space for input, then ask for input
    char input[11];
    printf("%s", prompt);
    fgets(input, sizeof(input), stdin);

    // find the length of the inputted string
    int length = sizeof(input) / sizeof(input[0]);
    // go through each character of the inputted string
    for (int i = 0; i < length; i++) {
        // checks to see if the focused character is not a digit
        if (input[i] < 49 || input[i] > 56) {
            // if the character is a "new line" character, and it's not the first character in the
            // string, then we have reached the end of the string and we should exit
            if (input[i] == 10 && i != 0) {
                break;
            }
            // if the character is not a digit or negative symbol, then the string cannot be a number
            else {
                return get_int(prompt);
            }
        }
    }

    return atoi(input);
}