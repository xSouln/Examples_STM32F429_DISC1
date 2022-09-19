//==============================================================================
#ifndef _BREW_GROUP_MOTOR_BASE_H_
#define _BREW_GROUP_MOTOR_BASE_H_
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
#include "Common/xTypes.h"
//==============================================================================
typedef enum
{
	BrewGroupMotorEventIdle,
	
} BrewGroupMotorEventSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMotorRequestIdle,
	BrewGroupMotorRequestUpdateSensors,
	BrewGroupMotorRequestMoveStart,
	BrewGroupMotorRequestMoveStope,
	BrewGroupMotorRequestSetPower,
	
} BrewGroupMotorRequestSelector;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMotorValueIdle,
	BrewGroupMotorValueMoveDiraction
	
} BrewGroupMotorValueSelector;
//------------------------------------------------------------------------------
typedef void (*BrewGroupMotorHandlerT)(void* device);

typedef void (*BrewGroupMotorEventListenerT)(void* device, BrewGroupMotorEventSelector selector, uint32_t args, uint32_t count);
typedef xResult (*BrewGroupMotorRequestListenerT)(void* device, BrewGroupMotorRequestSelector selector, uint32_t args, uint32_t count);

//typedef uint32_t (*BrewGroupMotorActionGetValueT)(void* device, BrewGroupMotorValueSelector selector);
//typedef xResult (*BrewGroupMotorActionSetValueT)(void* device, BrewGroupMotorValueSelector selector, uint32_t value);
//------------------------------------------------------------------------------
typedef struct
{
	BrewGroupMotorHandlerT Handler;
	
	BrewGroupMotorEventListenerT EventListener;
	BrewGroupMotorRequestListenerT RequestListener;
	
	//BrewGroupMotorActionGetValueT GetValue;
	//BrewGroupMotorActionSetValueT SetValue;
	
} BrewGroupMotorInterfaceT;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMotionNoError,
	BrewGroupMotionTimeout,
	BrewGroupMotionOvercurrent,
	
} BrewGroupMotionResult;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupPositionClose,
	BrewGroupPositionOpen,
	
} BrewGroupPositions;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMotionStateStopped,
	BrewGroupMotionStateOpening,
	BrewGroupMotionStateClosing
	
} BrewGroupMotionStatus;
//------------------------------------------------------------------------------
typedef enum
{
	BrewGroupMoveModeCommon,
	BrewGroupMoveModeMoveOffTheSensor,
	
} BrewGroupMoveModes;
//------------------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Motion : 4;
		uint8_t MotionResult : 4;
	};
	
	uint8_t Value;
	
} BrewGroupMotorStatusT;
//------------------------------------------------------------------------------
typedef struct
{
	uint8_t Open : 1;
	uint8_t Close : 1;
	
} BrewGroupMotorTriggersT;
//------------------------------------------------------------------------------
typedef struct
{
	float Acceleration;
	float StartPower;
	
	float Power;
	
} BrewGroupMotorOptionsT;
//------------------------------------------------------------------------------
typedef struct
{
	float Power;
	uint32_t TimeOut;
	BrewGroupMoveModes Mode;
	BrewGroupPositions Position;
	
} BrewGroupMoveRequestT;
//------------------------------------------------------------------------------
typedef struct
{
	OBJECT_HEADER;
	
	void* Child;
	BrewGroupMotorInterfaceT* Interface;
	
	BrewGroupMotorOptionsT Options;
	BrewGroupMotorStatusT Status;
	BrewGroupMotorTriggersT Triggers;
	BrewGroupMoveModes Mode;
	
	float AccelerationIncrement;
	float TotalPower;
	float RequestPower;
	
	uint32_t MoveTime;
	uint32_t TimeOut;
	
} BrewGroupMotorBaseT;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif