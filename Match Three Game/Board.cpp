//
//  Board.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include <Board.h>

Board::Board(){

}

Board::Board(int posX, int posY, int width, int height){
    _posX = posX;
    _posY = posY;
    _width = width;
    _height = height;
}

void Board::start(){
    //Create random gems for each board cell
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j] = Gem();
        }
    }
    
    //TODO: REMOVE THIS FUNCTION Print the board
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << "[" << _board[i][j].type << "]";
        }
        cout << endl;
    }
}

void Board::update(){

}

void Board::draw(){
    
    
}
