//
//  Sprite.h
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include <iostream>
#include <stdio.h>
#include <SDL.h>

using namespace std;

class Sprite {

private:
    SDL_Surface *image;
    SDL_Rect rect;
    
    int x, y;
    
public:
    Sprite(string spriteFile, int posX, int posY, int width, int height);
};

#endif /* Sprite_hpp */
