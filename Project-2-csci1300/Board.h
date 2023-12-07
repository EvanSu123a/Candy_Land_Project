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
};



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

    void generateCandyStore();

    void loadCandyStores(vector <Candy>);


    void displayCandyStore(int);
    void displayCandy(Candy);
    Candy buyFromCandyStore(int);


    void generateTreasureTiles();

    void generateSpecialTile();

    bool isSpecialTile(int);

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

    void makeTileAGummyTile(int, int);
    // bool isTileAGummyTile(int);
    // int getGummyValue(int);
};

#endif
