#include "./../../include/wrapper/AppWrapper.hpp"
#include "./../../include/sequence-alignment/SequenceAlignment.hpp"
#include "./../../include/sequence-alignment/AlignmentStats.hpp"

AppWrapper::AppWrapper() {}

bool AppWrapper::ParseArgs(const int argumentCount, const char* const* argumentVector, string& sequenceFilePath, string& parameterConfigFilePath, int& alignmentFlag) {
    try {
        if (argumentCount != 4) {
            return false;
        }
        sequenceFilePath = argumentVector[1];
        parameterConfigFilePath = argumentVector[3];
        alignmentFlag = stoi(argumentVector[2]);
        return alignmentFlag == 0 || alignmentFlag == 1;
    } catch (...) {
        return false;
    }
}

AppWrapper& AppWrapper::GetInstance() {
    static AppWrapper instance;
    return instance;
}

void AppWrapper::Run(const int argumentCount, const char* const* argumentVector) {
    string sequenceFilePath = "";
    string parameterConfigFilePath = "";
    int alignmentFlag = 0;
    if (!this->ParseArgs(argumentCount, argumentVector, sequenceFilePath, parameterConfigFilePath, alignmentFlag)) {
        cerr << "Error parsing command line args, aborting" << endl;
        return;
    }
    AlignmentStats stats;
    if (!SequenceAlignment::AlignSequences(stats, sequenceFilePath, parameterConfigFilePath, alignmentFlag)) {
        return;
    }
}