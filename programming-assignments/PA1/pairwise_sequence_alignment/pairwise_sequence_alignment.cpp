#include "./pairwise_sequence_alignment.hpp"

void pairwise_sequence_alignment::pairwise_sequence_alignment_affine_gap_penalty(const string& fasta_file_path, const double m_a, const double m_i, const double h, const double g, int alignment_flag) {
    string s1, s2;
    gene_sequence_reader::read_gene_sequences(fasta_file_path, s1, s2);
    cout <<
        "s1: " << s1 << endl <<
        "s2: " << s2 << endl <<
        "m_a: " << m_a << endl <<
        "m_i: " << m_i << endl <<
        "h: " << h << endl <<
        "g: " << g << endl << endl;
}
