#include "./../../include/sequence-alignment/AlignmentParameters.hpp"

void AlignmentParameters::PrintContentsToCout(void) const {
    cout
        << "Alignment Flag: " << this->alignmentFlag << endl
        << "Match Score: " << this->matchScore << endl
        << "Mismatch Score: " << this->mismatchScore << endl
        << "Opening Gap Score: " << this->openingGapScore << endl
        << "Gap Extension Score: " << this->gapExtensionScore << endl;
}

void AlignmentParameters::SetMatchScore(const int32_t newMatchScore) {
    this->matchScore = newMatchScore;
}

void AlignmentParameters::SetMismatchScore(const int32_t newMismatchScore) {
    this->mismatchScore = newMismatchScore;
}

void AlignmentParameters::SetOpeningGapScore(const int32_t newOpeningGapScore) {
    this->openingGapScore = newOpeningGapScore;
}

void AlignmentParameters::SetGapExtensionScore(const int32_t newGapExtensionScore) {
    this->gapExtensionScore = newGapExtensionScore;
}

void AlignmentParameters::SetAlignmentFlag(const int32_t newAlignmentFlag) {
    this->alignmentFlag = newAlignmentFlag;
}


int32_t AlignmentParameters::GetMatchScore(void) const {
    return this->matchScore;
}

int32_t AlignmentParameters::GetMismatchScore(void) const {
    return this->mismatchScore;
}

int32_t AlignmentParameters::GetOpeningGapScore(void) const {
    return this->openingGapScore;
}

int32_t AlignmentParameters::GetGapExtensionScore(void) const {
    return this->gapExtensionScore;
}

int32_t AlignmentParameters::GetAlignmentFlag(void) const {
    return this->alignmentFlag;
}