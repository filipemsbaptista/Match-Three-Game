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
    //Gems matrix
    Gem _board [8][8];
    //Board management variables
    int currentRow, currentColumn, selectedColumn, selectedRow;
    bool swappingGems;
    Gem currentGem;

    void swapGems();
    bool orthogonalSwipe(int x, int y, int a, int b);

    //Sprite
    Sprite sprite;
    const char * spriteFile;
    int spriteWidth, spriteHeight;
    
};

#endif /* Board_h */
