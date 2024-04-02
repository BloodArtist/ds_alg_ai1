/**********************************************************************************
* Copyright ***. All rights reserved.
*
* Contains all essential declaration functions required for the "Queue" data type
*
*
*
*
* Code by Yossef Rubalcava & Davide Pietro
* Code Maintained by Yossef R.
**********************************************************************************/

#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__ 1

#include "adt_list.h"

/**
* @brief Structure representing a Queue with variables and callbacks.
*/
typedef struct adt_queue_s {
  // @brief Pointer that will contain all information
	List* storage_;
  // @brief Pointer to callbacks functions
	struct queue_ops_s *ops_;
} Queue;

/**
* @brief Struct that contains all functions attached to the Queue
*/
struct queue_ops_s {
  /**
* @brief Destroys the queue and its data
* @param *Stack stack Pointer to the stack
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullQueuePointer When the queue pointer is NULL
* @return s16 kErrorCode_NullListPointer When the queue큦 storage pointer is NULL
*/
	s16(*destroy)(Queue *queue);

 /**
* @brief Resets queue's data
* @param *Queue queue Pointer to the stack
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullQueuePointer When the queue pointer is NULL
* @return s16 kErrorCode_NullListPointer When the list pointer(storage) is NULL
*/
	s16(*reset)(Queue *queue);

 /**
* @brief Resizes the capacity of the queue. Some elements can be lost
* @param *Queue queue Pointer to the queue
* @param u16 new_size New capacity size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullQueuePointer When the queue pointer is NULL
* @return s16 kErrorCode_NullListPointer When the list pointer(storage) is NULL
* @return s16 kErrorCode_InvalidValue When the new_size value is 0
*/
	s16(*resize)(Queue *queue, u16 new_size);

/**
* @brief Returns the maximum number of elemets to store
* @param *Queue queue Pointer to the queue
* @return u16 List큦(storage) capacity from the queue
* @return u16 0 If Queue pointer is NULL
*/
	u16(*capacity)(Queue *queue);

/**
* @brief current number of elements (<= capacity)
* @param *Queue queue Pointer to the queue
* @return u16 List큦(storage) length from the queue
* @return u16 0 If Queue pointer is NULL
*/
	u16(*length)(Queue *queue);

 /**
* @brief Verifies is the Stack is empty
* @param *Queue queue Pointer to the queue
* @return bool false If Queue pointer is NULL
* @return bool Checks and returns comprobation with storage's length and 0
*/
	bool(*isEmpty)(Queue *queue);

 /**
* @brief Verifies is the Stack is full
* @param *Queue queue Pointer to the queue
* @return bool Returns false if Queue pointer is NULL
* @return bool Checks and returns comprobation with storage's capacity and length
*/
	bool(*isFull)(Queue *queue);

 /**
* @brief Returns a reference to the first element of the queue
* @param *Queue queue Pointer to the queue
* @return void* Returns the first storage nodes큦 data pointer
* @return NULL If Queue pointer is NULL
* @return NULL If storage pointer is NULL
*/
	void* (*front)(Queue *queue); 

 /**
* @brief Returns a reference to the last element of the queue
* @param *Queue queue Pointer to the queue
* @return void* Returns the last storage nodes큦 data pointer
* @return NULL If Queue pointer is NULL
* @return NULL If storage pointer is NULL
*/
	void* (*back)(Queue *queue);

 /**
* @brief Inserts an element in the first position of the queue
* @param *Queue queue Pointer to the queue
* @param u16 new_size New capacity size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullQueuePointer When the queue pointer is NULL
* @return s16 kErrorCode_NullListPointer When the list pointer(storage) is NULL
* @return s16 kErrorCode_InvalidValue When the bytes value is 0
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
*/
	s16(*enqueue)(Queue *queue, void *data, u16 bytes);

 /**
* @brief Extracts the first element of the queue
* @param *Queue queue Pointer to the queue
* @param u16 position Position of the element to extract
* @return void* data Returns storage nodes큦 data pointer
* @return NULL If the queue pointer is NULL
* @return NULL If the queue is empty
* @return NULL If storage pointer is NULL
*/
	void* (*dequeue)(Queue *queue, u16 position);

 /**
* @brief Concatenates two queues
* @param *Queue queue Pointer to the queue
* @param *Queue queue_src Pointer to the second queue
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullStackPointer When ether one of the two queue pointers is NULL
* @return s16 kErrorCode_NullListPointer When ether one of the two list(storage) pointers is NULL
*/
	s16(*concat)(Queue *queue, Queue *queue_src);

 /**
* @brief Prints the features and content of the stack
* @param *Queue queue Pointer to the queue
*/
	void(*print)(Queue *queue); // Prints the features and content of the queue
};

/**
* @brief Creates a new queue
* @param u16 capacity Maximum length that the queue can possibly have
* @return Queue* queue Returns a queue pointer with all variables initialized
* @return NULL If capacity parameter is 0
* @return NULL If there is not enough memory available
*/
Queue* QUEUE_create(u16 capacity); // Creates a new queue
#endif //__ADT_QUEUE_H__
