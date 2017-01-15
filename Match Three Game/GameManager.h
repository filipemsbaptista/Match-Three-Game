//
//  GameManager.h
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <Board.h>

class GameManager {

public:
    GameManager();
    void init();
    void run();
    
private:
    //Window variables
    SDL_Window* window;
    SDL_Surface* windowSurface;
    SDL_Renderer* renderer;
    int width, height;
    
    //Audio
    Mix_Music *music;   //Background Music
    Mix_Chunk *gemSelect, *swipe, *match, *invalid; //SFX
    
    //Game management variables
    bool quitGame;
    
    //Game board
    Board _board;
    
    //Main game loop
    void mainLoop();
};

#endif /* GameManager_h */
