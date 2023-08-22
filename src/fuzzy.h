#include <string>
#include "sequence.format.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string_view>
#include <cmath>
//#include "/tmp/global2/wxian/software/WFA2-lib/bindings/cpp/WFAligner.hpp"
#include <cctype>
#include <memory>
#include <cstring>
using namespace std;
//using namespace wfa;
//int optimizedDP(std::string_view left, std::string_view right, int maxInsertLength, int &matchingBases, int &editDistance);
//int optimizedDP( string_view left, string_view right, int maxInsertLength, int &matchingBases, int &editDistance, constexpr int m, constexpr int n);
void find_fuzzy(string DNA, string id, int unitlen_p, int up_p, unsigned int flanking_p, int revercomple_p, string cutoffunit_p, string arg, string unperfect_percentage_p );
