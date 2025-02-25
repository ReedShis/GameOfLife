#ifndef HELPER_H
#define HELPER_H

#include <string>
#include "Board.h"
using namespace std;

// had to move split function becasue it didn't want to compile across multiple.cpp's
int split(string input_string, char separator, string arr[], const int ARR_SIZE);

//add any other helper functions later

#endif
