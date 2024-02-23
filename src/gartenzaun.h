#ifndef GARTENZAUN_H
#define GARTENZAUN_H

// error codes for the gartenzaun functions
typedef enum gartenzaun_error {
    GARTENZAUN_NO_ERROR,
    GARTENZAUN_INVALID_KEY,
    GARTENZAUN_STRING_SIZE_MISMATCH
} gartenzaun_error;

gartenzaun_error gartenzaun_encrypt(char* plaintext, char* ciphertext, unsigned int length, unsigned int key);
gartenzaun_error gartenzaun_decrypt(char* ciphertext, char* plaintext, unsigned int length, unsigned int key);

#endif