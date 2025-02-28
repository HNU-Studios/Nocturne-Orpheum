#include "inventory.h"
using namespace std;
class sector{
    string Name;
    vector<item> Ground;
    int MinLevel;
    // bool in;
    int size;
    public:
        // sector(string n, vector<item> g, int level, bool In): Name(n), Ground(g), MinLevel(level), in(In){};
        sector(string n, vector<item> g, int level): Name(n), Ground(g), MinLevel(level), size(5)/*, in(false)*/{};
        sector(string n, vector<item> g, int level, int s): Name(n), Ground(g), MinLevel(level), size(s){};
};