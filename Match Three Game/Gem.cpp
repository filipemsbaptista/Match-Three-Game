//
//  Gem.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include <Gem.h>

Gem::Gem(){
}

Gem::Gem(int row, int col) : sprite(){
    //Generate a random gem type
    type = rand() % 5;
    destroyed = false;

    //Get correspondent sprite file (according to generated type)
    spriteFile = ("/Users/filipemsbaptista/GIT/Match Three Game/Match Three Game/sprites/Color-" + to_string(type+1) + ".png").c_str();
    spriteSize = 70;
    spriteOffsetX = (1024 - spriteSize * 8) / 2;
    spriteOffsetY = (768 - spriteSize * 8) / 2;
    
    _row = row;
    _column = col;
    
    posX = _column * spriteSize + spriteOffsetX;
    posY = _row * spriteSize + spriteOffsetY;
}

void Gem::loadSprite(SDL_Renderer* renderer){
    sprite = Sprite(renderer, spriteFile, 0, 0, spriteSize, spriteSize);
}

void Gem::update(){
    
}

void Gem::draw(){
    //Draw sprite according to its position on the board (matrix's row and column)
    //if (!destroyed)
    sprite.draw(_column * spriteSize + spriteOffsetX, _row * spriteSize + spriteOffsetY);
}
