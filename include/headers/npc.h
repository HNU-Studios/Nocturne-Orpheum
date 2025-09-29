#include <string>

// std::string name, type;
class npc {
  std::string name, type;
public:
  npc(std::string n, std::string t): name(n), type(t){}
  std::string getName() { return name; }
};
