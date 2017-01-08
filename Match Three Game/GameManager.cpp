//
//  GameManager.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 07/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include "GameManager.h"

GameManager::GameManager(){
    window = nullptr;
    width = 800;
    height = 600;
    
    _board = Board(0,0, width, height);
}

void GameManager::init(){
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //Create window
    window = SDL_CreateWindow("Match 3 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    
    quitGame = false;
    
    //Create game Board
    _board.start();
}

void GameManager::run(){
    //Initialize system
    init();
    
    //Main game loop
    mainLoop();
}

void GameManager::mainLoop(){
    
    SDL_Event event;
    
    while(!quitGame){
        
        //Handle input
        SDL_PumpEvents();
        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quitGame = true;
                    break;
            }
        }
        
        // --- UPDATE ---
        //Board
        _board.update();
        
        //--- DRAW ---
        _board.draw();
    }
}
