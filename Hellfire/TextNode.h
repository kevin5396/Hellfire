//
//  TextNode.h
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__TextNode__
#define __Hellfire__TextNode__

#include "SFML.h"
#include "SceneNode.h"
#include "ResourceIdentifiers.h"

class TextNode: public SceneNode
{
public:
    explicit            TextNode(const FontHolder& fonts,
                                 const std::string& text);
    
    void                setString(const std::string& text);
    void                setSize(int size);
    void                setFont(const FontHolder& fonts,Fonts::ID id);
    void                setColor(sf::Color color);
    
private:
    virtual void        drawCurrent(sf::RenderTarget& target,
                                    sf::RenderStates states) const;
    
private:
    sf::Text            mText;
};

#endif /* defined(__Hellfire__TextNode__) */
