//
//  GameManager.h
//  Match Three Game
//
//  Created by Filipe Baptista on 07/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

#pragma once

#include <SDL.h>

#include <Board.h>

class GameManager {

public:
    GameManager();
    
    void init();

    void run();
    
    void mainLoop();
    
    
private:
    //Window variables
    SDL_Window* window;
    int width, height;
    
    bool quitGame;
    
    //Game board
    Board _board;
};

#endif /* GameManager_h */
