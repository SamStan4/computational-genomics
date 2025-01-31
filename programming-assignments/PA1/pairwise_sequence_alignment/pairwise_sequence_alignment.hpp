#pragma once

#define USE_MULTIPLE_THREADS_DP false

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#if USE_MULTIPLE_THREADS_DP
    #include <thread>
    #include <mutex>
#endif
#include "./../file_readers/gene_sequence_reader.hpp"

#define S_VALUE_KEY 's'
#define D_VALUE_KEY 'd'
#define I_VALUE_KEY 'i'
#define MISMATCH_SYMBOL '1'
#define MATCH_SYMBOL '2'
#define INSERTION_SYMBOL '3'
#define DELETION_SYMBOL '4'

#if USE_MULTIPLE_THREADS_DP
    using std::mutex;
    using std::thread;
#endif
using std::cout;
using std::string;
using std::vector;
using std::cerr;
using std::max;
using std::endl;
using std::ofstream;
using std::numeric_limits;
using std::reverse;
using std::setw;
using std::left;

typedef struct dp_cell {
    int s_score;
    int d_score;
    int i_score;
    dp_cell(const int new_s_score = 0, const int new_d_score = 0, const int new_i_score = 0) {
        this->s_score = new_s_score;
        this->d_score = new_d_score;
        this->i_score = new_i_score;
    }
    char get_max_score(void) {
        if (this->d_score >= this->s_score && this->d_score >= this->i_score) {
            return D_VALUE_KEY;
        } else if (this->s_score >= this->d_score && this->s_score >= this->i_score) {
            return S_VALUE_KEY;
        } else {
            return I_VALUE_KEY;
        }
    }
} dp_cell;

typedef struct alignment_statistics {
    int optimal_alignment_score;
    int number_of_matches;
    int number_of_opening_gaps;
    int number_of_gap_extensions;
    string optimal_path;
    alignment_statistics() {
        this->optimal_alignment_score = 0;
        this->number_of_matches = 0;
        this->number_of_opening_gaps = 0;
        this->number_of_gap_extensions = 0;
    }
    void dump_alignment_to_file(ofstream& file, const string& s1, const string& s2, const int line_size) {
        int s1_consumed = 0, s2_consumed = 0;
        for (int i = 0, j = 0, k = 0; i < this->optimal_path.size(); i += line_size) {
            int m = 0, l = 0;
            file << left << setw(5) << "s1" << setw(10) << j + 1;
            for (l = 0, m = i; m < this->optimal_path.size() && l < line_size; ++l, ++m) {
                switch (this->optimal_path[m]) {
                    case MISMATCH_SYMBOL:
                    case MATCH_SYMBOL:
                    case DELETION_SYMBOL:
                        file << s1[j++];
                    break;
                    case INSERTION_SYMBOL:
                        file << "-";
                    break;
                }
            }
            file << left << setw(3) << "" << j << endl << setw(15) << "";
            for (l = 0, m = i; m < this->optimal_path.size() && l < line_size; ++l, ++m) {
                switch (this->optimal_path[m]) {
                    case MATCH_SYMBOL:
                        file << "|";
                    break;
                    case MISMATCH_SYMBOL:
                    case DELETION_SYMBOL:
                    case INSERTION_SYMBOL:
                        file << " ";
                    break;
                }
            }
            file << endl << left << setw(5) << "s2" << setw(10) << k + 1;
            for (l = 0, m = i; m < this->optimal_path.size() && l < line_size; ++l, ++m) {
                switch (this->optimal_path[m]) {
                    case MISMATCH_SYMBOL:
                    case MATCH_SYMBOL:
                    case INSERTION_SYMBOL:
                        file << s2[k++];
                    break;
                    case DELETION_SYMBOL:
                        file << "-";
                    break;
                }
            }
            file << left << setw(3) << "" << k << endl << endl;
        }
    }
} alignment_statistics;

class pairwise_sequence_alignment {
    private:
        static void initialize_dp_table_for_global_alignment(const string&, const string&, vector<vector<dp_cell>>&, const int, const int);
        static void initialize_dp_table_for_local_alignment(const string&, const string&, vector<vector<dp_cell>>&);

        static void dump_dp_table(const string&, const vector<vector<dp_cell>>&);

        #if USE_MULTIPLE_THREADS_DP

            static void dynamic_programming_for_global_alignment_thread_routine(void);

            static void dynamic_programming_for_local_alignment_thread_routine(void);

        #endif

        static void path_retrace_for_global_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, alignment_statistics& statistics);
        static void path_retrace_for_local_alignment(const string& s1, const string& s2, vector<vector<dp_cell>>& dp_table, alignment_statistics& statistics);

        static void run_dynamic_programming_for_global_alignment(const string&, const string&, vector<vector<dp_cell>>&, const int, const int, const int, const int);
        static void run_dynamic_programming_for_local_alignment(const string&, const string&, vector<vector<dp_cell>>&, const int, const int, const int, const int);

        static void pairwise_global_sequence_alignment_affine_gap_penalty(const string&, const string&, const int, const int, const int, const int, alignment_statistics&);
        static void pairwise_local_sequence_alignment_affine_gap_penalty(const string&, const string&, const int, const int, const int, const int, alignment_statistics&);
    public:
        static void pairwise_sequence_alignment_affine_gap_penalty(const string&, const int, const int, const int, const int, const int);
};