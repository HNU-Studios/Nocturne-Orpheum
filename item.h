#include <string>
#include <iostream>
class item {
    std::string name;
    std::string type;
    int power;
public:
    // Constructor
    item(std::string n, std::string t, int p) : name(n), type(t), power(p) {}
    item() : name(""), type(""), power(0) {}
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
    // Comparison operator for std::map
    bool operator<(const item& other) const {
        // Define comparison logic. This example compares items by their name.
        return name < other.name;
        // You can also add logic to compare by type and power if needed.
    }
};
        // void buffs(string stat, int amount){
        //     buffs[stat] = amount;
        // }
        // int getBuff(string stat){
        //     return buffs[stat];
        // }
#include <string>
#include <iostream>
class item {
    std::string name;
    std::string type;
    int power;
public:
    // Constructor
    item(std::string n, std::string t, int p) : name(n), type(t), power(p) {}
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
    // Comparison operator for std::map
    bool operator<(const item& other) const {
        // Define comparison logic. This example compares items by their name.
        return name < other.name;
        // You can also add logic to compare by type and power if needed.
    }
};
        // void buffs(string stat, int amount){
        //     buffs[stat] = amount;
        // }
        // int getBuff(string stat){
        //     return buffs[stat];
        // }