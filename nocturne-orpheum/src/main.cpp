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

void incrementProg() {
  std::cout << story[progress];
  history.push_back(story[progress]);
  progress++;
}

void decrementProg() {
  // Pop from the history vector
  history.pop_back();
  progress--;
}

void decrementProg(int times) {
  if (times > progress) {
    cout << "Invalid entry. Current progress is " << progress << ".\n";
  }
  for (int i = 0; i < times; i++) {
    history.pop_back();
    progress--;
  }
}
// Main game loop w/ story
int main() { // Story starts from here, core functionality is in the decision() function and other header files, ilke inventory.h or move.h
    incrementProg(); // 0
    while (!(cin >> seconds) || seconds < 1 || seconds > 20) {
      std::cout << "Please enter a valid number from 1 - 20 seconds: ";
      std::cin.clear(); std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    std::cin.clear();
    std::cin.ignore();
    incrementProg(); // 1
    incrementProg(); // 2
    std::string op = "";
    std::getline(std::cin, op);
    while (tolower(op[0]) != 't' && tolower(op[0]) != 's') {
      cout << "You entered " << op << ".\n";
      cout << "Please enter either 't' for the tutorial or 's' to skip to the story: ";
      std::cin.clear();
      std::getline(std::cin, op);
    }
    std::cin.clear();
    if (tolower(op[0]) == 's') { progress += 7; std::cin.clear(); }
    else if (tolower(op[0]) == 't') {
      // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.clear();
      currentSect.putOnGround(dullSword);
      currentSect.putOnGround(chippedHelmet);
      currentSect.putOnGround(revivalStone);
      incrementProg(); // 3
      if (next() == 'q') return 0;
      incrementProg(); // 4
      if (next() == 'q') return 0;
      incrementProg(); // 5
      if (next() == 'q') return 0;
      enemy first("Test", 1, 1);
      enemy second("Other Test", 1, 5);
      if (next() == 'q') return 0; // Part of ../include/headers/helpers.h
      currentSect.putOnGround(first);
      currentSect.putOnGround(second);
      incrementProg(); // 6
      if (equipped["Weapon"] == item("", "", 0)) { incrementProg(); progress++; } // 7, skip 8
      else progress++; // 8, skip 7
      if (next() == 'q') return 0;
      if (stat["Current HP"] <= 0) {
        if (equipped["Artifact 1"] == revivalStone || equipped["Artifact 2"] == revivalStone || equipped["Artifact 3"] == revivalStone || equipped["Artifact 4"] == revivalStone || equipped["Artifact 5"] == revivalStone) {
          cout << "You had the revival stone and have been brought back to life! Welcome back, " << name << ".\n";
          stat["Current HP"] = stat["HP"] / 1.1;
          if (equipped["Artifact 1"] == revivalStone) equipped["Artifact 1"] = templateItem;
          if (equipped["Artifact 2"] == revivalStone) equipped["Artifact 2"] = templateItem;
          if (equipped["Artifact 3"] == revivalStone) equipped["Artifact 3"] = templateItem;
          if (equipped["Artifact 4"] == revivalStone) equipped["Artifact 4"] = templateItem;
          if (equipped["Artifact 5"] == revivalStone) equipped["Artifact 5"] = templateItem;

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
    incrementProg(); // 9, end of tutorial
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
    std::cout << name << std::endl;
  }
  incrementProg(); // 10
  incrementProg(); // 11
  getline(std::cin, guideName);
  if (guideName == "" || guideName == "\n") getline(std::cin, guideName);
  npc* guide = new npc(guideName, "guide");
  std::cout << "Huh, " << guide -> getName();
  incrementProg();
  incrementProg();
  sleep(seconds * 1500); // Longer wait since this is a LOT of text
  std::cout << "\033[2J"; // Clear screen (multiplatform, system("CLS | clear") is annoying)
  std::cout << "\033[1;1H"; // Move cursor to the top left of the screen
  incrementProg();
  if (next() == 'q') return 0;
  return 0;
}
