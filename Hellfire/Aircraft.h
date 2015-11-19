//
//  Aircraft.h
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Aircraft__
#define __Hellfire__Aircraft__

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Command.h"
#include "Projectile.h"
//////////////////////////////////////
//
// Aircraft
//
/////////////////////////////////////
class Aircraft: public Entity
{
public:
    enum Type{Player1,Player2,Player3,Player4, Enemy1,Enemy2,Enemy3,Enemy4,Boss1,Boss2,Typecount};
    
    explicit Aircraft(Type type);
    Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);
    
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    // update Health
    void         updateText();
    
    // update Enemy Aircraft movement
    void         updateMovementPattern(sf::Time dt);
    // get Category
    virtual unsigned int getCategory() const;
    
    // used in collision detection
    virtual sf::FloatRect       getBoundingRect() const;
    
    
    float        getSpeed() const;
    bool         isAllied() const;
    Type         getType()  const;
    virtual bool         isMarkedForRemoval() const;
    
    void         fire();
    void         checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
    void         createBullet(SceneNode& node,const TextureHolder& textures) const;
    void         createProjectile(SceneNode& node, Projectile::Type type,
                                  float xoffset, float yoffset,
                                  const TextureHolder& textures) const;
    void		 checkPickupDrop(CommandQueue& commands);
    void	   	 createPickup(SceneNode& node, const TextureHolder& textures) const;

    
    void         increaseFireRate();
    void         increaseSpread();
    void         collectMissiles(unsigned int cnt);
    void         launchMissile();
    
private:
    Type mType;
    sf::Sprite mSprite;
    TextNode*  mHealthDisplay;
    float      mTravelledDistance;
    int        mDirectionIndex;
    bool       mIsFiring;
    bool       mIsLaunchMissile;
    sf::Time   mFireCountdown;
    int        mFireRateLevel;
    Command    mFireCommand;
    Command    mMissileCommand;
    int        mSpreadLevel;
    bool       mIsMarkedForRemoval;
    
    int						mMissileAmmo;
    
    Command 				mDropPickupCommand;
};

// independent function
Textures::ID toTextureID(Aircraft::Type type);
#endif