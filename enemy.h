#include <string>
#include <map>
#include "item.h"
class enemy {
    std::string name;
    int speed;
    int power;
    std::map<std::string, int> loot;
    int health;
public:
    enemy(std::string n, int s, int p): name(n), speed(s), power(p), loot({{"Gold", 5}, {"EXP", 50}}), health(5) {};
    enemy(std::string n, int s, int p, std::map<std::string, int> l): name(n), speed(s), power(p), loot(l), health(5) {};
    enemy(std::string n, int s, int p, std::map<std::string, int> l, int h): name(n), speed(s), power(p), loot(l), health(h) {};
    string getName(){return name;}
    int getSpeed(){return speed;}
    int getPower(){return power;}
    int getLoot(item i){}
};