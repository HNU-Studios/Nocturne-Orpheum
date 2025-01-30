#include <string>
#include <vector>
using std::string;
class item{
    string name;
    string type;
    map<string, int> buffs;
    int power;
    public:
        item(string n, string t, int p):
            name(n), type(t), power(p) {}
        string getName() const{
            return name;
        }
        string getType() const{
            return type;
        }
        int getPower() const{
            return power;
        }
        void buffs(string stat, int amount){
            buffs[stat] = amount;
        }
        int getBuff(string stat){
            return buffs[stat];
        }
};