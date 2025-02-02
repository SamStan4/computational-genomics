#pragma once

// For when I want to set the program to use multiple threads
#define MULTI_THREAD        false

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#if MULTI_THREAD
    #include <thread>
    #include <mutex>
#endif

// Symbols that I am going to be working with
#define S_VALUE_KEY         's'
#define D_VALUE_KEY         'd'
#define I_VALUE_KEY         'i'
#define MISMATCH_SYMBOL     '1'
#define MATCH_SYMBOL        '2'
#define INSERTION_SYMBOL    '3'
#define DELETION_SYMBOL     '4'

// Format for output file
#define OUTPUT_WIDTH_FORMAT  60

// Cause I dont want to type out the individual using statements
using namespace std;