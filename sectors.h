#include "sector.h"
#include <string>
vector<item> emptyGround;
sector Andris2 = sector("Andris-two", emptyGround, 1);
sector Andris = sector("Andris", emptyGround, 1, "Andris-two", "", "", "");
vector <sector> sects = {Andris, Andris2};