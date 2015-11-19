//
//  Player.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "Player.h"

AircraftMover::AircraftMover(float vx, float vy) : velocity(vx, vy) {}
void AircraftMover::operator()(Aircraft& aircraft, sf::Time) const
{
    aircraft.accelerate(velocity);
}

Player::Player()
: mMissionStatus(Running)
{}
void Player::handleEvent(const sf::Event &event, CommandQueue &commands)
{
    if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Space)
    {
        Command launchMissile;
        launchMissile.category = Category::PlayerAircraft;
        launchMissile.action = derivedAction<Aircraft>(
                                    [](Aircraft& a, sf::Time){ a.launchMissile();});
        commands.push(launchMissile);
    }
}

void Player::handleRealtimeInput(CommandQueue &commands)
{
    const float playerSpeed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        Command moveUp;
        moveUp.category = Category::PlayerAircraft;
        moveUp.action   = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
        
        commands.push(moveUp);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        Command moveDown;
        moveDown.category = Category::PlayerAircraft;
        moveDown.action   = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
        
        commands.push(moveDown);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        Command moveLeft;
        moveLeft.category = Category::PlayerAircraft;
        moveLeft.action   = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
        
        commands.push(moveLeft);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        Command moveRight;
        moveRight.category = Category::PlayerAircraft;
        moveRight.action   = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0));
        
        commands.push(moveRight);
    }
}

void Player::setMisssionStatus(Player::MissionStatus status)
{
    mMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
    return mMissionStatus;
}