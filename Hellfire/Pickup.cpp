//
//  Pickup.cpp
//  Hellfire
//
//  Created by Kevin Ling on 9/8/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "Pickup.h"
#include "DataTables.h"
namespace
{
    const std::vector<PickupData> data = initializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textures)
: Entity(1)
, mType(type)
, mSprite(textures.get(data[type].texture))
{
    centerOrigin(mSprite);
}

unsigned int   Pickup::getCategory() const
{
    return Category::Pickup;
}
sf::FloatRect  Pickup::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void           Pickup::apply(Aircraft& player) const
{
    data[mType].action(player);
}
void           Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}