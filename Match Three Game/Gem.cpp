//
//  Gem.cpp
//  Match Three Game
//
//  Created by Filipe Baptista on 08/01/17.
//  Copyright © 2017 Filipe Baptista. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <Gem.h>


Gem::Gem(){
    //Generate a random gem type
    type = rand() % 5;
}

void Gem::draw(){
    
}
