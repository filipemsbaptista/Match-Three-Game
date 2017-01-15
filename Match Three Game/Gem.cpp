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
    cout << "[Gem] Sprite File = " << spriteFile << endl;
    
    spriteSize = 70;
    spriteOffsetX = (1024 - spriteSize * 8) / 2;
    spriteOffsetY = (768 - spriteSize * 8) / 2;
    
    _row = row;
    _column = col;
    
    posX = _column * spriteSize + spriteOffsetX;
    posY = spriteOffsetY - spriteSize;

    speed = 1;
    
    arrivedDest = false;
}

void Gem::loadSprite(SDL_Renderer* renderer){
    sprite = Sprite(renderer, spriteFile, 0, 0, spriteSize, spriteSize);
}

void Gem::update(){
    
    //Check if gem is at the supposed position
    if(posX!= destX || posY != destY){
        arrivedDest = false;
        //Update horiontal position
        if(posX != destX)
            posX += speed * sign(posX, destX);
        //Update vertical position
        if(posY != destY)
            posY += speed * sign(posY,destY);
    } else
        arrivedDest = true;
    
}

void Gem::draw(){
    //Draw sprite according to its position on the board (matrix's row and column)
    sprite.draw(posX, posY);
}

void Gem::updatePos(int row, int col){
    _row = row;
    _column = col;
    
    //Set gem destination
    destX = _column * spriteSize + spriteOffsetX;
    destY = _row * spriteSize + spriteOffsetY;
    
    /*
     posX = posX + destX * sign(posX, destX) * speed;
     posY = posY + destY * sign(posY, destY) * speed;
     */
}


int Gem::sign(int pos, int dest){
    int sign;
    if(pos > dest) sign = -1;
    else if (pos <= dest) sign = 1;
    return sign;
}
