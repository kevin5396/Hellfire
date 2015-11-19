//
//  Pickup.h
//  Hellfire
//
//  Created by Kevin Ling 
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Pickup__
#define __Hellfire__Pickup__

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "Aircraft.h"
class Pickup: public Entity
{
public:
    enum Type
    {
        HealthRefill,
        MissileRefill,
        FireSpread,
        FireRate,
        TypeCount
    };
public:
    Pickup(Type type, const TextureHolder& textures);
    
    virtual unsigned int        getCategory() const;
    virtual sf::FloatRect       getBoundingRect() const;
    
    void                        apply(Aircraft& player) const;
    
protected:
    virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    Type                        mType;
    sf::Sprite                  mSprite;
};
#endif
