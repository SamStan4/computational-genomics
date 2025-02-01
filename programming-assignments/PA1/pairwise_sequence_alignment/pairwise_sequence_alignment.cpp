#include "./pairwise_sequence_alignment.hpp"

void pairwise_sequence_alignment::initialize_dp_table_for_global_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, const int h, const int g) {
    static const int negative_infinity = numeric_limits<int>::min();
    dp_table = vector<vector<dp_cell>>(s1.size() + 1, vector<dp_cell>(s2.size() + 1));
    // Initialize T(0, 0)
    dp_table[0][0].d_score = 0;
    dp_table[0][0].i_score = 0;
    dp_table[0][0].s_score = 0;
    // For all i in { 1 .. m } set T(i, 0) to appropreate value
    for (int i = 1; i < dp_table.size(); ++i) {
        dp_table[i][0].s_score = negative_infinity;
        dp_table[i][0].d_score = h + (i * g);
        dp_table[i][0].i_score = negative_infinity;
    }
    // For all j in { 1 .. n } set T(0, j) to appropreate value
    for (int j = 1; j < dp_table[0].size(); ++j) {
        dp_table[0][j].s_score = negative_infinity;
        dp_table[0][j].d_score = negative_infinity;
        dp_table[0][j].i_score = h + (j * g);
    }
}

void pairwise_sequence_alignment::initialize_dp_table_for_local_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table) {
    dp_table = vector<vector<dp_cell>>(s1.size() + 1, vector<dp_cell>(s2.size() + 1));
    // Initialize first row and column to be zeros
    for (int i = 0; i < dp_table.size(); ++i) {
        dp_table[i][0].s_score = 0;
        dp_table[i][0].d_score = 0;
        dp_table[i][0].i_score = 0;
    }
    for (int j = 1; j < dp_table[0].size(); ++j) {
        dp_table[0][j].s_score = 0;
        dp_table[0][j].d_score = 0;
        dp_table[0][j].i_score = 0;
    }
}

void pairwise_sequence_alignment::dump_dp_table(const string& file_path, const vector<vector<dp_cell>>& dp_table) {
    ofstream file(file_path);
    if (!file.is_open()) {
        cerr << "unable to open file: " << file_path << endl;
    }
    cout << "dumping file to: " << file_path << endl;
    const int n = dp_table.size(), m = dp_table[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            file << "(s: " << dp_table[i][j].s_score << ", d: " << dp_table[i][j].d_score << ", i: " << dp_table[i][j].i_score << "),";
        }
        file << endl;
    }
}

void pairwise_sequence_alignment::path_retrace_for_global_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, alignment_statistics& statistics) {
    statistics.optimal_path.clear();
    int i = dp_table.size() - 1, j = dp_table[0].size() - 1;
    while (i > 0 && j > 0) {
        switch (dp_table[i][j].get_max_score()) {
            case S_VALUE_KEY: // We are going to either have a match or a mismatch
                if (s1[i-1] == s2[j-1]) { // this is a match
                    statistics.optimal_path.push_back(MATCH_SYMBOL);
                } else { // this is a mismatch
                    statistics.optimal_path.push_back(MISMATCH_SYMBOL);
                }
                --i;
                --j;
            break;
            case D_VALUE_KEY: // This is a deletion
                statistics.optimal_path.push_back(DELETION_SYMBOL);
                --i;
            break;
            case I_VALUE_KEY: // This is an insertion
                statistics.optimal_path.push_back(INSERTION_SYMBOL);
                --j;
            break;
        }
    }
    while (i > 0) {
        statistics.optimal_path.push_back(DELETION_SYMBOL);
        --i;
    }
    while (j > 0) {
        statistics.optimal_path.push_back(INSERTION_SYMBOL);
        --j;
    }
    reverse(statistics.optimal_path.begin(), statistics.optimal_path.end());
}

void pairwise_sequence_alignment::path_retrace_for_local_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, alignment_statistics& statistics) {
}

#if USE_MULTIPLE_THREADS_DP
// Implementation using multiple threads

    void pairwise_sequence_alignment::dynamic_programming_for_global_alignment_thread_routine(void) {

    }

    void pairwise_sequence_alignment::dynamic_programming_for_local_alignment_thread_routine(void) {

    }


    void pairwise_sequence_alignment::run_dynamic_programming_for_global_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, const int m_a, const int m_i, const int h, const int g) {

    }

    void pairwise_sequence_alignment::run_dynamic_programming_for_local_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table,  const int m_a, const int m_i, const int h, const int g) {
        
    }

#else
// Single thread implementation

    void pairwise_sequence_alignment::run_dynamic_programming_for_global_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, const int m_a, const int m_i, const int h, const int g) {
    static const long long negative_infinity = numeric_limits<int>::min();
        const int n = dp_table.size(), m = dp_table[0].size();
        const signed long long m_a_sll = (signed long long)m_a, m_i_sll = (signed long long)m_i, h_sll = (signed long long)h, g_sll = (signed long long)g;
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                // Handle s_score
                dp_table[i][j].s_score = (int)max(negative_infinity, max((signed long long)max(dp_table[i-1][j-1].s_score, dp_table[i-1][j-1].d_score), (signed long long)dp_table[i-1][j-1].i_score) + (s1[i-1] == s2[j-1] ? m_a_sll : m_i_sll));
                // Handle d_score
                dp_table[i][j].d_score = (int)max(negative_infinity, max((signed long long)max(dp_table[i-1][j].i_score, dp_table[i-1][j].s_score) + h_sll + g_sll, (signed long long)dp_table[i-1][j].d_score + g_sll));
                // Handle i_score
                dp_table[i][j].i_score = (int)max(negative_infinity, max((signed long long)max(dp_table[i][j-1].s_score, dp_table[i][j-1].d_score) + h_sll + g_sll, (signed long long)dp_table[i][j-1].i_score + g_sll));
            }
        }
        pairwise_sequence_alignment::dump_dp_table("./output.csv", dp_table);
    }

    void pairwise_sequence_alignment::run_dynamic_programming_for_local_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, const int m_a, const int m_i, const int h, const int g) {
        const int n = dp_table.size(), m = dp_table[0].size();
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                // Handle s_score
                dp_table[i][j].s_score = max(max(max(dp_table[i-1][j-1].s_score, dp_table[i-1][j-1].d_score), dp_table[i-1][j-1].i_score) + (s1[i-1] == s2[j-1] ? m_a : m_i), 0);
                // Handle d_score
                dp_table[i][j].d_score = max(max(max(dp_table[i-1][j].i_score, dp_table[i-1][j].s_score) + h + g, dp_table[i-1][j].d_score + g), 0);
                // Handle i_score
                dp_table[i][j].i_score = max(max(max(dp_table[i][j-1].s_score, dp_table[i][j-1].d_score) + h + g, dp_table[i][j-1].i_score + g), 0);
            }
        }
    }

#endif

void pairwise_sequence_alignment::pairwise_global_sequence_alignment_affine_gap_penalty(const string& s1, const string& s2, const int m_a, const int m_i, const int h, const int g, alignment_statistics& stats) {
    vector<vector<dp_cell>> dp_table;
    pairwise_sequence_alignment::initialize_dp_table_for_global_alignment(s1, s2, dp_table, h, g);
    pairwise_sequence_alignment::run_dynamic_programming_for_global_alignment(s1, s2, dp_table, m_a, m_i, h, g);
    pairwise_sequence_alignment::path_retrace_for_global_alignment(s1, s2, dp_table, stats);
    ofstream file("./sample_output.txt");
    stats.dump_alignment_visual_to_file(file, s1, s2, 60);
}

void pairwise_sequence_alignment::pairwise_local_sequence_alignment_affine_gap_penalty(const string& s1, const string& s2, const int m_a, const int m_i, const int h, const int g, alignment_statistics& stats) {
    vector<vector<dp_cell>> dp_table;
    pairwise_sequence_alignment::initialize_dp_table_for_local_alignment(s1, s2, dp_table);
    pairwise_sequence_alignment::run_dynamic_programming_for_local_alignment(s1, s2, dp_table, m_a, m_i, h, g);
}

void pairwise_sequence_alignment::pairwise_sequence_alignment_affine_gap_penalty(const string& fasta_file_path, const int m_a, const int m_i, const int h, const int g, const int alignment_flag) {
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