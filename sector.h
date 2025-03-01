#include "inventory.h"
using namespace std;
class sector{
    string Name;
    vector<item> Ground;
    int MinLevel;
    // bool in;
    int size;
    sector north(string, vector<item> ground, int);
    sector south(string, vector<item> ground, int);
    sector east(string, vector<item> ground, int);
    sector west(string, vector<item> ground, int);
    public:
        // sector(string n, vector<item> g, int level, bool In): Name(n), Ground(g), MinLevel(level), in(In){};
        sector(string n, vector<item> g, int level): Name(n), Ground(g), MinLevel(level), size(5)/*, in(false)*/{};
        sector(string n, vector<item> g, int level, int s): Name(n), Ground(g), MinLevel(level), size(s){};
};