#include "./pairwise_sequence_alignment.hpp"

void pairwise_sequence_alignment::pairwise_global_sequence_alignment_affine_gap_penalty(const string& s1, const string& s2, const double m_a, const double m_i, const double h, const double g, alignment_statistics& stats) {
    cout << "inside global alignment function" << endl;
}

void pairwise_sequence_alignment::pairwise_local_sequence_alignment_affine_gap_penalty(const string& s1, const string& s2, const double m_a, const double m_i, const double h, const double g, alignment_statistics& stats) {
    cout << "inside local alignment function" << endl;
}

void pairwise_sequence_alignment::pairwise_sequence_alignment_affine_gap_penalty(const string& fasta_file_path, const double m_a, const double m_i, const double h, const double g, int alignment_flag) {
    string s1, s2;
    gene_sequence_reader::read_gene_sequences(fasta_file_path, s1, s2);
    alignment_statistics statistics;
    if (alignment_flag == 0) {
        pairwise_sequence_alignment::pairwise_global_sequence_alignment_affine_gap_penalty(s1, s2, m_a, m_i, h, g, statistics);
    } else if (alignment_flag == 1) {
        pairwise_sequence_alignment::pairwise_local_sequence_alignment_affine_gap_penalty(s1, s2, m_a, m_i, h, g, statistics);
    } else {
        cerr << "invalid alignment selection" << endl;
        return;
    }
}
