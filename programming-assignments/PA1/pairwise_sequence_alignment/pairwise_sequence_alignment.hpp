#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include <iostream>

using std::mutex;
using std::thread;
using std::string;
using std::vector;

using std::cin;
using std::cout;
using std::endl;

class pairwise_sequence_alignment {
    public:
        static void pairwise_sequence_alignment_affine_gap_penalty(const string&, const double, const double, const double, const double, int);
};