#include <string>
#include <map>
// using namespace std;
class enemy {
    std::string name;
    int speed;
    int power;
    // std::map<std::string, int> buffs;
public:
    enemy(std::string n, int s, int p): name(n), speed(s), power(p) {};
    // enemy(std::string n, int s, int p, std::map<std::string, int> b): name(n), speed(s), power(p), buffs(b) {};
    string getName(){return name;}
    int getSpeed(){return speed;}
    int getPower(){return power;}
    // std::map<std::string, int> getBuffs(){return buffs;}
};