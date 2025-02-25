#include "Player.h"
#include "Board.h"
#include "Advisors.h" // Include the advisor list
#include <iostream>
#include <cstdlib> // For srand and rand
#include <ctime>   // For time
#include <fstream>

using namespace std;

int main()
{
    srand(time(0));

    bool chosenCharacters[5] = {false};  // Tracks which characters are selected
    bool advisorAvailability[6] = {true, true, true, true, true, true};  // Index 0 is unused
    Player player1, player2;

    // Character selection for Player 1
    cout << "Player 1, select your character." << endl;
    player1.selectCharacter(chosenCharacters);
    player1.printStats(1);

    // Character selection for Player 2
    cout << "Player 2, select your character." << endl;
    player2.selectCharacter(chosenCharacters);
    player2.printStats(2);

    // Path choice for Player 1 and Player 2
    bool path_choice[2] = {false, false};
    char choice;

    // Path choice for Player 1
    cout << "Player 1, choose your path: 'C' for Cub Training or 'P' for Pride Lands: " << endl;
    cin >> choice;
    if (choice == 'P' || choice == 'p')
    {
        path_choice[0] = true;
        player1.toPrideLands();
    }
    else
    {
        player1.trainCub();
        cout << "Player 1, choose your advisor:" << endl;
        for (int i = 1; i <= NUM_ADVISORS; ++i)
        { // Skip "None" (index 0)
            if (advisorAvailability[i])
            { // Only show available advisors
                cout << i << ". " << ADVISORS[i].name << " - " << ADVISORS[i].ability << endl;
            }
        }

        int advisorChoice;
        cout << "Enter the number of your advisor (1-" << NUM_ADVISORS << "): ";
        cin >> advisorChoice;

        if (advisorChoice >= 1 && advisorChoice <= NUM_ADVISORS && advisorAvailability[advisorChoice])
        {
            player1.setAdvisor(advisorChoice, advisorAvailability);
            cout << "Player 1 has chosen " << ADVISORS[advisorChoice].name << " as their advisor!" << endl;
            cout << "Advisor availability before selection: ";

        }
        else
        {
            cout << "Invalid choice or advisor not available. No advisor selected." << endl;
        }
    }

    cout << "Player 1's stats after path choice: " << endl;
    player1.printStats(1);

    // Repeat for Player 2
    cout << "Player 2, choose your path: 'C' for Cub Training or 'P' for Pride Lands: " << endl;
    cin >> choice;
    if (choice == 'P' || choice == 'p')
    {
        path_choice[1] = true;
        player2.toPrideLands();
    }
    else
    {
        player2.trainCub();
        cout << "Player 2, choose your advisor:" << endl;
        for (int i = 1; i <= NUM_ADVISORS; ++i)
        {
            if (advisorAvailability[i])
            {
                cout << i << ". " << ADVISORS[i].name << " - " << ADVISORS[i].ability << endl;
            }
        }

        int advisorChoice;

        cout << "Enter the number of your advisor (1-" << NUM_ADVISORS << "): ";
        cin >> advisorChoice;
        cout << "Player 2 entered advisorChoice: " << advisorChoice << endl;

        if (advisorChoice >= 1 && advisorChoice <= NUM_ADVISORS && advisorAvailability[advisorChoice])
        {
            player2.setAdvisor(advisorChoice, advisorAvailability);
            cout << "Player 2 has chosen " << ADVISORS[advisorChoice].name << " as their advisor!" << endl;
        }
        else
        {
            cout << "Invalid choice or advisor not available. No advisor selected." << endl;
        }
    }

    cout << "Player 2's stats after path choice: " << endl;
    player2.printStats(2);

    // Store player1 and player2 in an array
    Player players[2] = {player1, player2};

    // Create the board with updated path choices
    Board gameBoard(2, players, path_choice);

    // Main game loop
    bool gameOn = true;
    int turn = 0; // 0 for Player 1, 1 for Player 2

    while (gameOn)
    {
        // Display the board and main menu based on the current turn
        gameBoard.displayBoard();
        
        // Call displayMainMenu and check if the player moved
        bool moved = gameBoard.displayMainMenu(turn);

        if (moved)
        {
            // Only switch turns if the player moved
            turn = 1 - turn;  // Toggle between Player 1 and Player 2
        }
        cout << moved << "a" << endl;

        // Check if both players have reached the end
        bool player1AtEnd = gameBoard.isPlayerAtEnd(0);
        bool player2AtEnd = gameBoard.isPlayerAtEnd(1);

        if (player1AtEnd && player2AtEnd)
        {
            gameOn = false;  // End the game
        }
    }

    // At the end of the game, calculate Pride Points and determine the winner
    int pridePoints1 = (player1.getStamina() / 100 + player1.getStrength() / 100 + player1.getWisdom() / 100) * 1000;
    int pridePoints2 = (player2.getStamina() / 100 + player2.getStrength() / 100 + player2.getWisdom() / 100) * 1000;

    cout << "Player 1's Pride Points: " << pridePoints1 << endl;
    cout << "Player 2's Pride Points: " << pridePoints2 << endl;

    // Determine winner based on Pride Points
    if (pridePoints1 > pridePoints2)
    {
        cout << "Player 1 wins with " << pridePoints1 << " Pride Points!" << endl;
    }
    else if (pridePoints2 > pridePoints1)
    {
        cout << "Player 2 wins with " << pridePoints2 << " Pride Points!" << endl;
    }
    else
    {
        cout << "It's a tie with " << pridePoints1 << " Pride Points each!" << endl;
    }

ofstream outFile("gameStats.txt");
if (outFile.is_open()) {
    outFile << "Game Stats:" << endl;
    outFile << "----------------------------------" << endl;
    outFile << "Player 1 Stats:" << endl;
    outFile << "Stamina: " << player1.getStamina() << endl;
    outFile << "Strength: " << player1.getStrength() << endl;
    outFile << "Wisdom: " << player1.getWisdom() << endl;
    outFile << "Pride Points: " << pridePoints1 << endl;
    outFile << "----------------------------------" << endl;
    outFile << "Player 2 Stats:" << endl;
    outFile << "Stamina: " << player2.getStamina() << endl;
    outFile << "Strength: " << player2.getStrength() << endl;
    outFile << "Wisdom: " << player2.getWisdom() << endl;
    outFile << "Pride Points: " << pridePoints2 << endl;
    outFile << "----------------------------------" << endl;

    if (pridePoints1 > pridePoints2) {
        outFile << "Winner: Player 1" << endl;
    } else if (pridePoints2 > pridePoints1) {
        outFile << "Winner: Player 2" << endl;
    } else {
        outFile << "Result: It's a tie!" << endl;
    }
    outFile.close();
    cout << "Game stats saved to gameStats.txt." << endl;
} else {
    cout << "Error: Unable to open gameStats.txt for writing." << endl;
}

    return 0;
}
