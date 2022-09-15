//==============================================================================
#ifndef SERIAL_PORT_USB_TX_ADAPTER_H
#define SERIAL_PORT_USB_TX_ADAPTER_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include "SerialPort_USB_AdapterTypes.h"
#include "SerialPort/SerialPort_Types.h"
//==============================================================================
xResult SerialPortUSB_TxAdapterInit(SerialPortT* serial_port, SerialPortUSB_AdapterT* adapter);
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif /* SERIAL_PORT_USB_TX_ADAPTER_H */

