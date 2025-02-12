#ifndef DP_CELL_HPP
#define DP_CELL_HPP

#include "./../imports.hpp"

#define S_VALUE_KEY 's'
#define D_VALUE_KEY 'd'
#define I_VALUE_KEY 'i'

struct DpCell {
public:
    int32_t sScore;
    int32_t dScore;
    int32_t iScore;
    DpCell(const int32_t newSScore = 0, const int32_t newDScore = 0, const int32_t newIScore = 0);
    char GetMaxScoreKey(void) const;
    int32_t GetMaxScore(void) const;
};

#endif