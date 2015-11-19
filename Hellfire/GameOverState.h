//
//  GameOverState.h
//  Hellfire
//
//  Created by Kevin Ling on 7/28/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__GameOverState__
#define __Hellfire__GameOverState__

#include "State.h"

class GameOverState : public State{
public:
    GameOverState(StateStack& stack, Context context);
    
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);
    
private:
    sf::Text            mText;
    sf::Time            mTimeElapsed;
    
};

#endif /* defined(__Hellfire__GameOverState__) */
