#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
class Board
{
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE];  //first array is for which path, second is position along the board
    static const int _MAX_PLAYERS = 2;
    int _player_count;
    int _player_position[_MAX_PLAYERS][2];   // The position of the player, which path it is on


    Player _players[_MAX_PLAYERS];  // Array of Player objects
    

public:
    Board();
    Board(int player_count, Player players[], bool path_choice[]);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    bool movePlayer(int player_index);
    int getPlayerPosition(int player_index, bool path_choice) const;
    void displayTile(int player_index, int pos);
    void initializeTiles(bool path_type);
    bool isPlayerOnTile(int player_index, int pos, int path_type);
    void applyTileEffects(int player_index);


//functions for main menu
bool displayMainMenu(int playerIndex);
void displayPlayerStats(int playerIndex);
void displayPlayerAdvisor(int playerIndex);
// void displayPlayerPosition(int playerIndex);  // outdated
void displayPlayerAdvisorChoice(int playerIndex);

bool isPlayerAtEnd(int playerIndex);

};
#endif
