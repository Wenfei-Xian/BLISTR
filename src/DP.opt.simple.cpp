#include <iostream>
#include <algorithm>
#include <string>
#include <string_view>
using namespace std;

const int MATCH = 2;      // 设定匹配得分
const int MISMATCH = 1;  // 设定错配得分
const int GAP = -1;       // 设定插入或删除的得分

int score(char a, char b) {
    return a == b ? MATCH : MISMATCH;
}

int optimizedDP(string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance) {
    int m = left.length();
    int n = right.length();

    int dp[5][6] = {0};
    int direction[5][6] = {0};  // 0: match, 1: deletion, 2: insertion

    int max_score = 0;
    int max_i = 0;
    int max_j = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = max(1, i - maxInsertLength); j <= min(n, i + maxInsertLength); ++j) {
            int match_score = dp[i - 1][j - 1] + score(left[i-1], right[j-1]);
            int del = dp[i - 1][j] + GAP;
            int ins = dp[i][j - 1] + GAP;

            int max_val = max({0, match_score, del, ins});

            if (max_val == match_score) {
                direction[i][j] = 0;
            } else if (max_val == del) {
                direction[i][j] = 1;
            } else {
                direction[i][j] = 2;
            }

            dp[i][j] = max_val;

            if (max_val > max_score) {
                max_score = max_val;
                max_i = i;
                max_j = j;
            }
        }
    }

    matchingBases = 0;
    editDistance = 0;
    int backtrack_i = max_i;
    int backtrack_j = max_j;

    while (backtrack_i > 0 || backtrack_j > 0) {
        if (backtrack_i == 0) {
            editDistance++;
            backtrack_j--;
            continue;
        } else if (backtrack_j == 0) {
            editDistance++;
            backtrack_i--;
            continue;
        }

        if (direction[backtrack_i][backtrack_j] == 0) {
            if (left[backtrack_i - 1] == right[backtrack_j - 1]) {
                matchingBases++;
            } else {
                editDistance++;
            }
            backtrack_i--;
            backtrack_j--;
        } else if (direction[backtrack_i][backtrack_j] == 1) {
            editDistance++;
            backtrack_i--;
        } else {
            editDistance++;
            backtrack_j--;
        }
    }

    return max_j;
}

int main() {
    string leftStr = "ATCG";
    string rightStr = "ATACG";
    string_view left = leftStr;
    string_view right = rightStr;
    int maxInsertLength = 1;
    int matchingBases, editDistance;
    int endPosition = optimizedDP(left, right, maxInsertLength, matchingBases, editDistance);
    cout << "End position in right sequence: " << endPosition << endl;
    cout << "Matching bases: " << matchingBases << endl;
    cout << "Edit distance: " << editDistance << endl;
    return 0;
}

