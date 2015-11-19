//
//  ResourceIdentifiers.h
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef Hellfire_ResourceIdentifiers_h
#define Hellfire_ResourceIdentifiers_h
#include "ResourceHolder.h"

namespace Textures
{
    enum ID{ End, Bullet,Missile,AlliedBullet, Background,HealthRefill,
        MissileRefill,
        FireSpread,
        FireRate,
        Enemy,
        Player,
        Boss,
        Map};
}
namespace Fonts
{
    enum ID{ Main, Blade2 };
}
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>       FontHolder;
#endif
