// Header files in the std namespace
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include <chrono>
#include <thread>

// Custom header files here
#include <headers/move.h>
#include <headers/Shop.h>
#include <headers/story.h>
#include <headers/npc.h>

// Creating variables & setting info
sector currentSect = Andris;
char where;
string name = "NAME";
bool b = false;
int lives = 5, seconds = 2; // Starting the user off with 5 lives, this IS changable. Check ../extra/lore.txt to see how
               
// Helper function to sleep for a certain amount of milliseconds
void sleep(int time) {
  std::this_thread::sleep_for(std::chrono::milliseconds(time)); // I am NOT typing this whole thing over and over, that's why I made it a function
}

// Helper function to get random number (used in attack)
double randomNum() {
    random_device rd; 
    mt19937 gen(rd());
    double min = 0;
    double max = 1;
    uniform_int_distribution<> distrib(min, max);
    double random_number = distrib(gen);
    return random_number;
}

// Help manu, idk why I didn't just put this in the switch case but wtvr
void help() {
    cout << "HELP MENU\n\nMAIN FUNCTIONS:\nc: continue the story\nq: quit game\ns: show your stats\n\nINVENTORY FUNCTIONS:\ni: show inventory\np: pick an item up from the ground\nd: drop an item to the ground\ne: equip an equippable item from your inventory\nu: unequip an equipped item\n$: show the shop\n\nLOCATION FUNCTIONS:\nm: move around\nw: show what sector you're in\nN: move north\nS: move south\nE: move east\n W: move west\n\nENEMIES:\na: attack enemies\nr: detect enemies with the radar\n";
}

// Returns the user's stats (this also could've been put in the switch case)
void stats() {
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}

// Change game settings like name, seconds to wait, etc
void settings() {
  int op;
  std::cout << "Choose a value to change:\n1) General settings\n2)Player info\n3) Controls\nEnter a number: ";
  while (!(std::cin >> op) || op < 0 || op > 3) {
    std::cout << "Invalid input, enter a value from 1-3. 0 to cancel: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  switch (op) {
    case (1):
      cout << "General settings:\n1) Change time between text clears\n2) Save current game progress (working on making this automatic)";
      break;
    case (2):
      cout << "Player info:\n1) Change name";
      break;
    case (3):
      cout << "Controls:\n";
      cout << "Current controls:\n";
      help();
  }
}

// Overloading tolower since it only takes a character, not a string smh
string tolower(string s) {
    string s2 = "";
    for (char c: s) {
        s2 += tolower(c);
    }
    return s2;
}

// Switch case for the user to preform actions
char decision() {
    while (true) {
        char option;
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
	        case ('a'): // Attack enemies
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
                    cout << "\nEnter the number of the enemy to attack (0 to cancel): ";
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
                    if (en <= 0) return 'a';
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
                            long unsigned int* skillChoice = new long unsigned int;
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
                        if (stat["Current HP"] < 0) stat["Current HP"] = 0;
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
                        if (equipped["Artifact 1"] == revivalStone || equipped["Artifact 2"] == revivalStone || equipped["Artifact 3"] == revivalStone || equipped["Artifact 4"] == revivalStone || equipped["Artifact 5"] == revivalStone) {
                            cout << "\nYou had the revival stone and have been brought back to life! Welcome back, " << name << ".\n";
                            stat["Current HP"] = stat["HP"];
                        }
                        else {
                            cout << "\n\n"
                                << "\x1b[1;31;41m\n\n"
                                << "=======================================\n"
                                << "               YOU DIED               \n"
                                << "=======================================\n"
                                << "\x1b[0m"
                                << " \n\n"
                                << "\x1b[1m"
                                << "You can play again, but will not retain any of your stuff.\n"
                                << "Good job on this run, " << name << ".\x1b[0m"
                                << " ";
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
            case ('c'): // Continue the story
                if (stat["Current HP"] <= 0) {
                    if (stat["Current HP"] <= 0) {
                        if (equipped["Artifact 1"] == revivalStone || equipped["Artifact 2"] == revivalStone || equipped["Artifact 3"] == revivalStone || equipped["Artifact 4"] == revivalStone || equipped["Artifact 5"] == revivalStone) {
                            cout << "You had the revival stone and have been brought back to life! Welcome back, " << name << ".\n";
                            stat["Current HP"] = stat["HP"];
                        }
                        else {
                            cout << "\n\n"
                                << "\x1b[1;31;41m\n\n"
                                << "=======================================\n"
                                << "               YOU DIED               \n"
                                << "=======================================\n"
                                << "\x1b[0m"
                                << " \n\n"
                                << "\x1b[1m"
                                << "You can play again, but will not retain any of your stuff.\n"
                                << "Good job on this run, " << name << ".\x1b[0m"
                                << " ";
                            return 'q';
                        }
                    }
                }
                if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];     
                return option;
            case ('h'): // Fallthhrough to next case (both of these are valid for help menu)
            case ('?'): // Returns the help menu
                help();
                return option;
            case ('i'): // Check ../include/headers/inventory.h for this function
                inventory();
                return option;
            case ('s'): // Returns user's stata
                stats();
                return option;
            case ('p'): // Picks up item from the ground (this is also in ../include/headers/inventory.h)
                pick(currentSect.getGround());
                return option;
            case ('e'): // This is ALSO in ../include/headers/inventory.h
                equip();
                return option;
            case ('u'): // I wonder where this could be... maybe ../include/headers/inventory.h?
                unequip();
                return option;
            case ('d'): // Yep, also in ../include/headers/inventory.h
                drop(currentSect.getGround());
                return option;
            case ('q'): // Quits the game 
                cout << "Goodbye, " << name << "." << endl;
                return option;
            case ('r'): // Radar to scan for enemies in the current sector
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
            case ('N'): // Move north but faster than m > n
              where = Move('N');
              if (where == ' ') cout << "Move complete\n";
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
              break;
            case ('S'): // Move south but faster than m > s
              where = Move('S');
              if (where == ' ') cout << "Move complete";
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
              break;
            case ('E'): // Move east but faster than m > e
              where = Move('E');
              if (where == ' ') cout << "Move complete";
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
              break;
            case ('W'): // Move west but faster than m > w
              where = Move('W');
              if (where == ' ') cout << "Move complete";
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
              break;
            case ('m'): // Move function (allows using u(p), d(own), l(eft), r(ight) instead of n, s, e, w)
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
            case ('w'): // Checks where the user is
                cout << "You are currently in " << currentSect.getName() << "\n" << "Your current coordinates are (" << currCoords.first << ", " << currCoords.second << ")." << endl;
                return option;
            case('$'): // Opens shop (not complete)
                shop();
                return option;
            case('o'):
              settings();
              return option;
		return option;
            default: // Self explanatory
                cout << "Invalid input, please try again\n";
                return option;
        }
    }
}

// Main game loop w/ story
int main() { // Story starts from here, core functionality is in the decision() function and other header files, ilke inventory.h or move.h
    cout << "Please enter a speed from 1 - 20. The lower the speed, the faster text will erase from the screen.\nIt will be easier to read at higher numbers, but the game will move faster at a lower number.\nYou can change this later in the game options.\nEnter a value now: ";
    while (!(cin >> seconds) || seconds < 1 || seconds > 20) {
      std::cout << "Please enter a valid number from 1 - 20 seconds: ";
      std::cin.clear(); std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cout << "Welcome, adventurer.\nEnter your name here: ";
    getline(cin, name);
    std::cout << "Would you like to start the tutorial or skip to the story? (For tutorial, type \"t\", for the story, type \"s\"): ";
    std::string op = "";
    std::getline(std::cin, op);
    while (tolower(op[0]) != 't' && tolower(op[0]) != 's') {
      cout << "You entered " << op << ".\n";
      cout << "Please enter either 't' for the tutorial or 's' to skip to the story: ";
      std::getline(std::cin, op);
    }
    if (tolower(op[0]) == 't') {
      cout << "Hello, " << name << ". Welcome to the world.\n\nYou start as a human with all your stats set to 1, HP at 10, but as time goes on, you can level up your stats, learn skills, collect weapons, and find gear.\n\nGear and weapons can also have their own buffs and skills as you get further in the game.\n\nHere, take this [BASIC DULL SWORD], [CHIPPED HELMET], and [REVIVAL STONE] (press p to pick up).\n\n";
      currentSect.putOnGround(dullSword);
      currentSect.putOnGround(chippedHelmet);
      currentSect.putOnGround(revivalStone);
      enemy first("Test", 1, 1);
      enemy second("Other Test", 1, 5);
      while (true) {
        char d = decision();
        if (d == 'q') return 0;
        if (d == 'c') break;
      }
      currentSect.putOnGround(first);
      currentSect.putOnGround(second);
      cout << "\nWatch it, there's an enemy ahead!" << endl;
      if (equipped["Weapon"] == item("", "", 0)) cout << endl << "You don't have a weapon equipped! If you haven't picked up a weapon, try using p to pick find one. If you have, use e to equip your weapon.";
      else cout << endl << "You have a weapon! Use 'a' to attack the enemy!";
      while (true) {
        char d = decision();
        if (d == 'q') return 0;
        if (d == 'c') break;
      }
      if (stat["Current HP"] <= 0) {
        if (equipped["Artifact 1"] == revivalStone || equipped["Artifact 2"] == revivalStone || equipped["Artifact 3"] == revivalStone || equipped["Artifact 4"] == revivalStone || equipped["Artifact 5"] == revivalStone) {
          cout << "You had the revival stone and have been brought back to life! Welcome back, " << name << ".\n";
          stat["Current HP"] = stat["HP"];
        }
      else {
        cout << "\n\n"
            << "\x1b[1;31;41m\n\n"
            << "=======================================\n"
            << "               YOU DIED               \n"
            << "=======================================\n"
            << "\x1b[0m"
            << " \n\n"
            << "\x1b[1m"
            << "You can play again, but will not retain any of your stuff.\n"
            << "Good job on this run, " << name << ".\x1b[0m"
            << " ";
        return 0;
      }
    }
    if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
    /* while (true) {
      char d = decision();
      if (d == 'q') return 0;
      if (d == 'c') break;
    } */
    cout << "\nGood job. You've defeated your first enemy. If you want to relax your arms, use 'u' to unequip your weapon! This is optional, of course.\nIf you'd like to move around, use 'm' and pick a direction.";
    while (true) {
      char d = decision();
      if (d == 'q') return 0;
      if (d == 'c') break;
    }
    if (stat["Current HP"] <= 0) {
      if (equipped["Artifact 1"] == revivalStone || equipped["Artifact 2"] == revivalStone || equipped["Artifact 3"] == revivalStone || equipped["Artifact 4"] == revivalStone || equipped["Artifact 5"] == revivalStone) {
        cout << "You had the revival stone and have been brought back to life! Welcome back, " << name << ".\n";
        stat["Current HP"] = stat["HP"];
      }
      else {
        cout << "\n\n"
            << "\x1b[1;31;41m\n\n"
            << "=======================================\n"
            << "               YOU DIED               \n"
            << "=======================================\n"
            << "\x1b[0m"
            << " \n\n"
            << "\x1b[1m"
            << "You can play again, but will not retain any of your stuff.\n"
            << "Good job on this run, " << name << ".\x1b[0m"
            << " ";
        return 0;
      }
    }
    if (stat["Current HP"] > stat["HP"]) stat["Current HP"] = stat["HP"];
    cout << "TUTORIAL FINISHED\n";
    clearInv();
    stat["Current HP"] = stat["HP"];
  }
  cout << "Alright, looks like you know the controls. Now, welcome to Zandris. You may have lost your memory after the collapse of Orpheum, so allow me to clue you in.\nThe sky you see above you is actually the ocean K'ver, and those stars are living leviathans. They've been docile until now, so we don't know what their intentions are, but at least they give us light.\nMost people, including you, have been corrupted by the side effects of magic and Orpheum collapsing. You, however, are special, patient 0. You can earn your memories back. However, it won't be easy. To start with, give this voice in your head a name, will you?\n";
  cout << "Enter your guide's name. This cannot be changed later on, so choose carefully!: ";
  // cin.ignore();
  getline(cin, name);
  npc* guide = new npc(name, "guide");
  cout << "Huh, " << guide -> getName() << ", I like that! Thanks! Now, let's get to it.\n";
  cout << "Firstly, here's something cool. Let's go back about a few hours, shall we?\n"; // If you look in ../extra/lore.txt, you'll see that a cutscene is mentioned at the beginning. Since I'm limited by this text based game, I'm just typing it out.
  sleep(seconds * 1500); // Longer wait since this is a LOT of text
  cout << "\033[2J"; // Clear screen (multiplatform, system("CLS | clear") is annoying)
  cout << "\033[1;1H"; // Move cursor to the top left of the screen
  cout << "Hmm, let's see here...\nTo start Project Orpheum, which was being developed in this very lab... if you can still call it that, was an attempt to link this world to a higher dimension using magic, and it worked. There were, however, adverse effects.\nIf you look above you, the leviathans that once lit up our world no longer have their light.\nThat's just one effect of the bridge between the 2 worlds. The major effect is... UNAUTHORIZED. REVERTING STATE.\n";
  while (true) {
    char d = decision();
    if (d == 'q') return 0;
    if (d == 'c') break;
  }
  return 0;
}
