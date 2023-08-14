#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

//g++ comparion_optDP_DP.cpp -o comparion_optDP_DP

int match_score = 2;
int mismatch_score = 1;
int gap_penalty = -1;

int score(char a, char b) {
    return a == b ? match_score : mismatch_score;
}

int opt_DP(string left_unit, string right_unit, int insertion);
int DP(string left_unit, string right_unit);

int main() {
    string left_unit = "ATCGCGAGC";
    string right_unit = "ATCGCGAAGC";
    int ins = 1;

    auto start_time_opt = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        opt_DP(left_unit, right_unit, ins);
    }
    auto end_time_opt = std::chrono::high_resolution_clock::now();
    auto duration_opt = std::chrono::duration_cast<std::chrono::microseconds>(end_time_opt - start_time_opt);

    auto start_time_dp = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        DP(left_unit, right_unit);
    }
    auto end_time_dp = std::chrono::high_resolution_clock::now();
    auto duration_dp = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dp - start_time_dp);

    cout << "Time taken by opt_DP: " << duration_opt.count() << " microseconds" << endl;
    cout << "Time taken by DP: " << duration_dp.count() << " microseconds" << endl;

    return 0;
}


int opt_DP(string left_unit, string right_unit, int insertion){

	int m=left_unit.length();
	int n=right_unit.length();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	int max_score = 0;
	int end_pos_right = 0;

	for (int i = 1; i <= m; ++i) {

		int start_j = max(1, end_pos_right);
		int end_j = min(n, end_pos_right + insertion + 1);

		for (int j = start_j; j <= end_j; ++j) {
			int match = dp[i - 1][j - 1] + score(left_unit[i - 1], right_unit[j - 1]);
			int delete_ = dp[i - 1][j] + gap_penalty;
			int insert = dp[i][j - 1] + gap_penalty;
			dp[i][j] = std::max({0, match, delete_, insert});

			if (dp[i][j] > max_score) {
				max_score = dp[i][j];
				end_pos_right = j;
			}
		}
	}
	int i = m, j = end_pos_right;
	int matches = 0;

	while (i > 0 && j > 0) {
		if (dp[i][j] == 0) break;
		if (dp[i][j] == dp[i - 1][j - 1] + score(left_unit[i - 1], right_unit[j - 1])) {
			if (left_unit[i - 1] == right_unit[j - 1]) {
				matches++;
			}
			i--;
			j--;
		}else if (dp[i][j] == dp[i - 1][j] + gap_penalty) {
			i--;
		}else {
			j--;
		}
	}
	return 0;
}

int DP(string left_unit, string right_unit){
        //int insertion=1;
        int m=left_unit.length();
        int n=right_unit.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        int max_score = 0;
        int end_pos_right = 0;
        
        for (int i = 1; i <= m; ++i) {
                
                //int start_j = max(1, end_pos_right);
                //int end_j = min(n, end_pos_right + insertion + 1);
                for(int j=1; j<=n; ++j){
                //for (int j = start_j; j <= end_j; ++j) {
                        int match = dp[i - 1][j - 1] + score(left_unit[i - 1], right_unit[j - 1]);
                        int delete_ = dp[i - 1][j] + gap_penalty;
                        int insert = dp[i][j - 1] + gap_penalty;
                        dp[i][j] = std::max({0, match, delete_, insert});
                        
                        if (dp[i][j] > max_score) {
                                max_score = dp[i][j];
                                end_pos_right = j;
                        }
                }
        }
        int i = m, j = end_pos_right;
        int matches = 0;
        
        while (i > 0 && j > 0) {
                if (dp[i][j] == 0) break;
                if (dp[i][j] == dp[i - 1][j - 1] + score(left_unit[i - 1], right_unit[j - 1])) {
                        if (left_unit[i - 1] == right_unit[j - 1]) {
                                matches++;
                        }
                        i--;
                        j--;
                }else if (dp[i][j] == dp[i - 1][j] + gap_penalty) {
                        i--;
                }else { 
                        j--;
                }       
        }       
        return 0;
}
