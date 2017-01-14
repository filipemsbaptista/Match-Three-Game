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
    _renderer = renderer;
    
    //Load Sprite
    spriteWidth = 1024;
    spriteHeight = 768;
    sprite = Sprite(_renderer, "/Users/filipemsbaptista/GIT/Match Three Game/Match Three Game/sprites/Backdrop13.jpg",
                    0, 0, spriteWidth, spriteHeight);
    
    
    //Create random gems for each board cell
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j] = Gem(i, j);
            _board[i][j].loadSprite(_renderer);
        }
        cout << endl;
    }
    
    cout << "AT START" << endl;
    printBoard();
    
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
            _board[i][j].draw();
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
    
        cout << "Selected Cell = (" << currentRow <<",  " <<  currentColumn << ")  |  Type = " << _board[currentRow][currentColumn].type << endl;
        //Handle gems swapping
        swapGems();
        
       
        /*
        //Print hceck state
        for(int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++){
                if(_board[i][j]._row != i)
                    cout << "Incoherent ROW found ! ";
                if(_board[i][j]._column != j)
                    cout << "Incoherent COLUMN found ! ";
                if(_board[i][j]._row != i || _board[i][j]._column != j)
                    cout << " On cell (" << i << ", " << j << ")" << endl;
            } cout << endl;
         */
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
                
                printBoard();
                
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

void Board::findDestroyMatches(){
    destroyGems = true;
    bool foundMatch;
    int a;
    
    while(destroyGems){
        
        destroyGems = false;
        
        //Vertical matches
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
        //Horizontal matches
        for( int i = 0; i < 8; i++){
            for( int j = 0; j < 8; j++){
                //Next row has equal?
                if(_board[i][j].type == _board[i][j+1].type){
                    //The second next as well?
                    if(_board[i][j+1].type == _board[i][j+2].type){
                        foundMatch = true;
                        destroyGems = true;
                        //Destroy 3 matched gems
                        for (int x = 0; x < 3; x++)
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
        if(destroyGems) {
            cout << "DESTROY!" << endl;
            //cout << "BEFORE DROP !" << endl;
            printBoard();
            
            dropColumns();
        
            //cout << "AFTER DROP !" << endl;
            printBoard();
            
            
            //Update gems own row and column references
            for(int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++){
                    _board[i][j].update(i , j);
                }
            
        }
    }
}


/*
 * Finds an empty space on the board and drops the the column above
 */
void Board::dropColumns(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(_board[j][i].destroyed){ //Found empty cell on current column
                cout << "Found empty cell on (" << i << ", " << j <<") !!!!" << endl;
                for(int x = j; x > 0; x--){
                    _board[x][i] = _board[x-1][i];
                    _board[x][i].destroyed = false;
                }
                _board[0][i] = Gem(0,i);
                _board[0][i].loadSprite(_renderer);
            }
        }
    }
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

void Board::printBoard(){
    for (int i = 0; i < 8; i++){
        cout << "i=" << i;
        for(int j = 0; j < 8; j++){
            cout << "j=" << j;
            cout << "[" << _board[i][j].type << "]";
        }
        cout << endl;
    }
}
