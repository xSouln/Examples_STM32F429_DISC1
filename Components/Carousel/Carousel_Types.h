//==============================================================================
#ifndef _CAROUSEL_TYPES_H
#define _CAROUSEL_TYPES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include "Common/xTypes.h"
#include "Common/xRxTransaction.h"
#include "Carousel_Config.h"
#include "Adapters/Carousel_AdapterBase.h"
//==============================================================================
typedef enum
{
	CarouselEventIdle,
	CarouselEventPositionIsSet,
	CarouselEventZeroMark,
	CarouselEventTimeout,
	CarouselEventOvercurrent
	
} CarouselEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselRequestIdle,
	CarouselRequestDelay
	
} CarouselRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselValueIdle,
	
} CarouselValueSelector;
//------------------------------------------------------------------------------
typedef void (*CarouselEventListenerT)(void* device, CarouselEventSelector event, uint32_t args, uint32_t count);
typedef xResult (*CarouselRequestListenerT)(void* device, CarouselRequestSelector event, uint32_t args, uint32_t count);

//typedef uint32_t (*CarouselActionGetValueT)(void* device, CarouselValueSelector event, uint32_t args, uint32_t count);
//typedef xResult (*CarouselActionSetValueT)(void* device, CarouselValueSelector event, uint32_t args, uint32_t count);
//------------------------------------------------------------------------------
typedef struct
{
	CarouselEventListenerT EventListener;
	CarouselRequestListenerT RequestListener;
	
	//CarouselActionGetValueT GetValue;
	//CarouselActionSetValueT SetValue;
	
} CarouselInterfaceT;
//==============================================================================
typedef struct
{
	float Acceleration;
	float Deceleration;
	
	float StartPower;
	float StopPower;
	
} CarouselOptionsT;
//------------------------------------------------------------------------------
typedef CarouselOptionsT CarouselRequestSetOptionsT;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselSetPositionModeCommomActionIdle,
	CarouselSetPositionModeStopAtZeroMark = 1 << 0
	
} CarouselSetPositionModes;
//------------------------------------------------------------------------------
typedef struct
{
	float Angle;
	float Power;
	
	uint32_t Timeout;
	
	uint32_t Mode;
	
} CarouselRequestSetPositionT;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselMotionNoError,
	CarouselMotionTimeout,
	CarouselMotionOvercurrent,
	
} CarouselMotionErrors;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselMotionStateStopped,
	CarouselMotionStateMovingForward,
	CarouselMotionStateMovingBackward,
	
} CarouselMotionStates;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselSensorZeroMark = 1 << 0,
	CarouselSensorOvercurrent = 1 << 1
	
} CarouselSensors;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t ZeroMark : 1;
		uint8_t Overcurrent : 1;
	};
	
	uint8_t Value;
	
} CarouselSensorsT;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		uint64_t Sensors : 2; //CarouselSensors
		
		uint64_t Motion : 4; //CarouselMotionStates
		uint64_t Errors : 4; //CarouselMotionErrors
		
		uint64_t InitResult : 4; //xResult
		uint64_t DriverInitResult : 4; //xResult
		uint64_t AdapterInitResult : 4; //xResult
	};
	
	uint64_t Value;
	
} CarouselStatusT;
//------------------------------------------------------------------------------
#define CAROUSEL_SPEED_CALIBRATION_POLYNOMIAL_SIZE 4

typedef struct
{
	float Polynomial[CAROUSEL_SPEED_CALIBRATION_POLYNOMIAL_SIZE];
	
} CarouselSpeedCalibrationPolynomialT;
//------------------------------------------------------------------------------
typedef struct
{
	float Position;
	//CarouselSpeedCalibrationPolynomialT Speed;
	
} CarouselCalibrationT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	CarouselAdapterBaseT Adapter;
	CarouselInterfaceT* Interface;
	
	CarouselStatusT Status;
	
	CarouselOptionsT Options;
	CarouselCalibrationT Calibration;
	
	float TotalAngle;
	float RequestAngle;
	
	float TotalPower;
	float RequestPower;
	
	uint32_t Mode;
	
	uint32_t MoveTime;
	uint32_t TimeOut;
	
	xRxRequestT* Requests;
	
} CarouselT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
