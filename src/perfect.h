#include <string>
#include "sequence.format.h"
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <nmmintrin.h>
#include <vector>
#include <regex>
#include <sstream>
#include <string_view>
using namespace std;

double vector_dot(uint32_t len,const float* a,const float* b);

void find_perfect(string DNA, string id, int unitlen_p, unsigned int flanking_p, int up_p, int revercomple_p, string cutoffunit_p, string arg );
