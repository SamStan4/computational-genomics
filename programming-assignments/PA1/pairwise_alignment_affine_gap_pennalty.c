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
 * lines appear in the form "key value" inside of the file
 */
void parse_file_line(char* buffer, struct alignment_parameters* parameters) {
    char key_string[FILE_READ_BUFFER_SIZE_BYTES] = { '\0' },
       value_string[FILE_READ_BUFFER_SIZE_BYTES] = { '\0' };
    int i = 0;
    for (int j = 0; i < FILE_READ_BUFFER_SIZE_BYTES && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0'; ++i, ++j) {
        key_string[j] = buffer[i];
    }
    while (i < FILE_READ_BUFFER_SIZE_BYTES && buffer[i] == ' ') {
        ++i;
    }
    for (int j = 0; i < FILE_READ_BUFFER_SIZE_BYTES && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0'; ++i, ++j) {
        value_string[j] = buffer[i];
    }
    match_key_to_value(key_string, value_string, parameters);
}

/**
 * Finds the appropreate field to match to and then sets it
 */
void match_key_to_value(char* key_string, char* value_string, struct alignment_parameters* parameters) {
    static const char* match_constant_key_name = "match";
    static const char* mismatch_constant_key_name = "mismatch";
    static const char* h_constant_key_name = "h";
    static const char* g_constant_key_name = "g";
    if (strcmp(key_string, match_constant_key_name) == 0) {
        parameters->match_constant = strtod(value_string, NULL);
    } else if (strcmp(key_string, mismatch_constant_key_name) == 0) {
        parameters->mismatch_constant = strtod(value_string, NULL);
    } else if (strcmp(key_string, h_constant_key_name) == 0) {
        parameters->h_constant = strtod(value_string, NULL);
    } else if (strcmp(key_string, g_constant_key_name) == 0) {
        parameters->g_constant = strtod(value_string, NULL);
    }
}