#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "gartenzaun.h"

void print_help() {
    printf(""
        "Usage:\n"
        "    gartenzaun [options] <key> <text>...\n"
        "    gartenzaun [options] <key>\n"
        "Encrypt or decrypt a piece of text using the rail fence cypher.\n"
        "\n"
        "Options:\n"
        "    -h --help      Prints this help message\n"
        "    -e --encrypt   Encrypts passed or piped text\n"
        "    -d --decrypt   Decrypts passed or piped text\n"
        "\n"
        "If no text has been passed upon calling the program, text will be read from the input stream and the output immediatly returned until the program gets terminated."
        "\n"
    );
}

void static_process(char* input, int length, int key, bool encrypt) {
    char output[length];

    if (encrypt)
        gartenzaun_encrypt(input, output, length - 1, key);
    else
        gartenzaun_decrypt(input, output, length - 1, key);

    printf("%s\n", output);
}

void dynamic_process(int key, bool encrypt) {
    int stepsize = 100;

    while (true) {
        int step = 1;
        char* input = malloc((stepsize * step + 1) * sizeof(char));

        char read[stepsize + 1];
        while (fgets(read, stepsize + 1, stdin)) {
            int end = strlen(read) - 1;
            if (end >= 0) {
                if (read[end] == '\n') {
                    read[end] = '\0'; // replace the \n with a terminator to remove it before coyping
                    strcat(input, read);

                    // full line read
                    break;
                }
                else {
                    strcpy(input, read);

                    // need to read more
                    // extend string
                    char* new_input = malloc((stepsize * ++step + 1) * sizeof(char));
                    strcpy(new_input, input);
                    free(input);
                    input = new_input;

                    // repeat
                }
            }
            else {
                // should never happen
                printf("Unexpected string!\n");
                return;
            }
        }

        char* output = malloc((stepsize * step + 1) * sizeof(char));

        if (encrypt)
            gartenzaun_encrypt(input, output, strlen(input), key);
        else
            gartenzaun_decrypt(input, output, strlen(input), key);

        free(input);
        printf("%s\n", output);
        free(output);
    }
}

int main(int argc, char** argv) {
    bool encrypt = true;
    int key = 1;
    int text_arg_start = argc;

    // check for options
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_help();
            return 0;
        }
        else if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0) {
            // do nothing
            // already set to encrypt
        }
        else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0) {
            encrypt = false;
        }
        else {
            printf("No encryption option and key specified.\n");
            return 1;
        }
    }

    // check key
    if (argc > 2) {
        key = atoi(argv[2]);
        if (key < 1) {
            printf("Invalid key.\n");
            return 2;
        }
    }
    else {
        printf("No key specified.\n");
        return 1;
    }

    // check text
    if (argc > 3) {
        text_arg_start = 3;
    }

    // determine length of passed text
    unsigned int array_size = 0;
    for (int i = text_arg_start; i < argc; i++) {
        array_size += strlen(argv[i]) + 1; // + 1 for whitespace or string termination
    }

    // pass on to subroutines
    if (array_size == 0) {
        dynamic_process(key, encrypt);
    }
    else {
        char* input = malloc(array_size * sizeof(char));

        for (int i = text_arg_start; i < argc; i++) {
            strcat(input, argv[i]);

            if (i < argc - 1)
                strcat(input, " ");
        }

        static_process(input, array_size, key, encrypt);

        free(input);
    }

    return 0;
}