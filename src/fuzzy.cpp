#include "fuzzy.h"
#include <iomanip>

const int MATCH = 2;
const int MISMATCH = 1;
const int GAP = -1;
const int GAP_pro = -6;

const int BLOSUM62[24][24] = {
//A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X  *
{4,-1,-2,-2,0,-1,-1,0,-2,-1,-1,-1,-1,-2,-1,1,0,-3,-2,0,-2,-1,0,-4},
{-1,5,0,-2,-3,1,0,-2,0,-3,-2,2,-1,-3,-2,-1,-1,-3,-2,-3,-1,0,-1,-4},
{-2,0,6,1,-3,0,0,0,1,-3,-3,0,-2,-3,-2,1,0,-4,-2,-3,3,0,-1,-4},
{-2,-2,1,6,-3,0,2,-1,-1,-3,-4,-1,-3,-3,-1,0,-1,-4,-3,-3,4,1,-1,-4},
{0,-3,-3,-3,9,-3,-4,-3,-3,-1,-1,-3,-1,-2,-3,-1,-1,-2,-2,-1,-3,-3,-2,-4},
{-1,1,0,0,-3,5,2,-2,0,-3,-2,1,0,-3,-1,0,-1,-2,-1,-2,0,3,-1,-4},
{-1,0,0,2,-4,2,5,-2,0,-3,-3,1,-2,-3,-1,0,-1,-3,-2,-2,1,4,-1,-4},
{0,-2,0,-1,-3,-2,-2,6,-2,-4,-4,-2,-3,-3,-2,0,-2,-2,-3,-3,-1,-2,-1,-4},
{-2,0,1,-1,-3,0,0,-2,8,-3,-3,-1,-2,-1,-2,-1,-2,-2,2,-3,0,0,-1,-4},
{-1,-3,-3,-3,-1,-3,-3,-4,-3,4,2,-3,1,0,-3,-2,-1,-3,-1,3,-3,-3,-1,-4},
{-1,-2,-3,-4,-1,-2,-3,-4,-3,2,4,-2,2,0,-3,-2,-1,-2,-1,1,-4,-3,-1,-4},
{-1,2,0,-1,-3,1,1,-2,-1,-3,-2,5,-1,-3,-1,0,-1,-3,-2,-2,0,1,-1,-4},
{-1,-1,-2,-3,-1,0,-2,-3,-2,1,2,-1,5,0,-2,-1,-1,-1,-1,1,-3,-1,-1,-4},
{-2,-3,-3,-3,-2,-3,-3,-3,-1,0,0,-3,0,6,-4,-2,-2,1,3,-1,-3,-3,-1,-4},
{-1,-2,-2,-1,-3,-1,-1,-2,-2,-3,-3,-1,-2,-4,7,-1,-1,-4,-3,-2,-2,-1,-2,-4},
{1,-1,1,0,-1,0,0,0,-1,-2,-2,0,-1,-2,-1,4,1,-3,-2,-2,0,0,0,-4},
{0,-1,0,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-2,-1,1,5,-2,-2,0,-1,-1,0,-4},
{-3,-3,-4,-4,-2,-2,-3,-2,-2,-3,-2,-3,-1,1,-4,-3,-2,11,2,-3,-4,-3,-2,-4},
{-2,-2,-2,-3,-2,-1,-2,-3,2,-1,-1,-2,-1,3,-3,-2,-2,2,7,-1,-3,-2,-1,-4},
{0,-3,-3,-3,-1,-2,-2,-3,-3,3,1,-2,1,-1,-2,-2,0,-3,-1,4,-3,-2,-1,-4},
{-2,-1,3,4,-3,0,1,-1,0,-3,-4,0,-3,-3,-2,0,-1,-4,-3,-3,4,1,-1,-4},
{-1,0,0,1,-3,3,4,-2,0,-3,-3,1,-1,-3,-1,0,-1,-3,-2,-2,1,4,-1,-4},
{0,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,0,0,-2,-1,-1,-1,-1,-1,-4},
{-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,1}
};


int score(char a, char b) {
	return a == b ? MATCH : MISMATCH;
}

int score_pro(char a, char b){
	return BLOSUM62[a - 'A'][b - 'A'];
}


struct DPInfo {
    int dp;
    int direction;
};

DPInfo merged_dp_direction_L6_I1[2000][2000] = {{0, 0}}; // maximum STR unit length observed in biology

int optimizedDP_L6_I1( string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance, const int m, const int n, int pro) { //specific for short unit
	
	int max_score = 0;
	int max_i = 0;
	int max_j = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = max(1, i - maxInsertLength); j <= min(n, i + maxInsertLength); ++j) {
			int match_score=0;
			int del=0;
			int ins=0;
			if(pro == 0){
				match_score = merged_dp_direction_L6_I1[i - 1][j - 1].dp + score(left[i-1], right[j-1]);
				del = merged_dp_direction_L6_I1[i - 1][j].dp + GAP;
				ins = merged_dp_direction_L6_I1[i][j - 1].dp + GAP;
			}
			else if(pro == 1){
				match_score = merged_dp_direction_L6_I1[i - 1][j - 1].dp + score_pro(left[i-1], right[j-1]);
				del = merged_dp_direction_L6_I1[i - 1][j].dp + GAP_pro;
				ins = merged_dp_direction_L6_I1[i][j - 1].dp + GAP_pro;
			}

			int max_val = max({0, match_score, del, ins});
			int direction_val;

			if (max_val == match_score) {
				direction_val = 0;
			}else if (max_val == del) {
				direction_val = 1;
			} else {
				direction_val = 2;
			}

			merged_dp_direction_L6_I1[i][j] = {max_val, direction_val};

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
		}
		else if (backtrack_j == 0) {
			editDistance++;
			backtrack_i--;
			continue;
		}
		int current_direction = merged_dp_direction_L6_I1[backtrack_i][backtrack_j].direction;
		if (current_direction == 0) {
			if (left[backtrack_i - 1] == right[backtrack_j - 1]) {
				matchingBases++;
			} else {
				editDistance++;
			}
			backtrack_i--;
			backtrack_j--;
		}else if (current_direction == 1) {
			editDistance++;
			backtrack_i--;
		}else {
			editDistance++;
			backtrack_j--;
		}
	}
	return max_j;
}

void find_fuzzy(string DNA, string id, int unitlen_p, int up_p, unsigned int flanking_p, int revercomple_p, string cutoffunit_p, string arg, string unperfect_percentage_p, string edit, int distance, int protein ){
	
	if( up_p == 1){ // up_p : whether transfer all the character to upper, default: 0
		transform( DNA.begin(), DNA.end(), DNA.begin(), ::toupper);
	}

	int cutoff_array_main[2001];
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
	double unperfect_percentage_values[2001];
	istringstream iss2(unperfect_percentage_p);
	string token2;
	int pos2=1;
	while( getline(iss2, token2, split) ){
		double cutoff2 = stod(token2);
		unperfect_percentage_values[pos2]=cutoff2;
		pos2++;
	}
	
	//int edit_cutoff_array[201];
	int insertion_values[2001];
	istringstream iss3(edit);
	//cout << "!!!!!!!!" << edit << endl;
	string token3;
	int pos3=1;
	while( getline(iss3, token3, split) ){
		int cutoff3 = stoi(token3);
		//edit_cutoff_array[pos3]=cutoff3;
		insertion_values[pos3] = cutoff3;
		pos3++;
	}

        unsigned int DNA_len=DNA.length();

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
				//cout << "Start " <<id << "\t" << start << "\t" << ssr_len << "\t" << repeat << endl;
				string_view right_unit;
				if( start_new+ssr_len+insertion+1 < DNA_len ){
					right_unit=string_view(DNA).substr( start_new, ssr_len+insertion );
				}
				else{
					repeat--;
					break;
				}
				int matchingBases=0;
				int editDistance=0;
				int endPosition=0;
				//cout << "Start " <<id << "\t" << start << "\t" << ssr_len << "\t" << repeat << "\t" << left_unit << "\t" << right_unit << endl;
				endPosition = optimizedDP_L6_I1(left_unit, right_unit, insertion, matchingBases, editDistance, ssr_len, ssr_len+insertion, protein);
				//cout << left_unit << "\t" << right_unit << "\t" << matchingBases << "\t" << editDistance << "\t" << endPosition << endl;
				//if( editDistance == 0 ){ 
				if( editDistance == 0 && matchingBases == ssr_len ){
					perfect_copy++;
				}

				//cout << "Before judge " << start << "\t" << left_unit << "\t" << right_unit << "\t" << repeat << "\t" << editDistance << "\t" << matchingBases<< endl;
				//cout << "Before judge " << start << "\t" << ssr_len << "\t" << left_unit << "\t" << right_unit << "\t" << repeat << "\t" << editDistance << "-" << insertion << "\t" << matchingBases << "-" << ssr_len-insertion << endl;

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
				else{
					//cout << "Before judge " << start << "\t" << left_unit << "\t" << right_unit << "\t" << repeat << "\t" << editDistance << "-" << insertion << "\t" << matchingBases << "-" << ssr_len-insertion << endl;
				//else if( ssr_len > 1 && ssr_len <=6 ){ //BUG 1-unperfect_percentage = 0.199999988079071, rather than 0.2 BUGBUGBUGBUGBUGBUG
                                        if( matchingBases < ssr_len-insertion || editDistance > insertion ){ // Sep 1
                                                //cout << "#***** No match: " << "start" << "\t" << "left_unit" << "\t" << "right_unit" << "\t" << "repeat" << "\t" << "editDistance" << "\t" << "matchingBases" << endl;
						repeat--;
						//cout << "#***** No match: " << start << "\t" << left_unit << "\t" << right_unit << "\t" << repeat << "\t" << editDistance << "\t" << matchingBases<< endl;
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
					//else{
					//	cout << "#&&&&&&&&" << start << "\t" << left_unit << "\t" << right_unit << "\t" << endPosition << "\t" << repeat << "\t" << perfect_copy << "\t" << unperfect_percentage<< endl;
					//}
                                        ssr_region+=DNA.substr(start_new,endPosition);
                                        ssr_region+=" ";
                                        start_new+=endPosition;
				}
                        }
			//cout << "Before output " << id << "\t" << start << "\t" << start_new << "\t" << left_unit << "\t" << repeat << endl;
			if( repeat >= cutoff_array_main[ssr_len-1] ){
				if( (ssr_len <=5 && perfect_copy >=2) || (ssr_len>6 && perfect_copy >=0) ){
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
					cout << "\t" << ssr_region ;
					cout << "\n";
					start+=(start_new-start-1+distance);
					//start+=(start_new-start-1-ssr_len);
                                	//start++;
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
						start+=(start_new-start-1+distance);
						//start+=(start_new-start-1-ssr_len);
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
						start+=(start_new-start-1+distance);
						//start+=(start_new-start-1-ssr_len);
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
						start+=(start_new-start-1+distance);
						//start+=(start_new-start-1-ssr_len);
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
						start+=(start_new-start-1+distance);
						//start+=(start_new-start-1-ssr_len);
						break;
					}
				}
				}
				}
			}
                }
        }
}
