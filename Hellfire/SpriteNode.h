//
//  SpriteNode.h
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__SpriteNode__
#define __Hellfire__SpriteNode__

#include "SFML.h"
#include "SceneNode.h"
/////////////////////////////////////////////////
//
// This class is  used to manage the background layer
//
////////////////////////////////////////////////

class SpriteNode : public SceneNode
{
public:
    explicit    SpriteNode(const sf::Texture& texture);
                SpriteNode(const sf::Texture& texture,
                           const sf::IntRect& rect);
    
private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;
    
private:
    sf::Sprite mSprite;
};

#endif /* defined(__Hellfire__SpriteNode__) */
