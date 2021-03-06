//
//  SequentialCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "SequentialCommand.h"
#include "LemonScriptTokenizer.h"

#include "CppCommand.h"
#include "WhileAlsoCommand.h"
#include "CompleteAnyCommand.h"
#include "CompleteCommand.h"
#include "SetCommand.h"
#include "DefCommand.h"
#include "ImportCommand.h"
#include "RunCommand.h"

#include <stdio.h>

void printTok(const std::string &tok, TokenType tk, int lineNum) {
    printf("===== TOKEN =====\nToken type = %d, lineNum = %d, tok = \n%s\n\n", tk, lineNum, tok.c_str());
}

lemonscript::SequentialCommand::SequentialCommand(int l, LemonScriptState *state, const std::string &sequenceString) : Command(l, state) {
    LemonScriptTokenizer tokenizer(sequenceString);
    
    
    std::string token;
    TokenType type;
    int lineNum;
    
    while(true) {
        std::tie(token, type, lineNum) = tokenizer.nextToken();
        if(type == NOT_A_TOKEN) {
            break;
        }
        
//        printTok(token, type, lineNum);
        
        Command *command;
        if(type == CppToken) {
            command = new CppCommand(lineNum, state, token);
        } else if(type == WhileAlsoToken) {
            command = new WhileAlsoCommand(lineNum, state, token);
        } else if(type == CompleteAnyToken) {
            command = new CompleteAnyCommand(lineNum, state, token);
        } else if(type == CompleteToken) {
            command = new CompleteCommand(lineNum, state, token);
        } else if(type == SetToken) {
            command = new SetCommand(lineNum, state, token);
        } else if(type == DefToken) {
            command = new DefCommand(lineNum, state, token);
        } else if(type == ImportToken) {
            command = new ImportCommand(lineNum, state, token);
        } else if(type == RunToken) {
            command = new RunCommand(lineNum, state, token);
        }
        
        sequence.push_back(command);
    }
}

lemonscript::SequentialCommand::~SequentialCommand() {
    for (auto it = sequence.begin(); it != sequence.end(); ++it) {
        delete *it;
    }
}

bool lemonscript::SequentialCommand::Update() {
    if(sequence.size() == 0) {
        return true;
    }
    
    Command *currentCommand = sequence[currentIndex];
    bool isDone = currentCommand->Update();
    
    // If the last command just finished, then we are done
    if(isDone && static_cast<size_t>(currentIndex) == sequence.size() - 1) {
        return true;
    } else if(isDone) {
        // If a command other than the last finished, go to next command
        currentIndex++;
    }
    
    return false;
}
