#include "./../../include/sequence-alignment/SequenceAlignment.hpp"

bool SequenceAlignment::ValidateFilesExist(const string& sequenceFilePath, const string& parameterFilePath) {
    bool result = true;
    if (!filesystem::exists(sequenceFilePath)) {
        cerr << "unable to locate genetic sequence file path" << endl;
        result = false;
    }
    if (!filesystem::exists(parameterFilePath)) {
        cerr << "unable to locate parameter config file path" << endl;
        result = false;
    }
    return result;
}

bool SequenceAlignment::AlignSequences(AlignmentStats& stats, string& sequenceFilePath, const string& parameterFilePath, const int alignmentFlag) {
    if (!SequenceAlignment::ValidateFilesExist(sequenceFilePath, parameterFilePath)) {
        return false;
    }
    cout << "here nowe" << endl;
    return false;
}