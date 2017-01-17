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
    
    //Load Background Sprite
    spriteWidth = 1024;
    spriteHeight = 768;
    spriteFile = "Resources/Backdrop13.jpg";
    sprite = Sprite(_renderer, spriteFile, 0, 0, spriteWidth, spriteHeight);
    

    //Create random gems for each board cell
    cout << "Generating board . . ." << endl;
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j] = Gem(i, j);
            _board[i][j].loadSprite(_renderer);
        }
    }
    
    printBoard();
    
    swappingGems = false;

    //Check if there are initial matches
    findDestroyMatches();
    
    //Set initial score
    score = 0;
    
    /*
     !!! Text rendering was discarded due to memory leaks caused by SDL_TTF !!!
     !!!!!!!!!!!!!!!!!!!!    See its code below    !!!!!!!!!!!!!!!!!!!!!!!!!!!!
     
     fontSize = 32;
     //Load Score text
     if(TTF_Init() == -1)
     cout << "TTF_Init: " << SDL_GetError() << endl;
     textFont = TTF_OpenFont("Resources/sansation.ttf", fontSize); //Define text font
     if(textFont == nullptr)
     cout << "TTF_OpenFont: " << SDL_GetError() << endl;
     textColor = {255, 255, 255}; // Text color
     textSurface = TTF_RenderText_Solid(textFont, "Score : " , textColor);
     if(textSurface == nullptr)
     cout << "TTF_RenderText_Solid: " << SDL_GetError() << endl;
     
     textRect.w = fontSize * 4; // controls the width of the rect
     textRect.h = fontSize; // controls the height of the rect
     textRect.x = spriteWidth / 2 - textRect.w / 2;  //controls the rect's x coordinate
     textRect.y = 15; // controls the rect's y coordinte
     */
    
}

void Board::update(){
    //Call gems update method
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            _board[i][j].update();
        }
    }
}

void Board::draw(){
    //Draw Backdrop
    sprite.draw(0, 0);
    
    //Draw Gems
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            _board[i][j].draw();
        }
    }
    
    /*  
    !!! Text rendering was discarded due to memory leaks caused by SDL_TTF !!!
    !!!!!!!!!!!!!!!!!!!!    See its code below    !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
     //Score Text
    scoreText =("Score : " + to_string(score)).c_str();
    textSurface = TTF_RenderText_Solid(textFont, scoreText, textColor);
    text = SDL_CreateTextureFromSurface(_renderer, textSurface); //Convert text into a texture
    SDL_RenderCopy(_renderer, text, NULL, &textRect);
     */
}

/*
 * Store currently selected board cell and call gems handling method
 */
void Board::processInput( int mouseX, int mouseY, bool click){
    int offsetX = (1024 - 70 * 8) / 2;
    int offsetY = (768 - 70 * 8) / 2;
    
    //Only handle mouse clicks if inside the board area
    if(mouseX > offsetX && mouseX < 1024 - offsetX && mouseY > offsetY && mouseY < 768 - offsetY){
        //If clicked in a new cell 
        if((mouseX - offsetX) / 70 != currentColumn || (mouseY - offsetY) / 70 != currentRow || click){
            // Store currently selected cell
            currentColumn = (mouseX - offsetX) / 70;
            currentRow = (mouseY - offsetY) / 70;
    
            cout << "Current Cell = (" << currentRow <<",  " <<  currentColumn << ")  |  Type = " << _board[currentRow][currentColumn].type << endl;
        
            //Handle gems swapping
            swapGems();
        }
    }
}

/*
 * Handle gems actions, i.e., picking up a new gem or, if already picked, swapping with another
 */
void Board::swapGems(){
    //Change action type only if selecting a different gem
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

                //Swap gems positions on the board
                _board[selectedRow][selectedColumn] = _board[currentRow][currentColumn];
                _board[currentRow][currentColumn] = currentGem;
                //And update their position references
                _board[selectedRow][selectedColumn].updatePos(selectedRow, selectedColumn);
                _board[currentRow][currentColumn].updatePos(currentRow, currentColumn);
                
                cout << "Swapping gems . . . . . . ." << endl;
                //Play swipe SFX
                if(Mix_PlayChannel( -1, Mix_LoadWAV("Resources/swipe.mp3"), 0 ) == -1)
                    cout << "ERROR: Couldn't SFX! " << SDL_GetError() << endl;
                //Play swipe Animation
                animateSwap();
                
                
                //Check if there's a 3-match, if not then undo and swap back !!!
                if(matchingSwap(currentRow, currentColumn) || matchingSwap(selectedRow, selectedColumn)){
                    
                    cout << "MATCH FOUND !" << endl;
                    findDestroyMatches();
                    
                    //Play swipe SFX
                    if(Mix_PlayChannel( -1, Mix_LoadWAV("Resources/match.mp3"), 0 ) == -1)
                        cout << "ERROR: Couldn't SFX! " << SDL_GetError() << endl;
                    
                    printBoard();
                } else {
                    cout << "Undoing swap . . . . . . ." << endl;
                    //Undo swapping
                    _board[currentRow][currentColumn] = _board[selectedRow][selectedColumn];
                    _board[selectedRow][selectedColumn] = currentGem;
                    //Reset gems position reference to their original ones
                    _board[selectedRow][selectedColumn].updatePos(selectedRow, selectedColumn);
                    _board[currentRow][currentColumn].updatePos(currentRow, currentColumn);
                    
                    //Play swipe SFX
                    if(Mix_PlayChannel( -1, Mix_LoadWAV("Resources/swipe.mp3"), 0 ) == -1)
                        cout << "ERROR: Couldn't SFX! " << SDL_GetError() << endl;
                    //Play swipe Animation
                    animateSwap();
                    
                    swappingGems = false;
                }
            }
            cout << "(" << selectedRow << ", " << selectedColumn << ") <-> (" << currentRow << ", " << currentColumn << ")" << endl;
        }
    }
}

/*
 * Checks if there's a match between 3 or more gems (horizontal or vertical alignement), updates score according to number of matched gems and sets them as destroyed
 */
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
                        //Update score
                        score += a;
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
                        //Update score
                        score += a;
                    } else{
                        //Skip one column
                        j++;
                    }
                }
            }
        }
        
        //If any gem was destroyed, call the columns drop function to handle the resultant chain column drops in order to fill up the board with no matches
        if(destroyGems) {
            //Call method for dropping columns
            dropColumns();
        
            //Update gems own row and column references
            for(int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++){
                    _board[i][j].updatePos(i , j);
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
 * Checks if two coordiantes are direct neighbors and from orthogonal axis
 */
bool Board::orthogonalSwipe(int x, int y, int a, int b){
    if((abs(x - a) == 1 && abs(y - b) == 0) || (abs(x - a) == 0 && abs(y - b) == 1)){
        return true;
    }
    return false;
}

/*
 * Animates the gems swap
 */
void Board::animateSwap(){
    animating = true;
    _board[selectedRow][selectedColumn].arrivedDest = false;
    _board[currentRow][currentColumn].arrivedDest = false;
    
    while (animating){
        SDL_RenderClear(_renderer);
        draw();
        _board[selectedRow][selectedColumn].update(); _board[selectedRow][selectedColumn].draw();
        _board[currentRow][currentColumn].update(); _board[currentRow][currentColumn].draw();
        SDL_RenderPresent(_renderer);
        
        if(_board[selectedRow][selectedColumn].arrivedDest && _board[currentRow][currentColumn].arrivedDest)
            animating = false;
    }
}

/*
 * Prints the current board state to the terminal
 */
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
