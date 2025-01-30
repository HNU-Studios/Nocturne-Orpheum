#include <string>
using std::string;
class item{
    string name;
    string type;
    int power;
    public:
        item(string n, string t, int p):
            name(n), type(t), power(p) {}
        string getName(){
            return name;
        }
        string getType(){
            return type;
        }
        int getPower(){
            return power;
        }
};