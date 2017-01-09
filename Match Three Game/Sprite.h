//
//  Sprite.h
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h
#pragma once

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Sprite {

private:
    //Renderer
    SDL_Renderer* _renderer;
    
    //Texture
    SDL_Texture* img;
    SDL_Rect texture_rect;
    
    int x, y;
    
public:
    Sprite();
    Sprite(SDL_Renderer* renderer, const char* spriteFile, int posX, int posY, int width, int height);
    
    void draw(int screenX, int screenY);
};

#endif /* Sprite_hpp */
