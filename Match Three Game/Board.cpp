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
        currentColumn = (mouseX - offsetX) / 70;
        currentRow = (mouseY - offsetY) / 70;
    
        cout << "Selected Cell = (" << currentColumn <<",  " << currentRow << ")  |  Type = " << _board[currentColumn][currentRow].type << endl;
        
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
        
        currentGem = _board[selectedColumn][selectedRow];
    } else {
        //Swap gems if dealing with orthognal neighboring cells
        if(orthogonalSwipe(selectedColumn, selectedRow, currentColumn, currentRow) ){

            if(!_board[selectedColumn][selectedRow].destroyed && !_board[currentColumn][currentRow].destroyed){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //!!! TODO: Drag sprites from one cell to the other !!!
                // insert code here . . .
                
                //Swap gems positions on the board
                _board[selectedColumn][selectedRow] = _board[currentColumn][currentRow];
                _board[currentColumn][currentRow] = currentGem;
                
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //!!! Check if there's a 3-match, if not then redo animation and swap back !!!
                if(matchingSwap(currentColumn, currentRow) || matchingSwap(selectedColumn, selectedRow)){
                    cout << "MATCH FOUND !" << endl;
                    findDestroyMatches();
                } else {
                    cout << "Undo swapping" << endl;
                    _board[currentColumn][currentRow] = _board[selectedColumn][selectedRow];
                    _board[selectedColumn][selectedRow] = currentGem;
                }
            }
            cout << "(" << selectedColumn << ", " << selectedRow << ") <-> (" << currentColumn << ", " << currentRow << ")" << endl;
        }
        
    }
}

// !!!! THIS NEEDS TO BE RECURSIVE WHILE A MATCH IS FOUND !!!!
void Board::findDestroyMatches(){
    bool foundMatch;
    int a;
    
    //Horizontal matches
    for( int j = 0; j < 8; j++){
        for( int i = 0; i < 8; i++){
            if(_board[i][j].type == _board[i + 1][j].type){
                if(_board[i+1][j].type == _board[i + 2][j].type){
                    foundMatch = true;
                    destroyGems = true;
                    //Destroy 3 matched gems
                    _board[i][j].destroyed = true;
                    _board[i+1][j].destroyed = true;
                    _board[i+2][j].destroyed = true;
                    
                    //Check if theres a bigger match (>3)
                    a = 3;
                    while (foundMatch){
                        if(_board[i+a][j].type == _board[i][j].type){
                            _board[i+a][j].destroyed = true;
                            a++;
                        } else
                            foundMatch = false;
                    }
                    i+= a - 1;
                } else{
                    //Skip one column, since we know the next is equal but not part of a match
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
                    foundMatch = true;
                    destroyGems = true;
                    //Destroy 3 matched gems
                    for(int x = 0; x < 3; x++)
                        _board[i][j + 1*x].destroyed = true;
                    
                    //Check if theres a bigger match (>3)
                    a = 3;
                    while (foundMatch){
                        if(_board[i][j+a].type == _board[i][j].type){
                            _board[i][j+a].destroyed = true;
                            a++;
                        } else
                            foundMatch = false;
                    }
                    j+=a-1;
                } else{
                    //Skip one column
                    j++;
                }
            }
            
        }
    }
    //If any gem was destroyed, check for the necessary column drops in order to fill up the board
    if(destroyGems)
        dropColumns();
}


/*
 * Finds an empty space on the board and drops the the column above
 */
void Board::dropColumns(){
    //If a gap is found, shift column and by the end call findDestroyMatches() else do nothing
    
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
