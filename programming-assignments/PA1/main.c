#include "./pairwise_alignment_affine_gap_pennalty.h"

int main(int argc, char** argv) {
    char* file_path = "./parameters.config";
    struct alignment_parameters params;
    alignment_parameters_init(&params);
    get_parameters(file_path, &params);
    return 0;
}