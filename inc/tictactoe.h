#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <cstdlib>

class ticTacToe{
    private:
    char playerX;
    char playerO;
    int fieldSize, terms;
    int** field;

    public:
    ticTacToe(int s, int t);
    ~ticTacToe();

    void setPlayers(char x='p', char o='m') {playerX=x; playerO=o;};

    char getPlayerX() {return playerX;};
    char getPlayerO() {return playerO;};

    void undoMove(int x, int y) {field[x][y]=0;};
    void player1move(int x, int y);
    void player2move(int x, int y);

    void reinit(int s, int t);
    int checkState();

    int getFieldSize() {return fieldSize;}
    int getTerms() {return terms;}
    int** getGameState() {return field;}
};

ticTacToe::ticTacToe(int s, int t){
    // define game field size
    if(s>=3 && s<=6)
        fieldSize = s;
    else
        fieldSize = 3;
    // define game terms
    if(t>=3 && t<=6)
        terms = t;
    else
        terms = 3;

    if(terms>fieldSize) terms = fieldSize;


    // creates game field
    field = new int*[fieldSize];

    for(int i=0; i<fieldSize; i++){
        field[i] = new int[fieldSize];
    }

    // empty tile means 0, X means 1, O means 2
    for(int i=0; i<fieldSize; i++){
        for(int j=0; j<fieldSize; j++){
            field[i][j] = 0;
        }
    }

}

ticTacToe::~ticTacToe() { }

void ticTacToe::player1move(int x, int y){
    field[x][y] = 1;
}

void ticTacToe::player2move(int x, int y){
    field[x][y] = 2;
}

void ticTacToe::reinit(int s, int t){
    // define game field size
    if(s>=3 && s<=6)
        fieldSize = s;
    else
        fieldSize = 3;
    // define game terms
    if(t>=3 && t<=6)
        terms = t;
    else
        terms = 3;

    if(terms>fieldSize) terms = fieldSize;

    // creates game field
    field = new int*[fieldSize];

    for(int i=0; i<fieldSize; i++){
        field[i] = new int[fieldSize];
    }

    // empty tile means 0, X means 1, O means 2
    for(int i=0; i<fieldSize; i++){
        for(int j=0; j<fieldSize; j++){
            field[i][j] = 0;
        }
    }
}

int ticTacToe::checkState(){
    int tmp = 0;
    int draw = 0;
    for(int i=0; i<fieldSize; i++){
        for(int j=0; j<fieldSize; j++){
            if(field[i][j]!=0){
                draw++;

                // 4 loops for all cases

                tmp = field[i][j];
                for(int t=1; t<terms; t++){
                    if((j+t)<fieldSize){
                        if(field[i][j+t]==tmp) tmp = field[i][j+t];
                        else{
                            tmp = 0;
                            break;
                        }
                        if(t==terms-1) return tmp; 
                    }
                }
                tmp = field[i][j];
                for(int t=1; t<terms; t++){
                    if((i+t)<fieldSize){
                        if(field[i+t][j]==tmp) tmp = field[i+t][j];
                        else{
                            tmp = 0;
                            break;
                        } 
                        if(t==terms-1) return tmp; 
                    }
                }
                tmp = field[i][j];
                for(int t=1; t<terms; t++){
                    if((i+t)<fieldSize && (j+t)<fieldSize){
                        if(field[i+t][j+t]==tmp) tmp = field[i+t][j+t];
                        else{
                            tmp = 0;
                            break;
                        } 
                        if(t==terms-1) return tmp; 
                    }
                }
                tmp = field[i][j];
                for(int t=1; t<terms; t++){
                    if((i+t)<fieldSize && (j-t)>=0){
                        if(field[i+t][j-t]==tmp) tmp = field[i+t][j-t];
                        else{
                            tmp = 0;
                            break;
                        } 
                        if(t==terms-1) return tmp;
                    }
                }

                tmp = 0;

                
            }
        }
    }
    if(draw==fieldSize*fieldSize) return -1;
    return 0;
}

#endif