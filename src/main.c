#include <stdio.h>
#include <string.h>
#include "gartenzaun.h"

int main(int argc, char** argv) {
    char* plaintext = "Gartenzaun test verFahren";
    char ciphertext[strlen(plaintext)];
    char reverted[strlen(plaintext)];

    gartenzaun_encrypt(plaintext, ciphertext, strlen(plaintext), 4);
    gartenzaun_decrypt(ciphertext, reverted, strlen(plaintext), 4);

    printf("%s\n", plaintext);
    printf("%s\n", ciphertext);
    printf("%s\n", reverted);

    return 0;
}