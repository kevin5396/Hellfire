//
//  CommandQueue.h
//  Hellfire
//
//  Created by Kevin Ling on 7/21/15.
//  Copyright (c) 2015 Kevin Ling. All rights reserved.
//

#ifndef __Hellfire__CommandQueue__
#define __Hellfire__CommandQueue__

#include "Command.h"
#include <queue>

class CommandQueue
{
public:
    void        push(const Command& command);
    Command     pop();
    bool        isEmpty() const;
    
private:
    std::queue<Command>     mQueue;
};

#endif /* defined(__Hellfire__CommandQueue__) */
