#include <string>
#include <iostream>
class item {
    std::string name;
    std::string type;
    int power;
    map<string, int> buffs;
public:
    // Constructor
    item(std::string n, std::string t, int p) : name(n), type(t), power(p) {}
    item() : name(""), type(""), power(0) {}
    item(std::string n, std::string t, int p, map<string, int> b) : name(n), type(t), power(p), buffs(b) {}
    // Getter methods
    std::string getName() const {
        return name;
    }
    std::string getType() const {
        return type;
    }
    int getPower() const {
        return power;
    }
    bool operator<(const item& other) const {
        return name < other.name;
    }
};