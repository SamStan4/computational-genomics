#include "./../globals-imports/globals_includes.hpp"

typedef struct dp_cell
{
    public:
        int s_score;
        int d_score;
        int i_score;
        dp_cell(const int new_s_score = 0, const int new_d_score = 0, const int new_i_score = 0) {
            this->s_score = new_s_score;
            this->d_score = new_d_score;
            this->i_score = new_i_score;
        }
        char get_max_score(void) {
            if (this->d_score >= this->s_score && this->d_score >= this->i_score) {
                return D_VALUE_KEY;
            } else if (this->s_score >= this->d_score && this->s_score >= this->i_score) {
                return S_VALUE_KEY;
            } else {
                return I_VALUE_KEY;
            }
        }
} dp_cell;