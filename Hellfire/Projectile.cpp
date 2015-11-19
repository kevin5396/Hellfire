//
//  Projectile.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/23/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "Projectile.h"
#include "DataTables.h"
#include "Aircraft.h"
#include <cmath>
namespace
{
    std::vector<ProjectileData> Table1 = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures)
: Entity(1)
, mType(type)
, mSprite(textures.get(Table1[type].texture))
{
    centerOrigin(mSprite);
}

float toDegree(float radian)
{
    return 180.f / 3.141592653589793238462643383f * radian;
}

sf::Vector2f unitVector(sf::Vector2f vec)
{
    float length = std::sqrt(vec.x*vec.x + vec.y*vec.y);
    assert(vec != sf::Vector2f(0.f,0.f));
    return vec / length;
    
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (isGuided())
        {
            const float approachRate = 200.f;
            sf::Vector2f newVelocity = unitVector(approachRate
                                                  * dt.asSeconds() * mTargetDirection + getVelocity());
            newVelocity *= getSpeed();
            float angle = std::atan2(newVelocity.y, newVelocity.x);
            setRotation(toDegree(angle) + 90.f);
            setVelocity(newVelocity);
        }
    Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
unsigned int   Projectile::getCategory() const
{
    if (mType == EnemyBullet)
        return Category::EnemyProjectile;
    else
        return Category::AlliedProjectile;
}
sf::FloatRect  Projectile::getBoundingRect() const
{
    return  getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
float Projectile::getSpeed() const
{
    return Table1[mType].speed;
}
int   Projectile::getDamage() const
{
    return Table1[mType].damage;
}
bool Projectile::isGuided() const
{
    return mType == Missile;
}

void Projectile::guideTowards(sf::Vector2f position)
{
    assert(isGuided());
    mTargetDirection = unitVector(position - getWorldPosition());
}


