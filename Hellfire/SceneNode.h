//
//  SceneNode.h
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__SceneNode__
#define __Hellfire__SceneNode__

#include "SFML.h"
#include "Category.h"
//#include "CommandQueue.h"
class CommandQueue;
class Command;
///////////////////////////////////////////////////////////////////////////
//
// SceneNode is a data structure used to manage hierachies between objects
// use relative coordinates
//
//
///////////////////////////////////////////////////////////////////////////
class SceneNode: public sf::Transformable, public sf::Drawable,
private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;
    
    SceneNode();
    
    void attachChild(Ptr child);
    Ptr  detachChild(const SceneNode& node);
    
    // get the absolute position
    sf::Transform getWorldTransform() const;
    sf::Vector2f  getWorldPosition()  const;
    
    // update
    void         update(sf::Time dt, CommandQueue& commands);
    
    // get Category
    virtual unsigned int getCategory() const;
    
    // handle the dead
    virtual bool        isDestroyed() const;
    virtual bool        isMarkedForRemoval() const;
    void                removeWrecks();
    
    // the nearby space
    virtual sf::FloatRect       getBoundingRect() const;
    
    // non-virtual onCommand method
    void onCommand(const Command& command, sf::Time dt);
    
    // collision handle
    void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
    void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
    
    
private:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    void         updateChildren(sf::Time dt, CommandQueue& commands);
    
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    std::vector<Ptr> mChildren;
    SceneNode*       mParent;
    
};

void centerOrigin(sf::Sprite& sprite);

void centerOrigin(sf::Text& text);

bool collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);


#endif /* defined(__Hellfire__SceneNode__) */
