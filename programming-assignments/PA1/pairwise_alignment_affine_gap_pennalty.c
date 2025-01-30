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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//  /$$$$$$$                                                        /$$                               /$$                                 /$$ /$$                    
// | $$__  $$                                                      | $$                              | $$                                | $$|__/                    
// | $$  \ $$ /$$$$$$   /$$$$$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$       | $$        /$$$$$$   /$$$$$$   /$$$$$$$ /$$ /$$$$$$$   /$$$$$$ 
// | $$$$$$$/|____  $$ /$$__  $$|____  $$| $$_  $$_  $$ /$$__  $$|_  $$_/   /$$__  $$ /$$__  $$      | $$       /$$__  $$ |____  $$ /$$__  $$| $$| $$__  $$ /$$__  $$
// | $$____/  /$$$$$$$| $$  \__/ /$$$$$$$| $$ \ $$ \ $$| $$$$$$$$  | $$    | $$$$$$$$| $$  \__/      | $$      | $$  \ $$  /$$$$$$$| $$  | $$| $$| $$  \ $$| $$  \ $$
// | $$      /$$__  $$| $$      /$$__  $$| $$ | $$ | $$| $$_____/  | $$ /$$| $$_____/| $$            | $$      | $$  | $$ /$$__  $$| $$  | $$| $$| $$  | $$| $$  | $$
// | $$     |  $$$$$$$| $$     |  $$$$$$$| $$ | $$ | $$|  $$$$$$$  |  $$$$/|  $$$$$$$| $$            | $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$| $$  | $$|  $$$$$$$
// |__/      \_______/|__/      \_______/|__/ |__/ |__/ \_______/   \___/   \_______/|__/            |________/ \______/  \_______/ \_______/|__/|__/  |__/ \____  $$
//                                                                                                                                                          /$$  \ $$
//                                                                                                                                                         |  $$$$$$/
//                                                                                                                                                          \______/ 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//

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
    char buffer[BUFFER_CHUNK_SIZE] = { '\0' };
    while (fgets(buffer, BUFFER_CHUNK_SIZE, file_pointer) != NULL) {
        parse_file_line(buffer, parameters);
        memset(buffer, '\0', BUFFER_CHUNK_SIZE);
    }
    fclose(file_pointer);
    return 1;
}

/**
 * Parses an individual line in the file, populates the
 * appropreate field inside the parameter structure
 * lines appear in the form "key value" inside of the file
 */
void parse_file_line(char* buffer, struct alignment_parameters* parameters) {
    char key_string[BUFFER_CHUNK_SIZE] = { '\0' },
       value_string[BUFFER_CHUNK_SIZE] = { '\0' };
    int i = 0;
    for (int j = 0; i < BUFFER_CHUNK_SIZE && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0'; ++i, ++j) {
        key_string[j] = buffer[i];
    }
    while (i < BUFFER_CHUNK_SIZE && buffer[i] == ' ') {
        ++i;
    }
    for (int j = 0; i < BUFFER_CHUNK_SIZE && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0'; ++i, ++j) {
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//   /$$$$$$                                                                              /$$                                 /$$ /$$                    
//  /$$__  $$                                                                            | $$                                | $$|__/                    
// | $$  \__/  /$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$$   /$$$$$$$  /$$$$$$       | $$        /$$$$$$   /$$$$$$   /$$$$$$$ /$$ /$$$$$$$   /$$$$$$ 
// |  $$$$$$  /$$__  $$ /$$__  $$| $$  | $$ /$$__  $$| $$__  $$ /$$_____/ /$$__  $$      | $$       /$$__  $$ |____  $$ /$$__  $$| $$| $$__  $$ /$$__  $$
//  \____  $$| $$$$$$$$| $$  \ $$| $$  | $$| $$$$$$$$| $$  \ $$| $$      | $$$$$$$$      | $$      | $$  \ $$  /$$$$$$$| $$  | $$| $$| $$  \ $$| $$  \ $$
//  /$$  \ $$| $$_____/| $$  | $$| $$  | $$| $$_____/| $$  | $$| $$      | $$_____/      | $$      | $$  | $$ /$$__  $$| $$  | $$| $$| $$  | $$| $$  | $$
// |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$|  $$$$$$$      | $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$| $$  | $$|  $$$$$$$
//  \______/  \_______/ \____  $$ \______/  \_______/|__/  |__/ \_______/ \_______/      |________/ \______/  \_______/ \_______/|__/|__/  |__/ \____  $$
//                           | $$                                                                                                               /$$  \ $$
//                           | $$                                                                                                              |  $$$$$$/
//                           |__/                                                                                                               \______/ 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//

/*
 * Reads a genetic sequence from a FASTA file
 * returns:
 *      NULL --> Memory allocation failure or EOF before sequence
 *      Pointer to sequence (char*) otherwise
 */
char* read_genetic_sequence(FILE* file_pointer) {
    char* sequence = (char*) malloc(BUFFER_CHUNK_SIZE);
    if (sequence == NULL) {
        return NULL;
    }

    size_t sequence_length = 0, sequence_capacity = BUFFER_CHUNK_SIZE;
    char read_buffer[BUFFER_CHUNK_SIZE];

    while (fgets(read_buffer, sizeof(read_buffer), file_pointer)) {
        if (read_buffer[0] == '>') {
            fseek(file_pointer, -strlen(read_buffer), SEEK_CUR);
            break;
        }

        size_t read_line_length = strcspn(read_buffer, "\r\n");
        if (sequence_length + read_line_length >= sequence_capacity) {
            sequence_capacity *= 2;
            char* temp = realloc(sequence, sequence_capacity);
            if (temp == NULL) {
                free(sequence);
                return NULL;
            }
            sequence = temp;
        }

        memcpy(sequence + sequence_length, read_buffer, read_line_length);
        sequence_length += read_line_length;
    }

    sequence[sequence_length] = '\0';
    return sequence;
}

/*
 * Loads two genetic sequences from a FASTA file
 * returns:
 *      0 --> Error reading the file
 *      1 --> Successfully loaded two sequences
 */
int load_genetic_sequences(const char* file_path, char** s1_ptr, char** s2_ptr) {
    FILE* file_pointer = fopen(file_path, "r");
    if (!file_pointer) return 0;

    char read_buffer[BUFFER_CHUNK_SIZE];

    while (fgets(read_buffer, sizeof(read_buffer), file_pointer)) {
        if (read_buffer[0] == '>') break;
    }

    *s1_ptr = read_genetic_sequence(file_pointer);
    if (!*s1_ptr) {
        fclose(file_pointer);
        return 0;
    }

    while (fgets(read_buffer, sizeof(read_buffer), file_pointer)) {
        if (read_buffer[0] == '>') break;
    }

    *s2_ptr = read_genetic_sequence(file_pointer);
    if (!*s2_ptr) {
        free(*s1_ptr);
        fclose(file_pointer);
        return 0;
    }

    fclose(file_pointer);
    return 1;
}