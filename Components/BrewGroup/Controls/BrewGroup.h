//==============================================================================
#ifndef _BREW_GROUP_H
#define _BREW_GROUP_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "BrewGroup/BrewGroup_Types.h"
//==============================================================================
xResult BrewGroupInit(BrewGroupT* BrewGroup, void* parent, BrewGroupInterfaceT* interface);
void BrewGroupHandler(BrewGroupT* BrewGroup);

xResult BrewGroupSetMotorOptions(BrewGroupT* device, BrewGroupMotorOptionsT* request);

void BrewGroupStop(BrewGroupT* device);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
