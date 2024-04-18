#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_string(char prompt[]);

int main(int argc, char *args[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // checks the key's length
    char *key = args[1];
    if (strlen(key) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // checks if the key is all letters
    for (int i = 0; i < 26; i++) {
        if (key[i] < 65 || key[i] > 90) {
            if (key[i] < 97 || key[i] > 122) {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    // checks for duplicate characters
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (i == j) {
                continue;
            }
            else if (key[i] == key[j]) {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    // makes all the letters in the key uppercase
    for (int i = 0; i < 26; i++) {
        if (key[i] >= 97) {
            key[i] -= 32;
        }
    }

    char *input = get_string("plaintext: ");
    int length = strlen(input);
    char *output = malloc(sizeof(char) * (length - 1));

    int char_value;
    for (int i = 0; i < length; i++) {
        char_value = (int) input[i];
        // converts inputted letter from ascii to an index of the alphabet
        if (char_value >= 97) {
            char_value -= 97;
            output[i] = key[char_value] + 32;
        }
        else if (char_value >= 65) {
            char_value -= 65;
            output[i] = key[char_value];
        }

        // if the character is a "new line" character, then we should stop encrypting
        else if (char_value == 10) {
            break;
        }
        // if a character is not a letter, it should remain the same
        else {
            output[i] = input[i];
        }
    }

    printf("ciphertext: %s\n", output);

    free(input);
    free(output);
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