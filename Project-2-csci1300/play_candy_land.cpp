#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GameResources.h"
#include "Board.h"


#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;



/*
draw cards
25% 
25%
25%
8%
8%
9%
then
update player position
function returns the number of steps moved ahead
takes in the current color of the tilt player are on

first generate a number between 0-99
0-32 = MAGENTA
33-65 = GREEN
66-99 = BLUE

then generate another number to determine single or double
0-74 = single
75-99 = double
bool isDouble
int number_move = 0;
number move + 3 if it is a double card
if same color +3
if current magenta into green = 1
if current magenta into blue = 2
6 if else statements
return move needed
*/







/*
do calamities
take in a tile position
check if the tile position is a regular tile
if it is a special tile then end function
if it is a regular tile generate a number between 0-99
if it is 0-39 then it is a calamity
if it is 40-99 then it is not a calamity
if it is a calamity generate another number between 0-99
0-29 = candy bandits
30-64 = lost in a lollipop labrinth
65-79 = candy avalanch
80-99 = sticky taffy trap
*/

/*

*/

int main()
{
    //set random seed
    srand(time(0));

    //variables to determine if game is over
    bool player_one_win = false;
    bool player_two_win = false;

    //starting game initialize all game resources
    GameResources all_game_resources = GameResources();
    all_game_resources.loadCharacters();
    all_game_resources.loadInCandies();

    //generate board and special tiles
    //generate candystores
    Board game_board = Board();
    game_board.generateCandyStore();
    vector <Candy> all_candies_in_this_game = all_game_resources.getAllCandyInThisGame();
    game_board.loadCandyStores(all_candies_in_this_game);
    //generate treasures
    game_board.generateTreasureTiles();
    //generate other special tiles
    game_board.generateSpecialTile();


    //int num_participants = 2;
    //loading players
    string player1_name;
    string player1_character_selection;
    string player2_name;
    string player2_character_selection;
    cout << "Welcome to the game of candyland. Player 1 please enter your name" <<endl;
    cin >> player1_name;
    cout << "Awesome! Here are a list of characters a player can select from:" << endl;
    all_game_resources.printCharacterList();
    cin >> player1_character_selection;
    all_game_resources.load_player_one(player1_character_selection, player1_name);

    cout << "Player 2 please enter your name" << endl;
    cin >> player2_name;
    cout << "Awesome! Here are a list of characterss a player can select from: " << endl;
    all_game_resources.printCharacterList();
    cin >> player2_character_selection;
    all_game_resources.load_player_two(player2_character_selection, player2_name);


    int player_1_moves = 0;
    int player_2_moves = 0;
    while(!player_one_win && !player_two_win)
    {
        //player 1 turn
        int player_one_action = 0;
        cout << "Player 1 it is your turn" << endl;
        cout << "Enter 1 to draw a card" << endl;
        cout << "Enter 2 to use a candy" << endl;
        cout << "Enter 3 to display stats" << endl;
        cin >> player_one_action;
        if(player_one_action == 1)
        {
            int player1_current_position = game_board.getPlayerOnePosition();
            string player1_current_tile_color = game_board.getTileColor(player1_current_position);
            player_1_moves = drawCardsAndMove(player1_current_tile_color);
            player_one_win = !(game_board.movePlayerOne(player_1_moves));
            cout << "Here is the board after your move" << endl;
            game_board.displayBoard();
            cout << endl;
        }
        else if (player_one_action == 2)
        {

        }
        else if(player_one_action == 3)
        {
            all_game_resources.print_player1_stats();
            cout << endl;
        }
        //moveplayer returns true if you can be moved forward and returns false if you are at castle
        if(player_one_win)
        {
            cout << "Player 1 wins" << endl;
            break;
        }

        //player 2 turn
        int player_2_action = 0;
        cout << "Player 2 it is your turn" << endl;
        cout << "Enter 1 to draw a card" << endl;
        cin >> player_2_action;
        if(player_2_action == 1)
        {
            int player2_current_position = game_board.getPlayerTwoPosition();
            string player2_current_tile_color = game_board.getTileColor(player2_current_position);
            player_2_moves = drawCardsAndMove(player2_current_tile_color);
            player_two_win = !(game_board.movePlayerTwo(player_2_moves));
            cout << "Here is the board after your move" << endl;
            game_board.displayBoard();
            cout << endl;
        }
        else if(player_2_action == 2)
        {

        }
        else if(player_2_action == 3)
        {
            all_game_resources.print_player2_stats();
            cout << endl;
        }
        if (player_two_win)
        {
            cout << "Player 2 wins" << endl;
            break;
        }
    }

    cout << game_board.getPlayerOnePosition()<<endl;
    cout << game_board.getPlayerTwoPosition()<<endl;


    
    return 0;
}