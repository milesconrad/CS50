#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double get_float(char prompt[]);

int main(void) {
    float input = get_float("Amount owed: ");
    long cents = round(input * 100);
    int coins = 0;

    while (cents > 0) {
        if (cents >= 25) {
            cents -= 25;
            coins++;
        }
        else if (cents >= 10) {
            cents -= 10;
            coins++;
        }
        else if (cents >= 5) {
            cents -= 5;
            coins++;
        }
        else {
            cents -= 1;
            coins++;
        }
    }

    printf("%i\n coins", coins);
}

double get_float(char prompt[]) {
    // reserve space for input, then ask for input
    int length = 20;
    char *input = malloc(sizeof(char) * length);
    printf("%s", prompt);
    fgets(input, sizeof(char) * length, stdin);

    // go through each character of the inputted string
    for (int i = 0; i < length; i++) {
        // checks to see if the focused character is not a digit
        if ((input[i] < 48 || input[i] > 57) && input[i] != 46) {
            // if the character is a "new line" character, and it's not the first character in the
            // string, then we have reached the end of the string and we should exit
            if (input[i] == 10 && i != 0) {
                break;
            }
            // if the character is not a digit, negative symbol or decimal, then the string cannot be a number
            else {
                return get_float(prompt);
            }
        }
    }

    return atof(input);
}