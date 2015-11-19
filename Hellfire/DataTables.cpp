//
//  DataTables.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "DataTables.h"
#include "Projectile.h"
#include "Pickup.h"
using std::placeholders::_1;
Direction::Direction(float angle, float distance)
: angle(angle), distance(distance) {}

std::vector<AircraftData> initializeAircraftData()
{
    std::vector<AircraftData> data(Aircraft::Typecount);
    
    data[Aircraft::Player1].hitpoints = 100;
    data[Aircraft::Player1].speed     = 200.f;
    data[Aircraft::Player1].texture   = Textures::Player;
    data[Aircraft::Player1].textRect  = sf::IntRect(394,102,116,92);
    
    data[Aircraft::Enemy1].hitpoints = 40;
    data[Aircraft::Enemy1].speed     = 80.f;
    data[Aircraft::Enemy1].texture   = Textures::Enemy;
    data[Aircraft::Enemy1].textRect  = sf::IntRect(148,551,173,133);
    data[Aircraft::Enemy1].directions.push_back(Direction(45, 80));
    data[Aircraft::Enemy1].directions.push_back(Direction(-45, 160));
    data[Aircraft::Enemy1].directions.push_back(Direction(45, 80));
    
    
    data[Aircraft::Enemy2].hitpoints = 30;
    data[Aircraft::Enemy2].speed     = 50.f;
    data[Aircraft::Enemy2].texture   = Textures::Enemy;
    data[Aircraft::Enemy2].textRect  = sf::IntRect(47,423,96,79);
    data[Aircraft::Enemy2].directions.push_back(Direction(45, 50));
    data[Aircraft::Enemy2].directions.push_back(Direction(0, 50));
    data[Aircraft::Enemy2].directions.push_back(Direction(-45, 100));
    data[Aircraft::Enemy2].directions.push_back(Direction(0, 50));
    data[Aircraft::Enemy2].directions.push_back(Direction(45, 50));
    
    data[Aircraft::Boss1].hitpoints = 800;
    data[Aircraft::Boss1].speed     = 20.f;
    data[Aircraft::Boss1].texture   = Textures::Boss;
    data[Aircraft::Boss1].textRect  = sf::IntRect(0,0,566,370);
    
    // more...
    
    return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
    std::vector<ProjectileData> data(Projectile::Typecount);
    
    data[Projectile::AlliedBullet].damage = 10;
    data[Projectile::AlliedBullet].speed  = 300.f;
    data[Projectile::AlliedBullet].texture = Textures::AlliedBullet;
    
    data[Projectile::EnemyBullet].damage = 10;
    data[Projectile::EnemyBullet].speed  = 200.f;
    data[Projectile::EnemyBullet].texture = Textures::Bullet;
    
    data[Projectile::Missile].damage = 200;
    data[Projectile::Missile].speed = 150.f;
    data[Projectile::Missile].texture = Textures::Missile;
    
    //TODO:
    
    return data;
}

std::vector<PickupData> initializePickupData()
{
    std::vector<PickupData> data(Pickup::TypeCount);
    data[Pickup::HealthRefill].texture = Textures::HealthRefill;
    data[Pickup::HealthRefill].action
    = std::bind(&Aircraft::repair, _1, 20);
    data[Pickup::MissileRefill].texture = Textures::MissileRefill;
    data[Pickup::MissileRefill].action
    = std::bind(&Aircraft::collectMissiles, _1, 3);
    data[Pickup::FireSpread].texture = Textures::FireSpread;
    data[Pickup::FireSpread].action
    = std::bind(&Aircraft::increaseSpread, _1);
    data[Pickup::FireRate].texture = Textures::FireRate;
    data[Pickup::FireRate].action
    = std::bind(&Aircraft::increaseFireRate, _1);
    return data;
}