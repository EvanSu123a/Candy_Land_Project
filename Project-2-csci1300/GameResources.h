#include <iostream>
#include <vector>
#include "structs.h"
#include "Player.h"
using namespace std;

struct Character
{
    string name;
    int stamina;
    int gold;
    string candies_owned[9];
    bool picked;

};


#ifndef GANERESOURCES_H
#define GAMERESOURCES_H

class GameResources
{
    private:
        int _characters_count;
        vector <Character> _character_list;
        vector <Candy> _all_candy_data;

    public:
        GameResources();
        void loadCharacters(); 
        void printCharacterList();
};

#endif
