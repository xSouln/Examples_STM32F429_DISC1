//------------------------------------------------------------------------------
#ifndef __OV2640_SATURATION_TABLES_H
#define __OV2640_SATURATION_TABLES_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//------------------------------------------------------------------------------
#include <stdint.h>
//==============================================================================
static const uint8_t OV2640_SATURATION_P2[][2] =
{
	{ 0xff, 0x00 },
	{ 0x7c, 0x00 },
	{ 0x7d, 0x02 },
	{ 0x7c, 0x03 },
	{ 0x7d, 0x68 },
	{ 0x7d, 0x68 },
};
//------------------------------------------------------------------------------
static const uint8_t OV2640_SATURATION_P1[][2] =
{
	{ 0xff, 0x00 },
	{ 0x7c, 0x00 },
	{ 0x7d, 0x02 },
	{ 0x7c, 0x03 },
	{ 0x7d, 0x58 },
	{ 0x7d, 0x58 },
};
//------------------------------------------------------------------------------
static const uint8_t OV2640_SATURATION_0[][2] =
{
	{ 0xff, 0x00 },
	{ 0x7c, 0x00 },
	{ 0x7d, 0x02 },
	{ 0x7c, 0x03 },
	{ 0x7d, 0x48 },
	{ 0x7d, 0x48 }
};
//------------------------------------------------------------------------------
static const uint8_t OV2640_SATURATION_M1[][2] =
{
	{ 0xff, 0x00 },
	{ 0x7c, 0x00 },
	{ 0x7d, 0x02 },
	{ 0x7c, 0x03 },
	{ 0x7d, 0x38 },
	{ 0x7d, 0x38 },
};
//------------------------------------------------------------------------------
static const uint8_t OV2640_SATURATION_M2[][2] =
{
	{ 0xff, 0x00 },
	{ 0x7c, 0x00 },
	{ 0x7d, 0x02 },
	{ 0x7c, 0x03 },
	{ 0x7d, 0x28 },
	{ 0x7d, 0x28 },
};
//==============================================================================
#ifdef __cplusplus
}
#endif
//==============================================================================
#endif /* __OV2640_SATURATION_TABLES_H */
