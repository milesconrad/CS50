#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_string(char prompt[]);

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // if the key is over 26, we want to reduce it so we aren't looping through the alphabet
    int shift = atoi(argv[1]) % 26;
    if (shift < 1) {
        printf("Usage: ./caesar key\n");
        return 2;
    }

    char *cipher = get_string("plaintext: ");
    int length = strlen(cipher);

    for (int i = 0; i < length; i++) {
        if (cipher[i] >= 'a' && cipher[i] <= 'z') {
            if ('z' - cipher[i] < shift) {
                cipher[i] -= 26 - shift;
            }
            else {
                cipher[i] += shift;
            }
        }
        else if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
            if ('Z' - cipher[i] < shift) {
                cipher[i] -= 26 - shift;
            }
            else {
                cipher[i] += shift;
            }
        }
    }

    printf("ciphertext: %s\n", cipher);
    free(cipher);
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