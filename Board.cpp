#include "Board.h"
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

#include "Board.h"
#include "Player.h" // Ensure the Player class is included for the constructor and player details
#include "Tile.h"
#include "Advisors.h"

void Board::initializeBoard()
{
    // Initialize board with both paths
    // Generate the board for both lanes independently
    // Cub Training (Top Lane) and Straight to the Pridelands (Bottom Lane)
    initializeTiles(false); // Top lane
    initializeTiles(true);  // Bottom lane

    // Now, place each player on the correct lane based on their path choice
    for (int i = 0; i < _player_count; i++)
    {
        if (_players[i].getPathChoice() == false) // Player chose top lane (Cub Training)
        {
            _player_position[i][0] = 0; // Player is on the top lane (Cub Training)
        }
        else // Player chose bottom lane (Straight to the Pridelands)
        {
            _player_position[i][1] = 0; // Player is on the bottom lane (Straight to the Pridelands)
        }
    }
}

void Board::initializeTiles(bool path_type)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1)
        {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        }
        else if (i == 0)
        {
            // Set the first tile as Grey for start  (Y = grey since G = Green)
            temp.color = 'Y';
        }
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count))
        {
            temp.color = 'G';
            green_count++;
        }
        else
        {

            int color_choice = rand() % 100; // use a percent out of 100 to simulate the different percentages a tile may be
            if (path_type)                   // "Straight to the Pridelands"
            {
                // First half of the lane (25% Graveyard, 25% Hyena, 20% Advisor, 5% Oasis)
                if (i < total_tiles / 2)
                {
                    if (color_choice < 25)
                    {
                        temp.color = 'R'; // Graveyard (Red)
                    }
                    else if (color_choice < 50)
                    {
                        temp.color = 'N'; // Hyena (Brown)
                    }
                    else if (color_choice < 70)
                    {
                        temp.color = 'B'; // Oasis (Blue)
                    }
                    else if (color_choice < 90)
                    {
                        temp.color = 'P'; // Counseling (Pink)
                    }
                    else
                    {
                        temp.color = 'U'; // Challenge (Purple)
                    }
                }
                // Second half of the lane (15% Graveyard, 15% Hyena, 20% Advisor, 25% Oasis)
                else
                {
                    if (color_choice < 15)
                    {
                        temp.color = 'R'; // Graveyard (Red)
                    }
                    else if (color_choice < 30)
                    {
                        temp.color = 'N'; // Hyena (Brown)
                    }
                    else if (color_choice < 50)
                    {
                        temp.color = 'B'; // Oasis (Blue)
                    }
                    else if (color_choice < 70)
                    {
                        temp.color = 'P'; // Counseling (Pink)
                    }
                    else
                    {
                        temp.color = 'U'; // Challenge (Purple)
                    }
                }
            }
            else // "Cub Training"
            {
                // Throughout the game (20% Graveyard, 20% Hyena, 15% Advisor)
                if (color_choice < 20)
                {
                    temp.color = 'R'; // Graveyard (Red)
                }
                else if (color_choice < 40)
                {
                    temp.color = 'N'; // Hyena (Brown)
                }
                else if (color_choice < 55)
                {
                    temp.color = 'P'; // Counseling (Pink)
                }
                else if (color_choice < 80)
                {
                    temp.color = 'B'; // Oasis (Blue)
                }
                else
                {
                    temp.color = 'U'; // Challenge (Purple)
                }
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[path_type][i] = temp;
    }
}

// Default constructor
Board::Board()
{
    _player_count = 1;

    //     // Initialize player position
    _player_position[0][0] = 0;
}

Board::Board(int player_count, Player players[], bool path_choice[])
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Store the Player objects in the _players array
    for (int i = 0; i < _player_count; i++)
    {
        _players[i] = players[i]; // Copy player properties from the passed array
        // Initialize player positions based on their path choice
        if (path_choice[i] == false)
        {                               // Top track (Cub Training)
            _player_position[i][0] = 0; // Start at position 0 on the top track
            _players[i].setPathChoice(0);
        }
        else
        {                               // Bottom track (Straight To)
            _player_position[i][1] = 0; // players on bottom
            _players[i].setPathChoice(1);
        }
    }

    // Initialize tiles

    initializeBoard();
}

bool Board::isPlayerOnTile(int playerIndex, int tilePos, int path_type)
{
    // cout << playerIndex << endl;
    bool pathChoice = _players[playerIndex].getPathChoice();
    // int x;
    // cout << pathChoice << " " << path_type << endl;
    // cin >> x;
    // cout << tilePos << endl;
    return _player_position[playerIndex][pathChoice] == tilePos && path_type == pathChoice;
}

void Board::displayTile(int path_type, int pos)
{
    // string space = "                                       ";
    string color = "";
    // int player = isPlayerOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[path_type][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[path_type][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[path_type][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[path_type][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[path_type][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[path_type][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[path_type][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[path_type][pos].color == 'Y')
    {
        color = GREY;
    }
    // Check if any player is on this tile
    // bool playersontile = 0;
    string playerSymbols = "";
    for (int i = 0; i < _player_count; i++)
    {
        if (isPlayerOnTile(i, pos, path_type))
        {
            if (!playerSymbols.empty())
            {
                playerSymbols += "&"; 
            }
            playerSymbols += to_string(i + 1); // Use player numbers (1, 2)
        }
    }
    // cout << playersontile << endl;
    //  Display the tile with or without players
    if (!playerSymbols.empty())
    {
        cout << color << "|" << playerSymbols << "|" << RESET;
    }
    else
    {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int path_type)
{

    for (int i = 0; i < _BOARD_SIZE; i++)
    {

        displayTile(path_type, i);
    }
    cout << endl;
}

// Display Board and do Tile effects
void Board::displayBoard()
{
    // Display top lane (Cub Training)
    displayTrack(0);

    cout << endl;

    // Display bottom lane (Straight to the Pridelands)
    displayTrack(1);

    // debug to check names
    //  for (int i = 0; i < _player_count; ++i) {
    //  cout << "Player " << i + 1 << " name: " << _players[i].getName() << endl;}
}

void Board::applyTileEffects(int playerIndex)
{
    // Validate player index
    if (playerIndex < 0 || playerIndex >= _player_count)
    {
        return;
    }

    // Determine the player's path and position
    bool pathChoice = _players[playerIndex].getPathChoice();
    int tilePos = _player_position[playerIndex][pathChoice];

    // Get a copy of the tile the player is currently on
    Tile currentTile = _tiles[pathChoice][tilePos];

    // What type of tile was landed on
    cout << _players[playerIndex].getName() << " landed on a ";

    switch (currentTile.color)
    {
    case 'R':
        cout << "Red (Graveyard) tile.";
        break;
    case 'G':
        cout << "Green (Grassland) tile.";
        break;
    case 'B':
        cout << "Blue (Oasis) tile.";
        break;
    case 'N':
        cout << "Brown (Hyena) tile.";
        break;
    case 'P':
        cout << "Pink (Counseling) tile.";
        break;
    case 'U':
        cout << "Purple (Challenge) tile.";
        break;
    case 'O':
        cout << "Orange (Pride Rock) tile.";
        break;
    case 'Y':
        cout << "Grey (Start) tile.";
        break;
    default:
        cout << "Mystery tile.";
        break;
    }
    cout << endl;

    // Apply the tile effect to the player
    _players[playerIndex] = currentTile.applyTileAffect(_players[playerIndex]);
}

bool Board::movePlayer(int playerIndex)
{
    // Validate player index
    if (playerIndex < 0 || playerIndex >= _player_count)
    {
        return false;
    }

    // Determine the player's chosen path (top or bottom track)
    bool pathChoice = _players[playerIndex].getPathChoice();

    // Get the current position of the player on their chosen path
    int currentPosition = _player_position[playerIndex][pathChoice];

    // Roll the spinner (1-6)
    int spinnerResult = rand() % 6 + 1;
    cout << _players[playerIndex].getName() << " spins the spinner and rolls a " << spinnerResult << "!" << endl;

    // Calculate the new position
    int newPosition = currentPosition + spinnerResult;

    // Ensure the player does not move past the last tile
    if (newPosition >= _BOARD_SIZE)
    {
        newPosition = _BOARD_SIZE - 1; // Clamp to last tile
    }

    // Apply the tile's effect at the new position
    cout << _players[playerIndex].getName() << " moves to position " << newPosition << "." << endl;

    // Simulate the effect of the tile
    Player updatedPlayer = _players[playerIndex];
    char tileColor = _tiles[pathChoice][newPosition].getColor();

    switch (tileColor)
    {
    case 'B':
    { // Oasis
        cout << "You've found an oasis! Extra turn awarded." << endl;

        // Extra turn logic
        int extraRoll = rand() % 6 + 1;
        int extraPosition = newPosition + extraRoll;

        if (extraPosition >= _BOARD_SIZE)
        {
            extraPosition = _BOARD_SIZE - 1;
        }

        cout << _players[playerIndex].getName() << " moves an extra " << extraRoll
             << " tiles to position " << extraPosition << "." << endl;

        newPosition = extraPosition; // Update position after extra turn
        break;
    }

    case 'R':
    { // Graveyard
        cout << "Oh no! You've landed in the graveyard and move back 10 tiles." << endl;
        int backPosition = newPosition - 10;
        if (backPosition < 0)
        {
            backPosition = 0; // Clamp to start of the board
        }
        cout << _players[playerIndex].getName() << " moves to position " << backPosition
             << " without triggering further effects." << endl;
        newPosition = backPosition; // Update position
        return true;
        break;
    }

    case 'N':
    { // Hyenas
        cout << "The hyenas chase you back to your previous position!" << endl;
        cout << _players[playerIndex].getName() << " moves to position " << currentPosition
             << " without triggering further effects." << endl;
        newPosition = currentPosition; // Revert to previous position
        return true;
        break;
    }

    default:

        break;
    }

    // Update the player's position and stats
    _player_position[playerIndex][pathChoice] = newPosition;
    _players[playerIndex] = updatedPlayer;

    //  cout << _players[playerIndex].getName() << "'s new position is " << newPosition << "." << endl;

    // Apply tile effects for the current player only
    applyTileEffects(playerIndex);

    return true; // Movement successful
}

bool Board::displayMainMenu(int playerIndex)
{
    int choice;
    bool moved = false; // Tracks whether the player has moved

    do
    {
        cout << "-- Main Menu for Player " << playerIndex + 1 << " --" << endl;
        cout << "1. Display Player Stats" << endl;
        cout << "2. Review Character" << endl;
        cout << "3. Check Position" << endl;
        cout << "4. Review Advisor" << endl;
        cout << "5. Move Forward" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayPlayerStats(playerIndex);
            break;
        case 2:
            cout << "Character: " << _players[playerIndex].getName() << endl;
            cout << "Age: " << _players[playerIndex].getAge() << " years" << endl;

            // Ask if they want to know a fact about their character for a second layer
            char factChoice;
            cout << "Would you like to know a fun fact about " << _players[playerIndex].getName() << "? (y/n): ";
            cin >> factChoice;

            if (factChoice == 'y' || factChoice == 'Y')
            {
                // Check the character name and display the fun fact
                string name = _players[playerIndex].getName();
                if (name == "Tyler")
                {
                    cout << "Tyler's first studio album, \"Goblin,\" was released in 2011." << endl;
                }
                else if (name == "Boldy")
                {
                    cout << "Fun fact about Boldy: Born James Clay Jones III on August 9, 1982, in Detroit, Michigan, Boldy James was raised in a struggling family in one of the most dangerous inner-city neighborhoods in the US, notorious for its high crime rates and constant violence. However, music gave him the motivation required to pursue a career in the industry and become a successful rapper." << endl;
                }
                else if (name == "Gunn")
                {
                    cout << "Fun fact about Gunn: Most people probably assume that Westside Gunn is from New York City, but that isn't the case. While he is from New York State, he's from Buffalo which is over six hours away from the city." << endl;
                }
                else if (name == "Freddie")
                {
                    cout << "Fun fact about Freddie: Freddie Gibbs played football at Ball State University on an athletic scholarship but was expelled from college." << endl;
                }
                else if (name == "Earl")
                {
                    cout << "Fun fact about Earl: Most people would agree that it's pretty obvious that Earl Sweatshirt is a stage name. However, it still wouldn't be too far out to think that Earl Sweatshirt's first name was actually Earl. That isn't the case at all, though.  Earl Sweatshirt was born Thebe Neruda Kgositsile." << endl;
                }
                else
                {
                    cout << "No fun fact available." << endl;
                }
            }
            break;
        case 3:
            displayBoard(); // Updated to call displayBoard instead of displayPlayerPosition
            break;
        case 4:
            _players[playerIndex].displayAdvisor();
            break;
        case 5:
            cout << "Moving player " << playerIndex + 1 << " forward..." << endl;
            movePlayer(playerIndex); // Move the player
            moved = true;            // Indicate that the player moved
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return moved; // Return whether the player moved or not
}

// Function to display player stats (directly using Player's getters)
void Board::displayPlayerStats(int playerIndex)
{
    cout << "Player " << playerIndex + 1 << "'s Stats:" << endl;
    cout << "Strength: " << _players[playerIndex].getStrength() << endl;
    cout << "Stamina: " << _players[playerIndex].getStamina() << endl;
    cout << "Wisdom: " << _players[playerIndex].getWisdom() << endl;
    cout << "Pride Points: " << _players[playerIndex].getPride() << endl;
    cout << endl;
}

// really redundant but good to just have something work, could probably be done in either the movePlayer or isPlayerOnTile
bool Board::isPlayerAtEnd(int playerIndex)
{

    // Determine the player's chosen path
    bool pathChoice = _players[playerIndex].getPathChoice();

    // The last tile on the board is the last index in the respective path
    int lastTilePosition = _BOARD_SIZE - 1;

    // Check if the player is at the last tile of their chosen path
    if (_player_position[playerIndex][pathChoice] == lastTilePosition)
    {
        return true; // Player has reached the end
    }

    return false; // Player has not reached the end
}
