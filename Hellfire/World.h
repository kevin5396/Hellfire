//
//  World.h
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__World__
#define __Hellfire__World__
/////////////////////////////////////////////////////////////////////
//
// World is a concrete class that construct the graphic world
//
////////////////////////////////////////////////////////////////////
#include "SFML.h"
#include "SpriteNode.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include "Entity.h"
#include "ResourceHolder.h"
#include "CommandQueue.h"

class World : private sf::NonCopyable
{
public:
    explicit        World(sf::RenderWindow& window, FontHolder& fonts);
    void            update(sf::Time dt);
    void            draw();
    
    CommandQueue&   getCommandQueue();
    bool            hasPlayerAlive() const;
    bool            hasPlayerReachEnd() const;
    
private:
    void            loadTextures();
    void            buildScene();
    void            spawnEnemies();
    void            addEnemy(Aircraft::Type type, float x, float y);
    void            addEnemies();
    void            guideMissiles();
    
    void            handleCollision();
    
    void            destoryEntitiesOutOfView();
    

    
    sf::FloatRect            getViewBounds() const;
    sf::FloatRect            getBattleField()const;
    
    void            updateScore();
    
    
private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };
    struct SpawnPoint
    {
        SpawnPoint(Aircraft::Type, float x, float y);
        
        Aircraft::Type type;
        float          x;
        float          y;
    };
    
private:
    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;              // control the view camera
    TextureHolder                       mTextures;              // texture manager
    FontHolder&                         mFonts;
    
    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayers;
    
    sf::FloatRect                       mWorldBounds;            // full world size
    sf::Vector2f                        mSpawnPosition;          // player spawn position
    float                               mScrollSpeed;            // the background scroll speed
    Aircraft*                           mPlayerAircraft;         // player's aircraft
    TextNode*                           mScoreDisplay;
    int                                 mScore;
    int                                 mLevel;
    CommandQueue                        mCommandQueue;
    
    std::vector<SpawnPoint>             mEnemySpawnPoints;
    std::vector<Aircraft*>              mActiveEnemies;
    
};


#endif /* defined(__Hellfire__World__) */
