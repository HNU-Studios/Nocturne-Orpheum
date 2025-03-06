#include <iostream>
#include <cctype>
using namespace std;
int speed = 1;
pair <int, int> center = {3, 3};
pair <int, int> currCoords = {3, 3};
char Move(){
    string option;
    cout << "Enter the direction to move: ";
    cin >> option;
    if ((toupper(option[0]) == 'U') || (toupper(option[0]) == 'N')){
        currCoords.second++;
        if(currCoords.second == 6){
            currCoords = {currCoords.first, 1};
            return 'n';
        }
    }
    else if ((toupper(option[0]) == 'D') || (toupper(option[0]) == 'S')){
        currCoords.second--;
        if (currCoords.second == 0){
            currCoords = {currCoords.first, 1};
            return 's';
        }
    }
    else if ((toupper(option[0]) == 'L') || (toupper(option[0]) == 'W')){
        currCoords.first--;
        if (currCoords.first == 0){
            currCoords = {1, currCoords.second};
            return 'w';
        }
    }
    else if ((toupper(option[0]) == 'R') || (toupper(option[0]) == 'E')){
        currCoords.first++;
        if (currCoords.first == 6){
            currCoords = {1, currCoords.second};
            return 'e';
        }
    }
    else{
        return ' ';
    }
    return ' ';
}
void getCoords(){
    cout << "Your current coordinates are (" << currCoords.first << ", " << currCoords.second << ").";
}
