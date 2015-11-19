//
//  GameState.h
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__GameState__
#define __Hellfire__GameState__

#include "State.h"
#include "World.h"
class GameState: public State
{
public:
    GameState(StateStack& stack, Context context);
    
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);
private:
    World               mWorld;
    Player&             mPlayer;

};

#endif /* defined(__Hellfire__GameState__) */
