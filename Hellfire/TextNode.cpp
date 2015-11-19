//
//  TextNode.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "TextNode.h"

TextNode::TextNode(const FontHolder& fonts,
                   const std::string& text)
{
    mText.setFont(fonts.get(Fonts::Main));
    mText.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mText, states);
}

void TextNode::setString(const std::string &text)
{
    mText.setString(text);
    centerOrigin(mText);
}

void TextNode::setSize(int size)
{
    mText.setCharacterSize(size);
}

void TextNode::setFont(const FontHolder& fonts,Fonts::ID id)
{
    mText.setFont(fonts.get(id));
}

void TextNode::setColor(sf::Color color)
{
    mText.setColor(color);
}
