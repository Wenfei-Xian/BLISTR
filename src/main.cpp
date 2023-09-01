#include "main.h"

int main( int argc, char *argv[] ){
	
	if(argc ==  1 ){
		return usage();
	}

	if( strcmp(argv[1], "fuzzy_costom" ) == 0 || strcmp(argv[1], "fuzzy_vntr_default" ) == 0 || strcmp(argv[1], "fuzzy_str_default" ) == 0 ){
		return fuzzy_model( argc-1, argv+1 );
	}
	else if( strcmp( argv[1], "perfect_costom") == 0 || strcmp( argv[1], "perfect_vntr_default") == 0 || strcmp( argv[1], "perfect_str_default") == 0  ){
		return perfect_model( argc-1, argv+1 );
	}
	else{
		cerr << "Command can't recognized" << " " << argv[1] << endl;
		return usage();
	}

}

string read_gz_line(gzFile &gz_input) {
    char buffer[1024];
    string line;
    while(true) {
        if(gzgets(gz_input, buffer, sizeof(buffer)) == NULL) {
	    return "";
        }
        line += buffer;
        if (line.back() == '\n') {
            line.pop_back();
            return line;
        }
    }
}

int usage(){
	cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
	cout << "Usage: BLISTR <command> [options]" << endl;
	cout << "Command:" << endl;
	cout << "	perfect_str_default <options>" << endl;
	//cout << "	perfect_vntr_default <options>" << endl;
	cout << "	perfect_costom <options>" << endl;
	cout << "	fuzzy_str_default <options>" << endl;
	//cout << "	fuzzy_vntr_default <options>" << endl;
	cout << "	fuzzy_costom <options>" << endl;
	return 0;
}

string getFirstArgument(int argc, char* argv[]) {
	return string(argv[0]);
}

int perfect_model( int argc, char *argv[] ){
	int a;
	int unitlen_p=6;
	int up_p=1;
	string fasta;
	int para=0;
	unsigned int flanking_p=0;
	int revercomple_p=0;
	string cutoffunit_p="10,5,4,3,2,2";
	string arg;
	arg=getFirstArgument(argc, argv);

	if( arg == "perfect_vntr_default" ){
		unitlen_p=200;
		cutoffunit_p="10,5,4,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2";
	}

	while(( a=getopt(argc, argv, "f:l:L:s:u:r:n:c:")) >= 0){ // :一个:表示必须有后接参数，两个::表示可选参数，没有:表示不用接参数
		if( a == 'f'){
			fasta = optarg;
			para++;
		}
		else if( a == 'l'){
			unitlen_p = atof(optarg);//atof 字符串变浮点
			para++;
		}
		else if( a == 's'){
			flanking_p = atof(optarg);
			para++;
		}
		else if( a == 'u' ){
			up_p = atof(optarg);
			para++;
		}
		else if( a == 'r' ){
			revercomple_p = atof(optarg);
			para++;
		}
		else if( a == 'c' ){
			cutoffunit_p = optarg;
			para++;
		}
	}

	if( para == 0 ){
		if( arg == "perfect_str_default"){
			cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
			cout << "Usage: BLISTR perfect_str_default <options>" << endl;
			cout << "	unit length range is 1-6bp and copy number threshold is 10,5,4,3,2,2" << endl;
		}
		//else if( arg == "perfect_vntr_default"){
		//	cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
		//	cout << "Usage: BLISTR perfect_vntr_default <options>" << endl;
		//	cout << "	unit length range is 7-200bp and 10,5,4,3,2,2,2,2,2,2,2...." << endl;
		//}
		else if( arg == "perfect_costom"){
			cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
			cout << "Usage: BLISTR perfect_costom <options>" << endl;
		}
	        cout << "Options:" << endl;
        	cout << "       -f string     fasta format file (mandatory)" << endl;
		if( arg == "perfect_costom" ){
			cout << "       -l int        maximum length of SSR unit, example: -l 10 (mandatory)" << endl;
			cout << "       -c string     copy shreshold for each unit, example: -c 10,5,4,3,2,2,2,2,2,2 (mandatory)" << endl;
		}
		cout << "       -s int        whether output the flanking sequence of SSR region (default value: 0 -> don't output; length of flanking sequences -> output)" << endl;
		cout << "       -u int        whether replace all letters with uppercase letters (default value: 0 -> don't replace; 1 -> replace)" << endl;
		cout << "       -r int        whether output the reverse complement sequence (default value: 0 -> don't output; 1 -> output)" << endl; 
		return -1;
	}
	
	ifstream input;
	gzFile gz_input=nullptr;

	string file_extension = fasta.substr(fasta.size() - 3); // Take last 3 characters of filename
	bool is_gzip = (file_extension == ".gz");

	if (is_gzip) {
		gz_input = gzopen(fasta.c_str(), "r");
		if (!gz_input) {
			cerr << "Can't open " << fasta << endl;
			return -1;
		}
	}
	else {
        	input.open(fasta);
        	if (!input.good()) {
            	cerr << "Can't open " << fasta << endl;
            	return -1;
        	}
    	}	

	int num=count(cutoffunit_p.begin(),cutoffunit_p.end(),',');
	
	if( num+1 != unitlen_p ){
		cerr << "Maximum lenght of SSR unit is: " << unitlen_p << ", but the number of lenght cutoff for each unit is: " << num+1 << endl;
		return -1;
	}

	if( flanking_p > 0 && revercomple_p > 0){
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" "unit_reverse_complement" << "\t" << "Repeats" << "\t" << "SSR_region_length" << "\t" <<  "SSR_region" << "\t" << "SSR_region_flanking" << endl;
	}
	else if( flanking_p > 0 && revercomple_p == 0 ){
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" << "Repeats" << "\t" << "SSR_region_length" << "\t" << "SSR_region" << "\t" << "SSR_region_flanking" << endl;
	}
	else if( flanking_p == 0 && revercomple_p > 0 ){
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" "unit_reverse_complement" << "\t" << "Repeats" << "\t" << "SSR_region_length" << "\t" << "SSR_region" << endl;
	}
	else {
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" << "Repeats" << "\t" << "SSR_region_length" << "\t" << "SSR_region" << endl;
	}

	string line, id, DNA;
	if (is_gzip) {
		gz_input = gzopen(fasta.c_str(), "r");
		if (!gz_input) {
			cerr << "Can't open " << fasta << endl;
			return -1;
		}
		while ( true ) {
			line = read_gz_line(gz_input);
			if (line.empty()) {
				if( !id.empty() ){
					find_perfect(DNA, id, unitlen_p, flanking_p, up_p, revercomple_p, cutoffunit_p, arg);
				}
				break;
			}

			if( line[0] == '>' ){
				if( !id.empty() ){
					find_perfect( DNA, id, unitlen_p, flanking_p, up_p, revercomple_p, cutoffunit_p, arg);
				}
				id=line.substr(1);
				DNA.clear();
			}
			else{
				DNA+=line;
			}
		}
		gzclose(gz_input);
		return 0;
	}
	else{
		while( getline(input, line) ){
			if( line.empty() ){
				continue;
			}
			if( line[0] == '>' ){
				if( !id.empty() ){
					//find_perfect( DNA, id, unitlen_p, ssrlen_p, flanking_p, up_p, revercomple_p,mincopy_p,cutoffunit_p);
					find_perfect( DNA, id, unitlen_p, flanking_p, up_p, revercomple_p, cutoffunit_p, arg);
				}
				id=line.substr(1);
				DNA.clear();
			}
			else{
				DNA+=line;
			}
		}
		if( !id.empty() ){
			//find_perfect( DNA, id, unitlen_p, ssrlen_p, flanking_p, up_p, revercomple_p,mincopy_p,cutoffunit_p);
			find_perfect( DNA, id, unitlen_p, flanking_p, up_p, revercomple_p, cutoffunit_p, arg);
		}
		return 0;
	}
}

int fuzzy_model( int argc, char *argv[] ){
	
	int a;
	int unitlen_p=6;
	int up_p=0;
	int flanking_p=0;
	int revercomple_p=0;
	int distance=-6;
	string edit="1,1,1,1,1,1";
	string cutoffunit_p="12,6,4,3,2,2";
	string unperfect_percentage_p="0.3,0.4,0.5,0.5,0.5,1";
	string arg;
	string fasta;
	arg=getFirstArgument(argc, argv);
	if( arg == "fuzzy_vntr_default" ){
		unitlen_p=200;
		cutoffunit_p="10,5,4,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2";
	}

	int para=0;
	
	while(( a=getopt( argc, argv, "f:l:s:u:r:c:p:e:d:")) >= 0 ){

		if( a == 'f' ){
			fasta=optarg;
			para++;
		}
		else if( a == 'c' ){
			cutoffunit_p=optarg;
			para++;
		}
		else if( a == 'l'){
			unitlen_p=atof(optarg);
			para++;
		}
		else if( a == 'u'){
			up_p=atof(optarg);
			para++;
		}
		else if( a == 's'){
			flanking_p=atof(optarg);
			para++;
		}
		else if( a == 'r'){
			revercomple_p=atof(optarg);
			para++;
		}
		else if( a == 'p'){
			unperfect_percentage_p=optarg;
			para++;
		}
		else if( a == 'e' ){
			edit=optarg;
			para++;
		}
		else if( a == 'd' ){
			distance=atof(optarg);
			para++;
		}
	}

        if( para == 0 ){
                if( arg == "fuzzy_str_default"){
                        cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
                        cout << "Usage: BLISTR fuzzy_str_default <options>" << endl;
                        cout << "	unit length range is 1-6bp, copy number threshold is 12,6,4,3,2,2, percentage of imperfect threshold is 0.3,0.4,0.5,0.5,0.5,1, edit distance of each unit is 1,1,1,1,1,1" << endl;
                }
                //else if( arg == "fuzzy_vntr_default"){
                //        cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
                //        cout << "Usage: BLISTR fuzzy_vntr_default <options>" << endl;
                //        cout << "	unit length range is 7-200bp, copy number threshold is 10,5,4,3,2,2,2,2,2,2..., percentage of imperfect threshold is 0.3,0.4,0.5,0.5,0.5,1,1,1,1,1..." << endl;
                //}
                else if( arg == "fuzzy_costom"){
                        cout << "BLISTR: BLurry Imperfect Short Tandem Repeats" << endl;
                        cout << "Usage: BLISTR fuzzy_costom <options>" << endl;
                }
                cout << "Options:" << endl;
		cout << "	-f string     fasta format file (mandatory)" << endl;
                if( arg == "fuzzy_costom" ){
                        cout << "	-l int        maximum length of SSR unit, example: -l 6 (mandatory)" << endl;
                        cout << "	-c string     copy shreshold for each unit, example: -c 12,6,4,3,2,2 (mandatory)" << endl;
			cout << "	-p string     percentage of imperfect units, example: -p 0.3,0.4,0.5,0.5,0.5,1 (mandatory)" << endl;
                	cout << "	-e string     edit distance for each unit, example: -e 1,1,1,1,1,2 (mandatory)" << endl;
			cout << "	-d int        Maximum distance between two seperate STR regions, using negative value for overlapping STRs, example: -d -4" << endl;
		}
		cout << "	-u int        whether to replace all letters with uppercase letters (default value: 0 -> don't replace; 1 -> replace)" << endl;
		cout << "	-s int        whether output the flanking sequnce of SSR region (default value: 0 -> don't output; length of flanking sequences -> output)" << endl;
		cout << "	-r int        whether output the reverse complement sequence (defalut value: 0 -> don't output; 1 -> output)" << endl; 
		return -1;
        }

	//ifstream input( fasta );
	ifstream input;
	gzFile gz_input = nullptr;

	string file_extension = fasta.substr(fasta.size() - 3);
	bool is_gzip = (file_extension == ".gz");

	if (is_gzip) {
		gz_input = gzopen(fasta.c_str(), "r");
		if (!gz_input) {
			cerr << "Can't open " << fasta << endl;
			return -1;
		}
	}else {
		input.open(fasta);
		if (!input.good()) {
			cerr << "Can't open " << fasta << endl;
			return -1;
		}
	}

	int num=count(cutoffunit_p.begin(),cutoffunit_p.end(),',');
	if( num+1 != unitlen_p ){
		cerr << "Maximum lenght of SSR unit is: " << unitlen_p << ", but the number of lenght cutoff for each unit is: " << num+1 << endl;
		return -1;
	}


	if( flanking_p > 0 && revercomple_p > 0){
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" <<  "unit_reverse_complement"<< "\t" << "Repeats" << "\t" << "SSR_region_length" << "\t" << "SSR_region" << "\t" << "SSR_region_flanking" << endl;
	}
	else if( flanking_p > 0 && revercomple_p == 0 ){
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" << "Repeats" << "\t" << "SSR_region_length" << "\t" << "SSR_region" << "\t" << "SSR_region_flanking" << endl;
	}
	else if( flanking_p == 0 && revercomple_p > 0 ){
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" << "SSR_reverse_complement" << "\t" <<  "Repeats" << "\t" << "SSR_region_length" << "\t" << "SSR_region" << endl;
	}
	else{
		cout << "#Chr/Scaffold" << "\t" << "Start" << "\t" << "End" << "\t" << "unit" << "\t" << "repeats" << "\t" << "perfect_repeats" << "\t" << "SSR_region"  << endl;
	}

	string line, id, DNA;

	if(is_gzip){
		gz_input = gzopen(fasta.c_str(), "r");
		if( !gz_input ){
			cerr << "Can't open " << fasta << endl;
			return -1;
		}
		while( true ){
			line = read_gz_line(gz_input);
			if (line.empty()) {
				if( !id.empty() ){
					find_fuzzy( DNA, id, unitlen_p, up_p, flanking_p, revercomple_p, cutoffunit_p, arg, unperfect_percentage_p, edit, distance);
				}
				break;
			}
			if( line[0] == '>' ){
				if( !id.empty() ){
					find_fuzzy( DNA, id, unitlen_p, up_p, flanking_p, revercomple_p, cutoffunit_p, arg, unperfect_percentage_p, edit, distance);
				}
				id=line.substr(1);
				DNA.clear();
			}
			else{
				DNA+=line;
			}
		}
		gzclose(gz_input);
		return 0;
	}
	else{
        	while( getline(input, line) ){//AUG 23
                	
			if( line.empty() ){
                        	continue;
                	}
                	if( line[0] == '>' ){
                        	if( !id.empty() ){
					find_fuzzy( DNA, id, unitlen_p, up_p, flanking_p, revercomple_p, cutoffunit_p, arg, unperfect_percentage_p, edit, distance);
				}
                        	id=line.substr(1);
                        	DNA.clear();
                	}
                	else{
                        	DNA+=line;
                	}
        	}

        	if( !id.empty() ){
			find_fuzzy( DNA, id, unitlen_p, up_p, flanking_p, revercomple_p, cutoffunit_p, arg, unperfect_percentage_p, edit, distance);
        	}
		return 0;
	}
}
