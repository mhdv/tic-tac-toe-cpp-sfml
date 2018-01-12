#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>
#include <cstdlib>

#include "tictactoe.h"

struct pcMove{
    int x;
    int y;
};

int calculateScore(ticTacToe game, int p){
    int score = game.checkState();
    int player = p;

    if(player == 2){
        if(score==0) return 0;
        if(score==1) return 10;
        if(score==2) return -10;
    }
    if(player == 1){
        if(score==0) return 0;
        if(score==1) return -10;
        if(score==2) return 10;  
    }
    return -666;
} 


int minimax(ticTacToe game, int depth, bool max, int p){
    int score = calculateScore(game, p);
    int player = p;
    int size = game.getFieldSize();
    int terms = game.getTerms();
    int maxdepth = 10000;
    if(terms<size){
        if(size == 4) maxdepth = 2;
        if(size == 5) maxdepth = 2;
        if(size == 6) maxdepth = 2;
    }else{
        if(size == 4) maxdepth = 4;
        if(size == 5) maxdepth = 2;
        if(size == 6) maxdepth = 2;
    }
    int** tmp = game.getGameState();

    if(score == 10) return score;
    if(score == -10) return score;

    bool areMovesLeft = false;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(tmp[i][j]==0) areMovesLeft = true;
        }
    }

    if(!areMovesLeft) return 0;

    // max

    if(max){
        int best = -100000;

        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if(tmp[i][j]==0){
                    if(player == 1){
                        game.player2move(i, j);
                        if (depth<maxdepth)
                        best = std::max(best, minimax(game, depth+1, !max, player));
                        game.undoMove(i, j);
                    }
                    if(player == 2){
                        game.player1move(i, j);
                        if (depth<maxdepth)
                        best = std::max(best, minimax(game, depth+1, !max, player));
                        game.undoMove(i, j);
                    }
                }
            }
        }
        return best;
    }
    
    // min

    else{
        int best = 100000;

        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if(tmp[i][j]==0){
                    if(player == 1){
                        game.player1move(i, j);
                        if (depth<maxdepth)
                        best = std::min(best, minimax(game, depth+1, !max, player));
                        game.undoMove(i, j);
                    }
                    if(player == 2){
                        game.player2move(i, j);
                        if (depth<maxdepth)
                        best = std::min(best, minimax(game, depth+1, !max, player));
                        game.undoMove(i, j);
                    }
                }
            }
        }
        return best;
    }
}

pcMove findBestMove(ticTacToe game, int p){
    int best = -100000;
    int player = p;
    pcMove bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    int size = game.getFieldSize();
    int** tmp = game.getGameState();

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(tmp[i][j]==0){
                int moveVal;
                if(player==1){
                    game.player1move(i, j);
                    moveVal = minimax(game, 0, false, 2);
                    game.undoMove(i, j);
                }
                if(player==2){
                    game.player2move(i, j);
                    moveVal = minimax(game, 0, false, 1);
                    game.undoMove(i, j);
                }

                if(moveVal>best){
                    bestMove.x = i;
                    bestMove.y = j;
                    best = moveVal;
                }

            }


        }
    }
    return bestMove;
}

#endif