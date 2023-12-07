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

string generateCalamities()
{
    int is_there_a_calamity = generateRandom(0,99);
    if(is_there_a_calamity <= 39)
    {
        int the_calamity_type = generateRandom(0,99);
        if(the_calamity_type <= 34)
        {
            return "candyBandits";
        } 
        else if(the_calamity_type >=35 && the_calamity_type <= 64)
        {
            return "lollipopLabyrinth";
        }
        else if(the_calamity_type >= 65 && the_calamity_type <= 79)
        {
            return "candyAvalanche";
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "noCalamity";
    }
}
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
    getline(cin, player1_name);
    cout << "Awesome! Here are a list of characters a player can select from:" << endl;
    all_game_resources.printCharacterList();
    cin >> player1_character_selection;
    cin.ignore(100, '\n');
    all_game_resources.load_player_one(player1_character_selection, player1_name);

    cout << "Player 2 please enter your name" << endl;
    getline(cin, player2_name);
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
                cout << "You have successfully bought " << candy_player_1_bought.name << endl;
                all_game_resources.player1AddCandy(candy_player_1_bought);  
                all_game_resources.player1LoseGold(cost);
                cout <<endl;
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
                cout << "You have successfully bought " <<candy_player_2_bought.name << endl;
                all_game_resources.player2AddCandy(candy_player_2_bought);
                all_game_resources.player1LoseGold(cost);
                cout << endl;
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
            cout << "Enter 1 to draw a card" << endl;
            cout << "Enter 2 to use a candy" << endl;
            cout << "Enter 3 to display stats" << endl;
            cin >> player_one_action;
            //check if player can actually move
            if(all_game_resources.getTurnsPlayer1CannotMove() < 0)
            {
                //if player is currently immobilized get turns cannot move minues 1 and exit the loop
                all_game_resources.player1Get1TurnBack();
                cout << "You are currently immobilized and you are still immobilized for the next " << -1 * all_game_resources.getTurnsPlayer1CannotMove() << " turns" << endl; 
                break;
            }
            else if(player_one_action == 1)
            {
                if(all_game_resources.getPlayer1Stamina() == 0)
                {
                    //if player is 0 stamina, they cannot move for this turn and next 2 turns but gain 20 stamina back once they can move and exits loop
                    cout <<"You have 0 stamina, you cannot move this turn and the next 2 turns" << endl;
                    all_game_resources.player1GainStamina(20);
                    all_game_resources.immobilizePlayer1(-2);
                    break;
                }
                //use 1 stamina to move
                all_game_resources.player1LoseStamina(1);

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
                    // if(tile_type == "gummyTile")
                    // {
                    //     cout <<"Player 1 you stepped on a gummy tile and you are immobolized for " << game_board.getGummyValue(game_board.getPlayerOnePosition()) << endl;
                    //     all_game_resources.immobilizePlayer1(-1 * game_board.getGummyValue(game_board.getPlayerOnePosition()));
                    // }

                    //after the move 40% chance a calamity happends
                }

                //check for candystores
                if(game_board.isPositionCandyStore(game_board.getPlayerOnePosition()))
                {
                    cout << "Player 1 you stepped on a candystore" << endl;
                    cout << "Player 1 would you like to visit the candystore enter 1 to visit candystore and 0 to skip candy store" << endl;
                    cin >> player_1_visit_candy_store;
                    if(player_1_visit_candy_store == 1)
                    {
                        game_board.displayCandyStore(game_board.getPlayerOnePosition());
                        Candy candy_player_1_bought = game_board.buyFromCandyStore(game_board.getPlayerOnePosition());
                        int cost = candy_player_1_bought.price;
                        if(all_game_resources.getPlayer1Gold() >= cost)
                        {
                            if(candy_player_1_bought.name != "")
                            {
                                cout << "You have successfully purchased " << candy_player_1_bought.name << endl;
                                all_game_resources.player1AddCandy(candy_player_1_bought);  
                                all_game_resources.player1LoseGold(cost);
                                cout << endl;
                                all_game_resources.print_player1_stats();
                            }
                        }
                        else
                        {
                            cout << "Insufficient gold" << endl;
                        }
                    }
                }
                cout << endl;
                cout << "You are now at position " << game_board.getPlayerOnePosition() << endl;
                cout << "Here is the board after your move" << endl;
                game_board.displayBoard();
                cout << endl;

                //40% chance calamity happends after a turn
                string calamity = generateCalamities();
                if(calamity == "candyBandits")
                {
                    int lost = generateRandom (1, 10);
                    cout << "You encountered candy bandits you lost " << lost << " gold";
                    all_game_resources.player1LoseGold(lost);
                }
                if(calamity == "lollipopLabyrinth")
                {
                    cout << "You got lost in the lollipop labrinth" << endl;
                    cout << "You lost 1 turn" << endl;
                    cout << "You play rock paper scissors in attempt to recover the damage" << endl;
                    bool rock_paper_scissors = all_game_resources.play_rock_paper_scissors();
                    if(rock_paper_scissors)
                    {
                        cout <<"You won the rock paper scissors!" <<endl;
                        cout <<"You do not lose 1 turn" << endl;
                    }
                    else
                    {
                        cout <<"You lose 1 turn" << endl;
                        all_game_resources.immobilizePlayer1(-1);
                    }
                }
                if(calamity == "candyAvalanche")
                {
                    cout << "You got struct by a candy avalanche" << endl;
                    cout << "You play rock paper scissors in attempt to recover the damage" << endl;
                    int stamina_lost = generateRandom(5,10);
                    bool rock_paper_scissors = all_game_resources.play_rock_paper_scissors();
                    if(rock_paper_scissors)
                    {
                        cout <<"You won the rock paper scissors!" << endl;
                        cout <<"You do not take any damage" <<endl;
                    }
                    else
                    {
                        cout <<"You lose rock paper scissors" <<endl;
                        cout <<"You lose 1 turn" <<endl;
                        cout <<"You also lose " << stamina_lost <<" stamina" <<endl;
                        all_game_resources.immobilizePlayer2(-1);
                        all_game_resources.player2LoseStamina(stamina_lost);
                    }
                }
                if(calamity == "taffyTrap")
                {
                    // all_game_resources.excecuteTaffyTrap(1);
                }
            }
            else if (player_one_action == 2)
            {
                cout << "Here are your stats"<< endl;
                all_game_resources.print_player1_stats();
                int candy_player_used;
                cout << endl;
                cout << "What candy do you want to use enter a number 1-9 corresponding to the position in your inventory" <<endl;
                cin >> candy_player_used;
                candy_player_used -= 1;
                Candy candy_used = all_game_resources.findCandyFromPlayer1ByIndex(candy_player_used);
                if(candy_used.name == "")
                {
                    cout << "Candy unavaliable" << endl;
                }
                else if(candy_used.candy_type == "magical")
                {
                    all_game_resources.applyMagicalCandy(1, candy_player_used, candy_used);
                }
                else if(candy_used.candy_type == "poison")
                {
                    all_game_resources.applyPoisonAndImmunityCandy(1, candy_player_used, candy_used);
                }
                // else if(candy_used.candy_type == "gummy")
                // {
                //     cout << "You used a gummy tile and " << game_board.getPlayerOnePosition() << " is now a gummy tile and will immobilize players for";
                //     if(candy_used.name == "Fearsome Fudge") 
                //     {
                //         cout <<" 1 turn" << endl;
                //         game_board.makeTileAGummyTile(game_board.getPlayerOnePosition(), 1);
                //     }
                //     if(candy_used.name == "Ruby Rapture")
                //     {
                //         cout <<" 2 turns" << endl;
                //         game_board.makeTileAGummyTile(game_board.getPlayerOnePosition(), 2);
                //     }
                // }
                
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
            cout << "Enter 1 to draw a card" << endl;
            cout << "Enter 2 to use a candy" << endl;
            cout << "Enter 3 to display stats" << endl;
            cin >> player_2_action;
            //check if player can actually move
            if(all_game_resources.getTurnsPlayer2CannotMove() < 0)
            {
                //if player is currently immobilized get turns cannot move minues 1 and exit the loop
                all_game_resources.player2Get1TurnBack();
                cout << "You are currently immobilized and you are still immobilized for the next " << -1 * all_game_resources.getTurnsPlayer1CannotMove() << " turns" << endl; 
                break;
            }
            if(player_2_action == 1)
            {
                if(all_game_resources.getPlayer2Stamina() == 0)
                {
                    //if player is 0 stamina, they cannot move for this turn and next 2 turns but gain 20 stamina back once they can move and exits loop
                    cout <<"You have 0 stamina, you cannot move this turn and the next 2 turns" << endl;
                    all_game_resources.player2GainStamina(20);
                    all_game_resources.immobilizePlayer2(-2);
                    break;
                }
                //use 1 stamina to move
                all_game_resources.player2LoseStamina(1);

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
                    // if(tile_type == "gummyTile")
                    // {
                    //     cout <<"Player 2 you stepped on a gummy tile and you are immobolized for " << game_board.getGummyValue(game_board.getPlayerTwoPosition()) << endl;
                    //     all_game_resources.immobilizePlayer2(-1 * game_board.getGummyValue(game_board.getPlayerTwoPosition()));
                    // }
                }

                //check for candystore
                if(game_board.isPositionCandyStore(game_board.getPlayerTwoPosition()))
                {   
                    cout << "Player 2 you stepped on a candy store" << endl;
                    cout << "Player 2 would you like to visit the candystore enter 1 to visit candystore and 0 to skip candy store" <<endl;
                    cin >> player_2_visit_candy_store;
                    if(player_2_visit_candy_store == 1)
                    {
                        game_board.displayCandyStore(game_board.getPlayerTwoPosition());
                        Candy candy_player_2_bought = game_board.buyFromCandyStore(game_board.getPlayerTwoPosition());
                        int cost = candy_player_2_bought.price;
                        if(all_game_resources.getPlayer2Gold() >= cost)
                        {
                            if(candy_player_2_bought.name != "")
                            {
                                cout << "You have successfully purchased " << candy_player_2_bought.name << endl;
                                all_game_resources.player2AddCandy(candy_player_2_bought);
                                all_game_resources.player1LoseGold(cost);
                                cout << endl;
                                all_game_resources.print_player2_stats();
                            }
                        }
                        else
                        {
                            cout << "Insufficient gold" << endl;
                        }
                    }
                }
                cout << endl;
                cout << "You are now at position " << game_board.getPlayerTwoPosition() << endl;
                cout << "Here is the board after your move" << endl;
                game_board.displayBoard();
                cout << endl;

                //40% chance calamity happends
                string calamity = generateCalamities();
                cout << calamity << endl;
                if(calamity == "candyBandits")
                {
                    int lost = generateRandom (1, 10);
                    cout << "You encountered candy bandits you lost " << lost << " gold";
                    all_game_resources.player2LoseGold(lost);
                }
                if(calamity == "lollipopLabyrinth")
                {
                    cout << "You got lost in the lollipop labrinth" << endl;
                    cout << "You play rock paper scissors in attempt to recover the damage" << endl;
                    bool rock_paper_scissors = all_game_resources.play_rock_paper_scissors();
                    if(rock_paper_scissors)
                    {
                        cout <<"You won the rock paper scissors!" <<endl;
                        cout <<"You do not take any damage" << endl;
                    }
                    else
                    {
                        cout << "You lose rock paper scissors" << endl;
                        cout <<"You lose 1 turn" << endl;
                        all_game_resources.immobilizePlayer1(-1);
                    }
                }
                if(calamity == "candyAvalanche")
                {
                    cout << "You got struct by a candy avalanche" << endl;
                    cout << "You play rock paper scissors in attempt to recover the damage" << endl;
                    int stamina_lost = generateRandom(5,10);
                    bool rock_paper_scissors = all_game_resources.play_rock_paper_scissors();
                    if(rock_paper_scissors)
                    {
                        cout <<"You won the rock paper scissors!" << endl;
                        cout <<"You do not take any damage" <<endl;
                    }
                    else
                    {
                        cout <<"You lose rock paper scissors" <<endl;
                        cout <<"You lose 1 turn" <<endl;
                        cout <<"You also lose " << stamina_lost <<" stamina" <<endl;
                        all_game_resources.immobilizePlayer2(-1);
                        all_game_resources.player2LoseStamina(stamina_lost);
                    }
                }
                if(calamity == "taffyTrap")
                {
                    // all_game_resources.excecuteTaffyTrap(2);
                }
            }
            else if(player_2_action == 2)
            {
                cout << "Here are your stats"<< endl;
                all_game_resources.print_player2_stats();
                int candy_player_used;
                cout << endl;
                cout << "What candy do you want to use enter a number 1-9 corresponding to the index of the candy in your inventory, enter 9 to not use any candy" <<endl;
                cin >> candy_player_used;
                candy_player_used -= 1;
                Candy candy_used = all_game_resources.findCandyFromPlayer2ByIndex(candy_player_used);
                if(candy_used.name == "")
                {
                    cout << "Candy unavaliable" << endl;
                }
                else if(candy_used.candy_type == "magical")
                {
                    all_game_resources.applyMagicalCandy(2, candy_player_used, candy_used);
                }
                else if(candy_used.candy_type == "poison")
                {
                    all_game_resources.applyPoisonAndImmunityCandy(2, candy_player_used, candy_used);
                }
                // else if(candy_used.candy_type == "gummy")
                // {
                //     cout << "You used a gummy tile and " << game_board.getPlayerTwoPosition() << " is now a gummy tile and will immobilize players for";
                //     if(candy_used.name == "Fearsome Fudge") 
                //     {
                //         cout <<" 1 turn" << endl;
                //         game_board.makeTileAGummyTile(game_board.getPlayerTwoPosition(), 1);
                //     }
                //     if(candy_used.name == "Ruby Rapture")
                //     {
                //         cout <<" 2 turns" << endl;
                //         game_board.makeTileAGummyTile(game_board.getPlayerTwoPosition(), 2);
                //     }
                // }
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


