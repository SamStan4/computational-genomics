#include "./../../include/sequence-alignment/AlignmentStats.hpp"

void AlignmentStats::PrintContentsToCout(void) const {
    cout
        << "> " << this->s1Name << endl
        << this->s1 << endl << endl
        << "> " << this->s2Name << endl
        << this->s1 << endl;
}

string& AlignmentStats::GetS1Ref(void) {
    return this->s1;
}

string& AlignmentStats::GetS2Ref(void) {
    return this->s2;
}

string& AlignmentStats::GetS1NameRef(void) {
    return this->s1Name;
}

string& AlignmentStats::GetS2NameRef(void) {
    return this->s2Name;
}

string& AlignmentStats::GetAlignmentPathRef(void) {
    return this->alignmentPath;
}

const string& AlignmentStats::GetS1ConstRef(void) const {
    return this->s1;
}

const string& AlignmentStats::GetS2ConstRef(void) const {
    return this->s2;
}

const string& AlignmentStats::GetS1NameConstRef(void) const {
    return this->s1Name;
}

const string& AlignmentStats::GetS2NameConstRef(void) const {
    return this->s2Name;
}

const string& AlignmentStats::GetAlignmentPathConstRef(void) const {
    return this->alignmentPath;
}

void AlignmentStats::SetAlignmentFlag(const int32_t newAlignmentFlag) {
    this->alignmentFlag = newAlignmentFlag;
}

int32_t AlignmentStats::GetAlignmentFlag(void) const {
    return this->alignmentFlag;
}

void AlignmentStats::SetS1Start(const size_t newS1Start) {
    this->s1Start = newS1Start;
}

void AlignmentStats::SetS2Start(const size_t newS2Start) {
    this->s2Start = newS2Start;
}

void AlignmentStats::SetS1End(const size_t newS1End) {
    this->s1End = newS1End;
}

void AlignmentStats::SetS2End(const size_t newS2End) {
    this->s2End = newS2End;
}

size_t AlignmentStats::GetS1Start(void) const {
    return this->s1Start;
}

size_t AlignmentStats::GetS2Start(void) const {
    return this->s2Start;
}

size_t AlignmentStats::GetS1End(void) const {
    return this->s1End;
}

size_t AlignmentStats::GetS2End(void) const {
    return this->s2End;
}

void AlignmentStats::SetAlignmentScore(const int32_t newAlignmentScore) {
    this->alignmentScore = newAlignmentScore;
}

void AlignmentStats::SetMatchScore(const int32_t newMatchScore) {
    this->matchScore = newMatchScore;
}

void AlignmentStats::SetMismatchScore(const int32_t newMismatchScore) {
    this->mismatchScore = newMismatchScore;
}

void AlignmentStats::SetOpeningGapScore(const int32_t newOpeningGapScore) {
    this->openingGapScore = newOpeningGapScore;
}

void AlignmentStats::SetGapExtensionScore(const int32_t newGapExtensionScore) {
    this->gapExtensionScore = newGapExtensionScore;
}

void AlignmentStats::CalculateStats(void) {
    this->numberMatches = 0;
    this->numberMismatches = 0;
    this->numberOpeningGaps = 0;
    this->numberGapExtensions = 0;
    const size_t retraceSize = this->alignmentPath.size();
    for (size_t i = 0; i < retraceSize; ++i)
        switch (this->alignmentPath[i]) {
            case MATCH_SYMBOL:
                ++this->numberMatches;
            break;
            case MISMATCH_SYMBOL:
                ++this->numberMismatches;
            break;
            case INSERTION_SYMBOL:
            case DELETION_SYMBOL:
                ++this->numberGapExtensions;
            break;
        }
    if (this->alignmentPath[0] == DELETION_SYMBOL || this->alignmentPath[0] == INSERTION_SYMBOL)
        ++this->numberOpeningGaps;
    for (size_t i = 0; i < retraceSize; ++i)
        if ((this->alignmentPath[i] == DELETION_SYMBOL && this->alignmentPath[i-1] != DELETION_SYMBOL) || (this->alignmentPath[i] == INSERTION_SYMBOL && this->alignmentPath[i-1] != INSERTION_SYMBOL))
            ++this->numberOpeningGaps;
}

_Float32 AlignmentStats::GetIdentityPercentage(void) const {
    if (this->alignmentPath.empty())
        return numeric_limits<_Float32>::min();
    return (_Float32)this->numberMatches / (_Float32)this->alignmentPath.size();
}

_Float32 AlignmentStats::GetGapPercentage(void) const {
    if (this->alignmentPath.empty())
        return numeric_limits<_Float32>::min();
    return (_Float32)this->numberGapExtensions / (_Float32)this->alignmentPath.size();
}

void AlignmentStats::DumpAlignmentHeaderToFile(ofstream& outStream) const {
    if (!outStream.is_open()) {
        cerr << "Error, output stream not open" << endl;
        return;
    }
    const size_t s1Size = this->s1.size();
    const size_t s2Size = this->s2.size();
    outStream
        << "INPUT:" << endl
        << "******" << endl
        << endl
        << ">" << this->s1Name << endl;
    for (size_t i = 0; i < s1Size;) {
        for (size_t j = 0, k = i; k < s1Size && j < OUTPUT_WIDTH_FORMAT; ++j, ++k)
            outStream << this->s1[k];
        i += OUTPUT_WIDTH_FORMAT;
        outStream << endl;
    }
    outStream
        << endl
        << ">" << this->s2Name << endl;
    for (size_t i = 0; i < s2Size;) {
        for (size_t j = 0, k = i; k < s2Size && j < OUTPUT_WIDTH_FORMAT; ++j, ++k)
            outStream << this->s2[k];
        i += OUTPUT_WIDTH_FORMAT;
        outStream << endl;
    }
    outStream << endl;
}

void AlignmentStats::DumpInputOverviewToFile(ofstream& outStream) const {
    if (!outStream.is_open()) {
        cerr << "Error, output stream not open" << endl;
        return;
    }
    outStream
        << "Scores:    match = " << this->matchScore << ", mismatch = " << this->mismatchScore << ", h = " << this->openingGapScore << ", g = " << this->gapExtensionScore << endl
        << endl
        << "Sequence 1 = " << this->s1Name << ", length = " << this->s1.size() << " characters" << endl
        << "Sequence 2 = " << this->s2Name << ", length = " << this->s2.size() << " characters" << endl
        << endl;
}

void AlignmentStats::DumpAlignmentVisualToFile(ofstream& outStream) const {
    if (!outStream.is_open()) {
        cerr << "Error, output stream not open" << endl;
        return;
    }
    const size_t retraceSize = this->alignmentPath.size();
    for (size_t i = 0, j = this->s1Start, k = this->s2Start; i < retraceSize; i += OUTPUT_WIDTH_FORMAT) {
        outStream
            << left << setw(5) << "s1" << setw(10) << j + 1;
        for (size_t l = 0, m = i; m < retraceSize && l < OUTPUT_WIDTH_FORMAT; ++l, ++m)
            switch (this->alignmentPath[m]) {
                case MISMATCH_SYMBOL:
                case MATCH_SYMBOL:
                case DELETION_SYMBOL:
                    outStream << this->s1[j++];
                break;
                case INSERTION_SYMBOL:
                    outStream << "-";
                break;
            }
        outStream
            << left << setw(3) << "" << j << endl
            << setw(15) << "";
        for (size_t l = 0, m = i; m < retraceSize && l < OUTPUT_WIDTH_FORMAT; ++l, ++m)
            switch (this->alignmentPath[m]) {
                case MATCH_SYMBOL:
                    outStream << "|";
                break;
                case MISMATCH_SYMBOL:
                case DELETION_SYMBOL:
                case INSERTION_SYMBOL:
                    outStream << " ";
                break;
            }
        outStream
            << endl
            << left << setw(5) << "s2" << setw(10) << k + 1;
        for (size_t l = 0, m = i; m < retraceSize && l < OUTPUT_WIDTH_FORMAT; ++l, ++m)
            switch (this->alignmentPath[m]) {
                case MISMATCH_SYMBOL:
                case MATCH_SYMBOL:
                case INSERTION_SYMBOL:
                    outStream << this->s2[k++];
                break;
                case DELETION_SYMBOL:
                    outStream << "-";
                break;
            }
        outStream
            << left << setw(3) << "" << k << endl
            << endl;
    }
}

void AlignmentStats::DumpAlignmentReportToFile(ofstream& outStream) const {
    if (!outStream.is_open()) {
        cerr << "Error, output stream not open" << endl;
        return;
    }
    outStream
        << "Report:" << endl
        << endl
        << (this->alignmentFlag == 0 ? "Global" : "Local") << " optimal score = " << this->alignmentScore << endl
        << endl
        << "Number of matches = " << this->numberMatches << ", mismatches = " << this->numberMismatches << ", opening gaps = " << this->numberOpeningGaps << ", gap extensions = " << this->numberGapExtensions << endl
        << endl
        << "Identites = " << this->numberMatches << "/" << this->alignmentPath.size() << " (" << this->GetIdentityPercentage() << "%), Gaps = " << this->numberGapExtensions << "/" << this->alignmentPath.size() << " (" << this->GetGapPercentage() << "%)" << endl;
}

void AlignmentStats::DumpToFile(const char* filePath) const {
    ofstream outStream(filePath);
    if (!outStream.is_open()) {
        cerr << "Error opening " << filePath << endl;
        return;
    }
    this->DumpAlignmentHeaderToFile(outStream);
    outStream
        << "OUTPUT:" << endl
        << "******" << endl << endl;
    this->DumpInputOverviewToFile(outStream);
    this->DumpAlignmentVisualToFile(outStream);
    this->DumpAlignmentReportToFile(outStream);
}