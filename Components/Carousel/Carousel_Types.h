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
#include "Components_Config.h"
#include "Carousel/Controls/Carousel_MotorBase.h"
//==============================================================================
typedef enum
{
	CarouselEventIdle,
	CarouselEventPositionIsSet,
	CarouselEventZeroMark,
	CarouselEventCalibrationComplete,
	CarouselEventCalibrationError,
	CarouselEventTimeout,
	CarouselEventOvercurrent,
	
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
	
	float Power;
	
} CarouselOptionsT;
//------------------------------------------------------------------------------
typedef CarouselOptionsT CarouselRequestSetOptionsT;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselSetPositionModeCommomActionIdle,
	CarouselSetPositionModeStopAtZeroMark,
	CarouselSetPositionModeMoveOutAtZeroMark,
	CarouselSetPositionModeFindZeroMark,
	
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
	
} CarouselMotionResult;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselMotionStateStopped,
	CarouselMotionStateMovingForward,
	CarouselMotionStateMovingBackward,
	
} CarouselMotionStatus;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselSensorZeroMark = 1 << 0,
	CarouselSensorOvercurrent = 1 << 1
	
} CarouselSensors;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselCalibratinStatusNotColibated,
	CarouselCalibratinStatusCalibrating,
	CarouselCalibratinStatusColibated,
	CarouselCalibratinStatusError
	
} CarouselCalibratinStatus;
//------------------------------------------------------------------------------
typedef enum
{
	CarouselCalibratinStateIdle,
	CarouselCalibratinStateFindZeroMark,
	CarouselCalibratinStateMoveOutAtZeroMarkAndResetSteps,
	CarouselCalibratinStateFindZeroMarkBackSide,
	CarouselCalibratinStateMoveOutAtZeroMarkAndCalibrate
	
} CarouselCalibratinStates;
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
		uint64_t MotionResult : 4; //CarouselMotionErrors
		
		uint64_t Calibration : 2; //CarouselCalibratinStatus
		uint64_t CalibrationState : 4;
		
		uint64_t LastSensorsState : 2;
		
		uint64_t InitResult : 4; //xResult
	};
	
	uint64_t Value;
	
} CarouselStatusT;
//------------------------------------------------------------------------------
typedef struct
{
	float Position;
	float Offset;
	
} CarouselCalibrationT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	CarouselInterfaceT* Interface;
	CarouselMotorBaseT Motor;
	
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
