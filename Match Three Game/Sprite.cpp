//
//  Sprite.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite(){
}

Sprite::Sprite(SDL_Renderer* renderer, const char* spriteFile, int posX, int posY, int width, int height){
    /*
    //Load sprite image form file
    image = SDL_LoadBMP(spriteFile);
  
    // Part of the sprite file we want to draw on the screen
    source.x = x;
    source.y = x;
    source.w = width;
    source.h = height;
    */
    // --------------------
    
    _renderer = renderer;
    
    //Create Texture
    file = spriteFile;
    img = IMG_LoadTexture(_renderer, file);
    if(img == nullptr)
        cout << "ERROR: " << SDL_GetError() << endl;
    
    //Set texture properties
    texture_rect.x = posX;  //the x coordinate
    texture_rect.y = posY; // the y coordinate
    texture_rect.w = width; //the width of the texture
    texture_rect.h = height; //the height of the texture
}


void Sprite::draw(int screenX, int screenY){
    texture_rect.x = screenX;
    texture_rect.y = screenY;
    
    SDL_RenderCopy(_renderer, img, NULL, &texture_rect);
}
