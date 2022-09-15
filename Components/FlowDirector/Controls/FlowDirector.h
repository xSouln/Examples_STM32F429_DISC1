//==============================================================================
#ifndef _FLOW_DIRECTOR_H
#define _FLOW_DIRECTOR_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "FlowDirector/FlowDirector_Types.h"
//==============================================================================
xResult FlowDirectorInit(FlowDirectorT* FlowDirector, void* parent, FlowDirectorInterfaceT* interface);

void FlowDirectorHandler(FlowDirectorT* FlowDirector);

xResult FlowDirectorStop(FlowDirectorT* FlowDirector);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
