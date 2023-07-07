// common_def.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#define VERBOSE_

typedef enum
{
  kErrorCode_Ok = 0,
  kErrorCode_NullMemoryNode = -1,
  kErrorCode_NullVectorPointer = -2,
  kErrorCode_NullPointer = -3,
  kErrorCode_InvalidValue = -4,
  kErrorCode_NullMemoryAllocation = -5,
  kErrorCode_InsertionFailed = -6,
  kErrorCode_ExtractionFailed = -7,
  kErrorCode_NullListPointer = -8,
  kErrorCode_NullDoubleLPointer = -9,
  kErrorCode_NullStackPointer = -10,
  kErrorCode_NullQueuePointer = -11,
	 kErrorCode_File = -20
} ErrorCode;

static const char* kErrorCodeText[] = {
  "OK",
  "Memory node pointing to NULL",
  "Vector pointing to NULL",
  "Pointer to NULL",
  "Invalid value",
  "NULL pointer while allocating memory",
  "Insertion failed",
  "Extraction failed",
  "Null list pointer",
  "Null double list pointer",
  "Null stack pointer",
  "Null queue pointer",
  "NULL file"
};

#endif // __COMMON_DEF_H__
