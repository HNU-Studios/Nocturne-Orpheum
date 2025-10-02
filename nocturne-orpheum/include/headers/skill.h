#include <string>
class skill {
    std::string name;
    int power;
    int uses;
    std::string kind;
public:
    skill(std::string n, int p, std::string k) : name(n), power(p), kind(k) {};
    std::string getName() {
        return name;
    }
    int getPower() {
        return power;
    }
    int getUses() {
        return uses;
    }
    std::string getKind() {
        return kind;
    }
};