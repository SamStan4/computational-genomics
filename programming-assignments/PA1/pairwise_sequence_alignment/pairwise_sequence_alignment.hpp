#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "./../file_readers/gene_sequence_reader.hpp"

#define USE_MULTIPLE_THREADS_DP false

#include <iostream>

using std::mutex;
using std::thread;
using std::string;
using std::vector;
using std::cerr;
using std::max;

using std::cin;
using std::cout;
using std::endl;

typedef struct dp_cell {
    int s_score;
    int d_score;
    int i_score;
    dp_cell(const int new_s_score = 0, const int new_d_score = 0, const int new_i_score = 0) {
        this->s_score = new_s_score;
        this->d_score = new_d_score;
        this->i_score = new_i_score;
    }
} dp_cell;

typedef struct alignment_statistics {
    int optimal_alignment_score;
    int number_of_matches;
    int number_of_opening_gaps;
    int number_of_gap_extensions;
    string optimal_path[3];
    alignment_statistics() {
        this->optimal_alignment_score = 0;
        this->number_of_matches = 0;
        this->number_of_opening_gaps = 0;
        this->number_of_gap_extensions = 0;
    }
} alignment_statistics;

class pairwise_sequence_alignment {
    private:
        static void initialize_dp_table_for_global_alignment(const string&, const string&, vector<vector<dp_cell>>&, const int, const int);
        static void initialize_dp_table_for_local_alignment(const string&, const string&, vector<vector<dp_cell>>&);

        #if USE_MULTIPLE_THREADS_DP

            static void dynamic_programming_for_global_alignment_thread_routine(void);

            static void dynamic_programming_for_local_alignment_thread_routine(void);

        #endif

        static void run_dynamic_programming_for_global_alignment(const string&, const string&, vector<vector<dp_cell>>&, const int, const int, const int, const int);
        static void run_dynamic_programming_for_local_alignment(const string&, const string&, vector<vector<dp_cell>>&, const int, const int, const int, const int);

        static void pairwise_global_sequence_alignment_affine_gap_penalty(const string&, const string&, const int, const int, const int, const int, alignment_statistics&);
        static void pairwise_local_sequence_alignment_affine_gap_penalty(const string&, const string&, const int, const int, const int, const int, alignment_statistics&);
    public:
        static void pairwise_sequence_alignment_affine_gap_penalty(const string&, const int, const int, const int, const int, const int);
};