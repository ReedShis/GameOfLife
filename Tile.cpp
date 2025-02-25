#include "Tile.h"
#include "helper.h"

#include <iostream>
#include <fstream>

// declare my split function to use later
int split(string input_string, char separator, string arr[], const int ARR_SIZE);

// Default constructor
Tile::Tile()
{
    color = 'G';
}

// Parameterized
Tile::Tile(char c)
{
    color = c;
}

char Tile::getColor() const
{
    return color;
}

void Tile::setColor(char c)
{
    color = c;
}

// Tile Affects
Player Tile::applyTileAffect(Player player)
{
    if (color == 'U')
    { // Challenge Tile (Purple)
        ifstream riddleFile("riddles.txt");
        string riddles[10];
        int count = 0;
        string line;

        if (!riddleFile.is_open())
        {
            cout << "We are out of riddles... oops." << endl;
            return player; // No changes to player stats
        }

        // Move riddles to riddle array
        while (getline(riddleFile, line) && count < 10)
        {
            riddles[count++] = line;
        }
        riddleFile.close();

        // Select a random riddle
        int randomIndex = rand() % count;
        string selectedRiddle = riddles[randomIndex];

        // Break up the riddle for later cout
        string parts[3];                      // Riddle parts for cout
        split(selectedRiddle, '|', parts, 3); // Parts array stores different parts

        string question = parts[0];
        string parameters = parts[1];
        string answer = parts[2];

        // Ask riddle
        cout << question << endl;
        cout << "(" << parameters << ")" << endl;
        cout << "Your answer: ";
        string userAnswer;
        cin >> userAnswer;

        bool isCorrect = (userAnswer == answer);
        if (!isCorrect)
        {
            // Check if player has an advisor
            if (player.getAdvisorIndex() != 0)
            {
                int randomChance = rand() % 10; // Generates 0-9
                if (randomChance == 0)
                { // 10% chance
                    cout << "Your advisor steps in with the correct answer!" << endl;
                    isCorrect = true;
                }
            }
        }

        // Result
        if (isCorrect)
        {
            cout << "Correct! You've earned 500 Wisdom Points." << endl;
            player.setWisdom(player.getWisdom() + 500);
        }
        else
        {
            cout << "Incorrect! No points gained." << endl;
            cout << "The correct answer was: " << answer << endl;
        }
    } else if (color == 'G') {  // Green Tile (Random Event)
    ifstream eventFile("random_events.txt");
    if (!eventFile.is_open()) {
        cout << "Could not load random events. The plains feel uneventful today." << endl;
        return player;
    }

    const int MAX_EVENTS = 50; // Assume a maximum number of events
    string events[MAX_EVENTS];
    int eventCount = 0;
    string line;

    getline(eventFile, line); // Skip the header line

    // Read all events into an array
    while (getline(eventFile, line) && eventCount < MAX_EVENTS) {
        events[eventCount++] = line;
    }
    eventFile.close();

    // Player's path choice
    bool pathChoice = player.getPathChoice(); // false = Cub Training, true = Pride Lands

    // Select and apply a valid event
    bool validEvent = false;

    while (!validEvent) {
        int randomIndex = rand() % eventCount;
        string selectedEvent = events[randomIndex];

        // Split the selected event
        string parts[7]; // Fields from the file
        split(selectedEvent, '|', parts, 7);

        int pathType = stoi(parts[1]);

        // Check if the event applies
        validEvent = (pathType == 2) || 
                     (pathType == 0 && !pathChoice) || 
                     (pathType == 1 && pathChoice);

        if (validEvent) {
            // Extract event details
            string description = parts[0];
            int eventAdvisor = stoi(parts[2]);
            int withoutAdvisorPoints = stoi(parts[3]);
            int withAdvisorPoints = stoi(parts[4]);
            string withAdvisorText = parts[5];
            string withoutAdvisorText = parts[6];

            // Determine if the player has the correct advisor
            int playerAdvisor = player.getAdvisorIndex();
            cout << description << endl;

            int prideChange = 0;
            if (playerAdvisor == eventAdvisor) {
                cout << withAdvisorText << endl;
                prideChange = withAdvisorPoints;
            } else {
                cout << withoutAdvisorText << endl;
                prideChange = withoutAdvisorPoints;
            }

            // Adjust player's pride points
            player.setPride(player.getPride() + prideChange);

            // Print the result
            if (prideChange > 0) {
                cout << "You gained " << prideChange << " pride points!" << endl;
            } else if (prideChange < 0) {
                cout << "You lost " << (-prideChange) << " pride points!" << endl;
            } else {
                cout << "No change in pride points." << endl;
            }
        }
    }
} 
    else
    {
        // Other cases for different tile effects
        switch (color)
        {
        case 'B': // Oasis Tile (Blue)
            cout << "You've found a peaceful oasis!" << endl;
            player.setStamina(player.getStamina() + 200);
            player.setStrength(player.getStrength() + 200);
            player.setWisdom(player.getWisdom() + 200);
            cout << "Gained 200 stamina, strength, and wisdom points! You also get an extra turn." << endl;
            break;

        case 'P':
        { // Counseling Tile (Pink)
            cout << "Welcome to the land of enrichment!" << endl;
            player.setStamina(player.getStamina() + 300);
            player.setStrength(player.getStrength() + 300);
            player.setWisdom(player.getWisdom() + 300);
            cout << "Gained 300 stamina, strength, and wisdom points!" << endl;

            cout << "Choose or switch an advisor from the list below:" << endl;

            // Display the list of advisors
            cout << "1. Rafiki - Invisibility" << endl;
            cout << "2. Nala - Night Vision" << endl;
            cout << "3. Sarabi - Energy Manipulation" << endl;
            cout << "4. Zazu - Weather Control" << endl;
            cout << "5. Sarafina - Super Speed" << endl;

            int advisorChoice = 0;
            do
            {
                cout << "Enter the number of your chosen advisor (1-5): ";
                cin >> advisorChoice;
            } while (advisorChoice < 1 || advisorChoice > 5);

            bool advisorAvailability[6] = {true, true, true, true, true, true};

            // Update the player's advisor
            player.setAdvisor(advisorChoice, advisorAvailability);
            cout << "You now have a new advisor!" << endl;
            break;
        }

        case 'R': // Graveyard Tile (Red)
            cout << "Uh-oh, you've stumbled into the Graveyard!" << endl;
            player.setStamina(player.getStamina() - 100);
            player.setStrength(player.getStrength() - 100);
            player.setWisdom(player.getWisdom() - 100);
            cout << "Lost 100 stamina, strength, and wisdom points!" << endl;
            cout << "You are forced to move back 10 tiles." << endl;
            break;

        case 'N': // Hyenas Tile (Brown)
            cout << "The Hyenas are on the prowl!" << endl;
            player.setStamina(player.getStamina() - 300);
            cout << "Lost 300 stamina points!" << endl;
            break;

        default:
            cout << "This tile has no special effects." << endl;
            break;
        }
    }

    return player;
}
