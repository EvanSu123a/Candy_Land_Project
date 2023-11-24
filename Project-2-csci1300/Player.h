#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <vector>
#include "structs.h"
using namespace std;



class Player
{
    private:
        string _player_name;
        string _character_name;
        int _stamina;
        int _gold;
        int _max_stamina;
        int _max_gold;
        int _max_candy_count_to_be_owned;
        vector <Candy> _inventory;
        int _current_candy_amount;

        bool _can_player_move;
        int _turns_player_cannot_move_for;
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
        
        //setters
        void setPlayerName(string);
        void setPlayerCharacterName(string);
        void setPlayerStamina(int);
        void setPlayerGold(int);
        void setCanPlayerMove(bool);
        void setTurnsPlayerCannotMoveFor(int);
        //getters
        string getPlayerName();
        string getPlayerCharacterName();
        int getPlayerStamina();
        int getPlayerGold();
        int getCurrentCandyAmount();
        bool getCanPlayerMove();
        int getTurnsPlayerCannotMoveFor();

        
        void addCandyToInventory(Candy);
        
        //you can remove candy by position or by name
        void removeCandyFromInventory(int);

        Candy getCandyFromInventory(int);

        void printInventory();

        
        /*
        use candy
        check which type of candy the user is using
        if the player uses a magical candy modify the own user's 
        */



};

#endif