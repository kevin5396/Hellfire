//
//  World.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "World.h"
#include "DataTables.h"
#include "Pickup.h"
#include <random>
#include <cmath>  // for squre root
World::SpawnPoint::SpawnPoint(Aircraft::Type type, float x, float y)
:type(type), x(x), y(y){}

namespace
{
    const std::vector<AircraftData> Table = initializeAircraftData();
}

namespace
{
    std::default_random_engine createRandomEngine_()
    {
        auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }
    
    auto RandomEngine_ = createRandomEngine_();
}
unsigned int ranInt(unsigned int count)
{
    std::uniform_int_distribution<> distr(0, count - 1);
    return distr(RandomEngine_);
}


World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mFonts(fonts)
, mScore(0)
, mLevel(1)
, mWorldBounds (
    0.f,                                //left x position
    0.f,                                // top y position
    mWorldView.getSize().x,             //width
                2500.f)                 //height
, mScrollSpeed(-50.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f,              //X
                 mWorldBounds.height - mWorldView.getSize().y / 2.f)  //Y
, mPlayerAircraft(nullptr)
{
    loadTextures();
    addEnemies();
    buildScene();
    mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
        mLevel = ranInt(5) + 1;
    mTextures.load(Textures::Player, resourcePath() + "player.png");
    mTextures.load(Textures::Enemy, resourcePath() + "enemy.png");
    mTextures.load(Textures::Boss, resourcePath() + "boss.png");
    mTextures.load(Textures::Map, resourcePath() + "level" + std::to_string(mLevel) + ".jpg");
    mTextures.load(Textures::Bullet, resourcePath() + "EnemyBullet.png");
    mTextures.load(Textures::AlliedBullet, resourcePath() + "AlliedBullet.png");
    mTextures.load(Textures::End, resourcePath() + "Endline.png");
    mTextures.load(Textures::Missile, resourcePath() + "Missile.png");
    mTextures.load(Textures::FireRate, resourcePath() + "FireRate.png");
    mTextures.load(Textures::FireSpread, resourcePath() + "FireSpread.png");
    mTextures.load(Textures::HealthRefill, resourcePath() + "HealthRefill.png");
    mTextures.load(Textures::MissileRefill, resourcePath() + "MissileRefill.png");
    // ... more textures
}

void World::buildScene()
{
   
    for (std::size_t i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
    
    // map
    sf::Texture& texture = mTextures.get(Textures::Map);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);
    
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
    
    // end line
    sf::Texture& end = mTextures.get(Textures::End);
    std::unique_ptr<SpriteNode> endSprite(new SpriteNode(end));
    
    endSprite->setPosition(0.f, -76.f);
    
    mSceneLayers[Background]->attachChild(std::move(endSprite));
    
    
    // player aircraft
    std::unique_ptr<Aircraft>   Leader(new Aircraft(Aircraft::Player1, mTextures, mFonts));
    mPlayerAircraft = Leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(0.f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(Leader));
    
    // score display
    std::unique_ptr<TextNode>   score(new TextNode(mFonts, ""));
    mScoreDisplay = score.get();
    score->setSize(40);
    score->setColor(sf::Color::Yellow);
    score->setFont(mFonts, Fonts::Blade2);
    score->setString("Score: " + std::to_string(mScore));
    score->setPosition(mWorldView.getSize().x - 100.f, mWorldBounds.height - 750.f);
    mSceneLayers[Air]->attachChild(std::move(score));

}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, dt.asSeconds() * mScrollSpeed);
    mPlayerAircraft->setVelocity(0.f, 0.f);
    destoryEntitiesOutOfView();
    guideMissiles();
    
    updateScore();
    // onCommand
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    
    // handles the diagonal velocity
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();
    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
    
    mPlayerAircraft->accelerate(0.f, mScrollSpeed);
    
    // handles the cases when aircraft reaches boundaries
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
                             mWorldView.getSize());
    const float borderDistance = 40.f;
    sf::Vector2f position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::min(position.y, viewBounds.top  + viewBounds.height - borderDistance -20.f);
    position.y = std::max(position.y, viewBounds.top +borderDistance);
    mPlayerAircraft->setPosition(position);
    
    ///////////////////
    handleCollision();
    mSceneGraph.removeWrecks();
    spawnEnemies();
    mSceneGraph.update(dt, mCommandQueue);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

sf::FloatRect World::getViewBounds() const
{
    return  sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattleField() const
{
    sf::FloatRect bounds = getViewBounds();
    bounds.top -= 100.f;
    bounds.height += 100.f;
    
    return bounds;
}

void World::spawnEnemies()
{
    while (!mEnemySpawnPoints.empty() &&
           mEnemySpawnPoints.back().y > getBattleField().top)
    {
        SpawnPoint spawn = mEnemySpawnPoints.back();
        std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, mTextures, mFonts));
        
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.f);
        
        mSceneLayers[Air]->attachChild(std::move(enemy));
        mEnemySpawnPoints.pop_back();
    }
}
void World::addEnemy(Aircraft::Type type, float x, float y)
{
    mEnemySpawnPoints.push_back(SpawnPoint(type, mSpawnPosition.x + x,
                                           mSpawnPosition.y - y));
}

void World::addEnemies()
{
    addEnemy(Aircraft::Enemy1,    0.f,  500.f);
    addEnemy(Aircraft::Enemy2, 200.f,  500.f);
    addEnemy(Aircraft::Enemy1, -300.f,  700.f);
    addEnemy(Aircraft::Enemy1,  350.f,  800.f);
    addEnemy(Aircraft::Enemy1,    0.f, 1000.f);
    addEnemy(Aircraft::Enemy1, +100.f, 1100.f);
    addEnemy(Aircraft::Enemy1, -100.f, 1100.f);
    addEnemy(Aircraft::Enemy2, -70.f, 1400.f);
    addEnemy(Aircraft::Enemy2, -70.f, 1600.f);
    addEnemy(Aircraft::Enemy2,  170.f, 1400.f);
    addEnemy(Aircraft::Enemy2,  70.f, 1600.f);
    addEnemy(Aircraft::Boss1, 0.f, 2000.f);
    // TODO...
    
    std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(),
              [](SpawnPoint lhs, SpawnPoint rhs)
              {
                  return lhs.y < rhs.y;
              });
}

void World::destoryEntitiesOutOfView()
{
    Command command;
    command.category = Category::EnemyAircraft | Category::Projectile;
    command.action = derivedAction<Entity>(
            [this](Entity& e, sf::Time dt)
            {
            if (!getBattleField().intersects(e.getBoundingRect()))
                e.destroy();
            });
    
    mCommandQueue.push(command);
}

bool matchCategories(SceneNode::Pair& colliders,
                     Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();
    
    if (category1 & type1 && category2 & type2)
    {
        return true;
    }
    else if (category1 & type2 && category2 & type1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void World::handleCollision()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);
    for (const SceneNode::Pair& cpair : collisionPairs)
    {
        SceneNode::Pair& pair = const_cast<SceneNode::Pair&>(cpair);
        if (matchCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
        {
            auto & player = static_cast<Aircraft&>(*pair.first);
            auto & enemy  = static_cast<Aircraft&>(*pair.second);
            player.damage(enemy.getHitpoints());
            enemy.destroy();
        }
        else if(matchCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
                || matchCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
        {
            auto & aircraft = static_cast<Aircraft&>(*pair.first);
            auto & projectile = static_cast<Projectile&>(*pair.second);
            if (!projectile.isDestroyed())
                aircraft.damage(projectile.getDamage());
            projectile.destroy();
            if (!aircraft.isAllied() && aircraft.isDestroyed())
            {
                mScore += Table[aircraft.getType()].hitpoints;
            }
        }
        else if(matchCategories(pair, Category::PlayerAircraft, Category::Pickup))
        {
            auto & player = static_cast<Aircraft&>(*pair.first);
            auto & pickup = static_cast<Pickup&>(*pair.second);
            pickup.apply(player);
            pickup.destroy();
        }
    }
}


void World::updateScore()
{
    mScoreDisplay->setString("Score: " + std::to_string(mScore));
    mScoreDisplay->setPosition(mWorldView.getCenter().x, mWorldView.getCenter().y - 200.f);
    mScoreDisplay->move(0.f, mScrollSpeed);
}

bool World::hasPlayerAlive() const
{
    return !mPlayerAircraft->isMarkedForRemoval();
}

bool World::hasPlayerReachEnd() const
{
    return !mWorldBounds.contains(mPlayerAircraft->getPosition());
}

void World::guideMissiles()
{
    Command enemyCollector;
    enemyCollector.category = Category::EnemyAircraft;
    enemyCollector.action = derivedAction<Aircraft>(
            [this](Aircraft& enemy, sf::Time)
                {
                    if(!enemy.isDestroyed())
                        mActiveEnemies.push_back(&enemy);
                });
    Command missileGuider;
    missileGuider.category = Category::AlliedProjectile;
    missileGuider.action = derivedAction<Projectile>(
            [this](Projectile& missile, sf::Time)
                 {
                     if(!missile.isGuided())
                         return;
                     float minDistance = std::numeric_limits<float>::max();
                     Aircraft* closestEnemy = nullptr;
                     
                     for(auto* enemy : mActiveEnemies)
                     {
                         float enemyDistance = distance(missile, *enemy);
                         
                         if(enemyDistance < minDistance)
                         {
                             closestEnemy = enemy;
                             minDistance = enemyDistance;
                         }
                     }
                     if (closestEnemy)
                     {
                         missile.guideTowards(closestEnemy->getWorldPosition());
                     }
                 });
    mCommandQueue.push(enemyCollector);
    mCommandQueue.push(missileGuider);
    mActiveEnemies.clear();
}























