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
    
    Sprite sprite;

private:
    //Gems matrix
    Gem _board [8][8];
    
    //Sprite
    const char * spriteFile;
    int spriteWidth, spriteHeight;
    

    int _posX, _posY, _width, _height;
};

#endif /* Board_h */
