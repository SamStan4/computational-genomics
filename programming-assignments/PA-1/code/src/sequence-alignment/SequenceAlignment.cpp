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

bool SequenceAlignment::LoadGeneticSequences(const string& sequenceFilePath, string& s1, string& s2, string& s1Name, string& s2Name) {
    ifstream fileStream(sequenceFilePath);
    if (!fileStream.is_open()) {
        cerr << "Error opening " << sequenceFilePath << endl;
        return false;
    }
    string readBuffer, * curSequence = nullptr;
    while (getline(fileStream, readBuffer)) {
        if (readBuffer.empty())
            continue;
        if (readBuffer[0] == '>') {
            if (curSequence == nullptr) {
                s1Name = readBuffer.substr(1);
                curSequence = &s1;
            } else {
                s2Name = readBuffer.substr(1);
                curSequence = & s2;
            }
        } else if (curSequence)
            *curSequence += readBuffer;
    }
    return true;
}

bool SequenceAlignment::LoadAlignmentParameters(const string& alignmentParameterPath, AlignmentParameters& params) {
    ifstream fileStream(alignmentParameterPath);
    if (!fileStream.is_open()) {
        cerr << "Error opening " << alignmentParameterPath << endl;
        return false;
    }
    unordered_map<string, int32_t> hashMap = {
        {"match", 0},
        {"mismatch", 0},
        {"g", 0},
        {"h", 0}  
    };
    string readBuffer;
    int8_t numRead = 0;
    while (getline(fileStream, readBuffer)) {
        if (readBuffer.empty())
            continue;
        stringstream readStream(readBuffer);
        string key;
        string value;
        readStream >> key >> value;
        if (hashMap.find(key) != hashMap.end()) {
            try {
                hashMap[key] = (int32_t)stoi(value);
                ++numRead;
            } catch (...) {
                cerr << "Error while parsing" << alignmentParameterPath << endl;
                return false;
            }
        }
    }
    params.SetMatchScore(hashMap["match"]);
    params.SetMismatchScore(hashMap["mismatch"]);
    params.SetGapExtensionScore(hashMap["g"]);
    params.SetOpeningGapScore(hashMap["h"]);
    return numRead == 4;
}

void SequenceAlignment::AllocateAndInitializeDpTable(const AlignmentStats& stats, const AlignmentParameters& params, vector<vector<DpCell>>& dpTable) {
    const size_t s1Size = stats.GetS1ConstRef().size();
    const size_t s2Size = stats.GetS2ConstRef().size();
    dpTable.assign(s1Size + 1, vector<DpCell>(s2Size + 1));
    if (stats.GetAlignmentFlag() == 0)
        SequenceAlignment::InitializeDpTableGlobal(params, dpTable);
    else
        SequenceAlignment::InitializeDpTableLocal(dpTable);
}

void SequenceAlignment::InitializeDpTableGlobal(const AlignmentParameters& params, vector<vector<DpCell>>& dpTable) {
    static const int32_t negativeInfinity = numeric_limits<int32_t>::min();
    const size_t rowSize = dpTable.size();
    if (rowSize == 0) return;
    const size_t colSize = dpTable[0].size();
    if (colSize == 0) return;
    const int32_t openingGapScore = params.GetOpeningGapScore();
    const int32_t gapExtensionScore = params.GetGapExtensionScore();
    dpTable[0][0].dScore = 0;
    dpTable[0][0].iScore = 0;
    dpTable[0][0].sScore = 0;
    for (size_t i = 1; i < rowSize; ++i) {
        dpTable[i][0].dScore = openingGapScore + (i * gapExtensionScore);
        dpTable[i][0].sScore = negativeInfinity;
        dpTable[i][0].iScore = negativeInfinity;
    }
    for (size_t j = 1; j < colSize; ++j) {
        dpTable[0][j].dScore = negativeInfinity;
        dpTable[0][j].sScore = negativeInfinity;
        dpTable[0][j].iScore = openingGapScore + (j * gapExtensionScore);
    }
}

void SequenceAlignment::InitializeDpTableLocal(vector<vector<DpCell>>& dpTable) {
    const size_t rowSize = dpTable.size();
    const size_t colSize = dpTable[0].size();
    for (size_t i = 0; i < rowSize; ++i) {
        dpTable[i][0].dScore = 0;
        dpTable[i][0].sScore = 0;
        dpTable[i][0].iScore = 0;
    }
    for (size_t j = 1; j < colSize; ++j) {
        dpTable[0][j].dScore = 0;
        dpTable[0][j].sScore = 0;
        dpTable[0][j].iScore = 0;
    }
}

void SequenceAlignment::ExecuteAlignmentDp(const AlignmentStats& stats, const AlignmentParameters& params, vector<vector<DpCell>>& dpTable) {
    const int64_t minVal = stats.GetAlignmentFlag() == 0 ? (int32_t)numeric_limits<int32_t>::min() : 0;
    const int64_t m_a = (int64_t)params.GetMatchScore();
    const int64_t m_i = (int64_t)params.GetMismatchScore();
    const int64_t h = (int64_t)params.GetOpeningGapScore();
    const int64_t g = (int64_t)params.GetGapExtensionScore();
    const size_t rowSize = dpTable.size();
    const size_t colSize = dpTable[0].size();
    const string& s1 = stats.GetS1ConstRef();
    const string& s2 = stats.GetS2ConstRef();
    for (size_t i = 1; i < rowSize; ++i) {
        for (size_t j = 1; j < colSize; ++j) {
            dpTable[i][j].dScore = (int32_t)max(minVal, max((int64_t)max(dpTable[i-1][j].iScore, dpTable[i-1][j].sScore) + h + g, (int64_t)dpTable[i-1][j].dScore + g));
            dpTable[i][j].sScore = (int32_t)max(minVal, (int64_t)max(max(dpTable[i-1][j-1].sScore, dpTable[i-1][j-1].dScore), dpTable[i-1][j-1].iScore) + (s1[i-1] == s2[j-1] ? m_a : m_i));
            dpTable[i][j].iScore = (int32_t)max(minVal, max((int64_t)max(dpTable[i][j-1].dScore, dpTable[i][j-1].sScore) + h + g, (int64_t)dpTable[i][j-1].iScore + g));
        }
    }
}

void SequenceAlignment::DumpDpTableToFile(const char* filePath, vector<vector<DpCell>>& dpTable) {
    ofstream fileStream(filePath);
    if (!fileStream.is_open()) return;
    const size_t rowSize = dpTable.size();
    if (rowSize == 0) {
        fileStream.close();
        return;
    }
    const size_t colSize = dpTable[0].size();
    for (size_t i = 0; i < rowSize; ++i) {
        for (size_t j = 0; j < colSize; ++j) {
            fileStream << "(" << dpTable[i][j].sScore << ", " << dpTable[i][j].dScore << ", " << dpTable[i][j].iScore << ") ";
        }
        fileStream << endl;
    }
    fileStream.close();
}

void SequenceAlignment::PathRetrace(AlignmentStats& stats, const vector<vector<DpCell>>& dpTable) {
    if (stats.GetAlignmentFlag() == 0)
        SequenceAlignment::GlobalPathRetrace(stats, dpTable);
    else
        SequenceAlignment::LocalPathRetrace(stats, dpTable);
}

void SequenceAlignment::GlobalPathRetrace(AlignmentStats& stats, const vector<vector<DpCell>>& dpTable) {
    const size_t rowSize = dpTable.size();
    if (rowSize == 0) return;
    const size_t colSize = dpTable[0].size();
    size_t i = rowSize - 1;
    size_t j = colSize - 1;
    const string& s1 = stats.GetS1ConstRef();
    const string& s2 = stats.GetS2ConstRef();
    string& pathRetrace = stats.GetAlignmentPathRef();
    while (i > 0 && j > 0) {
        switch (dpTable[i][j].GetMaxScoreKey()) {
            case S_VALUE_KEY:
                if (s1[i-1] == s2[j-1])
                    pathRetrace.push_back(MATCH_SYMBOL);
                else
                    pathRetrace.push_back(MISMATCH_SYMBOL);
                --i;
                --j;
            break;
            case D_VALUE_KEY:
                pathRetrace.push_back(DELETION_SYMBOL);
                --i;
            break;
            case I_VALUE_KEY:
                pathRetrace.push_back(INSERTION_SYMBOL);
                --j;
            break;
        }
    }
    while (i > 0) {
        pathRetrace.push_back(DELETION_SYMBOL);
        --i;
    }
    while (j > 0) {
        pathRetrace.push_back(INSERTION_SYMBOL);
        --j;
    }
    reverse(pathRetrace.begin(), pathRetrace.end());
    stats.SetS1Start(0);
    stats.SetS2Start(0);
    stats.SetS1End(s1.size() - 1);
    stats.SetS2End(s2.size() - 1);
    stats.CalculateStats();
    stats.SetAlignmentScore(dpTable.back().back().GetMaxScore());
}

void SequenceAlignment::LocalPathRetrace(AlignmentStats& stats, const vector<vector<DpCell>>& dpTable) {
    const size_t rowSize = dpTable.size();
    if (rowSize == 0) return;
    const size_t colSize = dpTable[0].size();
    size_t maxValRow = 0;
    size_t maxValCol = 0;
    int32_t maxVal = dpTable[0][0].GetMaxScore();
    for (size_t i = 0; i < rowSize; ++i)
        for (size_t j = 0; j < colSize; ++j) {
            const int32_t maxCellValue = dpTable[i][j].GetMaxScore();
            if (maxCellValue > maxVal) {
                maxVal = maxCellValue;
                maxValRow = i;
                maxValCol = j;
            }
        }
    stats.SetAlignmentScore(maxVal);
    stats.SetS1End(maxValRow - 1);
    stats.SetS2End(maxValCol - 1);
    size_t i = maxValRow;
    size_t j = maxValCol;
    size_t prevI = i;
    size_t prevJ = j;
    string& pathRetrace = stats.GetAlignmentPathRef();
    const string& s1 = stats.GetS1ConstRef();
    const string& s2 = stats.GetS2ConstRef();
    while (i > 0 && j > 0 && !dpTable[i][j].IsAllZero()) {
        prevI = i;
        prevJ = j;
        switch (dpTable[i][j].GetMaxScoreKey()) {
            case S_VALUE_KEY:
                if (s1[i-1] == s2[j-1])
                    pathRetrace.push_back(MATCH_SYMBOL);
                else
                    pathRetrace.push_back(MISMATCH_SYMBOL);
                --i;
                --j;
            break;
            case D_VALUE_KEY:
                pathRetrace.push_back(DELETION_SYMBOL);
                --i;
            break;
            case I_VALUE_KEY:
                pathRetrace.push_back(INSERTION_SYMBOL);
                --j;
            break;
        }
    }
    reverse(pathRetrace.begin(), pathRetrace.end());
    stats.SetS1Start(prevI - 1);
    stats.SetS2Start(prevJ - 1);
    stats.CalculateStats();
}

bool SequenceAlignment::AlignSequences(string& sequenceFilePath, const string& parameterFilePath, const int32_t alignmentFlag) {
    AlignmentStats stats;
    if (!SequenceAlignment::ValidateFilesExist(sequenceFilePath, parameterFilePath))
        return false;
    if (!SequenceAlignment::LoadGeneticSequences(sequenceFilePath, stats.GetS1Ref(), stats.GetS2Ref(), stats.GetS1NameRef(), stats.GetS2NameRef()))
        return false;
    AlignmentParameters params;
    if (!SequenceAlignment::LoadAlignmentParameters(parameterFilePath, params))
        return false;
    params.SetAlignmentFlag(alignmentFlag);
    stats.SetAlignmentFlag(alignmentFlag);
    stats.SetMatchScore(params.GetMatchScore());
    stats.SetMismatchScore(params.GetMismatchScore());
    stats.SetOpeningGapScore(params.GetOpeningGapScore());
    stats.SetGapExtensionScore(params.GetGapExtensionScore());
    vector<vector<DpCell>> dpTable;
    SequenceAlignment::AllocateAndInitializeDpTable(stats, params, dpTable);
    SequenceAlignment::ExecuteAlignmentDp(stats, params, dpTable);
    SequenceAlignment::PathRetrace(stats, dpTable);
    stats.DumpToFile("./program-output/output.txt");
    return true;
}