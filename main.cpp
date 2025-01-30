#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "item.h"
#include "inventory.h"
using namespace std;
int main(){
    cout << "Welcome, adventurer.\nEnter your name here: ";
    string name;
    cin >> name;
    cout << "Hello, " << name << ". Welcome to the world. You start as a human with all your stats set to 1, HP at 10, but as time goes\non, you can level up your stats, learn skills, collect weapons, and find gear. Gear and weapons can also have their\nown buffs and skills as you get further in the game. Here, take this [BASIC DULL SWORD] (press p to pick up).\n";
    ground.push_back(item("Dull sword", "Weapon", 1));
    while (true){
        char option;
        cout << "Enter an option (? or h for help, q to quit): ";
        cin >> option;
        if (option == 'i') inventory();
        else if (option == 'h' || option == '?') help();
        else if (option == 's') stats();
        else if (option == 'p') pick();
        else if (option == 'e') equip();
        else if (option == 'q') break;
        else continue;
    }
    return 0;
}