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
#include <headers/helpers.h> // Super important lmao, has like everything

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
      if (next() == 'q') return 0; // Part of ../include/headers/helpers.h
      currentSect.putOnGround(first);
      currentSect.putOnGround(second);
      cout << "\nWatch it, there's an enemy ahead!" << endl;
      if (equipped["Weapon"] == item("", "", 0)) cout << endl << "You don't have a weapon equipped! If you haven't picked up a weapon, try using p to pick find one. If you have, use e to equip your weapon.";
      else cout << endl << "You have a weapon! Use 'a' to attack the enemy!";
      if (next() == 'q') return 0;
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
    if (next() == 'q') return 0;
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
  if (next() == 'q') return 0;
  return 0;
}
