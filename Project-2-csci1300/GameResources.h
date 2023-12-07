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

       void applyMagicalCandy(int,int, Candy);
       void applyPoisonAndImmunityCandy(int,int, Candy);


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
        void player1LoseStamina(int);
        void player2LoseStamina(int);

        void player1SetRobbersRepel(bool);
        void player2SetRobbersRepel(bool);

        void player1AddCandy(Candy);
        void player2AddCandy(Candy);
        void player1GetJellyBeanOfVigor();
        void player2GetJellyBeanOfVigor();


        Candy findCandyFromPlayer1ByIndex(int);
        Candy findCandyFromPlayer2ByIndex(int);
        Candy findCandyFromPlayer1(string);
        Candy findCandyFromPlayer2(string);

        void immobilizePlayer1(int);
        void immobilizePlayer2(int);
        void player1Get1TurnBack();
        void player2Get1TurnBack();

        int getPlayer1Stamina();
        int getPlayer2Stamina();
        int getTurnsPlayer1CannotMove();
        int getTurnsPlayer2CannotMove();

        // void excecuteTaffyTrap(int);
};

#endif
