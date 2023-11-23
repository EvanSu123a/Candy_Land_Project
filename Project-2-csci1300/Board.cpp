#include "Board.h"

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
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player1_position = 0;
    _player2_position = 18;
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
        return false;
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