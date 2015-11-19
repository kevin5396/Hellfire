//
//  GameState.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "GameState.h"
#include "Application.h"
GameState::GameState(StateStack& stack, Context context)
:State(stack, context)
,mWorld(*context.window, *context.fonts)
,mPlayer(*context.player)
{}

void GameState::draw()
{
    mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
    if (!mWorld.hasPlayerAlive())
    {
        mPlayer.setMisssionStatus(Player::Failure);
        requestStackPush(States::GameOver);
    }
    else if (mWorld.hasPlayerReachEnd())
    {
        mPlayer.setMisssionStatus(Player::Success);
        requestStackPush(States::GameOver);
    }
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);
    return true;
}

bool GameState::handleEvent(const sf::Event &event)
{
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);
}