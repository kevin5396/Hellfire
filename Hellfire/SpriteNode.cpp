//
//  SpriteNode.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
:mSprite(texture){}

SpriteNode::SpriteNode(const sf::Texture& texture,
                       const sf::IntRect& rect)
:mSprite(texture, rect){}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}