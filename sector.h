#include "inventory.h"
using namespace std;
class sector{
    string Name;
    vector<item> Ground;
    int MinLevel;
    public:
        sector(string n, vector<item> g, int level): Name(n), Ground(g), MinLevel(level){};
};