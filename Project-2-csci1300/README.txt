-------------------------
HOW TO COMPILE AND RUN
-------------------------
Compile : g++ -std=c++17  -Wall -Werror -Wpedantic Board.cpp GameResources.cpp Player.cpp play_candy_land.cpp
Run : ./a.exe

--------------------
DEPENDENCIES
--------------------
Board.h Board.cpp GameResources.h GameResources.cpp Player.h Player.cpp structs.h 
candies.txt characters.txt riddles.txt must be in the same directory as the play_candy_land.cpp to Compile

----------------------------
SUBMISSION INFORMATION
----------------------------
CSCI 1300 FALL 2023 project 2
Author : Evan Su
Recitation : 402 - Pawin Taechoyotin
Date 12/7/2023

-----------------------
ABOUT THIS project
-----------------------
This project implement an interactive board game candy lane. In which 2 players each selects to be a 
character in candy land. The user progresses through the candyland by drawing colored cards and moving
through special tiles, treasures, calamities, and candystores. Players can use candy either to boost
their own progression towards the castle or to hinder other player's progression towards the candy 
castle. The player who reach the candy castle first wins the game.
