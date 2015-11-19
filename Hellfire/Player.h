//
//  Player.h
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__Player__
#define __Hellfire__Player__



///////////////////////////////////////////////////
//
//  handle player input  !!
//
///////////////////////////////////////////////////
#include "CommandQueue.h"
#include "SFML.h"
#include "Aircraft.h"

struct AircraftMover
{
    AircraftMover(float vx, float vy);
    
    void operator() (Aircraft& aircraft, sf::Time) const;
    
    sf::Vector2f velocity;
};


class Player
{
public:
    enum MissionStatus
    {
        Failure,
        Running,
        Success
    };
    Player();
    
    void    handleEvent(const sf::Event& event,
                        CommandQueue& commands);
    void    handleRealtimeInput(CommandQueue& commands);
    
    void    setMisssionStatus(MissionStatus status);
    MissionStatus  getMissionStatus() const;
private:
    MissionStatus   mMissionStatus;
};

#endif /* defined(__Hellfire__Player__) */
