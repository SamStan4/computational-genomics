#ifndef SEQUENCEALIGNMENT_HPP
#define SEQUENCEALIGNMENT_HPP

#include "./../imports.hpp"
#include "./AlignmentStats.hpp"

class SequenceAlignment {
private:
    static bool ValidateFilesExist(const string& sequenceFilePath, const string& parameterFilePath);
public:
    static bool AlignSequences(AlignmentStats& stats, string& sequenceFilePath, const string& parameterFilePath, const int alignmentFlag);
};

#endif