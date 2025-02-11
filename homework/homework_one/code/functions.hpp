#include <iostream>

#include <string>
#include <vector>
#include <queue>
#include <set>
#include <limits>

#define INT_MIN -2147483648

using namespace std;

int get_number_paths(const string& s1, const string& s2, const int match, const int mismatch, const int gap_penalty) {
    const int n = (int)s1.size();
    const int m = (int)s2.size();
    if (n == 0 || m == 0)
        return 1;
    vector<vector<int>> dp_table(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> path_count(n + 1, vector<int>(m + 1, 0));
    // Initialize
    dp_table[0][0] = 0;
    path_count[0][0] = 1;
    for (int i = 0; i <= n; ++i) {
        dp_table[i][0] = i * gap_penalty;
        path_count[i][0] = 1;
    }
    for (int j = 1; j <= m; ++j) {
        dp_table[0][j] = j * gap_penalty;
        path_count[0][j] = 1;
    }
    // populate dp_table and count table
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            const int a = dp_table[i-1][j] + gap_penalty;
            const int b = dp_table[i][j-1] + gap_penalty;
            const int c = dp_table[i-1][j-1] + (s1[i-1] == s2[j-1] ? match : mismatch);
            const int d = max(max(a, b), c);
            dp_table[i][j] = d;
            if (a == d)
                path_count[i][j] += path_count[i-1][j];
            if (b == d)
                path_count[i][j] += path_count[i][j-1];
            if (c == d)
                path_count[i][j] += path_count[i-1][j-1];
        }
    return path_count.back().back();
}