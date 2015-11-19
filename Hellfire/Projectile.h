//
//  Projectile.h
//  Hellfire
//
//  Created by Kevin Ling on 7/23/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Projectile__
#define __Hellfire__Projectile__

#include "Entity.h"
#include "ResourceIdentifiers.h"



class Projectile : public Entity
{
public:
    enum Type
    {
        AlliedBullet,
        EnemyBullet,
        Missile,
        Typecount
    };
public:
    Projectile(Type type, const TextureHolder& textures);
    
    void            guideTowards(sf::Vector2f position);
    bool            isGuided() const;
    
    virtual unsigned int    getCategory() const;
    virtual sf::FloatRect   getBoundingRect() const;
    float                   getSpeed()        const;
    int                     getDamage()       const;
    
private:
    virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
    virtual void            drawCurrent(sf::RenderTarget& target,
                                        sf::RenderStates states) const;
    
private:
    Type                    mType;
    sf::Sprite              mSprite;
    sf::Vector2f            mTargetDirection;
    
};

#endif /* defined(__Hellfire__Projectile__) */
