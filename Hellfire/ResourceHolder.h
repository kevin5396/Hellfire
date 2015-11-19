//
//  ResourceHolder.h
//  Hellfire
//
//  Created by Kevin Ling on 7/18/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////
//
// Since this is a template class, it's definition should be put together with declaration.
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __Hellfire__ResourceHolder__
#define __Hellfire__ResourceHolder__

#include "SFML.h"

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    
    void load(Identifier id, const std::string& filename);
    template <typename parameter> //overloaded load
    void load(Identifier id, const std::string& filename, const parameter& secondParam);
    
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
    
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
    
};

// Definition for member function
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - fail to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template<typename Resource, typename Identifier>
template<typename parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename
                                                ,const parameter& secondParam)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - fail to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}


#endif /* defined(__Hellfire__ResourceHolder__) */
