//==============================================================================
#ifndef _CAROUSEL_H
#define _CAROUSEL_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Carousel/Carousel_Types.h"
//==============================================================================
xResult CarouselInit(CarouselT* carousel, void* parent, CarouselInterfaceT* interface);

void CarouselHandler(CarouselT* carousel);

uint32_t CarouselGetAdapterValue(CarouselT* carousel, CarouselMotorValueSelector selector);
uint32_t CarouselSetAdapterValue(CarouselT* carousel, CarouselMotorValueSelector selector, uint32_t value);
xResult CarouselDeclareAdapterRequest(CarouselT* carousel, CarouselMotorRequestSelector selector, uint32_t args, uint32_t count);
void CarouselDeclareAdapterEvent(CarouselT* carousel, CarouselMotorEventSelector selector, uint32_t args, uint32_t count);

xResult CarouselSetPosition(CarouselT* carousel, CarouselRequestSetPositionT* request);
xResult CarouselResetPosition(CarouselT* carousel);
xResult CarouselStop(CarouselT* carousel);
xResult CarouselSetOptions(CarouselT* carousel, CarouselOptionsT* request);
xResult CarouselSetColibration(CarouselT* carousel, CarouselCalibrationT* request);
xResult CarouselCalibrateAsync(CarouselT* carousel);
xResult CarouselSetPod(CarouselT* carousel, uint8_t number);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
