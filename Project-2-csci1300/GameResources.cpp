#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "GameResources.h"


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
}

//loading characters from file
void GameResources :: loadCharacters()
{
    ifstream characters_file_in;
    characters_file_in.open("characters.txt");

    //read in characters from file
    Character this_character;
    string character_line_read_in;
    string character_attributes [4];
    string character_starting_candies [9];

    string header;

    getline(characters_file_in, header);

    while(getline(characters_file_in, character_line_read_in))
    {
        //first 3 character attributes are actual attributes
        split(character_line_read_in, '|', character_attributes, 4);
        
       //the last character attribute is candies
       split(character_attributes[3], ',', character_starting_candies, 9);
       
       this_character.name = character_attributes[0];
       this_character.stamina = stoi(character_attributes[1]);
       this_character.gold = stoi(character_attributes[2]);

       for(int i = 0; i < 9; i++)
       {
            this_character.candies_owned[i] = character_starting_candies[i];
       }

        this_character.picked = false;
        _character_list.push_back(this_character);
        _characters_count ++;
    }
}

//print out all avaliable characters for selection
void GameResources :: printCharacterList()
{
    for(int i = 0; i < _characters_count; i++)
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