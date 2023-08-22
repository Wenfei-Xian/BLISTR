#include "sequence.format.h"

void lower2up( char &seq ){
	if( seq == 'a' ){
		seq = 'A';
	}
	else if( seq == 't' ){
		seq = 'T';
	}
	else if( seq == 'c' ){
		seq = 'C';
	}
	else if( seq == 'g' ){
		seq = 'G';
	}
}

void reverse_complement( string &ssr ){
	reverse( ssr.begin(), ssr.end() );
	for ( short i=ssr.length()-1; i>-1; i-- ){
		if( ssr[i] == 'A' ){
			ssr[i] = 'T';
		}
		else if( ssr[i] == 'T' ){
			ssr[i] = 'A';
		}
		else if( ssr[i] == 'C' ){
			ssr[i] = 'G';
		}
		else if( ssr[i] == 'G' ){
			ssr[i] = 'C';
		}
	}
}

void complement( char &ssr_single ){
	if( ssr_single == 'A' ){
		ssr_single = 'T';
	}
	else if( ssr_single == 'T' ){
		ssr_single = 'A';
	}
	else if( ssr_single == 'C' ){
		ssr_single = 'G';
	}
	else if( ssr_single == 'G' ){
		ssr_single = 'C';
	}
}
