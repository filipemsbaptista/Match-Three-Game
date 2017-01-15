//
//  Board.h
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#ifndef Board_h
#define Board_h
#pragma once

#include <iostream>
#include <SDL_mixer.h>
#include <Gem.h>

using namespace std;

class Board{

public:
    Board();
    Board(SDL_Renderer* renderer);
    
    void update();
    void draw();
    void processInput(int mouseX, int mouseY);
    

private:
    SDL_Renderer* _renderer;
    //Gems matrix
    Gem _board [8][8];
    //Board management variables
    int currentRow, currentColumn, selectedColumn, selectedRow;
    Gem currentGem;
    
    bool swappingGems, destroyGems;
    
    void swapGems(), findDestroyMatches(), dropColumns();
    bool matchingSwap(int i, int j), orthogonalSwipe(int x, int y, int a, int b);
    void printBoard();
    
    bool animating;
    void animateSwap();
    
    
    
    //Sprite
    Sprite sprite;
    const char * spriteFile;
    int spriteWidth, spriteHeight;
    
    
    //Audio
    Mix_Music *music;   //Background Music
    Mix_Chunk *gemSelect, swap, match, invalid; //SFX
};

#endif /* Board_h */
