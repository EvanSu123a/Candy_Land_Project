#include <iostream>
#include <vector>
#include "structs.h"
#include "Player.h"
using namespace std;

int generateRandomBetweenMaxAndMin(int, int);

struct Character
{
    string name;
    int stamina;
    int gold;
    string candies_owned[9];
    bool picked;

};

struct Riddle
{
    string riddle;
    string answer;
};


#ifndef GANERESOURCES_H
#define GAMERESOURCES_H

class GameResources
{
    private:
        int _characters_count;
        int _candy_counts;
        int _riddle_counts;

        vector <Character> _character_list;
        vector <Candy> _all_candy_data;
        vector <Riddle> _all_riddles;

        Player _player_1;
        Player _player_2;

    public:
        GameResources();
        vector <Candy> getAllCandyInThisGame();
        
        void loadCharacters(); 
        void printCharacterList();
        void loadInCandies();
        void loadInRiddles();

        bool load_player_one(string, string);
        bool load_player_two(string, string);

        void print_player1_stats();
        void print_player2_stats();

        //if 2 players land on same tile the person who arrives first move back and rob other player
        void moneyRobbery(int);


        /*
        apply poison and immunity candy function takes in a Candy
        if lucky licorice is used 
            if the other user have bubblegum blast
                use both candy and no effect happend
            else if other user have sparkling sapphire
                use both candy and no effect happend
            else if other user have caramel comet
                use both candy and no effect happends
            else
                the other user lose 10 stamina
        else if venomous vortex is used 
            if the other user have sparkling sapphire
                use both candy and no effect happends
            else if the other user have caramel comet
                use both candy and no effect happends
            else
                the ther user lose 15 stamina
        else if toxic taffy is used
            if the other user have caramel comet
                use both candy and no effect happends
            else
                the other user lose 20 stamina
        */

        /*
        use candy functions takes in a Candy
        have 1 function for player1 use candy and another function for player 2 use candy
        returns a int of the effect value
        check what type of candy it is
        if it is a magical candy 
            add stamina to the user of the candy
        else if it is a poison candy
            call apply poison and immunity candy function
        else if it is a gummy candy
            return the amount of turns that if a player stand on it they would not be able to move for(1 or 2)
        

        if a gummy candy is called in main function use the board to set the tile to be a gummy tile
        then set the value of the tile to 1 or 2 based on the return value
        if a non gummy candy is used return -1;
        
        */
       void applyMagicalCandy(Candy);
       void applyPoisonAndImmunityCandy(Candy);

       /*
apply special candy function
this function is used if the user have jellybean of vigor or treasure hunter's truffle
takes in a Candy as parameter
if the candy is jellybean of vigor
    add 50 stamina to the user
    if user stamina end up being above 100
        change user stamina to 100
else if the candy is treasure hunter's truffle
    tell the user they found a hidden treasure
    asks a riddle to the user
    if the answer is correct
        give the hidden treasure to the user
    else
        the user lose the hidden treasure
*/
        void applySpecialCandy(Candy);

/*
play rock paper scissors function returns a bool
bool is_winner_decided = false
if winner is not decided
    randomly generate a number between 0-2 for the player's move
    0 = rock
    1 = paper
    2 = scissor
    randomly generate another number between 0-2 for the computer's move
    then compare the result of player move
    if they have the same move
        do nothing
    else
        return true if player wins
        return false if the computer wins
*/


        bool play_riddle();
        bool play_rock_paper_scissors();

        void setPlayer1(Player);
        void setPlayer2(Player);
        
        int getPlayer1Gold();
        int getPlayer2Gold();

        void player1LoseGold(int);
        void player2LoseGold(int);

        void player1GainGold(int);
        void player2GainGold(int);
        
        void player1GainStamina(int);
        void player2GainStamina(int);

        void player1SetRobbersRepel(bool);
        void player2SetRobbersRepel(bool);

        void player1AddCandy(Candy);
        void player2AddCandy(Candy);
        void player1GetJellyBeanOfVigor();
        void player2GetJellyBeanOfVigor();
};

#endif
