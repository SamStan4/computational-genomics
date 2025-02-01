#include <iostream>

#include <string>
#include <vector>
#include <queue>
#include <set>
#include <limits>

#define INT_MIN -2147483648

using namespace std;

int get_number_paths(const string& s1, const string& s2, const int match, const int mismatch, const int gap_penalty) {
    // Create and initialize the dp table
    vector<vector<int>> dp_table(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    for (int i = 0; i < dp_table.size(); ++i) {
        dp_table[i][0] = i * gap_penalty;
    }
    for (int j = 1; j < dp_table[0].size(); ++j) {
        dp_table[0][j] = j * gap_penalty;
    }

    // dynamic programming step
    for (int i = 1; i < dp_table.size(); ++i) {
        for (int j = 1; j < dp_table[i].size(); ++j) {
            const int value_1 = dp_table[i-1][j] + gap_penalty;
            const int value_2 = dp_table[i][j-1] + gap_penalty;
            const int value_3 = dp_table[i-1][j-1] + (s1[i-1] == s2[j-1] ? match : mismatch);
            dp_table[i][j] = max(value_1, max(value_2, value_3));
        }
    }

    // BFS backtracking for optimal alignment paths
    vector<vector<int>> path_counter(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    queue<pair<int, int>> bfs_queue;
    path_counter[path_counter.size()-1][path_counter[0].size()-1] = 1;
    bfs_queue.push({dp_table.size() - 1, dp_table[0].size() - 1});

    while (!bfs_queue.empty()) {
        const int bfs_queue_size = bfs_queue.size();
        set<pair<int, int>> next;
        for (int i = 0; i < bfs_queue_size; ++i) {
            const int r = bfs_queue.front().first;
            const int c = bfs_queue.front().second;
            bfs_queue.pop();
            if (r > 0 && (dp_table[r-1][c] + gap_penalty) == dp_table[r][c]) {
                path_counter[r-1][c] += path_counter[r][c];
                next.insert({r-1, c});
            }
            if (c > 0 && (dp_table[r][c-1] + gap_penalty) == dp_table[r][c]) {
                path_counter[r][c-1] += path_counter[r][c];
                next.insert({r, c-1});
            }
            if (r > 0 && c > 0 && (dp_table[r-1][c-1] + (s1[r-2] == s2[c-2] ? match : mismatch)) == dp_table[r][c]) {
                path_counter[r-1][c-1] += path_counter[r][c];
                next.insert({r-1, c-1});
            }
        }
        for (auto it = next.begin(); it != next.end(); ++it) {
            bfs_queue.push({it->first, it->second});
        }
    }

    return path_counter[0][0];
}