#include "./functions.hpp"

int main(void) {
    string s1 = "ATTATGCCTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTCTTTACTGGGTG";
    string s2 = "GCTTACGTCCTAAATGCCCTGAAAA";
    int match = 1, mismatch = -1, gap = -1;
    cout << get_number_paths(s1, s2, match, mismatch, gap) << endl;
    return 0;
}