#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include "./headers/move.h"
#include "./headers/Shop.h"
using namespace std;
sector currentSect = Andris;
char where;
string name;
bool b = false;
double randomNum() {
    random_device rd; 
    mt19937 gen(rd());
    double min = 0;
    double max = 1;
    uniform_int_distribution<> distrib(min, max);
    double random_number = distrib(gen);
    return random_number;
}
void help() { // Prints the help menu
    cout << "HELP MENU\n\nMAIN FUNCTIONS:\nc: continue the story\nq: quit game\ns: show your stats\n\nINVENTORY FUNCTIONS:\ni: show inventory\np: pick an item up from the ground\nd: drop an item to the ground\ne: equip an equippable item from your inventory\nu: unequip an equipped item\nS or $: show the shop\n\nLOCATION FUNCTIONS:\nm: move around\nw: show what sector you're in\n\nENEMIES:\na: attack enemies\nr: detect enemies with the radar\n";
}
void stats() { // Prints a user's stats
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}
char decision() {
    while (true) {
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
        long unsigned int* skillChoice = nullptr;
        switch (option) {
	        case ('a'):
                // *skillChoice = 0;
                cout << "Tip! You can scan for enemies without attacking them using your radar! Type 'r' to use it\n";
                if (currentSect.getEnemies().size() == 0) cout << "There are currently no enemies in this sector. Try using 'm' to move!";
                else {
                    int c = 1;
                    cout << "Current enemies: ";
                    for (enemy i: currentSect.getEnemies()){
                        cout << endl << c << ") NAME: " << i.getName() << ", ATK: "<< i.getPower() << ", HP: " << i.getHp();
                        c++;
                    }
                    cout << "\nEnter the number of the enemy to attack: ";
                    int en;
                    while (true) {
                        if (!(cin >> en) || en > (c - 1)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid number.\n";
                            continue;
                        }
                        else break;
                    }
                    if (skills.size() != 0) {
                        cout << "\nSkills avaliable: " << endl;
                        for (long unsigned int i = 0; i < skills.size(); i++) {
                            cout << i + 1 << ": " << skills[i].getName() << ", a " << skills[i].getKind() << " type skill with " << skills[i].getUses() << " uses left and " << skills[i].getPower() << " power.\n";
                        }
                        cout << "Use a skill? (y/n)";
                        char* temp = new char;
                        cin >> *temp;
                        if (toupper(*temp) == 'Y') {
                            delete temp;
                            temp = nullptr;
                            int* skillChoice = new int;
                            while (true) {
                                cout << "What skill would you like to use? Please enter the number from the list.\n";
                                cin >> *skillChoice;
                                if (*skillChoice > skills.size() + 1 || *skillChoice <= 0) {
                                    cout << "That isn't a valid skill :(\n";
                                }
                                else {
                                    break;
                                }
                            }
                            if (skills[*skillChoice - 1].getKind() == "Attack") {
                                if (randomNum() > 0.5) {
                                    currentSect.getEnemies()[en - 1].setHp(currentSect.getEnemies()[en - 1].getHp() - 1);
                                }
                            }
                            else if (skills[*skillChoice - 1].getKind() == "Health") {
                                stat["Current HP"]++;
                                if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
                            }
                            else if (skills[*skillChoice - 1].getKind() == "Defense") {
                                stat["Defense"]++;
                            }
                            else if (skills[*skillChoice - 1].getKind() == "Divine") {
                                stat["Divinity"]++;
                            }
                            else if (skills[*skillChoice - 1].getKind() == "Magic") {
                                stat["Intelligence"]++;
                            }
                            else if (skills[*skillChoice - 1].getKind() == "Charisma") {
                                stat["Charisma"]++;
                            }
                            else if (skills[*skillChoice - 1].getKind() == "Stealth") {
                                stat["Stealth"]++;
                            }
                        }
                        else {
                            delete temp;
                            temp = nullptr;
                            if (equipped["Weapon"] != item("", "", 0)) {
                                cout << "Not using a skill, only using your currently equipped weapon, " << equipped["Weapon"].getName() << ".\n";
                            }
                            else {
                                cout << "Not using a skill, only using your strength.\n";
                            }
                        }
                    }
                    double r = randomNum();
                    cout << "\nAttacking " << currentSect.getEnemies()[en - 1].getName() << " staring with HP " << currentSect.getEnemies()[en - 1].getHp() << " and you have " << stat["Strength"] << " attack power, along with " << stat["Current HP"] << " health.\n";
                    if (r < 0.5){
                        currentSect.getEnemies()[en - 1].setHp(currentSect.getEnemies()[en - 1].getHp() - stat["Strength"]);
                        if (currentSect.getEnemies()[en - 1].getHp() < 0) currentSect.getEnemies()[en - 1].setHp(0);
                        cout << "\nYou hit the enemy! Enemies new health: " << currentSect.getEnemies()[en - 1].getHp();
                    }
                    else {
                        cout << "\nYou missed the enemy!";
                    }
                    r = randomNum();
                    if (r < 0.5) {
                        stat["Current HP"] -= currentSect.getEnemies()[en - 1].getHp();
                        cout << "\nYou got hit! Your new health: " << stat["Current HP"];
                    }
                    else if (r > 0.5) {
                        cout << "\nThe enemy missed you!";
                    }
                    if (currentSect.getEnemies()[en - 1].getHp() <= 0){
                        cout << "\nYou've killed " << currentSect.getEnemies()[en - 1].getName() << "!";
                        currentSect.getEnemies().erase(currentSect.getEnemies().begin() + (en - 1));
                    }
                    if (stat["Current HP"] <= 0) {
                        if (equipped["Artifact 1"] != revivalStone || equipped["Artifact 2"] != revivalStone || equipped["Artifact 3"] != revivalStone || equipped["Artifact 4"] != revivalStone || equipped["Artifact 5"] != revivalStone) {
                            cout << "\nYou had the revival stone and have been brought back to life! Welcome back, adventurer.\n";
                            stat["Current HP"] = stat["HP"];
                        }
                        else {
                            cout << "\n\n\x1b[31;41YOU DIED\nYou can play again, but will not retain any of your stuff. Good job on this run, " << name << ".\x1b[0m\n\n";
                            return 'q';
                        }
                    }
                    return option;
                }
                cout << "";
                if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
                delete skillChoice;
                skillChoice = nullptr; // We love killing our variables :3
                return option;
                break;
            case ('c'):
                if (stat["Current HP"] <= 0) {
                    if (stat["Current HP"] <= 0) {
                        if (equipped["Artifact 1"] != revivalStone || equipped["Artifact 2"] != revivalStone || equipped["Artifact 3"] != revivalStone || equipped["Artifact 4"] != revivalStone || equipped["Artifact 5"] != revivalStone) {
                            cout << "You had the revival stone and have been brought back to life! Welcome back, adventurer.\n";
                            stat["Current HP"] = stat["HP"];
                        }
                        else {
                            cout << "\n\n\x1b[31;41YOU DIED\nYou can play again, but will not retain any of your stuff. Good job on this run, " << name << ".\x1b[0m\n\n";
                            return 'q';
                        }
                    }
                }
                if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];     
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
            case ('q'): // Sometimes doesn't close, idk why
                cout << "Goodbye, " << name << "." << endl;
                return option;
            case ('r'):
                if (currentSect.getEnemies().size() == 0) cout << "There are currently no enemies. You're safe!\n";
                else {
                    int count = 0;
                    cout << "Enemies currently present\n";
                    for (enemy i : currentSect.getEnemies()) {
                        count++;
                        cout << endl << count << ") Name: " << i.getName() << ", Speed: " << i.getSpeed() << ", Power: " << i.getPower() << ", Health: " << i.getHp();
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
int main() { // Story starts from here, core functionality is in the decision() function and other header files, ilke inventory.h or move.h
    cout << "Welcome, adventurer.\nEnter your name here: ";
    cin >> name;
    cout << "Hello, " << name << ". Welcome to the world.\n\nYou start as a human with all your stats set to 1, HP at 10, but as time goes on, you can level up your stats, learn skills, collect weapons, and find gear.\n\nGear and weapons can also have their own buffs and skills as you get further in the game.\n\nHere, take this [BASIC DULL SWORD], [CHIPPED HELMET], and [REVIVAL STONE] (press p to pick up).\n\n";
    currentSect.putOnGround(dullSword);
    currentSect.putOnGround(chippedHelmet);
    currentSect.putOnGround(revivalStone);
    enemy first("Test", 1, 1);
    enemy second("Other Test", 1, 5);
    while (true) {
        while (true) {
            char d = decision();
            if (d == 'q') return 0;
            if (d == 'c') break;
        }
        currentSect.putOnGround(first);
        currentSect.putOnGround(second);
        cout << "\nWatch it! There's an ememy ahead.";
        if (equipped["Weapon"] == item("", "", 0)) cout << endl << "You don't have a weapon equipped! If you haven't picked up a weapon, try using p to pick find one. If you have, use e to equip your weapon.";
        else cout << endl << "You have a weapon! Use 'a' to attack the enemy!";
        while (true) {
            char d = decision();
            if (d == 'q') return 0;
            if (d == 'c') break;
        }
        if (stat["Current HP"] <= 0) {
            if (equipped["Artifact 1"] != revivalStone || equipped["Artifact 2"] != revivalStone || equipped["Artifact 3"] != revivalStone || equipped["Artifact 4"] != revivalStone || equipped["Artifact 5"] != revivalStone) {
                cout << "You had the revival stone and have been brought back to life! Welcome back, adventurer.\n";
                stat["Current HP"] = stat["HP"];
            }
            else {
                cout << "\n\n\x1b[31;41YOU DIED\nYou can play again, but will not retain any of your stuff. Good job on this run, " << name << ".\x1b[0m\n\n";
                return 0;
            }
        }
        if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
        while (true) {
            char d = decision();
            if (d == 'q') return 0;
            if (d == 'c') break;
        }
        if (decision() == 'q') return 0;
        cout << "\nGood job. You've defeated your first enemy. If you want to relax your arms, use 'u' to unequip your weapon! This is optional, of course.\nIf you'd like to move around, use 'm' and pick a direction.";
        while (true) {
            char d = decision();
            if (d == 'q') return 0;
            if (d == 'c') break;
        }
        if (stat["Current HP"] <= 0) {
            if (equipped["Artifact 1"] == revivalStone || equipped["Artifact 2"] == revivalStone || equipped["Artifact 3"] == revivalStone || equipped["Artifact 4"] == revivalStone || equipped["Artifact 5"] == revivalStone) {
                cout << "You had the revival stone and have been brought back to life! Welcome back, adventurer.\n";
                stat["Current HP"] = stat["HP"];
            }
            else {
                cout << "\n\n\x1b[31;41YOU DIED\nYou can play again, but will not retain any of your stuff. Good job on this run, " << name << ".\x1b[0m\n\n";
                return 0;
            }
        }
        if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];    
    }
    return 0;
}
