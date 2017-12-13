/*
 * Blake Calvin
 * CS 361
 * game.h
 */

#ifndef LAB3_GAME_H
#define LAB3_GAME_H

//forward declaration of Player
class Player;

//possible game states
enum class GameState{ TurnP1, TurnP2, P1Won, P2Won, Draw};
//possible board states
enum class BoardField{ Empty, Player1, Player2};

class Game {

    Player* p1;
    Player* p2;

    public:
        static const int BoardWidth;
        static const int BoardHeight;

        Game(Player &p1, Player &p2);

        GameState& getState();
        bool isRunning();
        BoardField& operator() (int x, int y) const;
        void nextTurn();


    private:
        BoardField** Board;
        GameState current;
        BoardField currentPlayer;
        GameState possible;
        GameState nextMove;

};

#endif //LAB3_GAME_H