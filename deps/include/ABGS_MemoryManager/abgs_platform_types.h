/*!
* \file abgs_platform_types.h
* \brief Header file of basic data types.
* \par Description:
* Redefinition of basic data types to be platform-independent.
* \author Toni Barella
* \date Dec, 2016
* \copyright Artificial Bytes Game Studio (C) 2016-2020
*/
#ifndef __PLATFORM_TYPES_H__
#define __PLATFORM_TYPES_H__

#include <stdint.h>

typedef uint8_t 		  u8;
typedef int_least8_t 	s8;
typedef uint16_t 		  u16;
typedef int_least16_t s16;
typedef uint32_t 		  u32;
typedef int_least32_t s32;
typedef uint64_t 		  u64;
typedef int_least64_t	s64;

typedef uint8_t 		  bool;
#define true 			    1
#define false 			  0

typedef uint32_t		BIT_FIELD;

#endif // __PLATFORM_TYPES_H__
