//
//  Match Three Game
//
//  Created by Filipe Baptista on 07/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include <iostream>
#include <SDL.h>

#include <GameManager.h>

using namespace std;

int main(int argc, const char * argv[]) {
    
    GameManager gameManager;
    gameManager.run();
    
    
    
    // ------------------------------------------------------------------------------------------------------
    
    /*
    int width = 800;
    int height = 600;
    
    //Handle SDL initialization error
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "\nSDL initialization failed:  %s", SDL_GetError());
        return 0;
    }
    //Set logging to verbose
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    //Create window
    auto window = SDL_CreateWindow("My Window", 0, 0, width, height, SDL_WINDOW_SHOWN);
    
    if(window == 0){
        SDL_Quit();
        return false;
    }
    
    //Main loop
    SDL_Event event;
    bool exit = false;
    while(!exit){
        SDL_PumpEvents();
        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    exit = true;
                    break;
            }
        }
    }
    */
    return 0;
}
