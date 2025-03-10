#include "inventory.h"
class sector{
    std::string Name;
    vector<item> Ground;
    int MinLevel;
    // bool in;
    int size;
    std::string North = "";
    std::string South = "";
    std::string East = "";
    std::string West = "";
    public:
        
        // sector(string n, vector<item> g, int level, bool In): Name(n), Ground(g), MinLevel(level), in(In){};
        sector(string n, vector<item> g, int level): Name(n), Ground(g), MinLevel(level), size(5)/*, in(false)*/{};
        sector(string n, vector<item> g, int level, int s): Name(n), Ground(g), MinLevel(level), size(s){};
        sector(string n, vector<item> g, int level, string N, string S, string E, string W): Name(n), Ground(g), MinLevel(level), size(5), North(N), South(S), East(E), West(W)/*, in(false)*/{};
        sector(string n, vector<item> g, int level, int s, string N, string S, string E, string W): Name(n), Ground(g), MinLevel(level), size(s), North(N), South(S), East(E), West(W){};
        std::string getName(){
            return Name;
        }
        std::string getNorth(){
            return North;
        }
        std::string getSouth(){
            return South;
        }
        std::string getEast(){
            return East;
        }
        std::string getWest(){
            return West;
        }
        void putOnGround(item toPut){
            Ground.push_back(toPut);
        }
        vector<item> getGround(){
            return Ground;
        }
};