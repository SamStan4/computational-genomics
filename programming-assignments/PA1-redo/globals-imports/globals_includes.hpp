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
#include <memory>
#include <filesystem>
#include <unordered_map>
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

// Terminal colors
#define RESET        "\033[0m"
#define BLACK        "\033[30m"
#define RED          "\033[31m"
#define GREEN        "\033[32m"
#define YELLOW       "\033[33m"
#define BLUE         "\033[34m"
#define MAGENTA      "\033[35m"
#define CYAN         "\033[36m"
#define WHITE        "\033[37m"

// Format for output file
#define OUTPUT_WIDTH_FORMAT  60

// Cause I dont want to type out the individual using statements
using namespace std;