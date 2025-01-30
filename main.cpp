#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "item.h"
using namespace std;
// Inventory arrays
map<string, int> food;
map<string, int> weapons;
map<string, int> gear;
map<string, int> stat = {{"Strength", 1}, {"Defense", 1}};
map<string, string> skills;
vector<item> ground;
int c;
void inventory(){ // Functions for printing a user's inventory
    /*Instructions*/ cout << "For food: f\nFor weapons: w\nFor gear: g\nFor skills: s\nEnter your option (leave blank to exit this menu): ";
    char option;
    cin >> option;
    // Printing individual inventory menus
    if (option == 'f'){
        for (const auto& pair : food) {
            cout << pair.first << " x" << pair.second << "\n";
        }
    }
    else if (option == 'w'){
        for (const auto& pair : weapons) {
            cout << pair.first << " x" << pair.second << "\n";
        }
    }
    else if (option == 'g'){
        for (const auto& pair : gear) {
            cout << pair.first << " x" << pair.second << "\n";
        }
    }
    else if (option == 's'){
        for (const auto& pair : skills) {
            cout << pair.first << " x" << pair.second << "\n";
        }
    }
    // Print whole inventory
    else if(option == 'i'){
        cout << "ALL FOOD:\n";
        for (const auto& pair : food) {
            cout << pair.first << " x" << pair.second << "\n";
        }
        cout << "ALL WEAPONS:\n";
        for (const auto& pair : weapons) {
            cout << pair.first << " x" << pair.second << "\n";
        }
        cout << "ALL GEAR:\n";
        for (const auto& pair : gear) {
            cout << pair.first << " x" << pair.second << "\n";
        }
        cout << "ALL SKILLS:\n";
        for (const auto& pair : skills) {
            cout << pair.first << " x" << pair.second << "\n";
        }
    }
}
void help(){ // Prints the help menu
    cout << "HELP MENU\n\ni: open inventory\n?: open this help menu\ne: equip an item\ns: view stats\np: pick up an item (shows a menu if multiple)\n\n";
}
void stats(){ // Prints a user's stats
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}
void pick(){ // Picks up an item from the ground
    if (ground.empty()) cout << "There's nothing on the ground right now!\n";
    c = 1;
    for (item i : ground){ // Prints items on the ground
        string itemType = i.getType();
        transform(itemType.begin(), itemType.end(), itemType.begin(), ::toupper);
        cout << "Currently on the ground:\n" << c << ": " << i.getName() << " [" << itemType << "]" << "\n";
        c++;
    }
    int choice;
    while (true) {
        cout << "Enter the number of the item you want to pick up (0 to leave): ";
        if (!(cin >> choice)) {
            // If the input is not an integer, clear the error & ignore invalid input
            cin.clear(); // Clear error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
            cout << "Invalid input. Please enter a valid number.\n";
            continue; // Continue the code
        }
        // cin >> choice;
        if (choice == 0) break;
        else if (choice < 1 || choice > ground.size()) { // Runs if choice isn't valid
            cout << "Invalid choice. Please select a valid item number.\n";
        }
        else break;
    }
    if (choice == 0) return;
    item selected = ground[choice - 1];
    string itemType = selected.getType();
    if (ground[choice - 1].getType() == "weapon"){
        if (weapons.find(selected.getName()) == weapons.end()) weapons[selected.getName()] = 1;
        else weapons[selected.getName()]++;
        cout << "Picked up weapon: " << selected.getName() << "\n";
    }
    else if (ground[choice - 1].getType() == "food"){
        if (food.find(selected.getName()) == food.end()) food[selected.getName()] = 1;
        else food[selected.getName()]++;
        cout << "Picked up food: " << selected.getName() << "\n";
    }
    else if (ground[choice - 1].getType() == "gear"){
        if (gear.find(selected.getName()) == gear.end()) gear[selected.getName()] = 1;
        else gear[selected.getName()]++;
        cout << "Picked up gear: " << selected.getName() << "\n";
    }
    ground.erase(ground.begin() + (choice - 1));
    if (ground.empty()) cout << "There's nothing left on the ground.\n";
    else {
        cout << "Items left on the ground: ";
        for (int i = 0; i < ground.size(); i++) {
            string itemType = ground[i].getType();
            transform(itemType.begin(), itemType.end(), itemType.begin(), ::toupper);
            cout << i + 1 << ": " << ground[i].getName() << " [" << itemType << "]\n";
        }
        cout << "Type p again to pick up another item.\n";
    }
}


int main(){
    cout << "Welcome, adventurer.\nEnter your name here: ";
    string name;
    cin >> name;
    cout << "Hello, " << name << ". Welcome to the world. You start as a human with all your stats set to one, but as time goes on, you can\nlevel up your stats, learn skills, collect weapons, and find gear. Gear and weapons can also have their\nown buffs and skills as you get further in the game. Here, take this [BASIC DULL SWORD] (press p to pick up).\n";
    ground.push_back(item("Dull sword", "weapon", 1));
    while (true){
        char option;
        cout << "Enter an option (? or h for help, q to quit): ";
        cin >> option;
        if (option == 'i') inventory();
        else if (option == 'h' || option == '?') help();
        else if (option == 's') stats();
        else if (option == 'p') pick();
        else if (option == 'q') break;
    }
    return 0;
}