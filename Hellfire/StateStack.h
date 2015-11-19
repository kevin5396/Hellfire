//
//  StateStack.h
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__StateStack__
#define __Hellfire__StateStack__

#include "State.h"
#include "SFML.h"
class State;
class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

    explicit    StateStack(State::Context context);
    
    template <typename T>
    void        registerState(States::ID stateID);
    
    void        update(sf::Time dt);
    void        draw();
    void        handleEvent(const sf::Event& event);
    
    void        pushState(States::ID stateID);
    void        popState();
    void        clearStates();
    
    bool        isEmpty() const;
    
private:
    State::Ptr  createState(States::ID stateID);
    void        applyPendingChanges();
    
    struct PendingChange
    {
        explicit    PendingChange(Action action, States::ID stateID = States::None);
        Action      action;
        States::ID  stateID;
    };
    
    std::vector<State::Ptr>                             mStack;
    std::vector<PendingChange>                          mPendingList;
    State::Context                                      mContext;
    std::map<States::ID,std::function<State::Ptr()>>    mFactories;
};



template <typename T>
void    StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] = [this]()
    {
        return State::Ptr(new T(*this, mContext));
    };
}


#endif /* defined(__Hellfire__StateStack__) */
