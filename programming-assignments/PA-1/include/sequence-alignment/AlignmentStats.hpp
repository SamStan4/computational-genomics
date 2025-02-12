#ifndef ALIGNMENT_STATS
#define ALIGNMENT_STATS

#include "./../imports.hpp"
#include "./AlignmentParameters.hpp"

class AlignmentStats {
private:
    string s1;
    string s2;
    string s1Name;
    string s2Name;

    string alignmentPath;

    int32_t alignmentFlag;

    size_t s1Start;
    size_t s2Start;
    size_t s1End;
    size_t s2End;

    int32_t matchScore;
    int32_t mismatchScore;
    int32_t openingGapScore;
    int32_t gapExtensionScore;

    int32_t alignmentScore;
    int32_t numberMatches;
    int32_t numberMismatches;
    int32_t numberOpeningGaps;
    int32_t numberGapExtensions;

    void DumpAlignmentHeaderToFile(ofstream& outStream) const;
    void DumpInputOverviewToFile(ofstream& outStream) const;
    void DumpAlignmentVisualToFile(ofstream& outStream) const;
    void DumpAlignmentReportToFile(ofstream& outStream) const;

public:

    void PrintContentsToCout(void) const;

    string& GetS1Ref(void);
    string& GetS2Ref(void);
    string& GetS1NameRef(void);
    string& GetS2NameRef(void);

    string& GetAlignmentPathRef(void);
    const string& GetS1ConstRef(void) const;
    const string& GetS2ConstRef(void) const;
    const string& GetS1NameConstRef(void) const;
    const string& GetS2NameConstRef(void) const;
    const string& GetAlignmentPathConstRef(void) const;

    void SetAlignmentFlag(const int32_t newAlignmentFlag);

    int32_t GetAlignmentFlag(void) const;

    void SetS1Start(const size_t newS1Start);
    void SetS2Start(const size_t newS2Start);
    void SetS1End(const size_t newS1End);
    void SetS2End(const size_t newS2End);

    size_t GetS1Start(void) const;
    size_t GetS2Start(void) const;
    size_t GetS1End(void) const;
    size_t GetS2End(void) const;

    void SetAlignmentScore(const int32_t newAlignmentScore);

    void SetMatchScore(const int32_t newMatchScore);
    void SetMismatchScore(const int32_t newMismatchScore);
    void SetOpeningGapScore(const int32_t newOpeningGapScore);
    void SetGapExtensionScore(const int32_t newGapExtensionScore);

    void CalculateStats(void);

    _Float32 GetIdentityPercentage(void) const;
    _Float32 GetGapPercentage(void) const;

    void DumpToFile(const char* filePath) const;
};

#endif