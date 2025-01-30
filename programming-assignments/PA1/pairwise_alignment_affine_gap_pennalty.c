#include "./pairwise_alignment_affine_gap_pennalty.h"

/**
 * Initializer for alignemnt parameter structure
 */
void alignment_parameters_init(struct alignment_parameters* parameter) {
    parameter->match_constant = 0;
    parameter->mismatch_constant = 0;
    parameter->g_constant = 0;
    parameter->h_constant = 0;
}

/**
 * Initializer for the alignment dp cell structure
 */
void alignment_dp_cell_init(struct alignment_dp_cell* cell) {
    cell->d = 0;
    cell->i = 0;
    cell->s = 0;
}

/*
 * Gets the parameters from the file path
 * returns:
 *      0 --> Could not read from file
 *      1 --> Got input from the file
 */
int get_parameters(char* file_path, struct alignment_parameters* parameters) {
    FILE* file_pointer = fopen(file_path, "r");
    if (file_pointer == NULL) {
        return 0;
    }
    char buffer[FILE_READ_BUFFER_SIZE_BYTES] = { '\0' };
    while (fgets(buffer, FILE_READ_BUFFER_SIZE_BYTES, file_pointer) != NULL) {
        parse_file_line(buffer, parameters);
        memset(buffer, '\0', FILE_READ_BUFFER_SIZE_BYTES);
    }
    return 1;
}

/**
 * Parses an individual line in the file, populates the
 * appropreate field inside the parameter structure
 */
void parse_file_line(char* buffer, struct alignment_parameters* parameters) {
    
}