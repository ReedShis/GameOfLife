#include "Player.h"
#include "helper.h"  //for split func
#include "Advisors.h"
#include <iostream>
#include <fstream>


using namespace std;

// declare my split function to use later
// int split(string input_string, char separator, string arr[], const int ARR_SIZE);

// Default constructor
Player::Player() : _name(""), _strength(100), _stamina(100), _wisdom(100), _pride_points(0), _age(1) {}

// Parameterized constructor
Player::Player(string name, int age, int strength, int stamina, int wisdom, bool path_choice)
{
    _name = name;

    if (strength >= 100 && strength <= 1000) {
        _strength = strength;
    } else {
        _strength = 100;
    }

    if (stamina >= 100 && stamina <= 1000) {
        _stamina = stamina;
    } else {
        _stamina = 100;
    }

    if (wisdom >= 100 && wisdom <= 1000) {
        _wisdom = wisdom;
    } else {
        _wisdom = 100;
    }

    _path_choice = path_choice;

    _pride_points = 20000;
    _age = age;
}

// Function to select a character from a file
void Player::selectCharacter(bool chosenCharacters[])
{
    ifstream file("characters.txt");
    if (!file.is_open())
    {
        cout << "Error: Could not open characters file." << endl;
        return;
    }

    string line, characterData[5];
    string parts[6]; // Temporary storage for character details
    int characterIndex = 0;

    // Skip the first line so i can keep my column header in characters.txt
    getline(file, line);

    cout << "Character Selection Menu:" << endl;
    while (getline(file, line) && characterIndex < 5)
    {
        // Split the line into parts
        split(line, '|', parts, 6);
        
            // Skip already chosen characters
            if (!chosenCharacters[characterIndex])
            {
                cout << characterIndex + 1 << ". Name: " << parts[0] << ", Age: " << parts[1] 
                     << ", Strength: " << parts[2] << ", Stamina: " << parts[3] 
                     << ", Wisdom: " << parts[4] << ", Pride Points: " << parts[5] << endl;
            }
        
        characterData[characterIndex] = line; // Store for later
        characterIndex++;
    }
    file.close();

    // Ask the player to select a character
    int choice = 0;
    do
    {
        cout << "Select a character by entering the corresponding number: ";
        cin >> choice;
        if (choice < 1 || choice > characterIndex || chosenCharacters[choice - 1])  // have to have choice minus one so user sees characters starting at 1
        {
            cout << "Invalid choice or character already chosen. Please try again." << endl;
        }
    } while (choice < 1 || choice > characterIndex || chosenCharacters[choice - 1]);

    // Mark the selected character as chosen
    chosenCharacters[choice - 1] = true;

    // Split and assign stats to the player
   split(characterData[choice - 1], '|', parts, 6);
    _name = parts[0];
    _age = stoi(parts[1]);
    _strength = stoi(parts[2]);
    if (_strength < 100) _strength = 100;

    _stamina = stoi(parts[3]);
    if (_stamina < 100) _stamina = 100;

    _wisdom = stoi(parts[4]);
    if (_wisdom < 100) _wisdom = 100;

    _pride_points = stoi(parts[5]);

    cout << "You have chosen " << _name << "!" << endl;

}


// Getters
string Player::getName() const { return _name; }
int Player::getStrength() const { return _strength; }
int Player::getStamina() const { return _stamina; }
int Player::getWisdom() const { return _wisdom; }
int Player::getPride() const { return _pride_points; }
int Player::getAge() const { return _age; }
bool Player::getPathChoice() const {return _path_choice; }

// Setters
void Player::setName(string name) { _name = name; }
void Player::setStrength(int strength) { _strength = strength; }
void Player::setStamina(int stamina) { _stamina = stamina; }
void Player::setWisdom(int wisdom) { _wisdom = wisdom; }
void Player::setPride(int pride_points) { _pride_points = pride_points; }
void Player::setAge(int age) { _age = age; }
void Player::setPathChoice(bool path_choice) {_path_choice = path_choice; }

// Other Member Functions
void Player::trainCub()
{
    _strength += 500;
    _stamina += 500;
    _wisdom += 1000;
    _pride_points -= 5000;

}

void Player::toPrideLands()
{
    _pride_points += 5000;
    _strength += 200;
    _wisdom += 200;
    _stamina += 200;
}

void Player::printStats(int playerNumber) const
{
    //fun stats output
   /* cout<<"$$$$$$$ $$$$$$$$  $$$$$  $$$$$$$$ $$$$$$$ "<<endl;
    cout<<"$$         $$    $$   $$    $$    $$     "<<endl;
    cout<<"$$$$$$$    $$    $$$$$$$    $$    $$$$$$$ "<<endl;
    cout<<"     $$    $$    $$   $$    $$         $$ "<<endl;
    cout<<"$$$$$$$    $$    $$   $$    $$    $$$$$$$ "<<endl;
*/
    //stats output for better testing
    cout<<"############################"<<endl;
    cout<<"###   Player "<<playerNumber<< "'s Stats   ###"<<endl;
    cout<<"############################"<<endl;
    cout << "Name: " << _name << endl;
    cout << "Age: " << _age << " years" << endl;
    cout << "Strength: " << _strength << endl;
    cout << "Stamina: " << _stamina << endl;
    cout << "Wisdom: " << _wisdom << endl;
    cout << "Pride Points: " << _pride_points << endl;
    cout << endl;
}


// Advisor Function Implementations

void Player::setAdvisor(int index, bool advisorAvailability[]) {
    //cout << "setAdvisor called with advisorChoice: " << index << endl;
    if (index < 0 || index > 5) {
        cout << "Invalid advisor selection. No changes made." << endl;
        return; // Invalid index
    }

    if (advisorIndex != 0) {
        // Release the currently held advisor
        advisorAvailability[advisorIndex] = true;
    }

    // Update advisorIndex
    advisorIndex = index;

    if (index != 0) {
        // Mark the new advisor as unavailable
        advisorAvailability[index] = false;
    }

    // Output feedback
    if (advisorIndex != 0) {
        cout << "Advisor selected: " << advisorIndex << endl;
    } else {
        cout << "No advisor selected." << endl;
    }
}



int Player::getAdvisorIndex() const {
    return advisorIndex;
}

void Player::displayAdvisor() const {
    if (advisorIndex == 0) {
        cout << "No advisor currently selected." << endl;
        return;
    }

    // Define the list of advisors
    const Advisor advisors[6] = {
        {"None", "No ability"},
        {"Rafiki", "Invisibility"},
        {"Nala", "Night Vision"},
        {"Sarabi", "Energy Manipulation"},
        {"Zazu", "Weather Control"},
        {"Sarafina", "Super Speed"}
    };

    // Display the advisor's name
    cout << "Current Advisor: " << advisors[advisorIndex].name << endl;

    // Prompt the user for action
    char choice;
    cout << "Would you like to:" << endl;
    cout << "1. See their special ability" << endl;
    cout << "2. Receive words of wisdom" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice (1, 2, or 3): ";
    cin >> choice;

    if (choice == '1') {
        cout << "Special Ability: " << advisors[advisorIndex].ability << endl;
    } else if (choice == '2') {
        // Generate a random number between 0 and 6
        int randomIndex = rand() % 7;

        // Display a random motivational quote
        switch (randomIndex) {
            case 0:
                cout << "\"Believe you can and you're halfway there.\" —Theodore Roosevelt" << endl;
                break;
            case 1:
                cout << "\"It does not matter how slowly you go as long as you do not stop.\" —Confucius" << endl;
                break;
            case 2:
                cout << "\"Our greatest weakness lies in giving up. The most certain way to succeed is always to try just one more time.\" —Thomas A. Edison" << endl;
                break;
            case 3:
                cout << "\"Failure will never overtake me if my determination to succeed is strong enough.\" —Og Mandino" << endl;
                break;
            case 4:
                cout << "\"Start where you are. Use what you have. Do what you can.\" —Arthur Ashe" << endl;
                break;
            case 5:
                cout << "\"Optimism is the faith that leads to achievement. Nothing can be done without hope and confidence.\" —Helen Keller" << endl;
                break;
            case 6:
                cout << "\"Life is 10% what happens to you and 90% how you react to it.\" —Charles R. Swindoll" << endl;
                break;
            default:
                cout << "Your advisor is contemplating... Please try again." << endl;
                break;
        }
    } else if (choice == '3') {
        cout << "Exiting advisor menu." << endl;
    } else {
        cout << "Invalid choice. Exiting advisor menu." << endl;
    }
}

