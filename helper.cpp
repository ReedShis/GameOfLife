#include "helper.h"
#include "Player.h"
#include "Board.h"

int split(string input_string, char separator, string arr[], const int ARR_SIZE)
{
    int start = 0;
    int counter = 0;
    bool ifSeperator = false;
    for (unsigned int i = 0; i < input_string.length(); i++)
    {
        if (counter == ARR_SIZE)
        {
            return -1;
        }
        if (input_string[i] == separator)
        {
            ifSeperator = true;
            arr[counter] = input_string.substr(start, i - start);
            start = i + 1;
            counter++;
        }
    }
    if (input_string.length() == 0)
        return 0;
    if (!ifSeperator)
    {
        arr[0] = input_string;
        return 1;
    }
    else
    {
        arr[counter] = input_string.substr(start, input_string.length() - start);
    }
    counter++;
    return counter;
}
