//
//  CompleteAnyToken.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef CompleteAnyToken_hpp
#define CompleteAnyToken_hpp

#include <stdio.h>

#include "SimultaneousCommand.h"

#include "lemonscript.h"

class lemonscript::CompleteAnyCommand : public Command {
    
    
    SimultaneousCommand *anyCommands = NULL;
    
    
public:
    CompleteAnyCommand(int l, LemonScriptState &s, const std::string &commandString);
    
    bool Update();
    
};


#endif /* CompleteAnyToken_hpp */
