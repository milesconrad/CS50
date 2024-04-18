#include <string.h>
#include <stdio.h>
#include <stdlib.h>

double get_double(char prompt[]) {
    // reserve space for input, then ask for input
    int length = 30;
    char *input = malloc(sizeof(char) * length);
    printf("%s", prompt);
    fgets(input, sizeof(char) * length, stdin);

    int decimal_pos, negative_pos;
    // go through each character of the inputted string
    for (int i = 0; i < length; i++) {
        // checks to see if the focused character is not a digit
        if (input[i] < 48 || input[i] > 57) {
            // if the character is a "new line" character, and it's not the first character in the
            // string, then we have reached the end of the string and we should exit
            if (input[i] == 10 && i != 0) {
                break;
            }
            else if (input[i] == 45) {
                negative_pos = i;
            }
            else if (input[i] == 46) {
                decimal_pos = i;
            }
            // if the character is not a digit, negative symbol or decimal, then the string cannot be a number
            else {
                return get_double(prompt);
            }
        }
    }
    // if the string has a decimal point before there is a negative symbol, then it can't be a number
    if (decimal_pos < negative_pos || negative_pos > 0) {
        return get_double(prompt);
    }

    int output = atof(input);
    free(input);
    return output;
}

int get_int(char prompt[]) {
    // reserve space for input, then ask for input
    int length = 11;
    char *input = malloc(sizeof(char) * length);
    printf("%s", prompt);
    fgets(input, sizeof(char) * length, stdin);

    int negative_pos;
    // go through each character of the inputted string
    for (int i = 0; i < length; i++) {
        // checks to see if the focused character is not a digit
        if (input[i] < 48 || input[i] > 57) {
            // if the character is a "new line" character, and it's not the first character in the
            // string, then we have reached the end of the string and we should exit
            if (input[i] == 10 && i != 0) {
                break;
            }
            else if (input[i] == 45) {
                negative_pos = i;
            }
            // if the character is not a digit or negative symbol, then the string cannot be a number
            else {
                return get_int(prompt);
            }
        }
    }
    // if the string has a negative symbol in the middle of the string, then it is not a number and the function must restart
    if (negative_pos > 0) {
        return get_double(prompt);
    }

    int output = atoi(input);
    free(input);
    return output;
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
        // mapping input into a new string to remove the "new line" character
        int output_length = strlen(input) - 1;
        char *output = malloc(sizeof(char) * output_length);
        for (int i = 0; i < output_length; i++) {
            output[i] = input[i];
        }
        free(input);
        return output;
    }
}