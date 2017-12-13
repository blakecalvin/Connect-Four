/*
 * Blake Calvin
 * CS 361
 * players.cpp
 */
#include <iostream>
#include <vector>

#include "players.h"
#include "game.h"

using namespace std;

// Human player input for next move.
int HumanPlayer::getNextMove(Game &game) {
    int move;
    cin>>move;
    return move;
}

// AI player input for next move.
int AiPlayer::getNextMove(Game &game) {
    int move;
    vector< int > moves;

    // Determines possible moves and put value of column in vector
    for(int x = 0; x < game.BoardWidth; x++){
        if(game(x, 0) == BoardField::Empty){
            moves.push_back(x);
        }
    }


    //randomly selects an index from the vector
    int index = rand() % moves.size(); // 0 <= index < move.size()

    //sets next move to the value at that index
    move = moves.at(index);
    move++;

    //outputs move to console
    cout<<move<<"\n";

    return move;
}