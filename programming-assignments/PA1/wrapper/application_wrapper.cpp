#include "./application_wrapper.hpp"

bool application_wrapper::parse_out_argument_vector(int argument_count, char** argument_vector, string& sequence_file_path, int& alignment_flag, string& parameter_config_file_path) {
    if (argument_count != 4) {
        return false;
    }
    sequence_file_path = argument_vector[1];
    alignment_flag = stod(argument_vector[2]);
    parameter_config_file_path = argument_vector[3];
    return  true;
}
    
void application_wrapper::run_application(int argument_count, char** argument_vector) {
    string sequence_file_path, parameter_config_file_path;
    int alignment_flag;
    if (!application_wrapper::parse_out_argument_vector(argument_count, argument_vector, sequence_file_path, alignment_flag, parameter_config_file_path)) {
        cerr << "Error parsing command line arguments" << endl;
        return;
    }
    double match_score = 0, mismatch_score = 0, gap_opening_penalty = 0, gap_extension_penalty = 0;
    alignment_parameters_reader::read_alignment_parameters(parameter_config_file_path, match_score, mismatch_score, gap_opening_penalty, gap_extension_penalty);
    pairwise_sequence_alignment::pairwise_sequence_alignment_affine_gap_penalty(sequence_file_path, match_score, mismatch_score, gap_opening_penalty, gap_extension_penalty, alignment_flag);
}