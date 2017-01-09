//
//  GameManager.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 07/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include "GameManager.h"

GameManager::GameManager() {
    window = nullptr;
    width = 1024;
    height = 768;
}

void GameManager::init(){
    
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    //Create window
    window = SDL_CreateWindow("Match 3 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    //Game management variables
    quitGame = false;
    
    //Create game Board
    _board = Board(renderer);
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
        
        // --- INPUT ---
        SDL_PumpEvents();
        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    _board.processInput(event.button.x, event.button.y);
                    break;
                    
                case SDL_QUIT:
                    quitGame = true;
                    break;
            }
        }
        
        // ---- UPDATE ----
        _board.update();
        
        
        // ---- DRAW ----
        SDL_RenderClear(renderer); //Clear the renderer
        
        _board.draw();
        
        SDL_RenderPresent(renderer); //Update the renderer
    }
    
    //Destroy Window
    SDL_DestroyWindow(window);
    //Quit SDL
    SDL_Quit();
    
}
