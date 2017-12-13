/*
 * Blake Calvin
 * CS 361
 * game.cpp
 */

#include "game.h"
#include "players.h"

    //Height and width of board
    const int Game::BoardWidth = 7;
    const int Game::BoardHeight = 6;

    //Game constructor that takes two player references
    Game::Game(Player &p1, Player &p2){
        current = GameState::TurnP1;
        this->p1 = &p1;
        this->p2 = &p2;

        //populates board with empty
        Board = new BoardField*[BoardWidth];
        for(int x = 0; x < BoardWidth; x++){
            Board[x] = new BoardField[BoardHeight];
            for(int y = 0; y < BoardHeight; y++){
                Board [x][y] = BoardField::Empty;
            }
        }
    }

    //Returns the current state of the game
    GameState& Game::getState(){
        return current;
    }

    //Checks if a winning move or draw has occurred.
    bool Game::isRunning(){
        return !(current == GameState::Draw || current == GameState::P1Won || current == GameState::P2Won);
    }

    //returns the state of the given point on the board
    BoardField& Game::operator() (int x, int y) const{
        if(x < BoardWidth && y < BoardHeight){
            return Board [x][y];
        }
        BoardField coord = BoardField::Empty;
        return coord;
    }

    void Game::nextTurn(){
        int moveX = 0;

        //performs next move for current player if valid
        switch (current)
        {
            case GameState::TurnP1:
                moveX = p1->getNextMove(*this);
                currentPlayer = BoardField::Player1;
                possible = GameState::P1Won;
                nextMove = GameState::TurnP2;
                break;

            case GameState::TurnP2:
                moveX = p2->getNextMove(*this);
                currentPlayer = BoardField::Player2;
                possible = GameState::P2Won;
                nextMove = GameState::TurnP1;
                break;

            default:
                break;
        }

        moveX--;

        //check if valid
        bool isValid = false;
        if(Board[moveX][0]==BoardField::Empty){
            isValid = true;
        }

        if(isValid){

            //drop stone into column
            int y = 0;
            while(y<6 && Board[moveX][y]==BoardField::Empty){
                y++;
            }

            int moveY = y-1;
            //set move on board
            Board[moveX][moveY] = currentPlayer;

            //check for draw
            if(Board[0][0] != BoardField::Empty
               && Board[1][0] != BoardField::Empty
               && Board[2][0] != BoardField::Empty
               && Board[3][0] != BoardField::Empty
               && Board[4][0] != BoardField::Empty
               && Board[5][0] != BoardField::Empty
               && Board[6][0] != BoardField::Empty){
                current = GameState::Draw;
            }

            //check for vertical win
            if(moveY <= 2 && Board[moveX][moveY+1] == Board[moveX][moveY]
               && Board[moveX][moveY+2] == Board[moveX][moveY]
               && Board[moveX][moveY+3] == Board[moveX][moveY]){
                current = possible;
            }

            //check for horizontal win
            else if(moveX <= 3 && Board[moveX+1][moveY] == Board[moveX][moveY]
                    && Board[moveX+2][moveY] == Board[moveX][moveY]
                    && Board[moveX+3][moveY] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveX <= 4 && moveX >=1
                    && Board[moveX-1][moveY] == Board[moveX][moveY]
                    && Board[moveX+1][moveY] == Board[moveX][moveY]
                    && Board[moveX+2][moveY] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveX <= 5 && moveX >=2
                    && Board[moveX-1][moveY] == Board[moveX][moveY]
                    && Board[moveX-2][moveY] == Board[moveX][moveY]
                    && Board[moveX+1][moveY] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveX >= 3 && Board[moveX-1][moveY] == Board[moveX][moveY]
                    && Board[moveX-2][moveY] == Board[moveX][moveY]
                    && Board[moveX-3][moveY] == Board[moveX][moveY]){
                current = possible;
            }

            //check for diagonal right win
            else if(moveY <= 2 && moveX >= 3
                    && Board[moveX-1][moveY+1] == Board[moveX][moveY]
                    && Board[moveX-2][moveY+2] == Board[moveX][moveY]
                    && Board[moveX-3][moveY+3] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveY <= 3 && moveY >= 1 && moveX <= 5 && moveX >=2
                    && Board[moveX+1][moveY-1] == Board[moveX][moveY]
                    && Board[moveX-1][moveY+1] == Board[moveX][moveY]
                    && Board[moveX-2][moveY+2] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveY <= 4 && moveY >= 2 && moveX <= 4 && moveX >=1
                    && Board[moveX-1][moveY+1] == Board[moveX][moveY]
                    && Board[moveX+1][moveY-1]== Board[moveX][moveY]
                    && Board[moveX+2][moveY-2] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveY >= 3 && moveX <= 3
                    && Board[moveX+1][moveY-1] == Board[moveX][moveY]
                    && Board[moveX+2][moveY-2] == Board[moveX][moveY]
                    && Board[moveX+3][moveY-3] == Board[moveX][moveY]){
                current = possible;
            }

            //check for diagonal left win
            else if(moveY <= 2 && moveX <= 3
                    && Board[moveX+1][moveY+1] == Board[moveX][moveY]
                    && Board[moveX+2][moveY+2] == Board[moveX][moveY]
                    && Board[moveX+3][moveY+3] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveY <= 3 && moveY >= 1 && moveX <= 4 && moveX >=1
                    && Board[moveX-1][moveY-1] == Board[moveX][moveY]
                    && Board[moveX+1][moveY+1] == Board[moveX][moveY]
                    && Board[moveX+2][moveY+2] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveY <= 4 && moveY >= 2 && moveX <= 5 && moveX >=2
                    && Board[moveX+1][moveY+1] == Board[moveX][moveY]
                    && Board[moveX-1][moveY-1] == Board[moveX][moveY]
                    && Board[moveX-2][moveY-2] == Board[moveX][moveY]){
                current = possible;
            }
            else if(moveY >= 3 && moveX >= 3
                    && Board[moveX-1][moveY-1] == Board[moveX][moveY]
                    && Board[moveX-2][moveY-2] == Board[moveX][moveY]
                    && Board[moveX-3][moveY-3] == Board[moveX][moveY]){
                current = possible;
            }
                //if no win or draw occurs
            else{
                current = nextMove;
            }
        }
            //if not valid move
        else{
            current = nextMove;
        }
    }