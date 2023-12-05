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
    all_game_resources.loadInRiddles();
    

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

    all_game_resources.print_player1_stats();
    cout << endl << endl;
    all_game_resources.print_player2_stats();

    int player_1_moves = 0;
    int player_2_moves = 0;
    

    int player_1_visit_candy_store = 0;
    int player_2_visit_candy_store = 0;
    //player 1 visit candy store at the start of the candy store
    cout << endl;
    cout << "Player 1 would you like to visit the candystore before game start enter 1 to visit candystore and 0 to skip candy store" << endl;
    cin >> player_1_visit_candy_store;
    if(player_1_visit_candy_store == 1)
    {
        game_board.displayCandyStore(0);
        Candy candy_player_1_bought = game_board.buyFromCandyStore(0);
        int cost = candy_player_1_bought.price;
        if(all_game_resources.getPlayer1Gold() >= cost)
        {
            if(candy_player_1_bought.name != "")
            {
                all_game_resources.player1AddCandy(candy_player_1_bought);  
                all_game_resources.player1LoseGold(cost);
                all_game_resources.print_player1_stats();
            }
        }
        else
        {
            cout << "Insufficient gold" << endl;
        }
    }
    //player 2 visit the candystore at the start of the game
    cout << "Player 2 would you like to visit the candystore before game start enter 1 to visit candystore and 0 to skip candy store" <<endl;
    cin >> player_2_visit_candy_store;
    if(player_2_visit_candy_store == 1)
    {
        game_board.displayCandyStore(0);
        Candy candy_player_2_bought = game_board.buyFromCandyStore(0);
        int cost = candy_player_2_bought.price;
        if(all_game_resources.getPlayer2Gold() >= cost)
        {
            if(candy_player_2_bought.name != "")
            {
                all_game_resources.player2AddCandy(candy_player_2_bought);
                all_game_resources.player1LoseGold(cost);
                all_game_resources.print_player2_stats();
            }
        }
        else
        {
            cout << "Insufficient gold" << endl;
        }
    }
    
    

    while(!player_one_win && !player_two_win)
    {
        //player 1 turn
        int player_one_action = 0;
        while(player_one_action != 1)
        {
            cout << "Player 1 it is your turn" << endl;
            cout << endl;
            // cout << "Enter 1 to draw a card" << endl;
            // cout << "Enter 2 to use a candy" << endl;
            // cout << "Enter 3 to display stats" << endl;
            // cin >> player_one_action;
            player_one_action = 1;
            if(player_one_action == 1)
            {
                int player1_current_position = game_board.getPlayerOnePosition();
                string player1_current_tile_color = game_board.getTileColor(player1_current_position);
                player_1_moves = drawCardsAndMove(player1_current_tile_color);
                player_one_win = !(game_board.movePlayerOne(player_1_moves));
                //check for special tiles
                if(game_board.checkForSameTileConstraints(2))
                {
                    all_game_resources.moneyRobbery(2);
                    player1_current_position -=1;
                    all_game_resources.print_player1_stats();
                }
                bool current_position_is_a_special_tile_1 = game_board.isSpecialTile(player1_current_position);
                if(current_position_is_a_special_tile_1)
                {
                    string tile_type = game_board.getTileEffect(player1_current_position);
                    if(tile_type == "shortcutTile")
                    {
                        game_board.excecuteShortCutTile(1);
                    }
                    if(tile_type  == "iceCreamShopTile")
                    {
                        int player_1_pos = game_board.getPlayerOnePosition();
                        string color = game_board.getTileColor(player_1_pos); 
                        game_board.excecuteIceCreamShopTile(1, color);
                    }
                    if(tile_type == "gumdropForestTile")
                    {
                        int gold_loss = game_board.excecuteGumDropForestTile(1);
                        all_game_resources.player1LoseGold(gold_loss);
                        all_game_resources.print_player1_stats();
                    }
                    // if(tile_type == "gingerbreadHouseTile")
                    // {
                        
                    // }
                    if(tile_type == "staminaRefill")
                    {
                        cout << "Player 1 you stepped on a treasure tile, play a riddle to get it" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            int stamina_generated = generateRandom(10, 30);
                            cout << "You gained " << stamina_generated << " stamina" << endl;
                            all_game_resources.player1GainStamina(stamina_generated);
                        }
                    }
                    if(tile_type == "goldWindfall")
                    {
                        cout << "Player 1 you stepped on a treasure tile, play a riddle to gain gold!" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            int gold_gained = generateRandom(20, 40);
                            cout << "You gained " << gold_gained << " gold" << endl;
                            all_game_resources.player1GainGold(gold_gained);
                            all_game_resources.print_player1_stats();
                        }
                    }
                    if(tile_type == "robbersRepel")
                    {
                        cout << "Player 1 you stepped on a treasure tile, play a riddle to get robber's repel" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            all_game_resources.player1SetRobbersRepel(true);
                            all_game_resources.print_player1_stats();
                        }
                    }
                    if(tile_type == "jellybeanOfVigor")
                    {
                        cout << "Player 1 you stepped on a treasure tile, play a riddle to get a candy" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            all_game_resources.player1GetJellyBeanOfVigor();
                            all_game_resources.print_player1_stats();
                        }
                    }
                    if(tile_type == "treasureHunterTruffle")
                    {
                        cout << "Player 1 you stepped on a treasure! play a riddle to unlock it" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            cout << "You have unlocked treasure hunter truffle, win another riddle to access it" << endl;
                            bool solved_truffle = all_game_resources.play_riddle();
                            if(solved_truffle)
                            {
                                cout << "You unlocked treasure hunter's truffle" << endl;
                            }
                        }
                    }
                }
                cout << "You are now at position " << game_board.getPlayerOnePosition() << endl;
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
        }
        //check if player1 reached castle
        if(game_board.getPlayerOnePosition() >= 82)
        {
            cout << "Player 1 wins" << endl;
            break;
        }
        

        //player 2 turn
        int player_2_action = 0;
        while(player_2_action != 1)
        {
            cout << "Player 2 it is your turn" << endl;
            cout << endl;
            // cout << "Enter 1 to draw a card" << endl;
            // cout << "Enter 2 to use a candy" << endl;
            // cout << "Enter 3 to display stats" << endl;
            // cin >> player_2_action;
            player_2_action = 1;
            if(player_2_action == 1)
            {
                int player2_current_position = game_board.getPlayerTwoPosition();
                string player2_current_tile_color = game_board.getTileColor(player2_current_position);
                player_2_moves = drawCardsAndMove(player2_current_tile_color);
                player_two_win = !(game_board.movePlayerTwo(player_2_moves));
                //check for special tiles
                if(game_board.checkForSameTileConstraints(1))
                {
                    all_game_resources.moneyRobbery(1);
                    player2_current_position -= 1;
                    all_game_resources.print_player2_stats();
                }
                bool current_position_is_a_special_tile_2 = game_board.isSpecialTile(player2_current_position);
                if(current_position_is_a_special_tile_2)
                {
                    string tile_type = game_board.getTileEffect(player2_current_position);
                    if(tile_type == "shortcutTile")
                    {
                        game_board.excecuteShortCutTile(2);
                    }
                    if(tile_type  == "iceCreamShopTile")
                    {
                        int player_2_pos = game_board.getPlayerTwoPosition();
                        string color = game_board.getTileColor(player_2_pos); 
                        game_board.excecuteIceCreamShopTile(2, color);
                    }
                    if(tile_type == "gumdropForestTile")
                    {
                        int gold_loss = game_board.excecuteGumDropForestTile(2);
                        all_game_resources.player2LoseGold(gold_loss);
                        all_game_resources.print_player2_stats();
                    }
                    // if(tile_type == "gingerbreadHouseTile")
                    // {
                        
                    // }
                    if(tile_type == "staminaRefill")
                    {
                        cout << "Player 2 you stepped on a treasure tile, play a riddle to get it" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            int stamina_generated = generateRandom(10, 30);
                            cout << "You gained " << stamina_generated << " stamina" << endl;
                            all_game_resources.player2GainStamina(stamina_generated);
                        }
                    }
                    if(tile_type == "goldWindfall")
                    {
                        cout << "Player 2 you stepped on a treasure tile, play a riddle to gain gold!" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            int gold_gained = generateRandom(20, 40);
                            cout << "You gained " << gold_gained << " gold" << endl;
                            all_game_resources.player2GainGold(gold_gained);
                            all_game_resources.print_player2_stats();
                        }
                    }
                    if(tile_type == "robbersRepel")
                    {
                        cout << "Player 2 you stepped on a treasure tile, play a riddle to get robber's repel" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            all_game_resources.player2SetRobbersRepel(true);
                            all_game_resources.print_player2_stats();
                        }
                    }
                    if(tile_type == "jellybeanOfVigor")
                    {
                        cout << "Player 2 you stepped on a treasure tile, play a riddle to get a candy" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            all_game_resources.player1GetJellyBeanOfVigor();
                            all_game_resources.print_player1_stats();
                        }
                    }
                    if(tile_type == "treasureHunterTruffle")
                    {
                        cout << "Player 2 you stepped on a treasure! play a riddle to unlock it" << endl;
                        bool solved = all_game_resources.play_riddle();
                        if(solved)
                        {
                            cout << "You have unlocked treasure hunter truffle, win another riddle to access it" << endl;
                            bool solved_truffle = all_game_resources.play_riddle();
                            if(solved_truffle)
                            {
                                cout << "You unlocked treasure hunter's truffle" << endl;
                            }
                        }
                    }
                }
                cout << "You are now at position " << game_board.getPlayerTwoPosition() << endl;
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
        }
        //check if player 2 reached castle
        if (game_board.getPlayerTwoPosition() >= 82)
        {
            cout << "Player 2 wins" << endl;
            break;
        }
    }

    cout << game_board.getPlayerOnePosition()<<endl;
    cout << game_board.getPlayerTwoPosition()<<endl;


    
    return 0;
}


