#include <string>
#include <vector>
#include <headers/variables.h>
// Story snippet
std::vector<std::string> story = {
  /* Tutorial starts here*/
  /*0*/"[SYSTEM] Please enter a speed from 1 - 20. The lower the speed, the faster text will erase from the screen.\nIt will be easier to read at higher numbers, but the game will move faster at a lower number.\nYou can change this later in the game options.\nEnter a value now: ",
  /*1*/"[SYSTEM] Welcome to Zandris, part 1 Nocturne: Orpheum",
  /*2*/"[SYSTEM] Would you like to start the tutorial or skip to the story? (For tutorial, type \"t\", for the story, type \"s\"): ",
  /*3*/"[TUTORIAL] Welcome to the world.\n\nYou start as a human with all your stats set to 1, HP at 10, but as time goes on, you can level up your stats, learn skills, collect weapons, and find gear.\n\nGear and weapons can also have their own buffs and skills as you get further in the game.\n\nHere, take this [BASIC DULL SWORD], [CHIPPED HELMET], and [REVIVAL STONE] (press p to pick up).\n",
  /*4*/"[TUTORIAL] Watch it, there's an enemy ahead!\n",
  /*5*/"[TUTORIAL] You don't have a weapon equipped! If you haven't picked up a weapon, try using p to pick find one. If you have, use e to equip your weapon.\n",
  /*6*/"[TUTORIAL] You have a weapon! Use 'a' to attack the enemy!\n",
  /*7*/"[TUTORIAL] Good job. You've defeated your first enemy. If you want to relax your arms, use 'u' to unequip your weapon! This is optional, of course.\nIf you'd like to move around, use 'm' and pick a direction.\n",
  /*8*/"[TUTORIAL] The tutorial has now been finished. Welcome to\nSYSTEM ERROR, ALL PLAYER DATA HAS BEEN CLEARED"
  /*Story starts here*/
  /*9*/"[SYSTEM] Alright, looks like you know the controls. Now, welcome to Zandris. You may have lost your memory after the collapse of Orpheum, so allow me to clue you in.\nThe sky you see above you is actually the ocean K'ver, and those stars are living leviathans. They've been docile until now, so we don't know what their intentions are, but at least they give us light.\nMost people, including you, have been corrupted by the side effects of magic and Orpheum collapsing. You, however, are special, patient 0. You can earn your memories back.\n",
  /*10*/"[SYSTEM] You've awaken in a cold dungeon cell. Your head is pounding, and you don't recognize anything, not even your own name.\nHeels can be heard clacking down the dungeon hall, and a woman tailed by two guards comes into view.\nShe looks important, and she bears a sigil that looks royal.\n",
  /*11*/"[PLAYER] Who... who are you?",
  /*12*/"[SYSTEM] Suddenly, you hear a faint ringing in your head, along with a voice",
  /*13*/"[???] Lyran Nevel... so you've finally awaken",
  /*14*/"[SYSTEM] The voice fades as quickly as it came, tuning you back into the real world.\nThe lady is looking down at you like an insect, then walks in your cell and takes a seat",
  /*15*/"[Lady] The king sent me here to kill you. I would have, too, but there's no use now.",
  /*16*/"[SYSTEM] You look at her with a cold expression, refusing to speak until answered. She realizes this and sighs, exasperated",
  /*17*/"[Ethymia Lazarus] You're in the kingdom of Aurelia under the rule of king (king's name). I'm Ethymia Lazarus, second in line for the throne",
  /*18*/"[PLAYER] Why am I here? Why are you keeping me alive?",
  /*19*/"[SYSTEM] Ethymia doesn't answer, getting up to leave the cell",
  /*20*/"[Ethymia Lazarus] I will have a guard of mine bring you food and fresh clothing soon. Don't be difficult, just take the offerings. We have much to dicuss tomorrow.",
  /*21*/"[PLAYER] Tsk, not answering anything... The kingdom of Aurelia, you say? Must be what that sigil on her robes were",
  /*22*/"[SYSTEM] A flashback of your past flashes.\nYou see a map, but a lot of it is unclear, and the language isn't decipherable.\nOne of these islands must be Aurelia.\nYou count 9 islands, surrounded by some kind of water body, which has more land around it."
};

std::vector<std::string> history = {};
