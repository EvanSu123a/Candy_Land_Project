#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <vector>
#include "Player.h"
#include "structs.h"
using namespace std;



class Player
{
    private:
        string _player_name;
        string _character_name;
        int _stamina;
        int _gold;
        vector <Candy> _inventory;
        int _current_candy_amount;
        /*
        bool canplayermove
        int how many turn cannot move
        if a player cannot move for 2 turn
        change canplayermove to false
        make turn cannot move to 2
        if player cannot move when it is player's turn then make turn cannot move minus by 1
        if turn cannot move == 0 then make can player move to true
        */

    public:
        
        Player();
        /*
        use candy
        check which type of candy the user is using
        if the player uses a magical candy modify the own user's 
        */



};

#endif