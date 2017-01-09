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
    
    swappingGems = false;
}

void Board::update(){
    
  
}

void Board::draw(){
    //Backdrop
    sprite.draw(0, 0);
    
    //Gems
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j].draw(i, j);
        }
    }
}

void Board::processInput( int mouseX, int mouseY){
    int offsetX = (1024 - 70 * 8) / 2;
    int offsetY = (768 - 70 * 8) / 2;
    
    //Only handle mouse clicks if inside the board area
    if(mouseX > offsetX && mouseX < 1024 - offsetX && mouseY > offsetY && mouseY < 768 - offsetY){
        // Store currently selected cell
        currentRow = (mouseX - offsetX) / 70;
        currentColumn = (mouseY - offsetY) / 70;
    
        cout << "Selected Cell = (" << currentRow <<",  " << currentColumn << ")  |  Type = " << _board[currentRow][currentColumn].type << endl;
        
        //Handle gems swapping
        swapGems();
    }
}

void Board::swapGems(){
    swappingGems = !swappingGems;
    
    if(swappingGems){
        //Store currently selected gem into temp variable
        selectedRow = currentRow;
        selectedColumn = currentColumn;
        
        currentGem = _board[selectedRow][selectedColumn];
    } else {
        //Swap gems if dealing with neighboring cells
        if(abs(selectedRow - currentRow) <=1 && abs(selectedColumn - currentColumn)<=1){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //!!! TODO: Drag sprites from one cell to the other !!!
            // insert code here . . .
            
            //Swap gems positions on the board
            _board[selectedRow][selectedColumn] = _board[currentRow][currentColumn];
            _board[currentRow][currentColumn] = currentGem;
            
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //!!! TODO: Check if there's a 3-match, if not then redo animation and swap back !!!
            // insert code here . . .
            
        }
        cout << "(" << selectedRow << ", " << selectedColumn << ") <-> (" << currentRow << ", " << currentColumn << ")" << endl;
    }
}
