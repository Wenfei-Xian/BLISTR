#include "fuzzy.h"

int match_score = 2;
int mismatch_score = 1;
int gap_penalty = -1;
  
int score(char a, char b) {
    return a == b ? match_score : mismatch_score;
}

void find_fuzzy(string DNA, string id, int unitlen_p, int up_p, unsigned int flanking_p, int revercomple_p, string cutoffunit_p, string arg ){	
	
	if( up_p == 1){ // up_p : whether transfer all the character to upper, default: 0
		transform( DNA.begin(), DNA.end(), DNA.begin(), ::toupper);
	}

	int cutoff_array_main[unitlen_p]={0};
	istringstream iss(cutoffunit_p);
	string token;
	char split=',';
	int pos=0;
	while( getline(iss, token, split) ){
		int cutoff = stoi(token);
		cutoff_array_main[pos]=cutoff;
		pos++;
	}

        unsigned int DNA_len=DNA.length();

	int insertion_values[unitlen_p + 1]; // Optimization 1
	float perfect_percentage_values[unitlen_p + 1]; // Optimization 1

	for (unsigned short ssr_len = 1; ssr_len <= unitlen_p; ssr_len++) { // Pre-calculation loop
		
		int insertion = 1;
		if (ssr_len <= 10){
			insertion = 1;
		}
		else if(ssr_len <= 20){
			insertion = 2;
		}
		else if(ssr_len <= 50){
			insertion = 3;
		}
		else{
			insertion = 5;
		}
		insertion_values[ssr_len] = insertion;

		float perfect_percentage = 1.0;
		if(ssr_len == 1){
			perfect_percentage = 0.8;
		}
		else if(ssr_len == 2){
			perfect_percentage = 0.7;
		}
		else if(ssr_len == 3){
			perfect_percentage = 0.6;
		}
		else if(ssr_len == 4){
			perfect_percentage = 0.6;
		}
		else if(ssr_len == 5){
			perfect_percentage = 0.6;
		}
		else if(ssr_len ==6){
			perfect_percentage = 0.6;
		}
		else{
			perfect_percentage = 0;
		}
		perfect_percentage_values[ssr_len] = perfect_percentage;
	}


        for ( unsigned int start=0; start < DNA_len; start++){
                for (unsigned short ssr_len=1; ssr_len<= unitlen_p ; ssr_len++){ // unitlen_p : longest length of unit, default: 6

			int insertion = insertion_values[ssr_len]; // Optimization 1
			float perfect_percentage = perfect_percentage_values[ssr_len]; // Optimization 1

			unsigned short repeat=1;
			unsigned int start_new=start+ssr_len;

			string ssr_region; // used for output
			string_view left_unit;
			if (start+ssr_len < DNA_len) {
				left_unit=string_view(DNA).substr(start, ssr_len); // used for output
			}
			else{
				break;
			}

			ssr_region+=left_unit; // used for output
			ssr_region+=" "; // used for output
			int m=ssr_len;
			int n=ssr_len+insertion;
			int perfect_copy=0;

                        for ( ; ;++repeat ){
				string_view right_unit;
				if( start_new+ssr_len+insertion < DNA_len ){
					right_unit=DNA.substr( start_new, ssr_len+insertion );
				}
				else{
					break;
				}
				vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

				int max_score = 0;
				int end_pos_right = 0;

				for (int i = 1; i <= m; ++i) {

					//int start_j = max(1, end_pos_right - 2);
					//int end_j = min(n, end_pos_right + 2);
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
				//cout << start_new << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << endl;
				int i = ssr_len, j = end_pos_right;
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

				if( end_pos_right == ssr_len && matches == ssr_len ){
					perfect_copy++;
				}

				//cout << "######" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << "\t" << "repeat>cutoff:"<< static_cast<double>(repeat-perfect_copy)/repeat << "\t" << "repeat<cutoff:" << static_cast<double>(repeat-perfect_copy)/cutoff_array_main[ssr_len-1] << endl;

				if( ssr_len == 1 ){
					if( matches == 0 ){
						break;
					}
					else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/cutoff_array_main[ssr_len-1] > 1-perfect_percentage ){
						break;
					}
					else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/repeat > 1-perfect_percentage ){
						break;
					}
					ssr_region+=DNA.substr(start_new,end_pos_right);
					ssr_region+=" ";
					start_new+=end_pos_right;
                                }
				else if( ssr_len > 1 && ssr_len < 5 ){
                                        if( matches < ssr_len-insertion){
                                                break;
                                        }
                                        else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/cutoff_array_main[ssr_len-1] > 1-perfect_percentage ){
                                                ssr_region+=DNA.substr(start_new,end_pos_right);
                                                ssr_region+=" ";
                                                start_new+=end_pos_right;
                                                //cout << "!!!!!!!!!" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << endl;
                                                break;
                                        }
                                        else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/repeat > 1-perfect_percentage ){
                                                ssr_region+=DNA.substr(start_new,end_pos_right);
                                                ssr_region+=" ";
                                                start_new+=end_pos_right;
                                                //cout << "?????????" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << endl;
                                                break;
                                        }
                                        ssr_region+=DNA.substr(start_new,end_pos_right);
                                        ssr_region+=" ";
                                        start_new+=end_pos_right;
				}
				else if( ssr_len == 6 || ssr_len == 5 ){
                                        if( matches <=3  ){
                                                break;
                                        }
                                        else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/cutoff_array_main[ssr_len-1] > 1-perfect_percentage ){
                                                ssr_region+=DNA.substr(start_new,end_pos_right);
                                                ssr_region+=" ";
                                                start_new+=end_pos_right;
                                                //cout << "!!!!!!!!!" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << endl;
                                                break;
                                        }
                                        else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/repeat > 1-perfect_percentage ){
                                                ssr_region+=DNA.substr(start_new,end_pos_right);
                                                ssr_region+=" ";
                                                start_new+=end_pos_right;
                                                //cout << "?????????" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << endl;
                                                break;
                                        }
                                        ssr_region+=DNA.substr(start_new,end_pos_right);
                                        ssr_region+=" ";
                                        start_new+=end_pos_right;
				}	
                                else{ // ssr_len > 2
					if( matches < ssr_len*0.6 ){
						break;
					}
					else if( repeat < cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/cutoff_array_main[ssr_len-1] > 1-perfect_percentage ){
						ssr_region+=DNA.substr(start_new,end_pos_right);
						ssr_region+=" ";
						start_new+=end_pos_right;
						//cout << "!!!!!!!!!" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << endl;
						break;
					}
					else if( repeat >= cutoff_array_main[ssr_len-1] && static_cast<double>(repeat-perfect_copy)/repeat > 1-perfect_percentage ){
						ssr_region+=DNA.substr(start_new,end_pos_right);
						ssr_region+=" ";
						start_new+=end_pos_right;
						//cout << "?????????" << start << "\t" << left_unit << "\t" << right_unit << "\t" << end_pos_right << "\t" << matches << "\t" << repeat << "\t" << perfect_copy << endl;
						break;
					}
					ssr_region+=DNA.substr(start_new,end_pos_right);
					ssr_region+=" ";
					start_new+=end_pos_right;

                                }
                        }

			if( repeat >= cutoff_array_main[ssr_len-1] && perfect_copy+1 >= repeat*perfect_percentage ){
				if( (arg == "fuzzy_vntr_default" && ssr_len > 7) || arg == "fuzzy_str_default" || arg == "fuzzy_costom"){
				if( revercomple_p > 0 ){
					string ssr_recom;
					ssr_recom=left_unit;
					reverse_complement(ssr_recom);
					//left_unit+="\t";
					//left_unit+=ssr_recom;
				}
				
				if( flanking_p == 0 ){
					cout << id << "\t" << start+1 << "\t" << start_new << "\t" << left_unit << "\t" << repeat << "\t" << start_new-start;
					cout << "\t" << ssr_region ;
					cout << "\n";
					start+=(start_new-start);
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
						start+=(start_new-start);
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
                                                start+=(start_new-start);
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
						start+=(start_new-start);
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
						start+=(start_new-start);
						break;
					}
				}
				}
			}
                }
        }
}
