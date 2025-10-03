#include <iomanip>

inline char CONTINUE_STORY = 'c', QUIT_GAME = 'q', SHOW_STATS = 's', INVENTORY = 'i', PICK_ITEM = 'p', DROP_ITEM = 'd', EQUIP_ITEM = 'e', UNEQUIP_ITEM = 'u', SHOP = '$', MOVE = 'm', WHERE = 'w', NORTH = 'N', EAST = 'E', SOUTH = 'S', WEST = 'W', ATTACK = 'a', RADAR = 'r';
sector currentSect = Andris;
char where, key;
string name = "NAME";
bool b = false;
int lives = 5, seconds = 2; // Starting the user off with 5 lives, this IS changable. Check ../extra/lore.txt to see how

// Helper function to display player info upon screen clear
void header() {
  std::cout << "============================\n" // 28 character long for reference below 
            << "| HP: " << std::setw(3) << std::setfill('0') << stat["Current HP"] << "/" << std::setw(3) << std::setfill('0') << stat["HP"] << "              |\n"
            << "| Sector: " << currentSect.getName() << std::setw(19 - currentSect.getName().length()) << std::setfill(' ') << "|\n"
            << "| Name: " << name << std::setw(21 - name.length()) << std::setfill(' ') << "|\n"
            << "============================\n";
}

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
    cout << "HELP MENU\n\nMAIN FUNCTIONS:\n" << CONTINUE_STORY << ": continue the story\n" << QUIT_GAME << ": quit game\n " << SHOW_STATS << ": show your stats\n\nINVENTORY FUNCTIONS:\n" << INVENTORY << ": show inventory\n " << PICK_ITEM << ": pick an item up from the ground\n" << DROP_ITEM << ": drop an item to the ground\n" << EQUIP_ITEM << ": equip an equippable item from your inventory\n" << UNEQUIP_ITEM << ": unequip an equipped item\n" << SHOP << ": show the shop\n\nLOCATION FUNCTIONS:\n" << MOVE << ": move around\n" << WHERE << ": show what sector you're in\n" << NORTH << ": move north\n" << SOUTH << ": move south\n" << EAST << ": move east\n" << WEST << ": move west\n\nENEMIES:\n" << ATTACK << ": attack enemies\n" << RADAR << ": detect enemies with the radar\n";
}

// Returns the user's stats (this also could've been put in the switch case)
void stats() {
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}

// Change game settings like name, seconds to wait, etc
void settings() {
  int op, op2;
  std::cout << "Choose a value to change:\n1) General settings\n2)Player info\n3) Controls\nEnter a number: ";
  while (!(std::cin >> op) || op < 0 || op > 3) {
    std::cout << "Invalid input, enter a value from 1-3. 0 to cancel: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  switch (op) {
    case (1):
      cout << "General settings:\n1) Change time between text clears\n2) Save current game progress (working on making this automatic)"; // TODO: Make include/headers/save.h
      while (!(cin >> op2) || op2 < 0 || op2 > 2) {
        std::cout << "Invalid input, enter a value from 1-2. Use 0 to cancel: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      switch (op2) {
        case (0):
          break;
        case (1):
          std::cout << "The current time between inputs is " << seconds << ". Enter a new time between inputs: ";
          while (!(cin >> seconds) || seconds < 1 || seconds > 20) {
            std::cout << "Invalid input, please enter a number from 1-20. Use 0 to cancel: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          std::cout << "Time between prompts successfully set to " << seconds << ".\n";
          break;
        case (2):
          // if (save() != "ERROR") std::cout << "Saved successfully to " << save(); // TODO implement this
          // else std::cout << "Error while saving game.";
          break;
      }
      break;
    case (2):
      cout << "Player info:\n1) Change name";
      while (!(cin >> op2) || op2 < 0 || op2 > 2) {
        std::cout << "Invalid input, enter a vlue from 1-2. Use 0 to cancel: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      switch (op2) {
        case (0):
          break;
        case (1):
          std::cout << "Enter a new name: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          while (!(std::getline(cin, name))) {
            name = "NAME";
            std::cout << "Invalid input, please try again";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
          std::cout << "Name changed successfully to " << name;
          break;
        default:
          break;
      }
      break;
    case (3):
      cout << "Controls:\n";
      cout << "Current controls:\n";
      help();
      std::cout << "\nEnter the command to change the input for (for example, if you want to change the input for shop, type '$'): ";
      while (!(std::cin >> key)) {
        std::cout << "Invalid input, please try again. Remember, enter only a single character that is ALREADY SET TO AN ACTION! ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      if (key == CONTINUE_STORY) {
        cout << "Please enter a new key for CONTINUE_STORY now: ";
        while (!(cin >> CONTINUE_STORY)) {
          std::cout << "Please enter a valid character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      if (key == QUIT_GAME) cout << "Please enter a new key for QUIT_GAME now: ";
      if (key == SHOW_STATS) cout << "Please enter a new key for SHOW_STATS now: ";
      if (key == INVENTORY) cout << "Please enter a new key for INVENTORY now: ";
      if (key == PICK_ITEM) cout << "Please enter a new key for PICK_ITEM now: ";
      if (key == DROP_ITEM) cout << "Please enter a new key for DROP_ITEM now: ";
      if (key == EQUIP_ITEM) cout << "Please enter a new key for EQUIP_ITEM now: ";
      if (key == UNEQUIP_ITEM) cout << "Please enter a new key for UNEQUIP_ITEM now: ";
      if (key == SHOP) cout << "Please enter a new key for SHOP now: ";
      if (key == MOVE) cout << "Please enter a new key for MOVE now: ";
      if (key == WHERE) cout << "Please enter a new key for WHERE now: ";
      if (key == NORTH) cout << "Please enter a new key for NORTH now: ";
      if (key == EAST) cout << "Please enter a new key for EAST now: ";
      if (key == SOUTH) cout << "Please enter a new key for SOUTH now: ";
      if (key == WEST) cout << "Please enter a new key for WEST now: ";
      if (key == ATTACK) cout << "Please enter a new key for ATTACK now: ";
      if (key == RADAR) cout << "Please enter a new key for RADAR now: ";
    default: 
      break;
  }
}
}

// Overloading tolower since it only takes a character, not a string smh
std::string tolower(std::string s) {
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

// Helper function to prompt the user
char next() {
  while (true) {
    char d = decision();
    if (d == 'q') return 'q';
    if (d == 'c') break;
    sleep(seconds * 1000);
    cout << "\033[2J" << "\033[1;1H";
    header();
  }
  return ' ';
}

