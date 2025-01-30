#ifndef PAIRWISE_ALIGNMENT_AFFINE_GAP_PENNALTY
#define PAIRWISE_ALIGNMENT_AFFINE_GAP_PENNALTY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_CHUNK_SIZE 256

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

void match_key_to_value(char*, char*, struct alignment_parameters*);

char* read_genetic_sequence(FILE*);

int load_genetic_sequences(const char*, char**, char**);

#endif