//==============================================================================
#ifndef __OV2640_X_VGA_TABLES_H
#define __OV2640_X_VGA_TABLES_H
//==============================================================================
#ifdef __cplusplus
 extern "C" {
#endif 
//==============================================================================
#include <stdint.h>
#include "OV2640_Registers.h"
//==============================================================================
/* Initialization sequence for VGA resolution (640x480)*/
static const uint8_t OV2640_VGA[][2] =
{
  {OV2640_DSP_RA_DLMT, 0x00},  /* Device control register list Table 12 */
  {0x2c, 0xff},  /* Reserved                              */
  {0x2e, 0xdf},  /* Reserved                              */
  {OV2640_DSP_RA_DLMT, 0x01},  /* Device control register list Table 13 */
  {0x3c, 0x32},  /* Reserved                              */
  {OV2640_SENSOR_CLKRC, 0x00},  /* Clock Rate Control                    */
  {OV2640_SENSOR_COM2, 0x02},  /* Common control 2                      */
  {0x04, 0xA8},  /* Mirror                                */
  {OV2640_SENSOR_COM8, 0xe5},  /* Common control 8                      */
  {OV2640_SENSOR_COM9, 0x48},  /* Common control 9                      */
  {0x2c, 0x0c},  /* Reserved                              */
  {0x33, 0x78},  /* Reserved                              */
  {0x3a, 0x33},  /* Reserved                              */
  {0x3b, 0xfB},  /* Reserved                              */
  {0x3e, 0x00},  /* Reserved                              */
  {0x43, 0x11},  /* Reserved                              */
  {0x16, 0x10},  /* Reserved                              */
  {0x4a, 0x81},  /* Reserved                              */
  {0x21, 0x99},  /* Reserved                              */
  {OV2640_SENSOR_AEW, 0x40},  /* Luminance signal High range           */
  {OV2640_SENSOR_AEB, 0x38},  /* Luminance signal low range            */
  {OV2640_SENSOR_W, 0x82},  /*                                       */
  {0x5C, 0x00},  /* Reserved                              */
  {0x63, 0x00},  /* Reserved                              */
  {OV2640_SENSOR_FLL, 0x3f},  /* Frame length adjustment               */
  {OV2640_SENSOR_COM3, 0x3c},  /* Common control 3                      */
  {OV2640_SENSOR_HISTO_LOW, 0x70},  /* Histogram algo low level              */
  {OV2640_SENSOR_HISTO_HIGH, 0x80},  /* Histogram algo high level             */
  {0x7c, 0x05},  /* Reserved                              */
  {0x20, 0x80},  /* Reserved                              */
  {0x28, 0x30},  /* Reserved                              */
  {0x6c, 0x00},  /* Reserved                              */
  {0x6d, 0x80},  /* Reserved                              */
  {0x6e, 0x00},  /* Reserved                              */
  {0x70, 0x02},  /* Reserved                              */
  {0x71, 0x94},  /* Reserved                              */
  {0x73, 0xc1},  /* Reserved                              */
  {0x3d, 0x34},  /* Reserved                              */
  {0x5A, 0x57},  /* Reserved                              */
  {OV2640_SENSOR_COM7, 0x00},  /* Common control 7                      */
  {OV2640_SENSOR_CLKRC, 0x00},  /* Clock Rate Control                   2*/
  {OV2640_SENSOR_HREFST, 0x11},  /* Horiz window start MSB 8bits          */
  {OV2640_SENSOR_HREFEND, 0x75},  /* Horiz window end MSB 8bits            */
  {OV2640_SENSOR_VSTART, 0x01},  /* Vert window line start MSB 8bits      */
  {OV2640_SENSOR_VEND, 0x97},  /* Vert window line end MSB 8bits        */
  {0x32, 0x36},
  {OV2640_SENSOR_COM1, 0x0f},
  {0x37, 0x40},
  {OV2640_SENSOR_BD50, 0xbb},
  {OV2640_DSP_CTRLI, 0x9c},
  {0x5A, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {OV2640_SENSOR_ARCOM2, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {OV2640_SENSOR_COM4, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {OV2640_DSP_RESET, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {OV2640_DSP_R_DVP_SP, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
  {OV2640_DSP_RA_DLMT, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {OV2640_DSP_HSIZE8, 0xc8},
  {OV2640_DSP_VSIZE8, 0x96},
  {0x8c, 0x00},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x92},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {0x5A, 0x50},
  {OV2640_DSP_ZMOH, 0x3c},
  {0x5C, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x04},
  {OV2640_DSP_SS_ID, 0x00},
  {OV2640_DSP_IMAGE_MODE, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {OV2640_DSP_RESET, 0x00},
  {0xdd, 0x7f},
  {OV2640_DSP_R_BYPASS, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {OV2640_DSP_RESET, 0x04},
  {OV2640_DSP_HSIZE8, 0xc8},
  {OV2640_DSP_VSIZE8, 0x96},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x92},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {OV2640_DSP_TEST, 0x00},
  {0x5A, 0x50},
  {OV2640_DSP_ZMOH, 0x3c},
  {0x5C, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x04},
  {OV2640_DSP_RESET, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {OV2640_DSP_R_BYPASS, 0x00},
  {OV2640_DSP_IMAGE_MODE, 0x08},
  {OV2640_DSP_IMAGE_MODE, 0x09},
  {0x98, 0x00},
  {0x99, 0x00},
  {0x00, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {OV2640_DSP_RESET, 0x04},
  {OV2640_DSP_HSIZE8, 0xc8},
  {OV2640_DSP_VSIZE8, 0x96},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x89},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {OV2640_DSP_TEST, 0x00},
  {0x5A, 0xA0},
  {OV2640_DSP_ZMOH, 0x78},
  {0x5C, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x02},
  {OV2640_DSP_RESET, 0x00},
};
//==============================================================================
/* Initialization sequence for QVGA resolution (320x240) */
static const uint8_t OV2640_QVGA[][2] =
{
	{OV2640_DSP_RA_DLMT, 0x00},
  {0x2c, 0xff},
  {0x2e, 0xdf},
	//===========================================
	{OV2640_DSP_RA_DLMT, 0x01},
  {0x3c, 0x32},
  {OV2640_SENSOR_CLKRC, 0x00},
  {OV2640_SENSOR_COM2, 0x02},
  {0x04, 0xA8},
  {OV2640_SENSOR_COM8, 0xe5},
  {OV2640_SENSOR_COM9, 0x48},
  {0x2c, 0x0c},
  {0x33, 0x78},
  {0x3a, 0x33},
  {0x3b, 0xfB},
  {0x3e, 0x00},
  {0x43, 0x11},
  {0x16, 0x10},
  {0x4a, 0x81},
  {0x21, 0x99},
  {OV2640_SENSOR_AEW, 0x40},
  {OV2640_SENSOR_AEB, 0x38},
  {OV2640_SENSOR_W, 0x82},
  {0x5C, 0x00},
  {0x63, 0x00},
  {OV2640_SENSOR_FLL, 0x3f},
  {OV2640_SENSOR_COM3, 0x3c},
  {OV2640_SENSOR_HISTO_LOW, 0x70},
  {OV2640_SENSOR_HISTO_HIGH, 0x80},
  {0x7c, 0x05},
  {0x20, 0x80},
  {0x28, 0x30},
  {0x6c, 0x00},
  {0x6d, 0x80},
  {0x6e, 0x00},
  {0x70, 0x02},
  {0x71, 0x94},
  {0x73, 0xc1},
  {0x3d, 0x34},
  {0x5A, 0x57},
	
	//{0x15, 0x20},
	
  {OV2640_SENSOR_COM7, 0x00},
  {OV2640_SENSOR_CLKRC, 0x00},
  {OV2640_SENSOR_HREFST, 0x11},
  {OV2640_SENSOR_HREFEND, 0x75},
  {OV2640_SENSOR_VSTART, 0x01},
  {OV2640_SENSOR_VEND, 0x97},
  {0x32, 0x36},
  {OV2640_SENSOR_COM1, 0x0f},
  {0x37, 0x40},
  {OV2640_SENSOR_BD50, 0xbb},
  {0x50, 0x9c},
  {0x5A, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {OV2640_SENSOR_ARCOM2, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {OV2640_SENSOR_COM4, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
	//===========================================
		{OV2640_DSP_RA_DLMT, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {OV2640_DSP_RESET, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {OV2640_DSP_R_DVP_SP, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
	//===========================================
		{OV2640_DSP_RA_DLMT, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {OV2640_DSP_HSIZE8, 0xc8},//you can see the camera is already installed
  {OV2640_DSP_VSIZE8, 0x96},
  {0x8c, 0x00},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x92},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {OV2640_DSP_ZMOW, 0x50},
  {OV2640_DSP_ZMOH, 0x3c},
  {OV2640_DSP_ZMHH, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x04},
  {OV2640_DSP_SS_ID, 0x00},
  {OV2640_DSP_IMAGE_MODE, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {OV2640_DSP_RESET, 0x00},
  {0xdd, 0x7f},
  {OV2640_DSP_R_BYPASS, 0x00},
	//===========================================
  {OV2640_DSP_RA_DLMT, 0x00},
  {OV2640_DSP_RESET, 0x04},
  {OV2640_DSP_HSIZE8, 0xc8},
  {OV2640_DSP_VSIZE8, 0x96},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x92},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {OV2640_DSP_TEST, 0x00},
  {OV2640_DSP_ZMOW, 0x50},
  {OV2640_DSP_ZMOH, 0x3C},
  {OV2640_DSP_ZMHH, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x08},
	
  {OV2640_DSP_RESET, 0x00},
	//===========================================
		{OV2640_DSP_RA_DLMT, 0x00},
		
	{0xc3, 0xed},
	{0x7f, 0x00},
		
  {OV2640_DSP_IMAGE_MODE, 0x09}, // image output format select
  //{OV2640_DSP_IMAGE_MODE, 0x09}, // image output format select
  //{0x98, 0x00},
  //{0x99, 0x00},
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{OV2640_DSP_R_BYPASS, 0x00},
  {0x00, 0x00},
};
//==============================================================================
/* Initialization sequence for QQVGA resolution (160x120) */
static const char OV2640_QQVGA[][2] =
{
	//===========================================
	{OV2640_DSP_RA_DLMT, 0x00},
  {0x2c, 0xff},
  {0x2e, 0xdf},
	//===========================================
  {OV2640_DSP_RA_DLMT, 0x01},
  {0x3c, 0x32},
  {OV2640_SENSOR_CLKRC, 0x00},
  {OV2640_SENSOR_COM2, 0x02},
  {0x04, 0xA8},
  {OV2640_SENSOR_COM8, 0xe5},
  {OV2640_SENSOR_COM9, 0x48},
  {0x2c, 0x0c},
  {0x33, 0x78},
  {0x3a, 0x33},
  {0x3b, 0xfB},
  {0x3e, 0x00},
  {0x43, 0x11},
  {0x16, 0x10},
  {0x4a, 0x81},
  {0x21, 0x99},
  {OV2640_SENSOR_AEW, 0x40},
  {OV2640_SENSOR_AEB, 0x38},
  {OV2640_SENSOR_W, 0x82},
  {0x5C, 0x00},
  {0x63, 0x00},
  {OV2640_SENSOR_FLL, 0x3f},
  {OV2640_SENSOR_COM3, 0x3c},
  {OV2640_SENSOR_HISTO_LOW, 0x70},
  {OV2640_SENSOR_HISTO_HIGH, 0x80},
  {0x7c, 0x05},
  {0x20, 0x80},
  {0x28, 0x30},
  {0x6c, 0x00},
  {0x6d, 0x80},
  {0x6e, 0x00},
  {0x70, 0x02},
  {0x71, 0x94},
  {0x73, 0xc1},
  {0x3d, 0x34},
  {0x5A, 0x57},
  {OV2640_SENSOR_COM7, 0x00},
  {OV2640_SENSOR_CLKRC, 0x00},
  {OV2640_SENSOR_HREFST, 0x11},
  {OV2640_SENSOR_HREFEND, 0x75},
  {OV2640_SENSOR_VSTART, 0x01},
  {OV2640_SENSOR_VEND, 0x97},
  {0x32, 0x36},
  {OV2640_SENSOR_COM1, 0x0f},
  {0x37, 0x40},
  {OV2640_SENSOR_BD50, 0xbb},
  {OV2640_DSP_CTRLI, 0x9c},
  {0x5A, 0x57},
  {0x6d, 0x80},
  {0x6d, 0x38},
  {0x39, 0x02},
  {0x35, 0x88},
  {0x22, 0x0a},
  {0x37, 0x40},
  {0x23, 0x00},
  {OV2640_SENSOR_ARCOM2, 0xa0},
  {0x36, 0x1a},
  {0x06, 0x02},
  {0x07, 0xc0},
  {OV2640_SENSOR_COM4, 0xb7},
  {0x0e, 0x01},
  {0x4c, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {0xe5, 0x7f},
  {0xf9, 0xc0},
  {0x41, 0x24},
  {OV2640_DSP_RESET, 0x14},
  {0x76, 0xff},
  {0x33, 0xa0},
  {0x42, 0x20},
  {0x43, 0x18},
  {0x4c, 0x00},
  {0x87, 0xd0},
  {0x88, 0x3f},
  {0xd7, 0x03},
  {0xd9, 0x10},
  {OV2640_DSP_R_DVP_SP, 0x82},
  {0xc8, 0x08},
  {0xc9, 0x80},
  {0x7d, 0x00},
  {0x7c, 0x03},
  {0x7d, 0x48},
  {0x7c, 0x08},
  {0x7d, 0x20},
  {0x7d, 0x10},
  {0x7d, 0x0e},
  {0x90, 0x00},
  {0x91, 0x0e},
  {0x91, 0x1a},
  {0x91, 0x31},
  {0x91, 0x5a},
  {0x91, 0x69},
  {0x91, 0x75},
  {0x91, 0x7e},
  {0x91, 0x88},
  {0x91, 0x8f},
  {0x91, 0x96},
  {0x91, 0xa3},
  {0x91, 0xaf},
  {0x91, 0xc4},
  {0x91, 0xd7},
  {0x91, 0xe8},
  {0x91, 0x20},
  {0x92, 0x00},
  {0x93, 0x06},
  {0x93, 0xe3},
  {0x93, 0x02},
  {0x93, 0x02},
  {0x93, 0x00},
  {0x93, 0x04},
  {0x93, 0x00},
  {0x93, 0x03},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x93, 0x00},
  {0x96, 0x00},
  {0x97, 0x08},
  {0x97, 0x19},
  {0x97, 0x02},
  {0x97, 0x0c},
  {0x97, 0x24},
  {0x97, 0x30},
  {0x97, 0x28},
  {0x97, 0x26},
  {0x97, 0x02},
  {0x97, 0x98},
  {0x97, 0x80},
  {0x97, 0x00},
  {0x97, 0x00},
  {0xc3, 0xef},
  {OV2640_DSP_RA_DLMT, 0x00},
  {0xba, 0xdc},
  {0xbb, 0x08},
  {0xb6, 0x24},
  {0xb8, 0x33},
  {0xb7, 0x20},
  {0xb9, 0x30},
  {0xb3, 0xb4},
  {0xb4, 0xca},
  {0xb5, 0x43},
  {0xb0, 0x5c},
  {0xb1, 0x4f},
  {0xb2, 0x06},
  {0xc7, 0x00},
  {0xc6, 0x51},
  {0xc5, 0x11},
  {0xc4, 0x9c},
  {0xbf, 0x00},
  {0xbc, 0x64},
  {0xa6, 0x00},
  {0xa7, 0x1e},
  {0xa7, 0x6b},
  {0xa7, 0x47},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x2e},
  {0xa7, 0x85},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {0xa7, 0x1b},
  {0xa7, 0x74},
  {0xa7, 0x42},
  {0xa7, 0x33},
  {0xa7, 0x00},
  {0xa7, 0x23},
  {OV2640_DSP_HSIZE8, 0xc8},
  {OV2640_DSP_VSIZE8, 0x96},
  {0x8c, 0x00},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x92},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {0x5A, 0x50},
  {OV2640_DSP_ZMOH, 0x3c},
  {0x5C, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x04},
  {OV2640_DSP_SS_ID, 0x00},
  {OV2640_DSP_IMAGE_MODE, 0x00},
  {0xe5, 0x1f},
  {0xe1, 0x67},
  {OV2640_DSP_RESET, 0x00},
  {0xdd, 0x7f},
  {OV2640_DSP_R_BYPASS, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {OV2640_DSP_RESET, 0x04},
  {OV2640_DSP_HSIZE8, 0xc8},
  {OV2640_DSP_VSIZE8, 0x96},
  {OV2640_DSP_CTRL2, 0x3d},
  {OV2640_DSP_CTRLI, 0x92},
  {OV2640_DSP_HSIZE, 0x90},
  {OV2640_DSP_VSIZE, 0x2c},
  {OV2640_DSP_XOFFL, 0x00},
  {OV2640_DSP_YOFFL, 0x00},
  {OV2640_DSP_VHYX, 0x88},
  {OV2640_DSP_TEST, 0x00},
  {0x5A, 0x28}, 
  {OV2640_DSP_ZMOH, 0x1E}, 
  {0x5C, 0x00},
  {OV2640_DSP_R_DVP_SP, 0x08},
  {OV2640_DSP_RESET, 0x00},
  {OV2640_DSP_RA_DLMT, 0x00},
  {OV2640_DSP_R_BYPASS, 0x00},
  {OV2640_DSP_IMAGE_MODE, 0x08},
  {OV2640_DSP_IMAGE_MODE, 0x09},
  {0x98, 0x00},
  {0x99, 0x00},
  {0x00, 0x00},
};

//==============================================================================
#ifdef __cplusplus
}
#endif
//==============================================================================
#endif /* __OV2640_X_VGA_TABLES_H */
