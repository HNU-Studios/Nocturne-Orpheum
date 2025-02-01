#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "inventory.h"
using namespace std;
void help(){ // Prints the help menu
    cout << "HELP MENU\n\ni: open inventory\n?/ h: open this help menu\ne: equip an item\nu: unequip an item\ns: view stats\np: pick up an item (shows a menu if multiple)\n\n";
}
void stats(){ // Prints a user's stats
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}
int main(){
    cout << "Welcome, adventurer.\nEnter your name here: ";
    string name;
    cin >> name;
    cout << "Hello, " << name << ". Welcome to the world.\n\nYou start as a human with all your stats set to 1, HP at 10, but as time goes on, you can level up your stats, learn skills, collect weapons, and find gear.\n\nGear and weapons can also have their own buffs and skills as you get further in the game.\n\nHere, take this [BASIC DULL SWORD] (press p to pick up).\n\n";
    ground.push_back(dullSword);
    ground.push_back(chippedHelmet);
    while (true){
        bool b = false;
        char option;
        cout << "Enter an option (? or h for help, q to quit): ";
        cin >> option;
        switch (option){
            case ('h' || '?'):
                help();
            case ('i'):
                inventory();
            case ('s'):
                stats();
            case ('p'):
                pick();
            case ('e'):
                equip();
            case ('u'):
                unequip();
            // case ('d'):
            //     ground.push_back(drop());
            case ('q'):
                b = true; // For some reason, just putting break; here wasn't working, so had to make the boolean b
        }
        if (b) break; // breaks using b
    }
    return 0;
}