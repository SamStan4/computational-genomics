#ifndef PAIRWISE_ALIGNMENT_AFFINE_GAP_PENNALTY
#define PAIRWISE_ALIGNMENT_AFFINE_GAP_PENNALTY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FILE_READ_BUFFER_SIZE_BYTES 100

extern const char* match_constant_key_name;
extern const char* mismatch_constant_key_name;
extern const char* h_constant_key_name;
extern const char* g_constant_key_name;

/**
 * The different parameters for the pairwise affine gap pennalty
 * sequence alignment algorithm.
 */
struct alignment_parameters {
    double match_constant;
    double mismatch_constant;
    double h_constant;
    double g_constant;
};

/**
 * This is the dynamic programming cell that we went over in class
 * this cell will include three difference values.
 */
struct alignment_dp_cell {
    int s;
    int i;
    int d;
};

void alignment_parameters_init(struct alignment_parameters*);

void alignment_dp_cell_init(struct alignment_dp_cell*);

int get_parameters(char*, struct alignment_parameters*);

void parse_file_line(char*, struct alignment_parameters*);

#endif