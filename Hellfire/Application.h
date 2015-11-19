//
//  Application.h
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Application__
#define __Hellfire__Application__

#include "SFML.h"
#include "StateStack.h"
#include "Player.h"
#include "ResourceIdentifiers.h"
#include "GameState.h"
#include "MenuState.h"
#include "GameOverState.h"
class Application
{
public:
                    Application();
    
    // run the application
    void            run();
private:

    void            processInput();
    void            update(sf::Time dt);

    // display
    void            render();
    
    // register available states, e.g: Menu, Game, GameOver...
    void            registerStates();
    

private:
    
    // time step modification
    static const sf::Time   timePerFrame;
    
    // main window
    sf::RenderWindow        mWindow;
    
    // store the textures
    TextureHolder           mTextures;
    FontHolder              mFonts;
    
    // handle input
    Player                  mPlayer;
    
    // a collection of states
    StateStack              mStateStack;
};



#endif /* defined(__Hellfire__Application__) */
