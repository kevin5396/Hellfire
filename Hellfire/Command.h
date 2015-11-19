//
//  Command.h
//  Hellfire
//
//  Created by Kevin Ling on 7/20/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Command__
#define __Hellfire__Command__

#include "SFML.h"
#include "SceneNode.h"
#include <functional>
#include "Category.h"

class SceneNode;
struct Command
{
    Command();
    
    std::function<void(SceneNode&, sf::Time)>   action;
    unsigned int                                category;
};



template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return [=](SceneNode& node, sf::Time dt)
    {
         // check if it's safe to cast
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        
        fn(static_cast<GameObject&>(node), dt);
    };
}
#endif /* defined(__Hellfire__Command__) */
