//
//  GameOverState.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/28/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "GameOverState.h"

GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mText()
, mTimeElapsed(sf::Time::Zero)
{
    sf::Font& font = context.fonts->get(Fonts::Blade2);
    mText.setFont(font);
    sf::Vector2f windowSize(context.window->getSize());
    
    if (context.player->getMissionStatus() == Player::Failure)
        mText.setString("Mission Failed");
    else if (context.player->getMissionStatus() == Player::Success)
        mText.setString("Mission Success");
    mText.setColor(sf::Color::Red);
    mText.setCharacterSize(70);
    centerOrigin(mText);
    mText.setPosition(windowSize / 2.f);
    
}

void GameOverState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    
    window.draw(mText);
    
}
bool GameOverState::update(sf::Time dt)
{
    mTimeElapsed += dt;
    if (mTimeElapsed >= sf::seconds(3))   // back to menu after 3 seconds
    {
        requestStackClear();
        requestStackPush(States::Menu);
    }
    return false;
}

bool GameOverState::handleEvent(const sf::Event &event)
{
    return false;
}