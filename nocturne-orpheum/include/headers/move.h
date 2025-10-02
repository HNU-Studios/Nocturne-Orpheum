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
            currCoords = {currCoords.first, 5};
            return 's';
        }
    }
    else if ((toupper(option[0]) == 'L') || (toupper(option[0]) == 'W')){
        currCoords.first--;
        if (currCoords.first == 0){
            currCoords = {5, currCoords.second};
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
        cout << "That isn't a valid direction!";
        return 'S';
    }
    return ' ';
}
char Move(char option) {
  if ((toupper(option) == 'U') || (toupper(option) == 'N')){
    cout << "Current coords before moving: " << currCoords.first << ", " << currCoords.second << ".\n";
    currCoords.second++;
    if(currCoords.second == 6) {
      cout << "Hit north boundary!\n";
      currCoords = {currCoords.first, 1};
      return 'n';
    }
  }
  else if ((toupper(option) == 'D') || (toupper(option) == 'S')){
    currCoords.second--;
    if (currCoords.second == 0){
      currCoords = {currCoords.first, 5};
      return 's';
    }
  }
  else if ((toupper(option) == 'L') || (toupper(option) == 'W')){
    currCoords.first--;
    if (currCoords.first == 0){
      currCoords = {5, currCoords.second};
      return 'w';
    }
  }
  else if ((toupper(option) == 'R') || (toupper(option) == 'E')){
    currCoords.first++;
    if (currCoords.first == 6){
      currCoords = {1, currCoords.second};
      return 'e';
    }
  }
  else{
    cout << "That isn't a valid direction!";
    return 'S';
  }
  return ' ';
}
void getCoords(){
    cout << "Your current coordinates are (" << currCoords.first << ", " << currCoords.second << ").";
}
