//
//  StateStack.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "StateStack.h"

StateStack::StateStack(State::Context context)
:mFactories()
,mPendingList()
,mStack()
,mContext(context)
{}

StateStack::PendingChange::PendingChange(Action action,
                                         States::ID stateID)
:action(action)
,stateID(stateID)
{}

State::Ptr  StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    
    return found->second();
}

void StateStack::handleEvent(const sf::Event &event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
            break;
    }
    
    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            break;
    }
    
    applyPendingChanges();
}

void StateStack::draw()
{
    for (auto & state : mStack)
        state->draw();
}

void StateStack::applyPendingChanges()
{
    for (auto & change : mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;
                
            case Pop:
                mStack.pop_back();
                break;
            
            case Clear:
                mStack.clear();
                break;
        }
    }
    
    mPendingList.clear();
}

void StateStack::pushState(States::ID stateID)
{
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

































