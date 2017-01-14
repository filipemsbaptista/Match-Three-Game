//
//  Gem.h
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#ifndef Gem_h
#define Gem_h
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <Sprite.h>

class Gem {

public:
    Gem();
    Gem(int row, int col);
    void loadSprite(SDL_Renderer* renderer);
    void update();
    void draw();
    
    int type;
    
    bool destroyed;
    
    int posX, posY, destX, destY;
    
    Sprite sprite;
    const char * spriteFile;
    int spriteSize, spriteOffsetX, spriteOffsetY;
    
    int _column, _row;

private:
   
};

#endif /* Gem_h */
