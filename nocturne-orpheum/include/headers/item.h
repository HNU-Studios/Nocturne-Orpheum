#include <string>
#include <map>
#include <iostream>
class item {
    std::string name;
    std::string type;
    int power;
    std::map<std::string, int> buffs;
    bool hasSet;
public:
    // Constructor
    item() : name(""), type(""), power(0) {}
    item(std::string n, std::string t, int p) : name(n), type(t), power(p) {}
    item(std::string n, std::string t, std::map<std::string, int> b) : name(n), type(t), buffs(b) {}
    item(std::string n, std::string t, int p, std::map<std::string, int> b) : name(n), type(t), power(p), buffs(b) {}
    item(std::string n, std::string t, int p, std::map<std::string, int> b, bool h) : name(n), type(t), power(p), buffs(b), hasSet(h) {}
    item(std::string n, std::string t, int p, bool h) : name(n), type(t), power(p), hasSet(h) {}
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
    bool operator!=(const item& other) const {
        return name != other.name || type != other.type || power != other.power || buffs != other.buffs;
    }
    bool operator==(const item& other) const {
        return name == other.name && type == other.type && power == other.power && buffs == other.buffs;
    }
    bool operator<(const item& other) const {
      if (name != other.name)
        return name < other.name;
      if (type != other.type)
        return type < other.type;
      if (power != other.power)
        return power < other.power;
      return buffs < other.buffs;
    }

};
