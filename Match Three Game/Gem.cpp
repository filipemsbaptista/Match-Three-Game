//
//  Gem.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include <Gem.h>

Gem::Gem() : sprite(){
    //Generate a random gem type
    type = rand() % 5;
    
    //Get correspondent sprite file (according to generated type)
    spriteFile = ("/Users/filipemsbaptista/GIT/Match Three Game/Match Three Game/sprites/Color-" + to_string(type+1) + ".png").c_str();
}

void Gem::loadSprite(SDL_Renderer* renderer){
    spriteSize = 70;
    sprite = Sprite(renderer, spriteFile, 0, 0, spriteSize, spriteSize);
}

void Gem::draw(int row, int col){
    //Draw sprite according to its position on the board (matrix's row and column)
    sprite.draw(row * spriteSize, col * spriteSize);
}
