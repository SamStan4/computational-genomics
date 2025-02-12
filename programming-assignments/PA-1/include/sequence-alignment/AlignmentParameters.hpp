#ifndef ALIGNMENT_PARAMETERS_HPP
#define ALIGNMENT_PARAMETERS_HPP

#include "./../imports.hpp"

class AlignmentParameters {
private:
    int32_t matchScore;
    int32_t mismatchScore;
    int32_t openingGapScore;
    int32_t gapExtensionScore;
    int32_t alignmentFlag;
public:
    void PrintContentsToCout(void) const;
    void SetMatchScore(const int32_t newMatchScore);
    void SetMismatchScore(const int32_t newMismatchScore);
    void SetOpeningGapScore(const int32_t newOpeningGapScore);
    void SetGapExtensionScore(const int32_t newGapExtensionScore);
    void SetAlignmentFlag(const int32_t newAlignmentFlag);
    int32_t GetMatchScore(void) const;
    int32_t GetMismatchScore(void) const;
    int32_t GetOpeningGapScore(void) const;
    int32_t GetGapExtensionScore(void) const;
    int32_t GetAlignmentFlag(void) const;
};

#endif