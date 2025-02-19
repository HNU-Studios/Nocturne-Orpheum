#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "sectors.h"
#include "enemy.h"
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
    ground.push_back(revivalStone);
    enemy first("Test", 1, 1);
    while (true){
        char option;
        cout << "Enter an option (? or h for help, q to quit): ";
        if (!(cin >> option)) {
            // If the input is not an integer, clear the error & ignore invalid input
            cin.clear(); // Clear error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
            cout << "Invalid input. Please enter a valid letter. See the help menu for commands (type 'h' for help).\n";
            continue; // Continue the code
        }
        switch (option){
            case ('h'):
            case ('?'):
                help();
                break;
            case ('i'):
                inventory();
                break;
            case ('s'):
                stats();
                break;
            case ('p'):
                pick();
                break;
            case ('e'):
                equip();
                break;
            case ('u'):
                unequip();
                break;
            case ('d'):
                drop();
                break;
            case ('q'):
                cout << "Goodbye, " << name << ".";
                return 0; // breaks the loop
            case ('o'):
                if (enemies.size() == 0) cout << "There are currently no enemies. You're safe!";
                else{
                    int count = 0;
                    cout << "Enemies currently present\n";
                    for (enemy i : enemies){
                        count++;
                        cout << count << ") Name: " << i.getName() << ", Speed: " << i.getSpeed() << ", Power: " << i.getPower();
                    }
                    cout << "\n";
                }
        }
        if (stat["Current HP"] <= 0){
            if (gear.find(revivalStone) != gear.end()){
                cout << "You had the revival stone and have been brought back to life! Welcome back, adventurer.\n";
                stat["Current HP"] = stat["HP"];
            }
            else{
                cout << "\n\nYOU DIED\nYou can play again, but will not retain any of your stuff. Good job on this run, " << name << ".\n\n";
                break;
            }
        }
        if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
    }
    return 0;
}