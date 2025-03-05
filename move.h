#include <iostream>
#include <cctype>
using namespace std;
int speed = 1;
pair <int, int> center = {3, 3};
pair <int, int> currCords = {3, 3};
char Move(){
    string option;
    cout << "Enter the direction to move: ";
    cin >> option;
    if ((toupper(option[0]) == 'U') || (toupper(option[0]) == 'N')){
        currCords.second++;
        if(currCords.second == 6){
            currCords = {currCords.first, 1};
            return 'n';
        }
    }
    else if ((toupper(option[0]) == 'D') || (toupper(option[0]) == 'S')){
        currCords.second--;
        if (currCords.second == -1){
            currCords = {currCords.first, 1};
            return 's';
        }
    }
    else if ((toupper(option[0]) == 'L') || (toupper(option[0]) == 'W')){
        currCords.first--;
        if (currCords.first == -1){
            currCords = {1, currCords.second};
            return 'w';
        }
    }
    else if ((toupper(option[0]) == 'R') || (toupper(option[0]) == 'E')){
        currCords.first++;
        if (currCords.first == 6){
            currCords = {1, currCords.second};
            return 'e';
        }
    }
    return ' ';
}