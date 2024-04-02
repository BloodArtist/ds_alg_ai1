/**********************************************************************************
* Copyright ***. All rights reserved.
*
* Contains all essential declaration functions required for the "Stack" data type
*
*
*
*
* Code by Yossef Rubalcava & Davide Pietro
* Code Maintained by Yossef R.
**********************************************************************************/

#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__ 1

#include "adt_vector.h"
/**
* @brief Structure representing a Stack with variables and callbacks.
*/
typedef struct adt_stack_s {
  // @brief Pointer that will contain all the information
	Vector *storage_;
 // @brief Pointer to callbacks functions
	struct stack_ops_s *ops_;
} Stack;

/**
* @brief Struct that contains all functions attached to the Stack
*/
struct stack_ops_s {
/**
* @brief Destroys the storage vector pointer and all its data
* @param *Stack stack Pointer to the stack
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullStackPointer When the stack pointer is NULL
* @return s16 kErrorCode_NullVectorPointer When the stack큦 storage pointer is NULL
*/
	s16 (*destroy)(Stack *stack);	// Destroys the stack and its data
	
/**
* @brief Soft resets the storage's data from the stack
* @param *Stack stack Pointer to the stack
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullStackPointer When the Stack pointer is NULL
* @return s16 kErrorCode_NullVectorPointer When the vector pointer(storage) is NULL
*/
 s16 (*softReset)(Stack *stack);		// Soft resets stack's data
	
 /**
* @brief Resets vector's data
* @param *Stack stack Pointer to the stack
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullStackPointer When the Stack pointer is NULL
* @return s16 kErrorCode_NullVectorPointer When the vector pointer(storage) is NULL
* @return s16 kErrorCode_NullMemoryNode When the vector's storage pointer is NULL
*/
 s16 (*reset)(Stack *stack);		// Resets stack's data
	
 /**
 * @brief Resizes the capacity of the stack's storage. Some elements can be lost
 * @param *Stack stack Pointer to the stack
 * @param u16 new_size New capacity size
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullStackPointer When the stack pointer is NULL
 * @return s16 kErrorCode_NullVectorPointer When the vector pointer(storage) is NULL
 * @return s16 kErrorCode_InvalidValue When the new_size value is 0
 * @return s16 kErrorCode_NullMemoryAllocation When there is no memory to allocate
 */
 s16 (*resize)(Stack *stack, u16 new_size); // Resizes the capacity of the stack. Some elements can be lost

	// State queries
 /**
* @brief Returns the maximum number of elements that can be store
* @param *Stack stack Pointer to the stack
* @return u16 Vector큦 capacity from the stack
* @return u16 0 If Stack pointer is NULL
*/
	u16 (*capacity)(Stack *stack);		// returns the maximum number of elemets to store
	
 /**
* @brief Current number of elements (<= capacity)
* @param *Stack stack Pointer to the stack
* @return u16 Vector큦 length from the stack
* @return u16 0 If Stack pointer is NULL
*/
 u16 (*length)(Stack *stack);			// current number of elements (<= capacity)
	
/**
* @brief Verifies is the Stack is empty
* @param *Stack stack Pointer to the stack
* @return bool false If Stack pointer is NULL
* @return bool Checks and returns comprobation with storage's tail and 0
*/
 bool (*isEmpty)(Stack *stack);
	
 /**
* @brief Verifies is the Stack is full
* @param *Stack stack Pointer to the stack
* @return bool Returns false if Stack pointer is NULL
* @return bool Checks and returns comprobation with storage's capacity and length
*/
 bool (*isFull)(Stack *stack);

	// Data queries
/**
* @brief Returns a reference to the last element of the stack
* @param *Stack stack Pointer to the stack
* @return void* Returns storage nodes큦 data pointer
* @return NULL If Stack pointer is NULL
* @return NULL If storage pointer is NULL
*/
	void* (*top)(Stack *stack);
	// Insertion

/**
* @brief Inserts an element in the last position of the stack
* @param *Stack stack Pointer to the stack
* @return void* Returns storage nodes큦 data pointer
* @return s16 kErrorCode_NullStackPointer If Stack pointer is NULL
* @return s16 kErrorCode_InsertionFailed If Stack is full
* @return s16 kErrorCode_NullVectorPointer If storage nodes큦 data pointer is NULL
* @return s16 kErrorCode_NullPointer If data pointer is NULL
* @return s16 kErrorCode_InvalidValue If bytes value is 0
*/
	s16 (*push)(Stack *stack, void *data, u16 bytes);

	// Extraction
/**
* @brief Extracts the first element of the stack
* @param *Stack stack Pointer to the stack
* @return void* data Returns storage nodes큦 data pointer
* @return NULL If the stack pointer is NULL
* @return NULL If the stack is empty
* @return NULL If storage pointer is NULL
*/
	void* (*pop)(Stack *stack);

/**
* @brief Concatenates two stacks
* @param *Stack stack Pointer to the stack
* @param *Stack stack_src Pointer to the second stack
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullStackPointer When ether one of the two stack pointers is NULL
* @return s16 kErrorCode_NullVectorPointer When ether one of the two vector pointers(storage) is NULL
*/
 s16* (*concat)(Stack *stack, Stack *stack_src);

	// Miscellaneous
/**
* @brief Prints the features and content of the stack
* @param *Stack stack Pointer to the stack
*/
	void (*print)(Stack *stack); // Prints the features and content of the stack
};

/**
* @brief Creates a new stack
* @param u16 capacity Maximum length that the stack can possibly have
* @return Stack* stack Returns a stack pointer with all variables initialized
* @return NULL If capacity parameter is 0
* @return NULL If there is not enough memory available
*/
Stack* STACK_create(u16 capacity); // Creates a new stack
#endif //__ADT_STACK_H__
