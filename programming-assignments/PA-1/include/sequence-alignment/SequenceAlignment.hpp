#ifndef SEQUENCEALIGNMENT_HPP
#define SEQUENCEALIGNMENT_HPP

#include "./../imports.hpp"
#include "./AlignmentStats.hpp"
#include "./AlignmentParameters.hpp"
#include "./DpCell.hpp"

class SequenceAlignment {
private:
    static bool ValidateFilesExist(const string& sequenceFilePath, const string& parameterFilePath);
    static bool LoadGeneticSequences(const string& sequenceFilePath, string& s1, string& s2, string& s1Name, string& s2Name);
    static bool LoadAlignmentParameters(const string& alignmentParameterPath, AlignmentParameters& params);
    static void AllocateAndInitializeDpTable(const AlignmentStats& stats, const AlignmentParameters& params, vector<vector<DpCell>>& dpTable);
    static void InitializeDpTableGlobal(const AlignmentParameters& params, vector<vector<DpCell>>& dpTable);
    static void InitializeDpTableLocal(vector<vector<DpCell>>& dpTable);
public:
    static bool AlignSequences(AlignmentStats& stats, string& sequenceFilePath, const string& parameterFilePath, const int32_t alignmentFlag);
};

#endif