#pragma once

#include "./imports.hpp";
#include "./AlignmentStatistics.hpp"
/**
 * Class that is going to implement both local and global pairwise sequence alignment affine gap penalty
 */
class PairwiseSequenceAlignmentAffineGapPenalty {
    private:
        /**
         * Calculates statistics for local pairwise sequence alignment using the affine gap penalty
         */
        AlignmentStatistics CalculateLocalAlignment();

        /**
         * Calculates statistics for global pairwise sequence alignment using the affine gap penalty
         */
        AlignmentStatistics CalculateGlobalAlignment();
        
    public:
        AlignmentStatistics CalculateAlignment();
};