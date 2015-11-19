//
//  Entity.h   This file contains 3 classes: SceneNode , Entity , Aircraft
//  Hellfire
//
//  Created by Kevin Ling on 7/18/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Entity__
#define __Hellfire__Entity__

#include "SFML.h"
#include "ResourceHolder.h"
#include "SceneNode.h"


///////////////////////////////////////////////////////////
//
// Entity is the base class for all objects in Game
//
//////////////////////////////////////////////////////////
class Entity:public SceneNode
{
public:
    explicit       Entity(int hitpoints);
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    
    void    accelerate(sf::Vector2f velocity);
    void    accelerate(float vx, float vy);
    
    
    void    repair(int hitpoints);
    void    damage(int hitpoints);
    void    destroy();
    
    
    int     getHitpoints() const;
    virtual bool    isDestroyed()  const;
protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    
private:
    sf::Vector2f mVelocity;
    int          mHitpoints;
};















































#endif /* defined(__Hellfire__Entity__) */
