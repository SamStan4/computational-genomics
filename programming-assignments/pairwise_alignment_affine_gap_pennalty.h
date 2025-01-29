#ifndef PAIRWISE_ALIGNMENT_AFFINE_GAP_PENNALTY
#define PAIRWISE_ALIGNMENT_AFFINE_GAP_PENNALTY

#include <stdio.h>
#include <stdlib.h>

#define FILE_READ_BUFFER_SIZE_BYTES 100

/**
 * Gets the parameters from the file path
 * returns:
 *      0 --> Could not read from file
 *      1 --> Got input from the file
 */
int get_parameters(char* file_path, double* match_parameter, double* mismatch_parameter, double* h_parameter, double* g_parameter) {
    FILE* file_ptr = fopen(file_path, "r");
    if (file_ptr == NULL) {
        return 0;
    }
    char buffer[FILE_READ_BUFFER_SIZE_BYTES] = { '\0' };
    while (fgets(buffer, FILE_READ_BUFFER_SIZE_BYTES, file_ptr) != NULL) {
        char key[FILE_READ_BUFFER_SIZE_BYTES] = { '\0' }, value[FILE_READ_BUFFER_SIZE_BYTES] = { '\0' };
        int i = 0;
        for (int j = 0; i < FILE_READ_BUFFER_SIZE_BYTES && buffer[i] != ' '; ++i) {
            key[i] = buffer[i];
        }
        // TODO: finish this
    }
    return 1;
}

#endif