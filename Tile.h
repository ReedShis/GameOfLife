#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Player.h"
using namespace std;

struct Tile
{
    char color;  // Store the color as a character (e.g., 'G' for Green)
    // Default constructor that sets the color to 'G' (Green)
    Tile();

    // Parameterized constructor
    Tile(char c);

    // Getter for tile color
    char getColor() const;

    // Setter tile color
    void setColor(char c);
    //tile affect function
    Player applyTileAffect(Player player);
};

#endif
