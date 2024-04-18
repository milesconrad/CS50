#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *get_int_string(char prompt[]);

bool luhns(char credit_card_number[]);

int main(void) {
    char *card_number = get_int_string("Please insert a credit card number: ");

    if (luhns(card_number)) {
        // added the - 1 because of the "new line" character
        int length = strlen(card_number) - 1;

        if (length == 13 || length == 15 || length == 16) {
            if (card_number[0] == '4') {
                printf("VISA\n");
                return 0;
            }
            else if (card_number[0] == '5') {
                // ASCII code for 1 is 49, ASCII code for 5 is 53
                for (int i = 49; i < 54; i++) {
                    if ((int) card_number[1] == i) {
                        printf("MASTERCARD\n");
                        return 0;
                    }
                }
                printf("INVALID\n");
            }
            else if (card_number[0] == '3') {
                if (card_number[1] == '4' || card_number[1] == '7') {
                    printf("AMEX\n");
                    return 0;
                }
                else {
                    printf("INVALID\n");
                }
            }
            else {
                printf("INVALID\n");
            }
        }
        else {
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }
}

char *get_int_string(char prompt[]) {
    // reserve space for input, then ask for input
    int string_length = 40;
    char *input = malloc(sizeof(char) * string_length);
    printf("%s", prompt);
    fgets(input, sizeof(char) * string_length, stdin);

    // find the length of the inputted string
    int length = strlen(input);
    // go through each character of the inputted string
    for (int i = 0; i < length; i++) {
        // checks to see if the focused character is not a digit
        if (input[i] < 48 || input[i] > 57) {
            // if the character is a "new line" character, and it's not the first character in the
            // string, then we have reached the end of the string and we should exit
            if (input[i] == 10 && i != 0) {
                break;
            }
            // if the character is not a digit, then the string cannot be a number
            else {
                return get_int_string(prompt);
            }
        }
    }

    return input;
}

bool luhns(char *digits) {
    // added the - 1 because of the "new line" character
    int length = strlen(digits) - 1;
    int sum = 0;

    for (int i = length - 2; i >= 0; i -= 2) {
        // multiply focused number by 2, and convert it to a string so we can add 1 digit at a time
        char* num_as_string = malloc(sizeof(char) * 2);
        sprintf(num_as_string, "%i", (digits[i] - 48) * 2);

        for (int j = 0; j < 2; j++) {
            if (num_as_string[j] != 0) {
                sum += num_as_string[j] - 48;
            }
        }
    }
    for (int i = length - 1; i >= 0; i -= 2) {
        sum += digits[i] - 48;
    }

    return sum % 10 == 0;
}