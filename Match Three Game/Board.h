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
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Gem.h>

using namespace std;

class Board{

public:
    Board();
    Board(SDL_Renderer* renderer);
    
    void update();
    void draw();
    void processInput(int mouseX, int mouseY, bool click);
    
private:
    SDL_Renderer* _renderer;
    
    //Gems matrix
    Gem _board [8][8];
    
    //Board management variables
    int currentRow, currentColumn, selectedColumn, selectedRow;
    Gem currentGem;
    bool swappingGems, destroyGems;
    
    //Board management methods
    void swapGems(), findDestroyMatches(), dropColumns(), printBoard();
    bool matchingSwap(int i, int j), orthogonalSwipe(int x, int y, int a, int b);
    
    //Score
    int score;
    
    //Animations
    bool animating;
    void animateSwap();
    
    //Sprites
    Sprite sprite;
    const char * spriteFile;
    int spriteWidth, spriteHeight;
    
    //Score Text
    int fontSize;
    TTF_Font* textFont;
    SDL_Surface* textSurface;
    SDL_Color textColor;
    SDL_Texture* text;
    SDL_Rect textRect;
    const char *scoreText;
};

#endif /* Board_h */
