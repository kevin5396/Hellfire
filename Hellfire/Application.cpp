//
//  Application.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/22/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "Application.h"
const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);
Application::Application()
:mWindow(sf::VideoMode(512, 768),"Hellfire")
,mTextures()
,mFonts()
,mPlayer()
,mStateStack(State::Context(mWindow,mTextures,mFonts,mPlayer))
{
    //TODO
    mTextures.load(Textures::Background, resourcePath() + "menu.jpg");
    mFonts.load(Fonts::Main, resourcePath() + "sansation.ttf");
    mFonts.load(Fonts::Blade2, resourcePath() + "Blade2.ttf");
    registerStates();
    mStateStack.pushState(States::Menu);
}

void Application::registerStates()
{
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<GameOverState>(States::GameOver);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processInput();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            processInput();
            update(timePerFrame);
        }
        render();
    }
}
void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
        
        if (mStateStack.isEmpty())
            mWindow.close();
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    
    mStateStack.draw();
    
    mWindow.setView(mWindow.getDefaultView());
    
    mWindow.display();
}


