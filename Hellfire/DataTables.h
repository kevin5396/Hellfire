//
//  DataTables.h
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__DataTables__
#define __Hellfire__DataTables__

#include "SFML.h"
#include "ResourceIdentifiers.h"
#include "Aircraft.h"
struct Direction
{
            Direction(float angle, float distance);
    float   angle;
    float   distance;
};
struct AircraftData
{
    int                     hitpoints;
    float                   speed;
    Textures::ID            texture;
    sf::IntRect             textRect;
    std::vector<Direction>  directions;
};

struct ProjectileData
{
    int             damage;
    float           speed;
    Textures::ID    texture;
};
struct PickupData
{
    Textures::ID    texture;
    std::function<void(Aircraft&)>	action;
};

std::vector<ProjectileData> initializeProjectileData();
std::vector<AircraftData> initializeAircraftData();
std::vector<PickupData> initializePickupData();

#endif /* defined(__Hellfire__DataTables__) */
