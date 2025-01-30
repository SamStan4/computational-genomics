#include "./pairwise_alignment_affine_gap_pennalty.h"

int main(int argc, char** argv) {
    char *s1 = NULL, *s2 = NULL;
    load_genetic_sequences("sample_inputs/long_lines.fasta", &s1, &s2);
    printf("s1: %s\n\n", s1);
    printf("s2: %s\n\n", s2);
    return 0;
}