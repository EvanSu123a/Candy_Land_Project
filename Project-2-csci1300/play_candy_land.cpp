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


//function used to generate a random number
int generateRandom(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

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
    Board game_board = Board();

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

    

    

    while(!player_one_win && !player_two_win)
    {
        //player 1 turn
        int player1_current_position = game_board.getPlayerOnePosition();
        string player1_current_tile_color = game_board.getTileColor(player1_current_position);
        int player_1_moves = drawCardsAndMove(player1_current_tile_color);
        
        //moveplayer returns true if you can be moved forward and returns false if you are at castle
        player_one_win = !(game_board.movePlayerOne(player_1_moves));

        //player 2 turn
        int player2_current_position = game_board.getPlayerTwoPosition();
        string player2_current_tile_color = game_board.getTileColor(player2_current_position);
        int player_2_moves = drawCardsAndMove(player2_current_tile_color);

        player_two_win = !(game_board.movePlayerTwo(player_2_moves));

        game_board.displayBoard();


    }
    cout << game_board.getPlayerOnePosition()<<endl;
    cout << game_board.getPlayerTwoPosition()<<endl;

    all_game_resources.print_player1_stats();
    
    return 0;
}