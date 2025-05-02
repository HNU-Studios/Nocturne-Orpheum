#include <string>
#include <map>
class race {
    std::string name;
    std::map<std::string, int> buffs;
    public:
        race(std::string n): name(n){};
        int getAtk() {
            return buffs["ATK"];
        }
        
};