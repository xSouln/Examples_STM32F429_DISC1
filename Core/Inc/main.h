/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CAMERA_D4_Pin GPIO_PIN_4
#define CAMERA_D4_GPIO_Port GPIOE
#define BREW_MOTOR_PWM1_Pin GPIO_PIN_5
#define BREW_MOTOR_PWM1_GPIO_Port GPIOE
#define BREW_MOTOR_PWM2_Pin GPIO_PIN_6
#define BREW_MOTOR_PWM2_GPIO_Port GPIOE
#define HEATER_CUP_1_Pin GPIO_PIN_0
#define HEATER_CUP_1_GPIO_Port GPIOF
#define HEATER_CUP_2_Pin GPIO_PIN_1
#define HEATER_CUP_2_GPIO_Port GPIOF
#define HEATER_CUP_3_Pin GPIO_PIN_2
#define HEATER_CUP_3_GPIO_Port GPIOF
#define HEATER_CUP_4_Pin GPIO_PIN_3
#define HEATER_CUP_4_GPIO_Port GPIOF
#define WATER_PUMP_Pin GPIO_PIN_4
#define WATER_PUMP_GPIO_Port GPIOF
#define WATER_HEATER_Pin GPIO_PIN_5
#define WATER_HEATER_GPIO_Port GPIOF
#define OUT7_Pin GPIO_PIN_6
#define OUT7_GPIO_Port GPIOF
#define OUT8_Pin GPIO_PIN_7
#define OUT8_GPIO_Port GPIOF
#define OUT9_Pin GPIO_PIN_8
#define OUT9_GPIO_Port GPIOF
#define OUT10_Pin GPIO_PIN_9
#define OUT10_GPIO_Port GPIOF
#define OUT11_Pin GPIO_PIN_10
#define OUT11_GPIO_Port GPIOF
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define CAROUSEL_SENSOR_OVERCURRENT_Pin GPIO_PIN_0
#define CAROUSEL_SENSOR_OVERCURRENT_GPIO_Port GPIOC
#define SLIDER_SENSOR_OVERCURRENT_Pin GPIO_PIN_1
#define SLIDER_SENSOR_OVERCURRENT_GPIO_Port GPIOC
#define BREW_SENSOR_OVERCURRENT_Pin GPIO_PIN_2
#define BREW_SENSOR_OVERCURRENT_GPIO_Port GPIOC
#define FLOW_SENSOR_OVERCURRENT_Pin GPIO_PIN_3
#define FLOW_SENSOR_OVERCURRENT_GPIO_Port GPIOC
#define FLOW_METER_Pin GPIO_PIN_0
#define FLOW_METER_GPIO_Port GPIOA
#define FLOW_THERMOCOUPLE_Pin GPIO_PIN_1
#define FLOW_THERMOCOUPLE_GPIO_Port GPIOA
#define FLOW_DIR_MOTOR_PWM1_Pin GPIO_PIN_2
#define FLOW_DIR_MOTOR_PWM1_GPIO_Port GPIOA
#define FLOW_DIR_MOTOR_PWM2_Pin GPIO_PIN_3
#define FLOW_DIR_MOTOR_PWM2_GPIO_Port GPIOA
#define CAMERA_HSYNC_Pin GPIO_PIN_4
#define CAMERA_HSYNC_GPIO_Port GPIOA
#define CAMERA_PIXCLK_Pin GPIO_PIN_6
#define CAMERA_PIXCLK_GPIO_Port GPIOA
#define ACP_RST_Pin GPIO_PIN_7
#define ACP_RST_GPIO_Port GPIOA
#define USB_OTG_FS_POWER_ENABLE_Pin GPIO_PIN_4
#define USB_OTG_FS_POWER_ENABLE_GPIO_Port GPIOC
#define USB_OTG_FS_OVERCURRENT_Pin GPIO_PIN_5
#define USB_OTG_FS_OVERCURRENT_GPIO_Port GPIOC
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define WIZ_RESET_Pin GPIO_PIN_10
#define WIZ_RESET_GPIO_Port GPIOE
#define WIZ_CS_Pin GPIO_PIN_11
#define WIZ_CS_GPIO_Port GPIOE
#define WIZ_SCK_Pin GPIO_PIN_12
#define WIZ_SCK_GPIO_Port GPIOE
#define WIZ_MISO_Pin GPIO_PIN_13
#define WIZ_MISO_GPIO_Port GPIOE
#define WIZ_MOSI_Pin GPIO_PIN_14
#define WIZ_MOSI_GPIO_Port GPIOE
#define WIZ_INT_Pin GPIO_PIN_15
#define WIZ_INT_GPIO_Port GPIOE
#define OTG_HS_ID_Pin GPIO_PIN_12
#define OTG_HS_ID_GPIO_Port GPIOB
#define VBUS_HS_Pin GPIO_PIN_13
#define VBUS_HS_GPIO_Port GPIOB
#define OTG_HS_DM_Pin GPIO_PIN_14
#define OTG_HS_DM_GPIO_Port GPIOB
#define OTG_HS_DP_Pin GPIO_PIN_15
#define OTG_HS_DP_GPIO_Port GPIOB
#define CAROUSEL_MOTOR_PWM1_Pin GPIO_PIN_12
#define CAROUSEL_MOTOR_PWM1_GPIO_Port GPIOD
#define CAROUSEL_MOTOR_PWM2_Pin GPIO_PIN_13
#define CAROUSEL_MOTOR_PWM2_GPIO_Port GPIOD
#define SLIDER_MOTOR_PWM1_Pin GPIO_PIN_14
#define SLIDER_MOTOR_PWM1_GPIO_Port GPIOD
#define SLIDER_MOTOR_PWM2_Pin GPIO_PIN_15
#define SLIDER_MOTOR_PWM2_GPIO_Port GPIOD
#define SLIDER_SENSOR_CLOSE_Pin GPIO_PIN_2
#define SLIDER_SENSOR_CLOSE_GPIO_Port GPIOG
#define SLIDER_SENSOR_OPEN_Pin GPIO_PIN_3
#define SLIDER_SENSOR_OPEN_GPIO_Port GPIOG
#define CAROUSEL_SENSOR_ZERO_MARK_Pin GPIO_PIN_4
#define CAROUSEL_SENSOR_ZERO_MARK_GPIO_Port GPIOG
#define IN4_Pin GPIO_PIN_5
#define IN4_GPIO_Port GPIOG
#define IN5_Pin GPIO_PIN_6
#define IN5_GPIO_Port GPIOG
#define IN6_Pin GPIO_PIN_7
#define IN6_GPIO_Port GPIOG
#define IN7_Pin GPIO_PIN_8
#define IN7_GPIO_Port GPIOG
#define CAMERA_D0_Pin GPIO_PIN_6
#define CAMERA_D0_GPIO_Port GPIOC
#define CAMERA_D1_Pin GPIO_PIN_7
#define CAMERA_D1_GPIO_Port GPIOC
#define WS2812_CUPS_12_Pin GPIO_PIN_9
#define WS2812_CUPS_12_GPIO_Port GPIOA
#define WS2812_CUPS_24_Pin GPIO_PIN_10
#define WS2812_CUPS_24_GPIO_Port GPIOA
#define WS2812_LED_PANEL_Pin GPIO_PIN_11
#define WS2812_LED_PANEL_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define CAROUSEL_MOTOR_ENCODER_A_Pin GPIO_PIN_15
#define CAROUSEL_MOTOR_ENCODER_A_GPIO_Port GPIOA
#define ESP32_UART2_RX_Pin GPIO_PIN_10
#define ESP32_UART2_RX_GPIO_Port GPIOC
#define ESP32_UART2_RXC11_Pin GPIO_PIN_11
#define ESP32_UART2_RXC11_GPIO_Port GPIOC
#define CAMERA_D5_Pin GPIO_PIN_3
#define CAMERA_D5_GPIO_Port GPIOD
#define CAMERA_RESET_Pin GPIO_PIN_4
#define CAMERA_RESET_GPIO_Port GPIOD
#define CAMERA_PWDN_Pin GPIO_PIN_5
#define CAMERA_PWDN_GPIO_Port GPIOD
#define CAMERA_VSYNC_Pin GPIO_PIN_9
#define CAMERA_VSYNC_GPIO_Port GPIOG
#define CAMERA_D2_Pin GPIO_PIN_10
#define CAMERA_D2_GPIO_Port GPIOG
#define CAMERA_D3_Pin GPIO_PIN_11
#define CAMERA_D3_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_13
#define LED3_GPIO_Port GPIOG
#define LED4_Pin GPIO_PIN_14
#define LED4_GPIO_Port GPIOG
#define CAROUSEL_MOTOR_ENCODER_B_Pin GPIO_PIN_3
#define CAROUSEL_MOTOR_ENCODER_B_GPIO_Port GPIOB
#define CONTROL_PANEL_ENCODER_A_Pin GPIO_PIN_4
#define CONTROL_PANEL_ENCODER_A_GPIO_Port GPIOB
#define CONTROL_PANEL_ENCODER_B_Pin GPIO_PIN_5
#define CONTROL_PANEL_ENCODER_B_GPIO_Port GPIOB
#define CAMERA_SCL_Pin GPIO_PIN_6
#define CAMERA_SCL_GPIO_Port GPIOB
#define CAMERA_SDA_Pin GPIO_PIN_7
#define CAMERA_SDA_GPIO_Port GPIOB
#define CAMERA_D6_Pin GPIO_PIN_8
#define CAMERA_D6_GPIO_Port GPIOB
#define CAMERA_D7_Pin GPIO_PIN_9
#define CAMERA_D7_GPIO_Port GPIOB
#define ESP32_UART1_RX_Pin GPIO_PIN_0
#define ESP32_UART1_RX_GPIO_Port GPIOE
#define ESP32_UART1_TX_Pin GPIO_PIN_1
#define ESP32_UART1_TX_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
