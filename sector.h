#include "inventory.h"
using namespace std;
class sector{
    string Name;
    vector<item> Ground;
    int MinLevel;
    bool in;
    public:
        sector(string n, vector<item> g, int level, bool In): Name(n), Ground(g), MinLevel(level), in(In){};
        sector(string n, vector<item> g, int level): Name(n), Ground(g), MinLevel(level), in(false){};
};