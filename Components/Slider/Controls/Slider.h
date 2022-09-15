//==============================================================================
#ifndef _SLIDER_H
#define _SLIDER_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Slider/Slider_Types.h"
//==============================================================================
xResult SliderInit(SliderT* Slider, void* parent, SliderInterfaceT* interface);

void SliderHandler(SliderT* Slider);

uint32_t SliderGetAdapterValue(SliderT* Slider, SliderAdapterValueSelector selector);
uint32_t SliderSetAdapterValue(SliderT* Slider, SliderAdapterValueSelector selector, uint32_t value);
xResult SliderDeclareAdapterRequest(SliderT* Slider, SliderAdapterRequestSelector selector, uint32_t args, uint32_t count);
void SliderDeclareAdapterEvent(SliderT* Slider, SliderAdapterEventSelector selector, uint32_t args, uint32_t count);

xResult SliderOpen(SliderT* Slider, SliderMoveRequestT* request);
xResult SliderClose(SliderT* Slider, SliderMoveRequestT* request);
xResult SliderStop(SliderT* Slider);
xResult SliderSetOptions(SliderT* Slider, SliderOptionsT* request);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
