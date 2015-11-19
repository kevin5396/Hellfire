//
//  SceneNode.cpp
//  Hellfire
//
//  Created by Kevin Ling on 7/19/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#include "SceneNode.h"
#include "Command.h"
#include "Entity.h"
#include <cmath>
//////////////////////////////////
//
//  SceneNode implementation
//
//////////////////////////////////
SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{}
void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
    auto found = find_if(mChildren.begin(), mChildren.end(),
                         [&](const Ptr& p) { return p.get() == &node;});
    assert(found != mChildren.end());
    Ptr res = std::move(*found);
    res->mParent = nullptr;
    mChildren.erase(found);
    return res;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    
    for (const Ptr& child : mChildren)
    {
        child->draw(target, states);
    }
}
void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}
void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // blank. only for derived class
}
void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
    for (const Ptr& child:mChildren)
        child->update(dt, commands);
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform;
    return transform;
}
sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}

void SceneNode::onCommand(const Command &command, sf::Time dt)
{
    if (command.category & getCategory())
    {
        command.action(*this, dt);
        if (command.category == Category::Scene)
            return;
    }
    

    for (auto & child : mChildren)
        child->onCommand(command, dt);
}

bool SceneNode::isDestroyed() const
{
    return false;
}
bool SceneNode::isMarkedForRemoval() const
{
    return isDestroyed();
}
void SceneNode::removeWrecks()
{
    auto wreckBegin = std::remove_if(mChildren.begin(), mChildren.end(),
                                     std::mem_fn(&SceneNode::isMarkedForRemoval));
    mChildren.erase(wreckBegin, mChildren.end());
    std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect();
}
void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair> &collisionPairs)
{
    // valid collision
    if (this != &node && collision(*this, node)&& !isDestroyed() && !node.isDestroyed())
        collisionPairs.insert(std::minmax(this, &node));
    for (auto & child : mChildren)
        child->checkNodeCollision(node, collisionPairs);
}
void SceneNode::checkSceneCollision(SceneNode &sceneGraph, std::set<Pair> &collisionPairs)
{
    checkNodeCollision(sceneGraph, collisionPairs);
    
    for (Ptr & child : sceneGraph.mChildren)
        checkSceneCollision(*child, collisionPairs);
}







void centerOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

void centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
    return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}
float distance(const SceneNode& lhs, const SceneNode& rhs)
{
    sf::Vector2f vec = lhs.getWorldPosition() - rhs.getWorldPosition();
    return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}


