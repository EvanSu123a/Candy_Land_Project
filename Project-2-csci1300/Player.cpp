#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

Player :: Player()
{
    _player_name = "";
    _character_name = "";
    _stamina = 0;
    _gold = 0;
    _max_stamina = 100;
    _max_gold = 100;
    _max_candy_count_to_be_owned = 9;
    _current_candy_amount = 0;
    _can_player_move = true;
    _turns_player_cannot_move_for = 0;
}

void Player :: setPlayerName(string player_name)
{
    _player_name = player_name;
}
void Player :: setPlayerCharacterName(string character_name)
{
    _character_name = character_name;
}
void Player :: setPlayerStamina(int stamina)
{
    _stamina = stamina;
}
void Player :: setPlayerGold(int gold)
{
    _gold = gold;
}
void Player :: setCanPlayerMove(bool can_player_move)
{
    _can_player_move = can_player_move;
}
void Player :: setTurnsPlayerCannotMoveFor(int turns_player_cannot_move)
{
    _turns_player_cannot_move_for = turns_player_cannot_move;
}


string Player :: getPlayerName()
{
    return _player_name;
}
string Player :: getPlayerCharacterName()
{
    return _character_name;
}
int Player :: getPlayerStamina()
{
    return _stamina;
}
int Player :: getPlayerGold()
{
    return _gold;
}
bool Player :: getCanPlayerMove()
{
    return _can_player_move;
}
int Player :: getTurnsPlayerCannotMoveFor()
{
    return _turns_player_cannot_move_for;
}

void Player :: addCandyToInventory(Candy candy_to_be_addded)
{
    if(_current_candy_amount >= 9)
    {
        cout << "You do not have sufficient place in the candy inventory" <<endl;
    }
    else
    {
        _inventory.push_back(candy_to_be_addded);
        _current_candy_amount += 1;
    }
}

/*
remove candy from inventory
0 1 2 3 4 5 6 7 8
keep everything before the position the same
change everything from position to 7 to the candy that is in position+1 to 8
set 8 to empty
minues 1 from 
*/
void Player:: removeCandyFromInventory(int position)
{
    Candy not_a_candy {"", "", 0, ""};
    for(int i = position; i < 8; i++)
    {
        _inventory[i] = _inventory[i+1];
    }
    _inventory[8] = not_a_candy;
    _current_candy_amount -= 1;
}

Candy Player :: getCandyFromInventory(int position)
{
    return _inventory.at(position);
}

void Player :: printInventory()
{
    for(int i = 0; i < _current_candy_amount; i++)
    {
        cout << "[" << _inventory.at(i).name << "]";
        if(i%3 == 2)
        {
            cout << endl;
        }
    }
}

