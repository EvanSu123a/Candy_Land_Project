#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "GameResources.h"

int generateRandomBetweenMaxAndMin(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

//the split function to split a line by delimeter
int split(string input_string, char seperator, string arr[], int arr_size)
{
    int word_count = 0;
    string this_word;
    stringstream ss(input_string);
    while(getline(ss, this_word, seperator))
    {
        word_count +=1;
        if(word_count > arr_size)
        {
            return -1;
        }
        arr[word_count-1] = this_word;
    }
    return word_count;
}


//constructor
GameResources :: GameResources()
{
    _characters_count = 0;
    _player_1 = Player();
    _player_2 = Player();
    _candy_counts = 0;
}

//getters
vector <Candy> GameResources :: getAllCandyInThisGame()
{
    return _all_candy_data;
}

//loading characters from file
void GameResources :: loadCharacters()
{
    ifstream characters_file_in;
    characters_file_in.open("characters.txt");
    
    //check if file opened correctly
    if(characters_file_in.fail())
    {
        cout << "character.txt does not exist, characters cannot be loaded" << endl;
    }
    else
    {
        //read in characters from file
        Character this_character;
        string character_line_read_in;

        //read the header
        string header;

        getline(characters_file_in, header);

        while(getline(characters_file_in, character_line_read_in))
        {
            string character_attributes [4];
            //first 3 character attributes are actual attributes
            split(character_line_read_in, '|', character_attributes, 4);
            string character_starting_candies [9];
            //the last character attribute is candies
            split(character_attributes[3], ',', character_starting_candies, 9);
            
            this_character.name = character_attributes[0];
            this_character.stamina = stoi(character_attributes[1]);
            this_character.gold = stoi(character_attributes[2]);
            //assign candies
            for(int i = 0; i < 9; i++)
            {
                this_character.candies_owned[i] = character_starting_candies[i];
            }

                this_character.picked = false;
                _character_list.push_back(this_character);
                _characters_count ++;
        }
    }
}

//print out all avaliable characters for selection
void GameResources :: printCharacterList()
{
    for(int i = 0; i < _characters_count; i++)
    {
        if(_character_list[i].picked == false)
        {
            cout << "Name: " << _character_list[i].name << endl;
            cout << "Stamina " << _character_list[i].stamina <<endl;
            cout << "Gold " << _character_list[i].gold<<endl;
            //print out all candies
            for(int j = 0; j < 9; j++)
            {
                string this_candy = _character_list.at(i).candies_owned[j];
                if(this_candy != "")
                {
                    cout << "[" << this_candy << "]";
                }
                if(j % 3 ==2)
                {
                    cout << endl;
                }
            }
        }

    }
}

void GameResources :: loadInCandies()
{
    ifstream candies_file_in;
    candies_file_in.open("candies.txt");

    //check if file opened correctly
    if(candies_file_in.fail())
    {
        cout <<"candies.txt does not exist, candies cannot be loaded" << endl;
    }
    else
    {
        Candy thisCandy;
        string line_read_in;
        string candy_attributes[6];

        //read the header in
        string header;
        getline(candies_file_in, header);

        while(getline(candies_file_in, line_read_in))
        {
            split(line_read_in, '|', candy_attributes, 6);
            thisCandy.name = candy_attributes[0];
            thisCandy.description = candy_attributes[1];
            thisCandy.effect_type = candy_attributes[2];
            thisCandy.effect_value = stod(candy_attributes[3]);
            thisCandy.candy_type = candy_attributes[4];
            thisCandy.price = stod(candy_attributes[5]);

            _all_candy_data.push_back(thisCandy);
            _candy_counts+=1;
        }

    }
}

void GameResources :: loadInRiddles()
{
    ifstream riddle_file_in;
    riddle_file_in.open("riddles.txt");
    //check if file successfully opened
    if(riddle_file_in.fail())
    {
        cout << "riddle.txt cannot be found, failed to load in riddles" <<endl;
    }
    else
    {
        Riddle this_riddle;
        string line_read_in;
        string riddle_attributes[2];

        while(getline(riddle_file_in, line_read_in))
        {
            split(line_read_in, '|', riddle_attributes, 2);
            this_riddle.riddle = riddle_attributes[0];
            this_riddle.answer = riddle_attributes[1];

            _all_riddles.push_back(this_riddle);
            _riddle_counts += 1;
        }


    }
}

//load the stats of the character the player choose into player themselves
/**
 * takes in the name of the character user choosen
 * search through the avaliable character and see which one name match
 * define a new character variable and set it to the character with the name player choose
 * assign all the stats of that character to player
 * to load the starting candies from string in characters to Candy in player
 * loop through 0-8 and check if it is a empty candy
 * if it is not a empty candy then go through all candies and check for matching name
 * and assign add the matching name candy to the player's inventory
*/
bool GameResources :: load_player_one(string character_choosen_name, string player_name)
{
    bool character_invalid = true;
    _player_1.setPlayerName(player_name);
    Character character_choosen;
    int character_list_size = _character_list.size();
    for(int i = 0; i < character_list_size; i++)
    {
        if(character_choosen_name == _character_list.at(i).name)
        {
            character_choosen = _character_list[i];
            _character_list[i].picked = true;
            character_invalid = false;
            break;
        }
    }
    //check if the character user put is valid
    if(character_invalid)
    {
        cout << "Invalid character Please select a valid character" << endl;
        return false;
    }
    //load stats
    _player_1.setPlayerCharacterName(character_choosen.name);
    _player_1.setPlayerStamina(character_choosen.stamina);
    _player_1.setPlayerGold(character_choosen.gold);
    //load starting candies
    for(int i = 0; i < 9; i++)
    {
        if(character_choosen.candies_owned[i] != "")
        {
            Candy this_candy;
            for(int j = 0; j < _candy_counts; j++)
            {
                if(character_choosen.candies_owned[i] == _all_candy_data.at(j).name)
                {
                    this_candy = _all_candy_data[j];
                    _player_1.addCandyToInventory(this_candy);
                    break;
                }
            }
        }
    }
    return true;
}

bool GameResources :: load_player_two(string character_choosen_name, string player_name)
{
    bool character_invalid = true;
    _player_2.setPlayerName(player_name);
    Character character_choosen;
    int character_list_size = _character_list.size();
    for(int i = 0; i < character_list_size; i++)
    {
        if(character_choosen_name == _character_list.at(i).name)
        {
            character_choosen = _character_list[i];
            _character_list[i].picked = true;
            character_invalid = false;
            break;
        }
    }
    if(character_invalid)
    {
        cout << "Invalid character Please select a valid character" << endl;
        return false;
    }
    //load stats
    _player_2.setPlayerCharacterName(character_choosen.name);
    _player_2.setPlayerStamina(character_choosen.stamina);
    _player_2.setPlayerGold(character_choosen.gold);
    //load starting candies
    for(int i = 0; i < 9; i++)
    {
        if(character_choosen.candies_owned[i] != "")
        {
            Candy this_candy;
            for(int j = 0; j < _candy_counts; j++)
            {
                if(character_choosen.candies_owned[i] == _all_candy_data.at(j).name)
                {
                    this_candy = _all_candy_data[j];
                    _player_2.addCandyToInventory(this_candy);
                    break;
                }
            }
        }
    }
    return true;
}

void GameResources :: print_player1_stats()
{
    cout << "Here are your stats Player 1:" << endl;
    cout << "Player name: " << _player_1.getPlayerName() <<endl;
    cout << "Character: "<< _player_1.getPlayerCharacterName() << endl;
    cout << "Stamina: " << _player_1.getPlayerStamina() << endl;
    cout << "Gold: " << _player_1.getPlayerGold() << endl;
    cout << "Candies: " << endl;
    _player_1.printInventory();
    if(_player_1.getRobbersRepel())
    {
        cout << endl;
        cout << "Player 1 has robber's repel" << endl;
    }
}

void GameResources :: print_player2_stats()
{
    cout << "Here are your stats Player 2:" << endl;
    cout << "Player name: " << _player_2.getPlayerName() <<endl;
    cout << "Character: "<< _player_2.getPlayerCharacterName() <<endl;
    cout << "Stamina: " << _player_2.getPlayerStamina() <<endl;
    cout << "Gold: " << _player_2.getPlayerGold() <<endl;
    cout << "Candies: " << endl;
    _player_2.printInventory();
    if(_player_2.getRobbersRepel())
    {
        cout << endl;
        cout << "Player 2 has robber's repel" << endl;
    }
}

void GameResources :: moneyRobbery(int player_who_arrives_first)
{
    //player 1 arrives first
    if(player_who_arrives_first == 1)
    {
        cout << "Player 1 attempts to rob Player 2" << endl;
        if(_player_2.getRobbersRepel())
        {
            cout << "Player 2 has robbers repel, player 2 loses robbers repel but lose 0 gold" << endl;
            _player_2.setRobbersRepel(false);
        }
        else
        {
            int gold_lost = generateRandomBetweenMaxAndMin(5, 10);
            if(gold_lost <= _player_2.getPlayerGold())
            {
                cout << "Player 2 lose " << gold_lost <<" gold" << endl;
                cout << "Player 1 gained " << gold_lost << " gold" << endl;
                player1GainGold(gold_lost);
                player2LoseGold(gold_lost);
            }
            else
            {
                cout << "Player 2 lose " << _player_2.getPlayerGold() << " gold" << endl;
                cout << "Player 1 gain " << _player_2.getPlayerGold() << " gold" <<endl;
                int gold = _player_2.getPlayerGold();
                _player_2.setPlayerGold(0);
                player1GainGold(gold);
            }
        }
    }
    //player 2 arrives first
    else
    {
        cout << "Player 2 attempts to rob Player 1" << endl;
        if(_player_1.getRobbersRepel())
        {
            cout << "Player 1 has robbers repel, player 2 loses robbers repel but lose 0 gold" << endl;
            _player_1.setRobbersRepel(false);
        }
        else
        {
            int gold_lost = generateRandomBetweenMaxAndMin(5, 10);
            if(gold_lost <= _player_1.getPlayerGold())
            {
                cout << "Player 1 loses " << gold_lost << " gold" <<endl; 
                cout << "Player 2 gains " << gold_lost << " gold" << endl;
                player1LoseGold(gold_lost);
                player2GainGold(gold_lost);
            }
            else
            {
                cout << "Player 1 loses " << _player_1.getPlayerGold() << " gold" <<endl; 
                cout << "Player 2 gains " << _player_1.getPlayerGold() << " gold" <<endl;
                int gold = _player_1.getPlayerGold();
                player2GainGold(gold);
                _player_1.setPlayerGold(0);
            }
        }
    }
}

//apply magical candy candy to regain stamina
void GameResources :: applyMagicalCandy(int player_who_used_candy, Candy candy_applied)
{
    if(player_who_used_candy == 1)
    {
        if(candy_applied.name == "Frosty Fizz")
        {
            cout << "Player 1 you used Frosty Fizz you gain 10 stamina" << endl;
            player1GainStamina(10);
        }
        if(candy_applied.name == "Crimson Crystal")
        {
            cout << "Player 1 you used Crimson Crystal and you gained 15 stamina" << endl;
            player1GainStamina(15);
        }
        if(candy_applied.name == "Mystic Marshmallow")
        {
            cout << "Player 1 you used Mystic Marshmallow and you gained 20 stamina" <<endl;
            player1GainStamina(20);
        }
        if(candy_applied.name == "Breezy Butterscotch")
        {
            cout << "Player 1 you used Breezy Butterscotch and you gained 30 stamina" <<endl;
            player1GainGold(30);
        }
    }
    if(player_who_used_candy == 2)
    {
        if(candy_applied.name == "Frosty Fizz")
        {
            cout << "Player 2 you used Frosty Fizz you gain 10 stamina" << endl;
            player2GainStamina(10);
        }
        if(candy_applied.name == "Crimson Crystal")
        {
            cout << "Player 2 you used Crimson Crystal and you gained 15 stamina" << endl;
            player2GainStamina(15);
        }
        if(candy_applied.name == "Mystic Marshmallow")
        {
            cout << "Player 2 you used Mystic Marshmallow and you gained 20 stamina" <<endl;
            player2GainStamina(30);
        }
        if(candy_applied.name == "Breezy Butterscotch")
        {
            cout << "Player 2 you used Breezy Butterscotch and you gained 30 stamina" <<endl;
            player2GainStamina(30);
        }
        
    }
}

//play riddle
//return true if player solved riddle
//return false if player failed it
bool GameResources :: play_riddle()
{
    int riddle_number = generateRandomBetweenMaxAndMin(0,19);
    Riddle riddle_to_play = _all_riddles.at(riddle_number);
    string player_answer;
    string actual_answer = riddle_to_play.answer;
    cout << riddle_to_play.riddle << " enter answer:" << endl;
    cin >> player_answer;
    //compare player answer to the actual answer
    if(player_answer == actual_answer)
    {
        cout << "You solved the riddle!" << endl;
        return true;
    }
    else
    {
        cout << "You failed the riddle" <<endl;
        return false;
    }
}

void GameResources :: setPlayer1(Player player1_state)
{
    _player_1 = player1_state;
}

void GameResources :: setPlayer2(Player player2_state)
{
    _player_2 = player2_state;
}

int GameResources :: getPlayer1Gold()
{
    int gold = _player_1.getPlayerGold();
    return gold;
}
int GameResources :: getPlayer2Gold()
{
    int gold = _player_2.getPlayerGold();
    return gold;
}
void GameResources ::player1LoseGold(int gold_loss)
{
    int gold_player1_have = _player_1.getPlayerGold() - gold_loss;
    if(gold_player1_have > 0)
    {
        _player_1.setPlayerGold(gold_player1_have);
    }
    else
    {
        _player_1.setPlayerGold(0);
    }
}
void GameResources :: player2LoseGold(int gold_loss)
{
    int gold_player2_have = _player_2.getPlayerGold() - gold_loss;
    if(gold_player2_have > 0)
    {
        _player_2.setPlayerGold(gold_player2_have);
    }
    else
    {
        _player_2.setPlayerGold(0);
    }
}
void GameResources :: player1GainGold(int gold_gained)
{
    int gold_player1_have = _player_1.getPlayerGold() + gold_gained;
    if(gold_player1_have < 100)
    {
        _player_1.setPlayerGold(gold_player1_have);
    }
    else
    {
        _player_1.setPlayerGold(100);
    }
}
void GameResources :: player2GainGold(int gold_gained)
{
    int gold_player2_have = _player_2.getPlayerGold() + gold_gained;
    if(gold_player2_have < 100)
    {
        _player_2.setPlayerGold(gold_player2_have);
    }
    else
    {
        _player_2.setPlayerGold(100);
    }
}

void GameResources :: player1GainStamina(int stamina_gained)
{
    int stamina_player1_have = _player_1.getPlayerStamina() + stamina_gained;
    if(stamina_player1_have < 100)
    {
        _player_1.setPlayerStamina(stamina_player1_have);
    }
    else
    {
        _player_1.setPlayerStamina(100);
    }
}
void GameResources :: player2GainStamina(int stamina_gained)
{
    int stamina_player2_have = _player_2.getPlayerStamina() + stamina_gained;
    if(stamina_player2_have < 100)
    {
        _player_2.setPlayerStamina(stamina_player2_have);
    }
    else
    {
        _player_2.setPlayerStamina(100);
    }
}
void GameResources :: player1SetRobbersRepel(bool status)
{
    _player_1.setRobbersRepel(status);
}
void GameResources :: player2SetRobbersRepel(bool status)
{
    _player_2.setRobbersRepel(status);
}
void GameResources :: player1AddCandy(Candy to_be_added)
{
    _player_1.addCandyToInventory(to_be_added);
}
void GameResources :: player2AddCandy(Candy to_be_added)
{
    _player_2.addCandyToInventory(to_be_added);
}
void GameResources :: player1GetJellyBeanOfVigor()
{
    Candy jellybean = {"Jellybean of Vigor", "boost player's stamina by 50", "stamina", 50, "magical", 10};
    _player_1.addCandyToInventory(jellybean);
}
void GameResources :: player2GetJellyBeanOfVigor()
{
    Candy jellybean = {"Jellybean of Vigor", "boost player's stamina by 50", "stamina", 50, "magical", 10};
    _player_2.addCandyToInventory(jellybean);
}

Candy GameResources :: findCandyFromPlayer1ByIndex(int index)
{
    return _player_1.getCandyFromInventory(index);
}
Candy GameResources :: findCandyFromPlayer2ByIndex(int index)
{
    return _player_2.getCandyFromInventory(index);
}
Candy GameResources :: findCandyFromPlayer1(string candy_name)
{
    return _player_1.findCandy(candy_name);
}
Candy GameResources :: findCandyFromPlayer2(string candy_name)
{
    return _player_2.findCandy(candy_name);
}

