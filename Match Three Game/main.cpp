//
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
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
    //Handle SDL initialization error
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "\nSDL initialization failed:  %s", SDL_GetError());
        return 0;
    }

    //Set logging to verbose
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
     */
    
    return 0;
}
