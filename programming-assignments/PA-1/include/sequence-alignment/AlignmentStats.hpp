#ifndef ALIGNMENT_STATS
#define ALIGNMENT_STATS

#include "./../imports.hpp"

class AlignmentStats {
private:
    string s1;
    string s2;
    string s1Name;
    string s2Name;
    string alignmentPath;
    int32_t alignmentFlag;
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
};

#endif