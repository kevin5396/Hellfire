//
//  State.h
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__State__
#define __Hellfire__State__
//////////////////////////////////////////////////
//
// screen of the game:  Mainmenu, gameplay, etc.
//
//////////////////////////////////////////////////
#include "SFML.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include "Player.h"

class StateStack;
class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& texutures,
                FontHolder& fonts, Player& player);
        
        sf::RenderWindow*       window;
        TextureHolder*          textures;
        FontHolder*             fonts;
        Player*                 player;
    };
    
    State(StateStack& stack, Context context);
    virtual ~State();
    
    virtual void    draw() = 0;
    virtual bool    update(sf::Time dt) = 0;
    virtual bool    handleEvent(const sf::Event& event) = 0;
    
protected:
    void            requestStackPush(States::ID stateID);
    void            requestStackPop();
    void            requestStackClear();

    
    Context         getContext() const;
    
private:
    StateStack*     mStack;
    Context         mContext;
};
#endif /* defined(__Hellfire__State__) */
