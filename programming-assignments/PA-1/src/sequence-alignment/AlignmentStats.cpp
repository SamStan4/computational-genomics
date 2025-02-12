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