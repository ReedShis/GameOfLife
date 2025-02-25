#ifndef ADVISORS_H
#define ADVISORS_H

#include "Player.h"

// Define an array of advisors
const int NUM_ADVISORS = 5; // Number of advisors
const Advisor ADVISORS[NUM_ADVISORS + 1] = { // +1 for "No Advisor"
    {"None", "No special ability"},       // Index 0: No advisor
    {"Rafiki", "Invisibility"},
    {"Nala", "Night Vision"},
    {"Sarabi", "Energy Manipulation"},
    {"Zazu", "Weather Control"},
    {"Sarafina", "Super Speed"}
};

#endif
