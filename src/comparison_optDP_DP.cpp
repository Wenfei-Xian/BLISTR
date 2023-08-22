#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
//#include "/tmp/global2/wxian/software/WFA2-lib/bindings/cpp/WFAligner.hpp"
//using namespace wfa;
using namespace std;

//g++ comparison_optDP_DP.cpp -o comparison_optDP_DP
//g++ comparion_optDP_DP.cpp -o comparion_optDP_DP -L/tmp/global2/wxian/software/WFA2-lib/lib/ -I/tmp/global2/wxian/software/WFA2-lib -lwfacpp -fopenmp -lm

int match_score = 2;
int mismatch_score = 1;
int gap_penalty = -1;

int score(char a, char b) {
    return a == b ? match_score : mismatch_score;
}

int opt_DP(string left_unit, string right_unit, int insertion);
int DP(string left_unit, string right_unit);
int optimizedDP(string left_unit, string right_unit, int insertion);

int main() {
    string left_unit = "ACGTTC";
    string right_unit = "ACGGTTC";
    int ins = 1;

    // Create a WFAligner
    //WFAlignerGapAffine aligner(0,1,1,1,WFAligner::Alignment,WFAligner::MemoryHigh);
    //WFAlignerEdit aligner2(WFAligner::Alignment, WFAligner::MemoryHigh);

    //auto start_time_opt = std::chrono::high_resolution_clock::now();
    //for (int i = 0; i < 1000000; ++i) {
        //opt_DP(left_unit, right_unit, ins);
    //}
    //auto end_time_opt = std::chrono::high_resolution_clock::now();
    //auto duration_opt = std::chrono::duration_cast<std::chrono::microseconds>(end_time_opt - start_time_opt);

    auto start_time_dp = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        DP(left_unit, right_unit);
    }
    auto end_time_dp = std::chrono::high_resolution_clock::now();
    auto duration_dp = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dp - start_time_dp);

    auto start_time_opt2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        optimizedDP(left_unit, right_unit, ins);
    }
    auto end_time_opt2 = std::chrono::high_resolution_clock::now();
    auto duration_opt2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time_opt2 - start_time_opt2);

    //int opt_DP_o=opt_DP(left_unit, right_unit, ins);
    int DP_o=DP(left_unit, right_unit);
    int opt2_DP_o=optimizedDP(left_unit, right_unit, ins);
    
    //aligner.alignEnd2End(left_unit,right_unit);
    //string alignment = aligner.getAlignment();
    //cout << "Alignment: " << alignment  << endl;
    //cout << "opt_DP: " <<opt_DP_o << endl;
    //cout << "DP: " << DP_o << endl;
    //cout << "opt_DP: " << opt2_DP_o << endl;

    //auto start_time_w = std::chrono::high_resolution_clock::now();
    //for (int i = 0; i < 1000000; ++i){
    	    //cout << left_unit << endl;
	    //cout << right_unit << endl;
	    //aligner.alignEnd2End(left_unit,right_unit);
	    //string alignment = aligner.getAlignment();
	    //string cigar=aligner.getCIGAR(1);
	    //cout << "Cigar: " << cigar << endl;
	    //cout << "Alignment: " << alignment  << endl; 
    //}
    //auto end_time_w = std::chrono::high_resolution_clock::now();
    //auto duration_w = std::chrono::duration_cast<std::chrono::microseconds>(end_time_w - start_time_w);
	
    //cout << "Time taken by opt_DP: " << duration_opt.count() << " microseconds" << endl;
    cout << "Time taken by DP: " << duration_dp.count() << " microseconds" << endl;
    //cout << "Time taken by Wave: " << duration_w.count() << " microseconds" << endl;
    cout << "Time taken by opt_DP: " << duration_opt2.count() << " microseconds" << endl;
    //cout << "Time taken by opt3_DP: " << duration_opt3.count() << " microseconds" << endl;
    return 0;
}

int optimizedDP( string left, string right, int maxInsertLength) {
    int m = left.length();
    int n = right.length();

    std::vector<std::vector<int>> dp(maxInsertLength + 1, std::vector<int>(n + 1, 0));
    int max_score = 0;
    int max_i = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = std::max(1, i - maxInsertLength); j <= std::min(n, i + maxInsertLength); ++j) {
            int match = dp[(i - 1) % (maxInsertLength + 1)][j - 1] + score(left[i-1], right[j-1]);
            int del = dp[(i - 1) % (maxInsertLength + 1)][j] + gap_penalty;
            int ins = dp[i % (maxInsertLength + 1)][j - 1] + gap_penalty;

            dp[i % (maxInsertLength + 1)][j] = std::max({0, match, del, ins});

            if (dp[i % (maxInsertLength + 1)][j] > max_score) {
                max_score = dp[i % (maxInsertLength + 1)][j];
                max_i = i;
            }
        }
    }
    return max_i;
}

/*
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
	return end_pos_right;
}
*/

int DP(string left_unit, string right_unit){
        int m=left_unit.length();
        int n=right_unit.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        int max_score = 0;
        int end_pos_right = 0;
        
        for (int i = 1; i <= m; ++i) {
                for(int j=1; j<=n; ++j){
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
/*
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
*/	
        return end_pos_right;
}
