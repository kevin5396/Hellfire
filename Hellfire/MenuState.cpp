//
//  MenuState.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "MenuState.h"
MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mOptionIndex(0)
, mOptions()
{
    //TODO:
    mBackground.setTexture(context.textures->get(Textures::Background));
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Text play, level, quit;
    play.setFont(font);
    play.setString("Play");
    centerOrigin(play);
    play.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(play);
 /*   centerOrigin(level);
    level.setFont(font);
    level.setString("Level");
    level.setPosition(play.getPosition() + sf::Vector2f(-30.f, 30.f));
    mOptions.push_back(level); */
    centerOrigin(quit);
    quit.setFont(font);
    quit.setString("Quit");
    quit.setPosition(play.getPosition() + sf::Vector2f(-30.f, 50.f));
    mOptions.push_back(quit);
    
    updateOption();
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    
    window.draw(mBackground);
    for (const auto & text : mOptions)
    {
        window.draw(text);
    }
}

bool MenuState::update(sf::Time dt)
{
    return true;
}

void MenuState::updateOption()
{
    if (mOptions.empty())
        return;
    
    for (auto & option : mOptions)
        option.setColor(sf::Color::White);
    
    mOptions[mOptionIndex].setColor(sf::Color::Red);
}

bool MenuState::handleEvent(const sf::Event &event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;
    }
    updateOption();
    
    if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() -1)
            mOptionIndex++;
        else
            mOptionIndex = 0;
    }
    updateOption();
    
    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
        if (mOptionIndex == Quit)
        {
            requestStackPop();
        }
        
    }
    
    return true;
}



























