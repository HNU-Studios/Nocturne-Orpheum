#include <iomanip>

inline char 
CONTINUE_STORY = 'c', 
QUIT_GAME = 'q', 
SHOW_STATS = 's', 
INVENTORY = 'i', 
PICK_ITEM = 'p', 
DROP_ITEM = 'd', 
EQUIP_ITEM = 'e', 
UNEQUIP_ITEM = 'u', 
SHOP = '$', 
MOVE = 'm', 
WHERE = 'w', 
NORTH = 'N', 
EAST = 'E', 
SOUTH = 'S', 
WEST = 'W', 
ATTACK = 'a', 
RADAR = 'r', 
HELP = 'h', 
OPTIONS = 'o';
sector currentSect = Andris;
char where, key;
bool b = false;
int lives = 5, seconds = 2; // Starting the user off with 5 lives, this IS changable. Check ../extra/lore.txt to see how

// Helper function to display player info upon screen clear
void header() {
  std::cout << "Scroll up for previous history\n"
            << "============================\n" // This is 28 characters long for reference below (length needed to determine spacing) 
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
  std::cout << "Choose a value to change:\n1) General settings\n2) Player info\n3) Controls\nEnter a number: ";
  while (!(std::cin >> op) || op < 0 || op > 3) {
    std::cout << "Invalid input, enter a value from 1-3. 0 to cancel: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  switch (op) {
    case (1):
      cout << "General settings:\n1) Change time between text clears\n2) Save current game progress (working on making this automatic)\n"; // TODO: Make include/headers/save.h
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
          // std::string saveFile = save();
          // if (save() != "ERROR") std::cout << "Saved successfully to " << saveFile; // TODO implement this
          // else std::cout << "Error while saving game.";
          std::cout << "Apologies, save files haven't been implemented yet. These will be released in a future patch!\n";
          break;
      }
      break;
    case (2):
      cout << "Player info:\n1) Change name\n2) Change progress";
      while (!(cin >> op2) || op2 < 0 || op2 > 2) {
        std::cout << "Invalid input, enter a value from 1-2. Use 0 to cancel: ";
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
        case (2):
          std::cout << "Please try again later... this hasn't been implemented yet!\n";
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
        while (!(cin >> CONTINUE_STORY) || 
            CONTINUE_STORY == QUIT_GAME || 
            CONTINUE_STORY == SHOW_STATS || 
            CONTINUE_STORY == INVENTORY || 
            CONTINUE_STORY == PICK_ITEM || 
            CONTINUE_STORY == DROP_ITEM || 
            CONTINUE_STORY == EQUIP_ITEM ||
            CONTINUE_STORY == UNEQUIP_ITEM || 
            CONTINUE_STORY == SHOP || 
            CONTINUE_STORY == MOVE || 
            CONTINUE_STORY == WHERE ||
            CONTINUE_STORY == NORTH || 
            CONTINUE_STORY == EAST ||
            CONTINUE_STORY == SOUTH || 
            CONTINUE_STORY == WEST ||
            CONTINUE_STORY == ATTACK || 
            CONTINUE_STORY == RADAR ||
            CONTINUE_STORY == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

      }
      else if (key == QUIT_GAME) {
        cout << "Please enter a new key for QUIT_GAME now: ";
        while (!(cin >> QUIT_GAME) || 
            QUIT_GAME == CONTINUE_STORY || 
            QUIT_GAME == SHOW_STATS || 
            QUIT_GAME == INVENTORY || 
            QUIT_GAME == PICK_ITEM || 
            QUIT_GAME == DROP_ITEM || 
            QUIT_GAME == EQUIP_ITEM ||
            QUIT_GAME == UNEQUIP_ITEM || 
            QUIT_GAME == SHOP || 
            QUIT_GAME == MOVE || 
            QUIT_GAME == WHERE ||
            QUIT_GAME == NORTH || 
            QUIT_GAME == EAST ||
            QUIT_GAME == SOUTH || 
            QUIT_GAME == WEST ||
            QUIT_GAME == ATTACK || 
            QUIT_GAME == RADAR ||
            QUIT_GAME == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == SHOW_STATS) {
        cout << "Please enter a new key for SHOW_STATS now: ";
        while (!(cin >> SHOW_STATS) || 
            SHOW_STATS == CONTINUE_STORY || 
            SHOW_STATS == QUIT_GAME ||  
            SHOW_STATS == INVENTORY || 
            SHOW_STATS == PICK_ITEM || 
            SHOW_STATS == DROP_ITEM || 
            SHOW_STATS == EQUIP_ITEM ||
            SHOW_STATS == UNEQUIP_ITEM || 
            SHOW_STATS == SHOP || 
            SHOW_STATS == MOVE || 
            SHOW_STATS == WHERE ||
            SHOW_STATS == NORTH || 
            SHOW_STATS == EAST ||
            SHOW_STATS == SOUTH || 
            SHOW_STATS == WEST ||
            SHOW_STATS == ATTACK || 
            SHOW_STATS == RADAR ||
            SHOW_STATS == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == INVENTORY) {
        cout << "Please enter a new key for INVENTORY now: ";
        while (!(cin >> INVENTORY) ||
            INVENTORY == CONTINUE_STORY || 
            INVENTORY == SHOW_STATS ||  
            INVENTORY == QUIT_GAME || 
            INVENTORY == PICK_ITEM || 
            INVENTORY == DROP_ITEM || 
            INVENTORY == EQUIP_ITEM ||
            INVENTORY == UNEQUIP_ITEM || 
            INVENTORY == SHOP || 
            INVENTORY == MOVE || 
            INVENTORY == WHERE ||
            INVENTORY == NORTH || 
            INVENTORY == EAST ||
            INVENTORY == SOUTH || 
            INVENTORY == WEST ||
            INVENTORY == ATTACK || 
            INVENTORY == RADAR ||
            INVENTORY == HELP) {

          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == PICK_ITEM) {
        cout << "Please enter a new key for PICK_ITEM now: ";
        while (!(cin >> PICK_ITEM) ||
            PICK_ITEM == CONTINUE_STORY || 
            PICK_ITEM == SHOW_STATS ||  
            PICK_ITEM == INVENTORY || 
            PICK_ITEM == QUIT_GAME || 
            PICK_ITEM == DROP_ITEM || 
            PICK_ITEM == EQUIP_ITEM ||
            PICK_ITEM == UNEQUIP_ITEM || 
            PICK_ITEM == SHOP || 
            PICK_ITEM == MOVE || 
            PICK_ITEM == WHERE ||
            PICK_ITEM == NORTH || 
            PICK_ITEM == EAST ||
            PICK_ITEM == SOUTH || 
            PICK_ITEM == WEST ||
            PICK_ITEM == ATTACK || 
            PICK_ITEM == RADAR ||
            PICK_ITEM == HELP) {

          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == DROP_ITEM) {
        cout << "Please enter a new key for DROP_ITEM now: ";
        while (!(cin >> DROP_ITEM) || 
            DROP_ITEM == CONTINUE_STORY || 
            DROP_ITEM == SHOW_STATS || 
            DROP_ITEM == INVENTORY || 
            DROP_ITEM == PICK_ITEM || 
            DROP_ITEM == QUIT_GAME || 
            DROP_ITEM == EQUIP_ITEM ||
            DROP_ITEM == UNEQUIP_ITEM || 
            DROP_ITEM == SHOP || 
            DROP_ITEM == MOVE || 
            DROP_ITEM == WHERE ||
            DROP_ITEM == NORTH || 
            DROP_ITEM == EAST ||
            DROP_ITEM == SOUTH || 
            DROP_ITEM == WEST ||
            DROP_ITEM == ATTACK || 
            DROP_ITEM == RADAR ||
            DROP_ITEM == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == EQUIP_ITEM) {
        cout << "Please enter a new key for EQUIP_ITEM now: ";
        while (!(cin >> EQUIP_ITEM) || 
            EQUIP_ITEM == CONTINUE_STORY || 
            EQUIP_ITEM == SHOW_STATS || 
            EQUIP_ITEM == INVENTORY || 
            EQUIP_ITEM == PICK_ITEM || 
            EQUIP_ITEM == DROP_ITEM || 
            EQUIP_ITEM == QUIT_GAME||
            EQUIP_ITEM == UNEQUIP_ITEM || 
            EQUIP_ITEM == SHOP || 
            EQUIP_ITEM == MOVE || 
            EQUIP_ITEM == WHERE ||
            EQUIP_ITEM == NORTH || 
            EQUIP_ITEM == EAST ||
            EQUIP_ITEM == SOUTH || 
            EQUIP_ITEM == WEST ||
            EQUIP_ITEM == ATTACK || 
            EQUIP_ITEM == RADAR ||
            EQUIP_ITEM == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == UNEQUIP_ITEM) {
        cout << "Please enter a new key for UNEQUIP_ITEM now: ";
        while (!(cin >> UNEQUIP_ITEM) || 
            UNEQUIP_ITEM == CONTINUE_STORY || 
            UNEQUIP_ITEM == SHOW_STATS || 
            UNEQUIP_ITEM == INVENTORY || 
            UNEQUIP_ITEM == PICK_ITEM || 
            UNEQUIP_ITEM == DROP_ITEM || 
            UNEQUIP_ITEM == EQUIP_ITEM ||
            UNEQUIP_ITEM == QUIT_GAME|| 
            UNEQUIP_ITEM == SHOP || 
            UNEQUIP_ITEM == MOVE || 
            UNEQUIP_ITEM == WHERE ||
            UNEQUIP_ITEM == NORTH || 
            UNEQUIP_ITEM == EAST ||
            UNEQUIP_ITEM == SOUTH || 
            UNEQUIP_ITEM == WEST ||
            UNEQUIP_ITEM == ATTACK || 
            UNEQUIP_ITEM == RADAR ||
            UNEQUIP_ITEM == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == SHOP) {
        cout << "Please enter a new key for SHOP now: ";
        while (!(cin >> SHOP) || 
            SHOP == CONTINUE_STORY || 
            SHOP == SHOW_STATS || 
            SHOP == INVENTORY || 
            SHOP == PICK_ITEM || 
            SHOP == DROP_ITEM || 
            SHOP == EQUIP_ITEM ||
            SHOP == UNEQUIP_ITEM || 
            SHOP == QUIT_GAME|| 
            SHOP == MOVE || 
            SHOP == WHERE ||
            SHOP == NORTH || 
            SHOP == EAST ||
            SHOP == SOUTH || 
            SHOP == WEST ||
            SHOP == ATTACK || 
            SHOP == RADAR ||
            SHOP == HELP) {          
            std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == MOVE) {
        cout << "Please enter a new key for MOVE now: ";
        while (!(cin >> MOVE) || 
            MOVE == CONTINUE_STORY || 
            MOVE == SHOW_STATS || 
            MOVE == INVENTORY || 
            MOVE == PICK_ITEM || 
            MOVE == DROP_ITEM || 
            MOVE == EQUIP_ITEM ||
            MOVE == UNEQUIP_ITEM || 
            MOVE == SHOP || 
            MOVE == QUIT_GAME || 
            MOVE == WHERE ||
            MOVE == NORTH || 
            MOVE == EAST ||
            MOVE == SOUTH || 
            MOVE == WEST ||
            MOVE == ATTACK || 
            MOVE == RADAR ||
            MOVE == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == WHERE) {
        cout << "Please enter a new key for WHERE now: ";
        while (!(cin >> WHERE) || 
            WHERE == CONTINUE_STORY || 
            WHERE == SHOW_STATS || 
            WHERE == INVENTORY ||  
            WHERE == PICK_ITEM || 
            WHERE == DROP_ITEM || 
            WHERE == EQUIP_ITEM ||
            WHERE == UNEQUIP_ITEM || 
            WHERE == SHOP || 
            WHERE == MOVE || 
            WHERE == QUIT_GAME ||
            WHERE == NORTH || 
            WHERE == EAST ||
            WHERE == SOUTH || 
            WHERE == WEST ||
            WHERE == ATTACK || 
            WHERE == RADAR ||
            WHERE == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == NORTH) {
        cout << "Please enter a new key for NORTH now: ";
        while (!(cin >> NORTH) || 
            NORTH == CONTINUE_STORY || 
            NORTH == SHOW_STATS || 
            NORTH == INVENTORY ||  
            NORTH == PICK_ITEM || 
            NORTH == DROP_ITEM || 
            NORTH == EQUIP_ITEM ||
            NORTH == UNEQUIP_ITEM || 
            NORTH == SHOP || 
            NORTH == MOVE || 
            NORTH == WHERE ||
            NORTH == QUIT_GAME || 
            NORTH == EAST ||
            NORTH == SOUTH || 
            NORTH == WEST ||
            NORTH == ATTACK || 
            NORTH == RADAR ||
            NORTH == HELP) {          
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == EAST) {
        cout << "Please enter a new key for EAST now: ";
        while (!(cin >> EAST) ||
            EAST == CONTINUE_STORY || 
            EAST == SHOW_STATS || 
            EAST == INVENTORY || 
            EAST == PICK_ITEM || 
            EAST == DROP_ITEM || 
            EAST == EQUIP_ITEM ||
            EAST == UNEQUIP_ITEM || 
            EAST == SHOP || 
            EAST == MOVE || 
            EAST == WHERE ||
            EAST == NORTH || 
            EAST == RADAR ||
            EAST == SOUTH || 
            EAST == WEST ||
            EAST == ATTACK || 
            EAST == QUIT_GAME ||
            EAST == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == SOUTH) {
        cout << "Please enter a new key for SOUTH now: ";
        while (!(cin >> SOUTH) || 
            SOUTH == CONTINUE_STORY || 
            SOUTH == SHOW_STATS || 
            SOUTH == INVENTORY || 
            SOUTH == PICK_ITEM || 
            SOUTH == DROP_ITEM || 
            SOUTH == EQUIP_ITEM ||
            SOUTH == UNEQUIP_ITEM || 
            SOUTH == SHOP || 
            SOUTH == MOVE || 
            SOUTH == WHERE ||
            SOUTH == NORTH || 
            SOUTH == EAST ||
            SOUTH == QUIT_GAME || 
            SOUTH == WEST ||
            SOUTH == ATTACK || 
            SOUTH == RADAR ||
            SOUTH == HELP) {            
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == WEST) {
        cout << "Please enter a new key for WEST now: ";
        while (!(cin >> WEST) || 
            WEST == CONTINUE_STORY || 
            WEST == SHOW_STATS || 
            WEST == INVENTORY || 
            WEST == PICK_ITEM || 
            WEST == DROP_ITEM || 
            WEST == EQUIP_ITEM ||
            WEST == UNEQUIP_ITEM || 
            WEST == SHOP || 
            WEST == MOVE || 
            WEST == WHERE ||
            WEST == NORTH || 
            WEST == EAST ||
            WEST == SOUTH || 
            WEST == QUIT_GAME ||
            WEST == ATTACK || 
            WEST == RADAR ||
            WEST == HELP) {
          std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == ATTACK) {
        cout << "Please enter a new key for ATTACK now: ";
        while (!(cin >> ATTACK) || 
            ATTACK == CONTINUE_STORY || 
            ATTACK == SHOW_STATS || 
            ATTACK == INVENTORY || 
            ATTACK == PICK_ITEM || 
            ATTACK == DROP_ITEM || 
            ATTACK == EQUIP_ITEM ||
            ATTACK == UNEQUIP_ITEM || 
            ATTACK == SHOP || 
            ATTACK == MOVE || 
            ATTACK == WHERE ||
            ATTACK == NORTH || 
            ATTACK == EAST ||
            ATTACK == SOUTH || 
            ATTACK == WEST ||
            ATTACK == QUIT_GAME || 
            ATTACK == RADAR ||
            ATTACK == HELP) {
            std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      if (key == RADAR) {
        cout << "Please enter a new key for RADAR now: ";
        while (!(cin >> RADAR) || 
            RADAR == CONTINUE_STORY || 
            RADAR == SHOW_STATS || 
            RADAR == INVENTORY || 
            RADAR == PICK_ITEM || 
            RADAR == DROP_ITEM || 
            RADAR == EQUIP_ITEM ||
            RADAR == UNEQUIP_ITEM || 
            RADAR == SHOP || 
            RADAR == MOVE || 
            RADAR == WHERE ||
            RADAR == NORTH || 
            RADAR == EAST ||
            RADAR == SOUTH || 
            RADAR == WEST ||
            RADAR == ATTACK || 
            RADAR == QUIT_GAME ||
            RADAR == HELP) {
            std::cout << "Please enter a valid, single character that isn't already in use: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
    default: 
      break;
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
  char option;
    while (true) {
        cout << "\nEnter an option (? or h for help, c to continue story, q to quit): ";
        if (!(cin >> option)) {
            // If the input isn't an int, clear it and retry
            cin.clear(); // Clear err
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a valid letter. See the help menu for commands (type 'h' for help).\n";
            continue; // continue
        }
        long unsigned int* skillChoice = nullptr;
	      if (option == ATTACK) { // Attack enemies
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
                  else break;
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
                if (equipped["Weapon"].getName() != "") {
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
        }
        else if (option == CONTINUE_STORY) { // Continue the story
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
        }
        else if (option == HELP || option == '?') { // Returns the help menu
                help();
                return option;
        }
        else if (option == INVENTORY) { // Check ../include/headers/inventory.h for this function
                inventory();
                return option;
        }
        else if (option == SHOW_STATS) { // Returns user's stata
                stats();
                return option;
        }
        else if (option == PICK_ITEM) {// Picks up item from the ground (this is also in ../include/headers/inventory.h)
                pick(currentSect.getGround());
                return option;
        }
        else if (option == EQUIP_ITEM) { // This is ALSO in ../include/headers/inventory.h
                equip();
                return option;
        }
        else if (option == UNEQUIP_ITEM) { // I wonder where this could be... maybe ../include/headers/inventory.h?
                item templateItem = item("", "", 0);
                unequip(templateItem);
                return option;
        }
        else if (option == DROP_ITEM) { // Yep, also in ../include/headers/inventory.h
                drop(currentSect.getGround());
                return option;
        }
        else if (option == QUIT_GAME) { // Quits the game 
                cout << "Goodbye, " << name << "." << endl;
                return option;
        }
        else if (option == RADAR) { // Radar to scan for enemies in the current sector
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
        }
        else if (option == NORTH) { // Move north but faster than m > n
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
        }
        else if (option == SOUTH) { // Move south but faster than m > s
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
        }
        else if (option == EAST) { // Move east but faster than m > e
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
        }
        else if (option == WEST) { // Move west but faster than m > w
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
        }
        else if (option == MOVE) { // Move function (allows using u(p), d(own), l(eft), r(ight) instead of n, s, e, w)
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
        }
        else if (option == WHERE) { // Checks where the user is
                cout << "You are currently in " << currentSect.getName() << "\n" << "Your current coordinates are (" << currCoords.first << ", " << currCoords.second << ")." << endl;
                return option;
        }
        else if (option == SHOP) { // Opens shop (not complete)
                shop();
                return option;
        }
        else if (option == OPTIONS) {
              settings();
              return option;
        }
        else { // Self explanatory
                cout << "Invalid input, please try again\n";
                return option;
        }
    }
  std::cin.clear();
  std::cin.ignore();
  return option;
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

