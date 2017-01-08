//
//  Sprite.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite(string spriteFile, int posX, int posY, int width, int height){
    
    image = SDL_LoadBMP(spriteFile);
    
    // Part of the bitmap that we want to draw
    SDL_Rect source;
    source.x = 24;
    source.y = 63;
    source.w = 65;
    source.h = 44;
    
    // Part of the screen we want to draw the sprite to
    SDL_Rect destination;
    
    destination.x = 100;
    destination.y = 100;
    destination.w = 65;
    destination.h = 44;
    
    SDL_BlitSurface(image, &source, screen, &destination);
    
}
