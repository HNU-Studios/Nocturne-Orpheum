#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include "item.h"
using namespace std;
// Inventory arrays
map<item, int> food;
map<item, int> weapons;
map<item, int> gear;
map<string, int> stat = {{"Strength", 1}, {"Defense", 1}, {"Intelligence", 1}, {"HP", 10}};
map<string, string> skills;
map<string, string> equipped = {{"Weapon", ""}, {"Helmet", ""}, {"Breastplate", ""}, {"Gloves", ""}, {"Mask", ""}, {"Artifact 1", ""}, {"Artifact 2", ""}, {"Artifact 3", ""}, {"Artifact 4", ""}, {"Artifact 5", ""}};
vector<item> ground;
int c;
void inventory(){ // Functions for printing a user's inventory
    /*Instructions*/ cout << "For food: f\nFor weapons: w\nFor gear: g\nFor skills: s\nFor all items: i\nEnter your option (leave blank to exit this menu): ";
    char option;
    cin >> option;
    // Printing individual inventory menus
    if (option == 'f'){
        for (auto pair : food) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
    }
    else if (option == 'w'){
        for (const auto& pair : weapons) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
    }
    else if (option == 'g'){
        for (const auto& pair : gear) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
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
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
        cout << "ALL WEAPONS:\n";
        for (const auto& pair : weapons) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
        }
        cout << "ALL GEAR:\n";
        for (const auto& pair : gear) {
            cout << pair.first.getName() << " x" << pair.second << "\n";
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
    if (ground[choice - 1].getType() == "Weapon"){
        if (weapons.find(selected) == weapons.end()) weapons[selected] = 1;
        else weapons[selected]++;
        cout << "Picked up weapon: " << selected.getName() << "\n";
    }
    else if (ground[choice - 1].getType() == "Food"){
        if (food.find(selected) == food.end()) food[selected] = 1;
        else food[selected]++;
        cout << "Picked up food: " << selected.getName() << "\n";
    }
    else if (ground[choice - 1].getType() == "Artifact" || ground[choice - 1].getType() == "Helmet" || ground[choice - 1].getType() == "Breastplate" || ground[choice - 1].getType() == "Mask" || ground[choice - 1].getType() == "Gloves"){
        if (gear.find(selected) == gear.end()) gear[selected] = 1;
        else gear[selected]++;
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
void equip(){ // Lets the user equip an item
    // item toEquip = item("", "", 0);
    // c = 1;
    cout << "Please select a category of item to equip\n\n";
    cout << "For weapons: w\nFor gear/ artifacts: g\nEnter your option (leave blank to exit this menu): ";
    item toEquip = item("", "", 0);
    c = 1;
    char option;
    cin >> option;
    if (option == 'w'){
        for (const auto& pair : weapons) {
            cout << c << ": " << pair.first.getName() << " x" << pair.second << "\n";
            c++;
        }
        int o;
        while (true) {
            cout << "Enter the number of the item you want to pick up (0 to leave): ";
            if (!(cin >> o)) {
                // If the input is not an integer, clear the error & ignore invalid input
                cin.clear(); // Clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
                cout << "Invalid input. Please enter a valid number.\n";
                continue; // Continue the code
            }
            // cin >> choice;
            if (o == 0) break;
            else if (o < 1 || o > weapons.size()) { // Runs if choice isn't valid
                cout << "Invalid choice. Please select a valid item number.\n";
            }
            else break;
        }
        auto it = next(weapons.begin(), o - 1); 
        toEquip = it->first;
        if (toEquip.getType() == "Weapon"){ 
            equipped["Weapon"] = toEquip.getName(); 
            stat["Strength"] += toEquip.getPower();
    }
    }
    else if (option == 'g'){
        for (const auto& pair : gear) {
            cout << c << ": " << pair.first.getName() << " x" << pair.second << "\n";
            c++;
        }
        int o;
        cout << "Enter an item's number";
        cout << "Enter an item's number";
        while (true) {
            cout << "Enter the number of the item you want to pick up (0 to leave): ";
            if (!(cin >> o)) {
                // If the input is not an integer, clear the error & ignore invalid input
                cin.clear(); // Clear error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of invalid input
                cout << "Invalid input. Please enter a valid number.\n";
                continue; // Continue the code
            }
            // cin >> choice;
            if (o == 0) break;
            else if (o < 1 || o > gear.size()) { // Runs if choice isn't valid
                cout << "Invalid choice. Please select a valid item number.\n";
            }
            else break;
        }
        auto it = next(gear.begin(), o - 1);
        toEquip = it->first;
        if (toEquip.getType() == "Helmet"){
            equipped["Helmet"] = toEquip.getName(); 
            stat["HP"] += toEquip.getPower();
        }
        else if (toEquip.getType() == "Breastplate"){
            equipped["Breastplate"] = toEquip.getName(); 
            stat["HP"] += toEquip.getPower();
        }
        else if (toEquip.getType() == "Gloves"){
            equipped["Gloves"] = toEquip.getName(); 
            stat["Strength"] += toEquip.getPower();
        }
        else if (toEquip.getType() == "Mask"){
            equipped["Mask"] = toEquip.getName(); 
            stat["HP"] += toEquip.getPower();
        }
        // Checks for artifact slots and adds to the lowest one. If full, warns the user.
        else if (toEquip.getType() == "Artifact"){
            if (equipped["Artifact 5"] != ""){
                cout << "You have too many artifacts equipped (Max 5).";
                return;
            }
            else {
                if (equipped["Artifact 4"] != ""){
                    equipped["Artifact 5"] = toEquip.getName();
                }
                else {
                    if (equipped["Artifact 3"] != ""){
                        equipped["Artifact 4"] = toEquip.getName();
                    }
                    else{
                        if (equipped["Artifact 2"] != ""){
                            equipped["Artifact 1"] = toEquip.getName();
                        }
                    }
                }
            }
        }
    } 
}


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