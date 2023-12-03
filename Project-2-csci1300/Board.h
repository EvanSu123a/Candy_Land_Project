#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "structs.h"
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;


int generateRandom(int min, int max);
int drawCardsAndMove(string color_player_is_currently_on);





struct Tile
{
    string color;
    string tile_type;

    bool is_special_tile;
    bool is_treasure;
    bool is_gummy_tile;
    bool is_candy_store;
    int gummy_tile_value;

    /*potential tile effects
    a bool variable check is it a special tile or normal tile
    special tile
        30% shortcut tile
        30% icecreamstop tile
        30% gumdrop forest tile
        10% gingerhead house tile
    treasure 6 of them
        30% stamina refill
        10% gold windfall
        30% robber repel
        30% candy acquisition
            70% jellybean of vigor
            30% treasure hunters truffle
    candystore 3 of them

    other special tiles
    gummy tile when user use a candy on them
    */
};

/*
make candyStore a struct
candy store will contain a array of candies sold
*/

struct CandyStores
{
    string name;
    int position;
    vector <Candy> candy_store_stocks;
};


class Board 
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    CandyStores _candy_stores[_MAX_CANDY_STORE];
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    int _player1_position;
    int _player2_position;
public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    /*
    generate 3 candy stores

    first candy store a random magenta tile between first 0-26
    0, 3, 6, 9, 12, 15, 18, 21, 24
    generate random number between 0 and 8
    multiply number by 3 and place candy store there

    second candy store a random green between 27-53
    28, 31, 34, 37, 40, 43, 46, 49, 52
    generate random number between 0 and 8
    multipply number by 3 and add 28

    third candy store a random blue between 54-81
    56, 59, 62, 65, 68, 71, 74, 77, 80
    generate random number between 0 and 8
    multiply number by 3 and add 56
    
    make all these 3 tiles a candy store tile
    and add all of these 3 positions to the candy store 

    */
    void generateCandyStore();

/*
load candystore
takes in a vector of Candy which is all the candies in this game
there are 11 candies in the game
randomly generate 3 number from 0-10 and check if they are duplicates
return a candystore struct with those 3 candies being filled
*/

    void loadCandyStores(vector <Candy>);


/*
display candystore
display welcome message and display the candy with those price

buy from candy store 
ask user to buy candy
check if the candy is in the candy store
return the candy the user bought
*/

    void displayCandyStore(int);
    void displayCandy(Candy);
    Candy buyFromCandyStore();

/*
check if tile is a special tile
    returns true if it is a special tile
    returns false if it is a normal tile
*/


/*
generate treasure tiles
int trasure count
while(trasures < 6)
{
    generate number between 3-81
    check if that tile is a regular tile
    if it is a regular tile
    {
        make it a treasure tile
        add 1 to treasure count
        determine what treasure it is

        30% stamina refill
        10% gold windfall
        30% robber repel
        30% candy acquisition
            70% jellybean of vigor
            30% treasure hunters truffle
        number between 0-99
        0-29 = stamina refill
        30-39 = gold windfall
        40-69 = robber repel
        70-90 = jellybean of vigor
        91-100 = treasure hunters truffle

        make that tile a treasure tile 

    }
}
*/

    void generateTreasureTiles();

/*
generate special tiles
21 special tiles in the game

int special tile count
while(special tile count < 21)
    {
        generate a random number from 3-81
        check if it is a special tile
        if it is not already a special time
        {
            make it a special tile 
            special tile count +=1
            determine what special tile it is

            random number between 0-99 
            0-29 = shortcut tile
            30-59 = ice cream stop tile
            60-89 = gumdrop forest tile
            90-99 = gingerbread house tile

        }
    }    
  }
*/
    void generateSpecialTile();


/*
check special tile
when a player land on a tile check for special tile and do its actions
takes in a int the amount player just moved
if it is a special tile
    if it is a shortcut tile
        move the player 4 moves forward
    else if it is a icecreamshop tile
        draw another card and make player move forward a certain amount of tile
    else if it is a gumdrop forest tile
        move to user back 4 tiles
        randomly generate a number between 5-10
        and lose that much gold from user
    else if it is a gingerbread house tile
        move back the amount the user just moved
        and check if user have immunity candy
        if user have immunity candy
            the user loses that candy
*/
    bool isSpecialTile(int);

    
/*
check for same tile constraints
return true if the 2 player are on same tile
return false if they are not
move the first person who arrived there back 1 tile
*/
    bool checkForSameTileConstraints(int);

    void excecuteShortCutTile(int);
    void excecuteIceCreamShopTile(int, string);
    int excecuteGumDropForestTile(int);
    


    bool setPlayerOnePosition(int);
    bool setPlayerTwoPosition(int);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    string getTileColor(int);
    string getTileEffect(int);
    string getTileType(int);
    Tile getTile(int);
    int getPlayerOnePosition() const;
    int getPlayerTwoPosition() const;
    
    

    bool addCandyStore(int);
    bool isPositionCandyStore(int);


    bool movePlayerOne(int tile_to_move_forward);
    bool movePlayerTwo(int tile_to_move_forward);
};

#endif
