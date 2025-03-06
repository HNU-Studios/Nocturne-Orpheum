#include "inventory.h"
using namespace std;
class sector{
    string Name;
    vector<item> Ground;
    int MinLevel;
    // bool in;
    int size;
    string North = "";
    string South = "";
    string East = "";
    string West = "";
    public:
        
        // sector(string n, vector<item> g, int level, bool In): Name(n), Ground(g), MinLevel(level), in(In){};
        sector(string n, vector<item> g, int level): Name(n), Ground(g), MinLevel(level), size(5)/*, in(false)*/{};
        sector(string n, vector<item> g, int level, int s): Name(n), Ground(g), MinLevel(level), size(s){};
        sector(string n, vector<item> g, int level, string N, string S, string E, string W): Name(n), Ground(g), MinLevel(level), size(5), North(N), South(S), East(E), West(W)/*, in(false)*/{};
        sector(string n, vector<item> g, int level, int s, string N, string S, string E, string W): Name(n), Ground(g), MinLevel(level), size(s), North(N), South(S), East(E), West(W){};
        string getName(){
            return Name;
        }
        string getNorth(){
            return North;
        }
        string getSouth(){
            return South;
        }
        string getEast(){
            return East;
        }
        string getWest(){
            return West;
        }
        void putOnGround(item toPut){
            Ground.push_back(toPut);
        }
        vector<item> getGround(){
            return Ground;
        }
};