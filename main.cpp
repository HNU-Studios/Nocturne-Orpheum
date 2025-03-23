#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include "move.h"
#include "Shop.h"
using namespace std;
sector currentSect = Andris;
char where;
string name;
bool b = false;
void help() { // Prints the help menu
    cout << "HELP MENU\n\nc: continue the story\nS or $: show the shop\nq: quit game\ns: show your stats\nm: move around\ni: inventory\nw: show what sector you're in\nr: detect enemies with the radar\np: pick an item up from the ground\nd: drop an item to the ground\ne: equip an equippable item from your inventory\nu: unequip an equipped item\n\n";
}
void stats() { // Prints a user's stats
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}
char decision(){
    while (true){
        char option;
        // system("clear");
        cout << "\nEnter an option (? or h for help, c to continue story, q to quit): ";
        if (!(cin >> option)) {
            // If the input isn't an int, clear it and retry
            cin.clear(); // Clear err
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a valid letter. See the help menu for commands (type 'h' for help).\n";
            continue; // continue
        }
        switch (option) {
	    case ('a'):
		cout << "Enemy attacked!";
		return option;
            case ('c'):
                return option;
            case ('h'):
            case ('?'):
                help();
                return option;
            case ('i'):
                inventory();
                return option;
            case ('s'):
                stats();
                return option;
            case ('p'):
                pick(currentSect.getGround());
                return option;
            case ('e'):
                equip();
                return option;
            case ('u'):
                unequip();
                return option;
            case ('d'):
                drop(currentSect.getGround());
                return option;
            case ('q'):
                cout << "Goodbye, " << name << "." << endl;
                return option;
            case ('r'):
                if (enemies.size() == 0) cout << "There are currently no enemies. You're safe!\n";
                else{
                    int count = 0;
                    cout << "Enemies currently present\n";
                    for (enemy i : enemies) {
                        count++;
                        cout << count << ") Name: " << i.getName() << ", Speed: " << i.getSpeed() << ", Power: " << i.getPower();
                    }
                    cout << "\n";
                }
            	return option;
            case ('m'):
                where = Move();
                if(where == ' ') {
                    cout << "Move complete\n";
                }
                else if (where == 'n') {
                    if (currentSect.getNorth() != "") {
                        for (sector i: sects) {
                            if (i.getName() == currentSect.getNorth()) {
                                cout << "Found town North: " << currentSect.getNorth() << " is the town North of you." << i.getName() << endl;
                                currentSect = i;
                                return option;
                            }
                        }
                    }
                    else cout << "No town found North of you! You are currently as far North as possible in town " << currentSect.getName() << endl;
                }
                else if (where == 's') {
                    if (currentSect.getSouth() != "") {
                        for (sector i: sects) {
                            if (i.getName() == currentSect.getSouth()) {
                                cout << "Found town South: " << currentSect.getSouth() << " is the town South of you." << endl;
                                currentSect = i;
                                return option;
                            }
                        }
                    }
                    else cout << "No town found South of you! You are currently as far South as possible in town " << currentSect.getName() << endl;
                }
                else if (where == 'e') {
                    if (currentSect.getEast() != "") {
                        for (sector i: sects) {
                            if (i.getName() == currentSect.getEast()) {
                                cout << "Found town East: " << currentSect.getEast() << " is the town East of you." << endl;
                                currentSect = i;
                                return option;
                            }
                        }
                    }
                    else cout << "No town found East of you! You are currently as far East as possible in town " << currentSect.getName() << endl;
                }
                else if (where == 'w') {
                    if (currentSect.getWest() != "") {
                        for (sector i: sects) {
                            if (i.getName() == currentSect.getWest()) {
                                cout << "Found town West: " << currentSect.getWest() << " is the town West of you." << endl;
                                currentSect = i;
                                return option;
                            }
                        }
                    }
                    else cout << "No town found West of you! You are currently as far West as possible in town " << currentSect.getName() << endl;
                }
                else if (where == 'S') return option;
            return option;
            case ('w'):
                cout << "You are currently in " << currentSect.getName() << "\n" << "Your current coordinates are (" << currCoords.first << ", " << currCoords.second << ")." << endl;
                return option;
            case('S'):
            case('$'):
                shop();
		return option;
            default:
                cout << "Invalid input, please try again\n";
                return option;
        }
    }
}
int main() {
    cout << "Welcome, adventurer.\nEnter your name here: ";
    cin >> name;
    cout << "Hello, " << name << ". Welcome to the world.\n\nYou start as a human with all your stats set to 1, HP at 10, but as time goes on, you can level up your stats, learn skills, collect weapons, and find gear.\n\nGear and weapons can also have their own buffs and skills as you get further in the game.\n\nHere, take this [BASIC DULL SWORD] (press p to pick up).\n\n";
    currentSect.putOnGround(dullSword);
    currentSect.putOnGround(chippedHelmet);
    currentSect.putOnGround(revivalStone);
    enemy first("Test", 1, 1);
    while (true) {
        // if (decision() == 'q') break;
	while (decision() != 'c') {
		if (decision() == 'q') return 0;
	}
	cout << "\nWatch it! There's an ememy ahead.";
	if (equipped["Weapon"] == item("", "", 0)) cout << endl << "You don't have a weapon equipped! If you haven't picked up a weapon, try using p to pick find one. If you have, use e to equip your weapon.";
	else cout << endl << "You have a weapon! Use 'a' to attack the enemy!";
	if (decision() == 'q') break;
        if (stat["Current HP"] <= 0) {
            if (gear.find(revivalStone) != gear.end()) {
                cout << "You had the revival stone and have been brought back to life! Welcome back, adventurer.\n";
                stat["Current HP"] = stat["HP"];
            }
            else{
                cout << "\n\nYOU DIED\nYou can play again, but will not retain any of your stuff. Good job on this run, " << name << ".\n\n";
                break;
            }
        }
        if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
        // if (b) break;
    }
    return 0;
}
