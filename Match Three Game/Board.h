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
#include <stdio.h>
#include <Gem.h>

using namespace std;

class Board{

public:
    Board();
    Board(int posX, int posY, int width, int height);
    
    void start();
    
    void update();
    
    void draw();
    
private:
    int _posX, _posY, _width, _height;
    Gem _board [8][8];
};

#endif /* Board_h */
