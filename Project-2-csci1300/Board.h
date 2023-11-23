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







struct Tile
{
    string color;
    string tile_type;
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
    */
};

/*
make candyStore a struct
candy store will contain a array of candies sold
*/


class Board 
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
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

/*
generate candystore
there are 11 candies in the game
randomly generate 3 number from 0-10 and check if they are duplicates
return a candystore struct with those 3 candies being filled
*/

/*
display candystore
display welcome message and display the candy with those price

buy from candy store 
ask user to buy candy
check if the candy is in the candy store
return the candy the user bought
*/
/*
check if tile is a special tile 

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



    bool setPlayerOnePosition(int);
    bool setPlayerTwoPosition(int);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    string getTileColor(int);
    int getPlayerOnePosition() const;
    int getPlayerTwoPosition() const;

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 

    bool movePlayerOne(int tile_to_move_forward);
    bool movePlayerTwo(int tile_to_move_forward);
};

#endif
