//
//  Aircraft.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "Aircraft.h"
#include <cmath>
#include "CommandQueue.h"
#include "DataTables.h"
#include "Pickup.h"
//////////////////////
//
// Aircraft
//
//////////////////////
namespace
{
    const std::vector<AircraftData> Table = initializeAircraftData();
}
#include <random>
namespace
{
    std::default_random_engine createRandomEngine()
    {
        auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }
    
    auto RandomEngine = createRandomEngine();
}
float toRadian(float degree)
{
    return 3.141592653589793238462643383f / 180.f * degree;
}
unsigned int randomInt(unsigned int count)
{
    std::uniform_int_distribution<> distr(0, count - 1);
    return distr(RandomEngine);
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hitpoints)
, mType(type), mSprite(textures.get(Table[mType].texture), Table[mType].textRect),mHealthDisplay(nullptr)
, mTravelledDistance(0.f), mDirectionIndex(0), mIsFiring(false), mFireCountdown(sf::Time::Zero)
, mFireRateLevel(1), mFireCommand(), mSpreadLevel(1), mIsMarkedForRemoval(false)
, mMissileCommand(), mIsLaunchMissile(false), mMissileAmmo(2), mDropPickupCommand()
{
    if (!isAllied())
        mFireRateLevel = 0;
    centerOrigin(mSprite);
    
    std::unique_ptr<TextNode>   healthDisplay(new TextNode(fonts, ""));
    mHealthDisplay = healthDisplay.get();
    
    attachChild(std::move(healthDisplay));
    
    mFireCommand.category = Category::Scene;
    mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
    {
        createBullet(node, textures);
    };
    mMissileCommand.category = Category::Scene;
    mMissileCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
    {
        createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
    };
    
    mDropPickupCommand.category = Category::Scene;
    mDropPickupCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
    {
        createPickup(node, textures);
    };
}

void Aircraft::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


unsigned int Aircraft::getCategory() const
{
    switch (mType) {
        case Player1:
            return Category::PlayerAircraft;
        default:
            return Category::EnemyAircraft;
    }
}

float Aircraft::getSpeed() const
{
    return Table[mType].speed;
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (isDestroyed())
    {
        checkPickupDrop(commands);
        mIsMarkedForRemoval = true;
        return;
        
    }
    checkProjectileLaunch(dt, commands);
    updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);
    updateText();
}

void Aircraft::updateText()
{
    mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP");
    mHealthDisplay->setPosition(0.f, 50.f);
    mHealthDisplay->setRotation(-getRotation());
}

void Aircraft::updateMovementPattern(sf::Time dt)
{
    const std::vector<Direction>& directions = Table[mType].directions;
    if (!directions.empty())
    {
        float distanceToTravel = directions[mDirectionIndex].distance;
        if (mTravelledDistance > distanceToTravel)
        {
            mDirectionIndex = (mDirectionIndex + 1) % directions.size();
            mTravelledDistance = 0.f;
        }
        
        float Radians = toRadian(directions[mDirectionIndex].angle + 90.f);
        float vx = getSpeed() * std::cos(Radians);
        float vy = getSpeed() * std::sin(Radians);
        setVelocity(vx, vy);
        mTravelledDistance += getSpeed() * dt.asSeconds();
    }
}
bool Aircraft::isAllied() const
{
    return mType == Player1;       //TODO:
}

void Aircraft::fire()
{
    mIsFiring = true;
}
void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue &commands)
{
    fire();
    if (mIsFiring && mFireCountdown <= sf::Time::Zero)
    {
        
        commands.push(mFireCommand);
        mFireCountdown += sf::seconds(1.f / (mFireRateLevel + 1.f));
        mIsFiring = false;
    }
    else if (mFireCountdown > sf::Time::Zero)
    {
        mFireCountdown -= dt;
        mIsFiring = false;
    }
    
    if (mIsLaunchMissile)
    {
        commands.push(mMissileCommand);
        mIsLaunchMissile = false;
    }
    
}

void Aircraft::createBullet(SceneNode &node, const TextureHolder &textures) const
{
    Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;
    
    switch (mSpreadLevel)
    {
        case 1:
            createProjectile(node, type, 0.0f, 0.5f, textures);
            break;
        case 2:
            createProjectile(node, type, -0.33f, 0.33f, textures);
            createProjectile(node, type, 0.33f, 0.33f, textures);
            break;
        case 3:
            createProjectile(node, type, -0.33f, 0.33f, textures);
            createProjectile(node, type, 0.0f, 0.5f, textures);
            createProjectile(node, type, 0.33f, 0.33f, textures);
            break;
    }
}

void Aircraft::createProjectile(SceneNode &node, Projectile::Type type, float xoffset, float yoffset, const TextureHolder &textures) const
{
    std::unique_ptr<Projectile> projectile(new Projectile(type, textures));
    
    sf::Vector2f offset(
        xoffset * mSprite.getGlobalBounds().width,
                        yoffset * mSprite.getGlobalBounds().height);
    sf::Vector2f velocity(0, projectile->getSpeed());
    float sign = isAllied() ? -1.f : 1.f ;  // the move direction depends on it's ally or enemy
    
    projectile->setPosition(getWorldPosition() + offset * sign);
    projectile->setVelocity(velocity * sign);
    
   
    node.attachChild(std::move(projectile));
    
}

sf::FloatRect Aircraft::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

Aircraft::Type Aircraft::getType() const
{
    return mType;
}

bool Aircraft::isMarkedForRemoval() const
{
    return mIsMarkedForRemoval;
}

void Aircraft::increaseFireRate()
{
    if (mFireRateLevel < 10)
        ++mFireRateLevel;
}

void Aircraft::increaseSpread()
{
    if (mSpreadLevel < 3)
        ++mSpreadLevel;
}
void Aircraft::collectMissiles(unsigned int cnt)
{
    mMissileAmmo += cnt;
}
void Aircraft::launchMissile()
{
    if (mMissileAmmo > 0)
    {
        mIsLaunchMissile = true;
        --mMissileAmmo;
    }
}

void Aircraft::checkPickupDrop(CommandQueue &commands)
{
    if (!isAllied() &&  randomInt(3) == 0)
        commands.push(mDropPickupCommand);
    
}

void Aircraft::createPickup(SceneNode &node, const TextureHolder &textures) const
{
    auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));
    
    std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
    pickup->setPosition(getWorldPosition());
    pickup->setVelocity(0.f, 1.f);
    node.attachChild(std::move(pickup));

    
}

















