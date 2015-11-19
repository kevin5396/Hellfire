//
//  Entity.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/18/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "Entity.h"



///////////////////////////////////
//
//Entity
//
//////////////////////////////////
Entity::Entity(int hitpoints)
: mHitpoints(hitpoints)
{}
void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}
void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}
sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}
void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    move(mVelocity * dt.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

void Entity::repair(int hitpoints)
{
    mHitpoints += hitpoints;
}
void Entity::damage(int hitpoints)
{
    mHitpoints -= hitpoints;
}
void Entity::destroy()
{
    mHitpoints = 0;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}

bool Entity::isDestroyed() const
{
    return mHitpoints <= 0;
}












































