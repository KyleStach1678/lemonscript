//
//  LemonScriptSymbolTable.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "LemonScriptSymbolTable.h"

#include <stdlib.h>

void LemonScriptSymbolTable::declareVariable(int line, const std::string &name, DataType type, void *pointerToValue) {
    if(variableAddresses.find(name) != variableAddresses.end()) {
        throw "Line " + std::to_string(line) + ":\nDuplicate variable definition: " + name;
    }
    
    void *address;
    switch (type) {
        case INT:
            address = malloc(sizeof(int));
            memcpy(address, pointerToValue, sizeof(int));
            break;
            
        case FLOAT:
            address = malloc(sizeof(float));
            memcpy(address, pointerToValue, sizeof(float));
            break;
            
        case BOOLEAN:
            address = malloc(sizeof(bool));
            memcpy(address, pointerToValue, sizeof(bool));
            break;
            
        default:
            break;
    }
    
    variableAddresses[name] = address;
    variableTypes[name] = type;
}


void * LemonScriptSymbolTable::addressOfVariable(const std::string &variableName) const {
    auto it = variableAddresses.find(variableName);
    if(it != variableAddresses.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

DataType LemonScriptSymbolTable::typeOfVariable(const std::string &variableName) const {
    auto it = variableTypes.find(variableName);

    if(it != variableTypes.end()) {
        return it->second;
    } else {
        return INT;
    }

}