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
    void loadSprite(SDL_Renderer* renderer);
    void draw(int row, int col);
    
    int type;
    
private:
    int column, row;
    
    Sprite sprite;
    const char * spriteFile;
    int spriteSize;
};

#endif /* Gem_h */
