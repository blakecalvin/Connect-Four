/*
 * Blake Calvin
 * CS 361
 * players.h
 */

#ifndef LAB3_PLAYERS_H
#define LAB3_PLAYERS_H

//forward declaration of Game class
class Game;

class Player{

    Game* game;

    public:
        virtual int getNextMove(Game &game) = 0;
};

class HumanPlayer: public Player{
    public:
        int getNextMove(Game &game);
};

class AiPlayer: public Player{
    public:
        int getNextMove(Game &game);
};

#endif //LAB3_PLAYERS_H


