//
//  Category.h
//  Hellfire
//
//  Created by Kevin Ling on 7/20/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef Hellfire_Category_h
#define Hellfire_Category_h

namespace Category
{
    enum Type
    {
        None            = 0,
        Scene           = 1 << 0,
        PlayerAircraft  = 1 << 1,
        EnemyAircraft   = 1 << 2,
        AlliedProjectile= 1 << 3,
        EnemyProjectile = 1 << 4,
        Pickup          = 1 << 5,
        Aircraft = PlayerAircraft | EnemyAircraft,
        Projectile = AlliedProjectile | EnemyProjectile
    };
}

#endif
