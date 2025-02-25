#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

struct Advisor {
    string name;
    string ability;
};

class Player
{
private:
    string _name;
    int _strength, _stamina, _wisdom, _pride_points, _age;

    bool _path_choice; // false = Cub Training, true = Straight to Pride Lands
    int advisorIndex = 0;

public:
    //default
    Player();
    //paramaterized
    Player(string name, int age, int strength, int stamina, int wisdom, bool path_choice);
    //setters
    void setName(string name);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setWisdom(int wisdom);
    void setPride(int pride_points);
    void setAge(int age);
    void setPathChoice(bool path_choice);
    
    // Getters
    string getName() const;
    int getStrength() const;
    int getStamina() const;
    int getWisdom() const;
    int getPride() const;
    int getAge() const;
    bool getPathChoice() const;

    // Other Member Functions
    void trainCub(); // Increase stats when cub is trained
    void toPrideLands(); // Apply stat changes for going straight to pride lands
    void printStats(int playerNumber) const; // Print all stats for the Player
    void selectCharacter(bool chosenCharacters[]);

    // Advisor functions
    void setAdvisor(int index, bool advisorAvailability[]); // Assign advisor by index
    int getAdvisorIndex() const; // Get current advisor index
    void displayAdvisor() const; // Print advisor information
};

#endif 