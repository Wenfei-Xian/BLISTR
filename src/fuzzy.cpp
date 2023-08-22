#include "fuzzy.h"
#include <iomanip>

const int MATCH = 2;
const int MISMATCH = 1;
const int GAP = -1;

int score(char a, char b) {
	return a == b ? MATCH : MISMATCH;
}

int optimizedDP1_6( string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance, const int m, const int n) { //specific for short unit
	
	int dp[2][8]={0};
	int direction[2][8]={0};
	//vector<vector<int>> dp(maxInsertLength + 1, vector<int>(n + 1, 0));
	//vector<vector<int>> direction(maxInsertLength + 1, vector<int>(n + 1, 0)); // 0: match, 1: deletion, 2: insertion
	
	int max_score = 0;
	int max_i = 0;
	int max_j = 0;

	for (int i = 1; i <= m; ++i) {
		for (int j = max(1, i - maxInsertLength); j <= min(n, i + maxInsertLength); ++j) {
			int match_score = dp[(i - 1) % (maxInsertLength + 1)][j - 1] + score(left[i-1], right[j-1]);
			int del = dp[(i - 1) % (maxInsertLength + 1)][j] + GAP;
			int ins = dp[i % (maxInsertLength + 1)][j - 1] + GAP;
			int max_val = max({0, match_score, del, ins});
			if (max_val == match_score) {
				direction[i % (maxInsertLength + 1)][j] = 0;
			} else if (max_val == del) {
				direction[i % (maxInsertLength + 1)][j] = 1;
			} else {
				direction[i % (maxInsertLength + 1)][j] = 2;
			}
			dp[i % (maxInsertLength + 1)][j] = max_val;
			if (max_val > max_score) {
				max_score = max_val;
				max_i = i;
				max_j = j;
			}
		}
	}

	//backtracking
	matchingBases = 0;
	editDistance = 0;
	int backtrack_i = max_i; // Save the original values before backtracking
	int backtrack_j = max_j;

	while (backtrack_i > 0 || backtrack_j > 0) {
		if (backtrack_i == 0) {  // If we've already processed the entire left sequence
			editDistance++;  // These are insertions in the right sequence
			backtrack_j--;
			continue;
		} else if (backtrack_j == 0) {  // If we've already processed the entire right sequence
			editDistance++;  // These are deletions in the left sequence
			backtrack_i--;
			continue;
		}
		if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 0) { // match or mismatch
			if (left[backtrack_i - 1] == right[backtrack_j - 1]) {
				matchingBases++;
			} else {
				editDistance++;
			}
			backtrack_i--;
			backtrack_j--;
		} else if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 1) { // deletion
			editDistance++;
 			backtrack_i--;
    		} else { // insertion
        		editDistance++;
        		backtrack_j--;
    		}
	}
    	return max_j; // Return the saved end position value
}

int optimizedDP7_10( string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance, const int m, const int n) {
	
	int dp[2][12]={0};
	int direction[2][12]={0};
	//vector<vector<int>> dp(maxInsertLength + 1, vector<int>(n + 1, 0));
	//vector<vector<int>> direction(maxInsertLength + 1, vector<int>(n + 1, 0)); // 0: match, 1: deletion, 2: insertion
	
	int max_score = 0;
	int max_i = 0;
	int max_j = 0;

	for (int i = 1; i <= m; ++i) {
		for (int j = max(1, i - maxInsertLength); j <= min(n, i + maxInsertLength); ++j) {
			int match_score = dp[(i - 1) % (maxInsertLength + 1)][j - 1] + score(left[i-1], right[j-1]);
			int del = dp[(i - 1) % (maxInsertLength + 1)][j] + GAP;
			int ins = dp[i % (maxInsertLength + 1)][j - 1] + GAP;
			int max_val = max({0, match_score, del, ins});
			if (max_val == match_score) {
				direction[i % (maxInsertLength + 1)][j] = 0;
			} else if (max_val == del) {
				direction[i % (maxInsertLength + 1)][j] = 1;
			} else {
				direction[i % (maxInsertLength + 1)][j] = 2;
			}
			dp[i % (maxInsertLength + 1)][j] = max_val;
			if (max_val > max_score) {
				max_score = max_val;
				max_i = i;
				max_j = j;
			}
		}
	}

	//backtracking
	matchingBases = 0;
	editDistance = 0;
	int backtrack_i = max_i; // Save the original values before backtracking
	int backtrack_j = max_j;

	while (backtrack_i > 0 || backtrack_j > 0) {
		if (backtrack_i == 0) {  // If we've already processed the entire left sequence
			editDistance++;  // These are insertions in the right sequence
			backtrack_j--;
			continue;
		} else if (backtrack_j == 0) {  // If we've already processed the entire right sequence
			editDistance++;  // These are deletions in the left sequence
			backtrack_i--;
			continue;
		}
		if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 0) { // match or mismatch
			if (left[backtrack_i - 1] == right[backtrack_j - 1]) {
				matchingBases++;
			} else {
				editDistance++;
			}
			backtrack_i--;
			backtrack_j--;
		} else if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 1) { // deletion
			editDistance++;
 			backtrack_i--;
    		} else { // insertion
        		editDistance++;
        		backtrack_j--;
    		}
	}
    	return max_j; // Return the saved end position value
}

int optimizedDP11_20( string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance, const int m, const int n) {

	int dp[4][24]={0};
	int direction[4][24]={0};
	//vector<vector<int>> dp(maxInsertLength + 1, vector<int>(n + 1, 0));
	//vector<vector<int>> direction(maxInsertLength + 1, vector<int>(n + 1, 0)); // 0: match, 1: deletion, 2: insertion

	int max_score = 0;
	int max_i = 0;
	int max_j = 0;

	for (int i = 1; i <= m; ++i) {
		for (int j = max(1, i - maxInsertLength); j <= min(n, i + maxInsertLength); ++j) {
			int match_score = dp[(i - 1) % (maxInsertLength + 1)][j - 1] + score(left[i-1], right[j-1]);
			int del = dp[(i - 1) % (maxInsertLength + 1)][j] + GAP;
			int ins = dp[i % (maxInsertLength + 1)][j - 1] + GAP;
			int max_val = max({0, match_score, del, ins});
			if (max_val == match_score) {
				direction[i % (maxInsertLength + 1)][j] = 0;
			} else if (max_val == del) {
				direction[i % (maxInsertLength + 1)][j] = 1;
			} else {
				direction[i % (maxInsertLength + 1)][j] = 2;
			}
			dp[i % (maxInsertLength + 1)][j] = max_val;
			if (max_val > max_score) {
				max_score = max_val;
				max_i = i;
				max_j = j;
			}
		}
	}

	//backtracking
	matchingBases = 0;
	editDistance = 0;
	int backtrack_i = max_i; // Save the original values before backtracking
	int backtrack_j = max_j;

	while (backtrack_i > 0 || backtrack_j > 0) {
		if (backtrack_i == 0) {  // If we've already processed the entire left sequence
			editDistance++;  // These are insertions in the right sequence
			backtrack_j--;
			continue;
		} else if (backtrack_j == 0) {  // If we've already processed the entire right sequence
			editDistance++;  // These are deletions in the left sequence
			backtrack_i--;
			continue;
		}
		if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 0) { // match or mismatch
			if (left[backtrack_i - 1] == right[backtrack_j - 1]) {
				matchingBases++;
			} else {
				editDistance++;
			}
			backtrack_i--;
			backtrack_j--;
		} else if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 1) { // deletion
			editDistance++;
 			backtrack_i--;
    		} else { // insertion
        		editDistance++;
        		backtrack_j--;
    		}
	}
    	return max_j; // Return the saved end position value
}

int optimizedDP21_50( string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance, const int m, const int n) {
	
	int dp[6][58]={0};
	int direction[6][58]={0};
	//vector<vector<int>> dp(maxInsertLength + 1, vector<int>(n + 1, 0));
	//vector<vector<int>> direction(maxInsertLength + 1, vector<int>(n + 1, 0)); // 0: match, 1: deletion, 2: insertion
	
	int max_score = 0;
	int max_i = 0;
	int max_j = 0;

	for (int i = 1; i <= m; ++i) {
		for (int j = max(1, i - maxInsertLength); j <= min(n, i + maxInsertLength); ++j) {
			int match_score = dp[(i - 1) % (maxInsertLength + 1)][j - 1] + score(left[i-1], right[j-1]);
			int del = dp[(i - 1) % (maxInsertLength + 1)][j] + GAP;
			int ins = dp[i % (maxInsertLength + 1)][j - 1] + GAP;
			int max_val = max({0, match_score, del, ins});
			if (max_val == match_score) {
				direction[i % (maxInsertLength + 1)][j] = 0;
			} else if (max_val == del) {
				direction[i % (maxInsertLength + 1)][j] = 1;
			} else {
				direction[i % (maxInsertLength + 1)][j] = 2;
			}
			dp[i % (maxInsertLength + 1)][j] = max_val;
			if (max_val > max_score) {
				max_score = max_val;
				max_i = i;
				max_j = j;
			}
		}
	}

	//backtracking
	matchingBases = 0;
	editDistance = 0;
	int backtrack_i = max_i; // Save the original values before backtracking
	int backtrack_j = max_j;

	while (backtrack_i > 0 || backtrack_j > 0) {
		if (backtrack_i == 0) {  // If we've already processed the entire left sequence
			editDistance++;  // These are insertions in the right sequence
			backtrack_j--;
			continue;
		} else if (backtrack_j == 0) {  // If we've already processed the entire right sequence
			editDistance++;  // These are deletions in the left sequence
			backtrack_i--;
			continue;
		}
		if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 0) { // match or mismatch
			if (left[backtrack_i - 1] == right[backtrack_j - 1]) {
				matchingBases++;
			} else {
				editDistance++;
			}
			backtrack_i--;
			backtrack_j--;
		} else if (direction[backtrack_i % (maxInsertLength + 1)][backtrack_j] == 1) { // deletion
			editDistance++;
 			backtrack_i--;
    		} else { // insertion
        		editDistance++;
        		backtrack_j--;
    		}
	}
    	return max_j; // Return the saved end position value
}

void find_fuzzy(string DNA, string id, int unitlen_p, int up_p, unsigned int flanking_p, int revercomple_p, string cutoffunit_p, string arg, string unperfect_percentage_p ){	
	
	if( up_p == 1){ // up_p : whether transfer all the character to upper, default: 0
		transform( DNA.begin(), DNA.end(), DNA.begin(), ::toupper);
	}

	int cutoff_array_main[201];
	istringstream iss(cutoffunit_p);
	string token;
	char split=',';
	int pos=0;
	while( getline(iss, token, split) ){
		int cutoff = stoi(token);
		cutoff_array_main[pos]=cutoff;
		pos++;
	}
	//cout << unperfect_percentage_p << endl;
	double unperfect_percentage_values[201];
	istringstream iss2(unperfect_percentage_p);
	string token2;
	int pos2=1;
	while( getline(iss2, token2, split) ){
		double cutoff2 = stod(token2);
		unperfect_percentage_values[pos2]=cutoff2;
		pos2++;
	}
	
        unsigned int DNA_len=DNA.length();

	int insertion_values[201];
	for (unsigned short ssr_len = 1; ssr_len <= unitlen_p; ssr_len++) { // Pre-calculation loop
		
		int insertion = 1;
		if(ssr_len <= 10){
			insertion = 1;
		}
		else if(ssr_len <= 20){
			insertion = 3;
		}
		else if(ssr_len <= 50){
			insertion = 5;
		}
		else if(ssr_len <=100){
			insertion = 10;
		}
		else if(ssr_len <=200){
			insertion = 20;
		}
		else{
			insertion = 30;
		}
		insertion_values[ssr_len] = insertion;
		
		if(ssr_len > 6){
			unperfect_percentage_values[ssr_len] = 1;
		}
	}


        for ( unsigned int start=0; start < DNA_len; start++){
                for (unsigned short ssr_len=1; ssr_len<= unitlen_p ; ssr_len++){ // unitlen_p : longest length of unit, default: 6

			int insertion = insertion_values[ssr_len]; // Optimization 1
			float unperfect_percentage = unperfect_percentage_values[ssr_len]; // Optimization 1
			unsigned short repeat=1;
			unsigned int start_new=start+ssr_len;

			string ssr_region; // used for output
			string_view left_unit; // Optimization string 2 string_view when substr is needed
			if (start+ssr_len < DNA_len) {
				left_unit=string_view(DNA).substr(start, ssr_len); // used for output
			}
			else{
				break;
			}
			ssr_region+=left_unit; // used for output
			ssr_region+=" "; // used for output
			int perfect_copy=1;

                        for ( ; ; ){
				repeat++;
				string_view right_unit;
				if( start_new+ssr_len+insertion+1 < DNA_len ){
					right_unit=string_view(DNA).substr( start_new, ssr_len+insertion );
				}
				else{
					break;
				}
				int matchingBases=0;
				int editDistance=0;
				int endPosition=0;

				if( ssr_len <=6 ){
					endPosition = optimizedDP1_6(left_unit, right_unit, insertion, matchingBases, editDistance, ssr_len, ssr_len+insertion);
				}
				else if( ssr_len >=7 && ssr_len <=10 ){
					endPosition = optimizedDP7_10(left_unit, right_unit, insertion, matchingBases, editDistance, ssr_len, ssr_len+insertion);
				}
				else if( ssr_len >=11 && ssr_len <=20 ){
					endPosition = optimizedDP11_20(left_unit, right_unit, insertion, matchingBases, editDistance, ssr_len, ssr_len+insertion);
				}
				else if( ssr_len >=21 && ssr_len <=50 ){
					endPosition = optimizedDP21_50(left_unit, right_unit, insertion, matchingBases, editDistance, ssr_len, ssr_len+insertion);
				}

				if( matchingBases == ssr_len && endPosition == ssr_len ){
					perfect_copy++;
				}

				//cout << "#@@@@@@@" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << matchingBases << "\t" << editDistance << "\t" << static_cast<double>(repeat-perfect_copy)/static_cast<double>(cutoff_array_main[ssr_len-1]) << "\t" << static_cast<double>(repeat-perfect_copy)/static_cast<double>(repeat) << "\t" << repeat << "\t" << perfect_copy << "\t" << unperfect_percentage << endl;
				//cout << "#@@@@@@@@" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << repeat << "\t" << perfect_copy << "\t" << matchingBases << "\t" << editDistance << "\t" << "repeat>cutoff:"<< static_cast<double>((repeat-perfect_copy)/repeat) << "\t" << "repeat<cutoff:" << static_cast<double>((repeat-perfect_copy)/cutoff_array_main[ssr_len-1]) << endl;
				if( ssr_len == 1 ){
					if( matchingBases == 0 ){
						repeat--;
						//cout << "#***** No match" << endl;
						break;
					}
					else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy) / static_cast<double>(cutoff_array_main[ssr_len-1]) >= static_cast<double>(unperfect_percentage) ){
						repeat--;
						//cout << "#!!!!!!" << "\t" << static_cast<double>(repeat-perfect_copy)/cutoff_array_main[ssr_len-1] << "\t" << 1-unperfect_percentage << endl;
						//ssr_region+=DNA.substr(start_new,endPosition);
						//ssr_region+=" ";
						//start_new+=endPosition;
						break;
					}
					else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy) / static_cast<double>(repeat) >= static_cast<double>(unperfect_percentage) ){
						repeat--;
						//cout << "#$$$$$$" << endl;
						//ssr_region+=DNA.substr(start_new,endPosition);
						//ssr_region+=" ";
						//start_new+=endPosition;
						break;
					}
					ssr_region+=DNA.substr(start_new,endPosition);
					ssr_region+=" ";
					start_new+=endPosition;
                                }
				else if( ssr_len > 1 && ssr_len <=6 ){ //BUG 1-unperfect_percentage = 0.199999988079071, rather than 0.2 BUGBUGBUGBUGBUGBUG
                                        if( matchingBases < ssr_len-insertion || editDistance > 1 ){
                                                //cout << "#***** No match: " << start << "\t" << left_unit << "\t" << right_unit << "\t" << repeat << endl;
						repeat--;
						break;
                                        }
                                        else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/static_cast<double>(cutoff_array_main[ssr_len-1]) >= static_cast<double>(unperfect_percentage) ){
						repeat--;
				 		//ssr_region+=DNA.substr(start_new,endPosition);
                                                //ssr_region+=" ";
                                                //start_new+=endPosition;
						//cout << "#!!!!!!!!!" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << static_cast<double>(repeat-perfect_copy) << "\t" << static_cast<double>(cutoff_array_main[ssr_len-1]) << "\t" << unperfect_percentage << endl;
                                                break;
                                        }
                                        else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/static_cast<double>(repeat) >= static_cast<double>(unperfect_percentage) ){
                                                repeat--;
						//ssr_region+=DNA.substr(start_new,endPosition);
                                                //ssr_region+=" ";
                                                //start_new+=endPosition;
                                                //cout << "#?????????" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << repeat << "\t" << perfect_copy << "\t" << unperfect_percentage<< endl;
						break;
                                        }
                                        ssr_region+=DNA.substr(start_new,endPosition);
                                        ssr_region+=" ";
                                        start_new+=endPosition;
				}
                                else{ //
					if( matchingBases < ssr_len-insertion || editDistance > insertion ){
						repeat--;
						break;
					}
					else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy) / static_cast<double>(cutoff_array_main[ssr_len-1]) >= static_cast<double>(unperfect_percentage) ){
						repeat--;
						//ssr_region+=DNA.substr(start_new,endPosition);
						//ssr_region+=" ";
						//start_new+=endPosition;
						//cout << "###!!!!!!!!!" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << matchingBases << "\t" << repeat << "\t" << perfect_copy << endl;
						break;
					}
					else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy) / static_cast<double>(repeat) >= static_cast<double>(unperfect_percentage) ){
						repeat--;
						//ssr_region+=DNA.substr(start_new,endPosition);
						//ssr_region+=" ";
						//start_new+=endPosition;
						//cout << "###?????????" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << matchingBases << "\t" << repeat << "\t" << perfect_copy << endl;
						break;
					}
					ssr_region+=DNA.substr(start_new,endPosition);
					ssr_region+=" ";
					start_new+=endPosition;

                                }
                        }
			if( repeat >= cutoff_array_main[ssr_len-1] ){
				if( (ssr_len <=6 && perfect_copy >=2) || (ssr_len>6 && perfect_copy >=0) ){
				if( (arg == "fuzzy_vntr_default" && ssr_len > 7) || arg == "fuzzy_str_default" || arg == "fuzzy_costom" ){
				if( revercomple_p > 0 ){
					string ssr_recom;
					ssr_recom=left_unit;
					reverse_complement(ssr_recom);
					//left_unit+="\t";
					//left_unit+=ssr_recom;
				}
				
				if( flanking_p == 0 ){
					cout << id << "\t" << start+1 << "\t" << start_new << "\t" << left_unit << "\t" << repeat << "\t" << perfect_copy << "\t" << start_new-start;
					//cout << id << "\t" << start+1 << "\t" << start_new << "\t" << repeat << "\t" << left_unit << "\t" << start_new-start;
					cout << "\t" << ssr_region ;
					cout << "\n";
					//start+=(start_new-start); Wed Aug 16 1:23 BUG
					start+=(start_new-start-5);
                                	break;
				}
				else if( flanking_p > 0 ){
					string flanking_seq;
					string flanking_seq1;
					string flanking_seq2;
					if( start > flanking_p && start_new + flanking_p < DNA_len ){
						flanking_seq=DNA.substr( start - flanking_p , 2 * flanking_p + start_new - start );
						flanking_seq1=DNA.substr( start - flanking_p, flanking_p );
						flanking_seq2=DNA.substr( start_new, flanking_p );
						cout << id << "\t" << start+1 << "\t" << start_new << "\t" << left_unit << "\t" << repeat << "\t" << start_new-start;
						cout << "\t" << ssr_region ;
						cout << "\t" << flanking_seq;
						cout << "\t" << flanking_seq1;
						cout << "\t" << flanking_seq2;
						cout << "\n";
						start+=(start_new-start-3);
						break;
					}
					else if ( start <= flanking_p && start_new + flanking_p < DNA_len ){
						flanking_seq=DNA.substr( 0, start+start_new-start+flanking_p );
						flanking_seq1=DNA.substr( 0, start );
						flanking_seq2=DNA.substr( start_new, flanking_p );
						cout << id << "\t" << start+1 << "\t" << start_new << "\t" << left_unit << "\t" << repeat << "\t" << start_new-start;
						cout << "\t" << ssr_region ;
                                                cout << "\t" << flanking_seq;
						cout << "\t" << flanking_seq1;
						cout << "\t" << flanking_seq2;
                                                cout << "\n";
                                                start+=(start_new-start-3);
                                                break;
					}
					else if ( start > flanking_p && start_new + flanking_p >= DNA_len ){
						flanking_seq=DNA.substr( start-flanking_p, flanking_p+start_new-start+DNA_len-start_new );
						flanking_seq1=DNA.substr( start-flanking_p, flanking_p );
						flanking_seq2=DNA.substr( start_new, DNA_len - start_new );
						cout << id << "\t" << start+1 << "\t" << start_new << "\t" << left_unit << "\t" << repeat << "\t" << start_new-start ;
						cout << "\t" << ssr_region ;
						cout << "\t" << flanking_seq;
						cout << "\t" << flanking_seq1;
						cout << "\t" << flanking_seq2;
						cout << "\n";
						start+=(start_new-start-3);
						break;
					}
					else if ( start <= flanking_p && start_new+flanking_p >= DNA_len ){
						flanking_seq1=DNA.substr( 0, start );
						flanking_seq2=DNA.substr( start_new, DNA_len - start_new );
						cout << id << "\t" << start+1 << "\t" << start_new << "\t" << left_unit << "\t" << repeat << "\t" << start_new-start ;
						cout << "\t" << ssr_region ;
						cout << "\t" << flanking_seq1;
						cout << "\t" << flanking_seq2;
						cout << "\t" << DNA;
						cout << "\n";
						start+=(start_new-start-3);
						break;
					}
				}
				}
				}
			}
			//else{
			//	cout << "#******" << start << "\t" << left_unit << "\t" << perfect_copy+1 << "\t"<< repeat*unperfect_percentage << endl;
			//}
                }
        }
}
