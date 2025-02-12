#include "./../../include/sequence-alignment/DpCell.hpp"

DpCell::DpCell(const int32_t newSScore, const int32_t newDScore, const int32_t newIScore)
    : sScore(newSScore), dScore(newDScore), iScore(newIScore) {}

char DpCell::GetMaxScoreKey(void) const {
    const int32_t maxScore = this->GetMaxScore();
    if (this->dScore == maxScore) return D_VALUE_KEY;
    if (this->sScore == maxScore) return S_VALUE_KEY;
    return I_VALUE_KEY;
}

int32_t DpCell::GetMaxScore(void) const {
    return std::max(this->sScore, std::max(this->dScore, this->iScore));
}