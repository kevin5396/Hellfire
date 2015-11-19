//
//  State.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "State.h"
#include "StateStack.h"
#include "Application.h"
State::Context::Context(sf::RenderWindow& window, TextureHolder& textures
                        , FontHolder& fonts, Player& player)
:window(&window)
,textures(&textures)
,fonts(&fonts)
,player(&player)
{}


State::State(StateStack& stack, Context context)
:mStack(&stack)
,mContext(context)
{}

State::~State()
{
    
}
void State::requestStackClear()
{
    mStack->clearStates();
}
void State::requestStackPop()
{
    mStack->popState();
}
void State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

State::Context State::getContext() const
{
    return mContext;
}

