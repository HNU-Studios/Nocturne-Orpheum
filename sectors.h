#include "sector.h"
#include <string>
using namespace std;
vector<item> emptyGround;
sector Andris2 = sector("Andris part two", emptyGround, 1);
sector Andris = sector("Andris", emptyGround, 1, "Andris part two", "", "", "");
vector <sector> sects = {Andris, Andris2};