#include "gartenzaun.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * This function maps the given character index of row n into
 * the index of the same character in the plain text
 *
 * m = maximum numbers of rows
 * n = current row
 * i = index in row n
 */
int gartenzaun_index_function(unsigned int m, unsigned int n, unsigned int i)
{
    // determine amount of even and uneven regions up until the index
    unsigned int even   = (int) floor( (double)i / 2.0 );
    unsigned int uneven = (int) ceil ( (double)i / 2.0 );

    // define gap sizes in relation to the dimensions of the rail fence cipher
    unsigned int smallgap = (m + (m - 2) - 2 * n);
    unsigned int biggap = 2 * n;

    if (n == m - 1) {
        int tmp = biggap;
        biggap = smallgap;
        smallgap = tmp;
    }
    if (biggap == 0) biggap = smallgap;

    // return where the passed index would be in the rail fence cipher
    return n + even * biggap + uneven * smallgap;
}


gartenzaun_error gartenzaun_encrypt(char* restrict plaintext, char* restrict ciphertext, unsigned int length, unsigned int key)
{
    // perform error checks
    // NOTE: not checking for length > strlen(xyz_text)
    if (key < 2) return GARTENZAUN_INVALID_KEY;
    if (sizeof(plaintext) != sizeof(ciphertext)) return GARTENZAUN_STRING_SIZE_MISMATCH;

    // clear destination variable
    strcpy(ciphertext, "");

    // iterate over every row
    for (unsigned int n = 0; n < key; n++) {
        // iterate over every possible character in that row
        // (length / 2 + 1) is the theoretical maximum
        for (unsigned int i = 0; i < length / 2 + 1; i++) {
            int plain_index = gartenzaun_index_function(key, n, i);

            // check if i is actually out of range
            if (plain_index >= length) {
                // current row is done / fully appended to the cipher text
                // continue to the next
                break;
            }

            // append the found character to the cipher text
            char* sequence = (char[2]){ plaintext[plain_index], '\0' };
            strcat(ciphertext, sequence);
        }
    }

    // finish
    return GARTENZAUN_NO_ERROR;
}


gartenzaun_error gartenzaun_decrypt(char* restrict ciphertext, char* restrict plaintext, unsigned int length, unsigned int key)
{
    // perform error checks
    // NOTE: not checking for length > strlen(xyz_text)
    if (key < 2) return GARTENZAUN_INVALID_KEY;
    if (sizeof(plaintext) != sizeof(ciphertext)) return GARTENZAUN_STRING_SIZE_MISMATCH;

    // fill plaintext with placeholder symbols
    strcpy(plaintext, "");
    for (int i = 0; i < length; i++) {
        strcat(plaintext, "#");
    }

    // count variable to keep track of the current cursor position in the cipher text
    unsigned int cipher_index = 0;

    // iterate over every row
    for (unsigned int n = 0; n < key; n++) {
        // iterate over every possible character in that row
        // (length / 2 + 1) is the theoretical maximum
        for (unsigned int i = 0; i < length / 2 + 1; i++) {
            int plain_index = gartenzaun_index_function(key, n, i);

            // check if i is actually out of range
            if (plain_index >= length) {
                // current row is done / fully appended to the cipher text
                // continue to the next
                break;
            }

            // insert the current character into the plaintext
            plaintext[plain_index] = ciphertext[cipher_index++];
        }
    }

    // finish
    return GARTENZAUN_NO_ERROR;
}