//
//  MenuState.h
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__MenuState__
#define __Hellfire__MenuState__

#include "SFML.h"
#include "State.h"
class MenuState : public State
{
public:
    enum OptionName{Play, Quit};
    MenuState(StateStack& stack, Context context);
    
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);
    
    void                updateOption();
private:
    sf::Sprite              mBackground;
    std::vector<sf::Text>   mOptions;
    std::size_t             mOptionIndex;
};

#endif /* defined(__Hellfire__MenuState__) */
