#include "Board.h"

//function used to generate random numbers

int generateRandom(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

int drawCardsAndMove(string color_player_is_currently_on)
{
    int step_to_move_forward = 0;
    string color_of_card;
    bool isDouble = false;
    int number_to_determine_color =  generateRandom(0,99);
    int number_to_determine_double = generateRandom(0,99);

    //determine color
    if(number_to_determine_color <= 32)
    {
        color_of_card = "magenta";
    }
    else if(number_to_determine_color >= 33 && number_to_determine_color <= 65)
    {
        color_of_card = "green";
    }
    else
    {
        color_of_card = "blue";
    }
    //determine double
    if(number_to_determine_double <= 74)
    {
        isDouble = false;
    }
    else
    {
        isDouble = true;
    }

    if(isDouble)
    {
        cout << "You got a double " << color_of_card << "card. " << "Your game piece advanced two " << color_of_card << " tiles." << endl;
    }
    else
    {
        cout << "You got a " << color_of_card << " card. " << "Your game piece advanced to the next " << color_of_card << " tiles." << endl;
    }

    //determine steps moved forward
    if(color_player_is_currently_on == MAGENTA && color_of_card == "magenta")
    {
        step_to_move_forward = 3;
    }
    else if(color_player_is_currently_on == MAGENTA && color_of_card == "green")
    {
        step_to_move_forward = 1;
    }
    else if(color_player_is_currently_on == MAGENTA && color_of_card == "blue")
    {
        step_to_move_forward = 2;
    }
    else if(color_player_is_currently_on == GREEN && color_of_card == "green")
    {
        step_to_move_forward = 3;
    }
    else if(color_player_is_currently_on == GREEN && color_of_card == "blue")
    {
        step_to_move_forward = 1;
    }
    else if(color_player_is_currently_on == GREEN && color_of_card == "magenta")
    {
        step_to_move_forward = 2;
    }
    else if(color_player_is_currently_on == BLUE && color_of_card == "blue")
    {
        step_to_move_forward = 3;
    }
    else if(color_player_is_currently_on == BLUE && color_of_card == "magenta")
    {
        step_to_move_forward = 1;
    }
    else if(color_player_is_currently_on == BLUE && color_of_card == "green")
    {
        step_to_move_forward = 2;
    }

    if(isDouble)
    {
        step_to_move_forward += 3;
    }
    cout << "you move forward " << step_to_move_forward << " positions" << endl;
    return step_to_move_forward;




    return 0;
}

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regularTile", false, false, false, false, 0};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regularTile", false, false, false, false, 0};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player1_position = 0;
    _player2_position = 1;
}
//display 1 tile
void Board::displayTile(int position)
{
    //check if position is on board
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    //print out color tiles
    cout << target.color << " ";
    //if a player is on tile print out player number
    if (position == _player1_position)
    {
        cout << "1";
    }
    else if(position == _player2_position)
    {
        cout << "2";
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

void Board :: generateCandyStore()
{
    //generate first candystore on a megenta tile from 0-26
    int num_1 = generateRandom(0, 8);
    int first_candy_store_position = num_1 * 3;
    addCandyStore(first_candy_store_position);
    _tiles[first_candy_store_position].is_candy_store = true;
    _tiles[first_candy_store_position].tile_type = "candyStore";
    //generate second candystore on a green tile between 27-53
    int num_2 = generateRandom(0, 8);
    int second_candy_store_position = num_2 * 3 + 28;
    addCandyStore(second_candy_store_position);
    _tiles[second_candy_store_position].is_candy_store = true;
    _tiles[second_candy_store_position].tile_type = "candyStore";
    //generate third candystore on a blue tile between 54-81
    int num_3 = generateRandom(0, 8);
    int third_candy_store_position = num_3 * 3 +56;
    addCandyStore(third_candy_store_position);
    _tiles[third_candy_store_position].is_candy_store = true;
    _tiles[third_candy_store_position].tile_type = "candyStore";
}

void Board :: loadCandyStores(vector <Candy> list_of_all_candies)
{
    //pick 3 random candy for the first candy store
    int seperate_numbers_1 = 0;
    vector <Candy> candies_1;
    bool is_candy_used_1[] = {false, false, false, false, false, false, false, false, false, false, false};
    //while there are less then 3 seperate candy picked
    while(seperate_numbers_1 < 3)
    {
        int candy_position = generateRandom(0,10);
        if(!is_candy_used_1[candy_position])
        {
            seperate_numbers_1 += 1;
            is_candy_used_1[candy_position] = true;
            candies_1.push_back(list_of_all_candies.at(candy_position));
        }
    }
    //load the first candyStore
    CandyStores candystore_1;
    candystore_1.name = "candystore 1";
    candystore_1.position = _candy_store_position[0];
    candystore_1.candy_store_stocks.push_back(candies_1.at(0));
    candystore_1.candy_store_stocks.push_back(candies_1.at(1));
    candystore_1.candy_store_stocks.push_back(candies_1.at(2));
    _candy_stores[0] = candystore_1;

    //pick 3 random candy for the second candy store
    int seperate_numbers_2 = 0;
    vector <Candy> candies_2;
    bool is_candy_used_2[] = {false, false, false, false, false, false, false, false, false, false, false};
    while(seperate_numbers_2 < 3)
    {
        int candy_position = generateRandom(0,10);
        if(!is_candy_used_2[candy_position])
        {
            seperate_numbers_2 += 1;
            is_candy_used_2[candy_position] = true;
            candies_2.push_back(list_of_all_candies.at(candy_position));
        }
    }
    //load the second candyStore
    CandyStores candystore_2;
    candystore_2.name = "candystore 2";
    candystore_2.position = _candy_store_position[1];
    candystore_2.candy_store_stocks.push_back(candies_2.at(0));
    candystore_2.candy_store_stocks.push_back(candies_2.at(1));
    candystore_2.candy_store_stocks.push_back(candies_2.at(2));
    _candy_stores[1] = candystore_2;

    //pick 3 random candy for the third candy store
    int seperate_numbers_3 = 0;
    vector <Candy> candies_3;
    bool is_candy_used_3[] = {false, false, false, false, false, false, false, false, false, false, false};
    while(seperate_numbers_3 < 3)
    {
        int candy_position = generateRandom(0,10);
        if(!is_candy_used_3[candy_position])
        {
            seperate_numbers_3 += 1;
            is_candy_used_3[candy_position] = true;
            candies_3.push_back(list_of_all_candies.at(candy_position));
        }
    }
    //load the second candyStore
    CandyStores candystore_3;
    candystore_3.name = "candystore 3";
    candystore_3.position = _candy_store_position[2];
    candystore_3.candy_store_stocks.push_back(candies_3.at(0));
    candystore_3.candy_store_stocks.push_back(candies_3.at(1));
    candystore_3.candy_store_stocks.push_back(candies_3.at(2));
    _candy_stores[2] = candystore_3;

}

void Board :: displayCandyStore(int position)
{
    if(position >=0 && position <= 26)
    {
        cout << "Welcome to " << _candy_stores[0].name <<endl;
        cout << "Here is a list of candies in the candy store." << endl;
        cout << endl;
        for(int i = 0; i < 3; i++)
        {
            cout << i+1 << " :" << endl;
            displayCandy(_candy_stores[0].candy_store_stocks[i]);
            cout << endl;
        }
    }
    else if(position >= 27 && position <= 53)
    {
        cout << "Welcome to " << _candy_stores[1].name <<endl;
        cout << "Here is a list of candies in the candy store." << endl;
        cout << endl;
        for(int i = 0; i < 3; i++)
        {
            cout << i+1 << " :" << endl;
            displayCandy(_candy_stores[1].candy_store_stocks[i]);
            cout << endl;
        }
    }
    else
    {
        cout << "Welcome to " << _candy_stores[2].name <<endl;
        cout << "Here is a list of candies in the candy store." << endl;
        cout << endl;
        for(int i = 0; i < 3; i++)
        {
            displayCandy(_candy_stores[2].candy_store_stocks[i]);
            cout << endl;
        }
    }
    
}

void Board :: displayCandy(Candy candy_to_be_displayed)
{
    cout << "Name: " << candy_to_be_displayed.name << endl;
    cout << "Description: " << candy_to_be_displayed.description << endl;
    cout << "Effect: " <<candy_to_be_displayed.effect_type <<endl;
    cout << "Effect value: " << candy_to_be_displayed.effect_value <<endl;
    cout << "Candy type: " <<candy_to_be_displayed.candy_type <<endl;
    cout << "Price: " <<candy_to_be_displayed.price <<endl;
}

Candy Board :: buyFromCandyStore(int player_position)
{   
    Candy this_candy;
    int candy_name = 0;
    cout << "What candy would you like to purchase, enter the number corresponding to the candy" << endl;
    cin >> candy_name;
    if(player_position >= 0 && player_position <= 26)
    {
        CandyStores this_candy_store = _candy_stores[0];
        vector <Candy> all_candy_in_store = this_candy_store.candy_store_stocks;
        if(candy_name >= 1 && candy_name <= 3)
        {
            this_candy = all_candy_in_store.at(candy_name -1);
        }
        else
        {
            cout << "Candy unavaliable" << endl;
        }
        
    }
    else if(player_position >= 27 && player_position <= 53)
    {
        CandyStores this_candy_store = _candy_stores[1];
        vector <Candy> all_candy_in_store = this_candy_store.candy_store_stocks;
        if(candy_name >= 1 && candy_name <= 3)
        {
            this_candy = all_candy_in_store.at(candy_name -1);
        }
        else
        {
            cout << "Candy unavaliable" << endl;
        }
    }
    else
    {
        CandyStores this_candy_store = _candy_stores[2];
        vector <Candy> all_candy_in_store = this_candy_store.candy_store_stocks;
        if(candy_name >= 1 && candy_name <= 3)
        {
            this_candy = all_candy_in_store.at(candy_name -1);
        }
        else
        {
            cout << "Candy unavaliable" << endl;
        }
    }
    return this_candy;
    
}
//generate treasure tiles
void Board :: generateTreasureTiles()
{
    int treasure_count = 0;
    //generate 6 different random number that is not on a special tile
    while(treasure_count < 6)
    {
        int treasure_position = generateRandom(3,81);
        if(_tiles[treasure_position].tile_type == "regularTile")
        {
            _tiles[treasure_position].is_treasure = true;
            treasure_count += 1;
            //randomly generate what type of treasure it is
            int treasure_type = generateRandom(0, 99);
            if(treasure_type <= 29)
            {
                _tiles[treasure_position].tile_type = "staminaRefill";
            }
            else if(treasure_type >= 30 && treasure_type <= 39)
            {
                _tiles[treasure_position].tile_type = "goldWindfall";
            }
            else if(treasure_type >= 40 && treasure_type <= 69)
            {
                _tiles[treasure_position].tile_type = "robbersRepel";
            }
            else
            {
                //candy acquisitiion
                //decide what type of candy acquisition it would be
                int type_of_candy_acquisition = generateRandom(0,99);
                if(type_of_candy_acquisition <= 70)
                {
                    _tiles[treasure_position].tile_type = "jellybeanOfVigor";
                }
                else
                {
                    _tiles[treasure_position].tile_type = "treasureHunterTruffle";
                }
            }
        }
    }
}

void Board :: generateSpecialTile()
{
    //generate 21 different special tiles
    int special_tile_count = 0;
    while(special_tile_count < 21)
    {
        int special_tile_position = generateRandom(3,81);
        if(_tiles[special_tile_position].tile_type == "regularTile")
        {
            _tiles[special_tile_position].is_special_tile = true;
            special_tile_count += 1;
            //decide what type of special tile it is
            int special_tile_type = generateRandom(0,99);
            if(special_tile_type <= 29)
            {
                _tiles[special_tile_position].tile_type = "shortcutTile";
            }
            else if(special_tile_type >= 30 && special_tile_type <= 59)
            {
                _tiles[special_tile_position].tile_type = "iceCreamShopTile";
            }
            else if(special_tile_type >= 60 && special_tile_type <= 84)
            {
                _tiles[special_tile_position].tile_type = "gumdropForestTile";
            }
            else
            {
                _tiles[special_tile_position].tile_type = "gingerbreadHouseTile";
            }
        }
    }
}

bool Board :: isSpecialTile(int position)
{
    string tile_effect = _tiles[position].tile_type;
    if(tile_effect == "regularTile")
    {
        return false;
    }
    else
    {
        return true;
    }
}



bool Board :: checkForSameTileConstraints(int person_who_arrived_first)
{
    if(_player1_position == _player2_position)
    {
        //the first person arrives move back one
        if(person_who_arrived_first == 1)
        {
            cout << "Player 1 and player 2 landed on the same tile, player 1 move back 1 tile" << endl;
            _player1_position -= 1;
            return true;
        }
        else
        {
            cout << "Player 1 and player 2 landed on the same tile, player 2 move back 1 tile" << endl;
            _player2_position -=1;
            return true;
        }
    }
    else
    {
        return false;
    }
}

void Board :: excecuteShortCutTile(int player_number)
{
    //add 4 to player position
    if(player_number == 1)
    {
        cout << "Player 1 you stepped on a shortcut tile, you move forward 4 position" << endl;
        _player1_position += 4;
    }
    else if(player_number == 2)
    {
        cout << "Player 2 stepped on a shortcut tile, you move forward 4 position" << endl;
        _player2_position += 4;
    }
}

void Board :: excecuteIceCreamShopTile(int player_number, string color)
{
    //draw another card and move by that much
    if(player_number == 1)
    {
        cout << "Player 1 you stepped on a icecream shop tile, you get to draw another card" << endl;
        int steps_to_move = drawCardsAndMove(color);
        _player1_position += steps_to_move;
    }
    else if(player_number == 2)
    {
        cout << "Player 2 you stepped on a icecream shop tile, you get to draw another card" << endl;
        int steps_to_move = drawCardsAndMove(color);
        _player2_position += steps_to_move;
    }
}

int Board :: excecuteGumDropForestTile(int player_number)
{
    //move the player back 4 tiles
    if(player_number == 1)
    {
        cout << "Player 1 you stepped on a gum drop forest tile, you backwards 4 tiles, ";
        if(_player1_position <= 5)
        {
            _player1_position = 1;
        }
        else
        {
            _player1_position -= 4;
        }
    }
    else if(player_number == 2)
    {
        cout << "Player 2 you stepped on a gum drop forest tile, you backwards 4 tiles, ";
        if(_player1_position <= 6)
        {
            _player1_position = 2;
        }
        else
        {
            _player1_position -= 4;
        }
    }

    //generate random number of gold player losses
    int num_gold_loss = generateRandom(5, 10);
    cout << "and you lost " << num_gold_loss <<" gold" << endl;
    return num_gold_loss;
}




//setters for player positions
bool Board::setPlayerOnePosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player1_position = new_position;
        return true;
    }
    return false;
}

bool Board::setPlayerTwoPosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player2_position = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

string Board :: getTileColor(int position)
{
    return _tiles[position].color;
}
string Board :: getTileEffect(int position)
{
    return _tiles[position].tile_type;
}
string Board :: getTileType(int position)
{
    return _tiles[position].tile_type;
}
Tile Board :: getTile(int position)
{
    return _tiles[position];
}

//getters for player positions
int Board::getPlayerOnePosition() const
{
    return _player1_position;
}

int Board::getPlayerTwoPosition() const
{
    return _player2_position;
}


bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}


//to move player1 or player2 a certain steps ahead
bool Board::movePlayerOne(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player1_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        _player1_position = 82;
    }
    _player1_position = new_player_position;
    return true;
}

bool Board::movePlayerTwo(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player2_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        _player2_position = 82;
        return false;
    }
    _player2_position = new_player_position;
    return true;
}