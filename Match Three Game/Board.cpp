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

    //Check if there are initial matches
    findDestroyMatches();
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
        //Swap gems if dealing with orthognal neighboring cells
        if(orthogonalSwipe(selectedRow, selectedColumn, currentRow, currentColumn) ){

            if(!_board[selectedRow][selectedColumn].destroyed && !_board[currentRow][currentColumn].destroyed){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //!!! TODO: Drag sprites from one cell to the other !!!
                // insert code here . . .
                
                //Swap gems positions on the board
                _board[selectedRow][selectedColumn] = _board[currentRow][currentColumn];
                _board[currentRow][currentColumn] = currentGem;
                
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //!!! Check if there's a 3-match, if not then redo animation and swap back !!!
                if(matchingSwap(currentRow, currentColumn) || matchingSwap(selectedRow, selectedColumn)){
                    cout << "MATCH FOUND !" << endl;
                    findDestroyMatches();
                } else {
                    cout << "Undo swapping" << endl;
                    _board[currentRow][currentColumn] = _board[selectedRow][selectedColumn];
                    _board[selectedRow][selectedColumn] = currentGem;
                }
            }
            cout << "(" << selectedRow << ", " << selectedColumn << ") <-> (" << currentRow << ", " << currentColumn << ")" << endl;
        }
        
    }
}

// !!!! THIS NEEDS TO BE RECURSIVE WHILE A MATCH IS FOUND !!!!
void Board::findDestroyMatches(){
    foundMatch = false;
    
    //Horizontal matches
    for( int j = 0; j < 8; j++){
        for( int i = 0; i < 8; i++){
            if(_board[i][j].type == _board[i + 1][j].type){
                if(_board[i+1][j].type == _board[i + 2][j].type){
                    cout << " Destroying gems: (" << i << "," << j << ") , (" << i << "," << j+1 << ") and (" << i << "," << j+2 << ")" << endl;
                    //Destroy matched gems
                    _board[i][j].destroyed = true;
                    _board[i+1][j].destroyed = true;
                    _board[i+2][j].destroyed = true;
                    
                    foundMatch = true;
                    
                    i+=2;
                } else{
                    //Jump one column, since we know the next is equal but not part of a match
                    i++;
                }
            }
            
        }
    }
    //Vertical matches
    for( int i = 0; i < 8; i++){
        for( int j = 0; j < 8; j++){
            cout << "Checking row " << i << " column " << j << " . . ." << endl;
            //Next row has equal?
            if(_board[i][j].type == _board[i][j+1].type){
                //The second next as well?
                if(_board[i][j+1].type == _board[i][j+2].type){
                    cout << " Destroying gems: (" << i << "," << j << ") , (" << i << "," << j+1 << ") and (" << i << "," << j+2 << ")" << endl;
                    //Destroy matched gems
                    for(int x = 0; x < 3; x++)
                        _board[i][j + 1*x].destroyed = true;
                    
                    foundMatch = true;
                    
                    j+=2;
                } else{
                    //Jump one column, since we know the next is equal but not part of a match
                    j++;
                }
            }
            
        }
    }
    //If found any match, drop the necessary columns to fill up board
    if(foundMatch)
        dropColumns();
}

/*
 * Finds an empty space on the board and drops the the column above
 */
void Board::dropColumns(){
    
}


/*
 * Checks if the performed swap resulted in a 3-match
 */
bool Board::matchingSwap(int i, int j){
    //Horizontal Match
    if(_board[i][j-1].type == _board[i][j].type){
        if(_board[i][j-2].type == _board[i][j].type || _board[i][j+1].type == _board[i][j].type){
            cout << "Horizontal Match found !" << endl;
            return true;
        }
    } else if (_board[i][j+1].type == _board[i][j].type && _board[i][j+2].type == _board[i][j].type){
        cout << "Horizontal Match found !" << endl;
        return true;
    }
    
    //Vertical Match
    if(_board[i-1][j].type == _board[i][j].type){
        if(_board[i-2][j].type == _board[i][j].type || _board[i+1][j].type == _board[i][j].type){
            cout << "Vertical Match found !" << endl;
            return true;
        }
    } else if (_board[i+1][j].type == _board[i][j].type && _board[i+2][j].type == _board[i][j].type){
        cout << "Vertical Match found !" << endl;
        return true;
    }
    return false;
}


/*
 * Checks if two coordiantes are direct neighbors anf from orthogonal axis
 */
bool Board::orthogonalSwipe(int x, int y, int a, int b){
    if((abs(x - a) == 1 && abs(y - b) == 0) || (abs(x - a) == 0 && abs(y - b) == 1)){
        return true;
    }
    return false;
}
