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

Board::Board(SDL_Renderer* renderer){
    //Load Sprite
    spriteWidth = 1024;
    spriteHeight = 768;
    sprite = Sprite(renderer, "/Users/filipemsbaptista/GIT/Match Three Game/Match Three Game/sprites/Backdrop13.jpg",
                    0, 0, spriteWidth, spriteHeight);
    
    
    //Create random gems for each board cell
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j] = Gem();
            _board[i][j].loadSprite(renderer);
            cout << "[" << _board[i][j].type << "]";
        }
        cout << endl;
    }
}

void Board::update(){

}

void Board::draw(){
    //Backdrop
    sprite.draw(0, 0);
    
    //Board
    
    
    //Gems
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j].draw(i, j);
        }
    }
}
