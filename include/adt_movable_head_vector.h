// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MOVABLE_HEAD_VECTOR_H__
#define __ADT_MOVABLE_HEAD_VECTOR_H__

#include "adt_memory_node.h"

/**
* @brief Vector struct that contains all variables and callbacks
*/
typedef struct adt_movable_head_vector_s {
  // @brief u16 head_ First element in the vector
	u16 head_;
 // @brief u16 tail_ Corresponds to the first free place of the vector
	u16 tail_;
 // @brief u16 capacity Maximum length that the list can possibly have, cannot be 0
	u16 capacity_;
 // @brief MemoryNode *storage_ Container of all elements of the vector
	MemoryNode *storage_;
 // @brief vector_ops_s *ops_ Pointer to callback 
	struct movable_head_vector_ops_s *ops_;
} MovableHeadVector;

struct movable_head_vector_ops_s {
/**
* @brief Destroys the vector and its data
* @param *Vector pointer to the vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the vector pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage pointer is NULL
*/
	s16 (*destroy)(MovableHeadVector *vector);	

 /**
* @brief Soft resets vector's data
* @param *Vector pointer to the vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullListPointer When the List pointer(storage) is NULL
*/
 s16 (*softReset)(MovableHeadVector *vector);	

 /**
* @brief Resets vector's data
* @param *Vector pointer to the vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullListPointer When the List pointer(storage) is NULL
*/
 s16 (*reset)(MovableHeadVector *vector);	

 /**
 * @brief Resizes the capacity of the vector. Some elements can be lost
 * @param *Vector pointer to the vector
 * @param u16 new_size New size
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
 * @return s16 kErrorCode_NullListPointer When the list pointer(storage) is NULL
 * @return s16 kErrorCode_InvalidValue When the new_size value is 0
 * @return s16 kErrorCode_NullMemoryAllocation When there is no memory to allocate
 */
	s16 (*resize)(MovableHeadVector *vector, u16 new_size); 

	// State queries
   /**
* @brief Returns the maximum number of elemets to store
* @param *Vector pointer to the vector
* @return u16 Vector큦 capacity
* @return u16 0, if Vector pointer is NULL
*/
	u16 (*capacity)(MovableHeadVector *vector);

 /**
* @brief Current number of elements (<= capacity)
* @param *Vector pointer to the vector
* @return u16 Vector큦 length
* @return u16 0, if Vector pointer is NULL
*/
	u16 (*length)(MovableHeadVector *vector);			

 /**
* @brief Verifies is the Vector is empty
* @param *Vector pointer to the vector
* @return bool Returns 0 if Vector pointer is NULL, otherwise checks and returns comprobation with tail and 0
*/
	bool (*isEmpty)(MovableHeadVector *vector);

 /**
* @brief Verifies is the Vector is full
* @param *Vector pointer to the vector
* @return bool Returns 0 if Vector pointer is NULL, otherwise checks and returns comprobation with capacity and length
*/
	bool (*isFull)(MovableHeadVector *vector);

	// Data queries
 /**
* @brief Returns a reference to the first element of the vector
* @param *Vector pointer to the vector
* @return Returns nodes큦 data pointer, if Vector pointer is NULL, returns NULL
*/
	void* (*first)(MovableHeadVector *vector); 

 /**
* @brief Returns a reference to the last element of the vector
* @param *Vector pointer to the vector
* @return Returns nodes큦 data pointer, if Vector pointer is NULL, returns NULL
*/
	void* (*last)(MovableHeadVector *vector); 

 /**
* @brief Returns a reference to the element at a given position
* @param *Vector pointer to the vector
* @return Returns nodes큦 data pointer, if Vector pointer is NULL, returns NULL
*/
	void* (*at)(MovableHeadVector *vector, u16 position); 

	// Insertion
 /**
* @brief Inserts an element in the first position of the vector
* @param *Vector pointer to the vector
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the vector is full
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
*/
	s16 (*insertFirst)(MovableHeadVector *vector, void *data, u16 bytes); 
	

 /**
* @brief Inserts an element in the last position of the vector
* @param *Vector pointer to the vector
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the vector is full
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
*/
 s16 (*insertLast)(MovableHeadVector *vector, void *data, u16 bytes); 
	
 /**
* @brief Inserts an element at the given position of the vector
* @param *Vector pointer to the vector
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the vector is full
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
*/
 s16 (*insertAt)(MovableHeadVector *vector, void *data, u16 bytes, u16 position); 

	// Extraction
   /**
 * @brief Extracts the first element of the vector
 * @param *Vector pointer to the vector
 * @return Returns nodes큦 data pointer
 * @return NULL if Vector pointer is NULL
 * @return NULL if Vector ops pointer is NULL
 * @return NULL if the vector is empty
 * @return NULL if the Vector큦 storage is NULL
 * @return NULL if the first Vector큦 data is NULL
 */
	void* (*extractFirst)(MovableHeadVector *vector); 
  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(Vector *vector, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(Vector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);
  */
  /**
 * @brief Extracts the last element of the vector
 * @param *Vector pointer to the vector
 * @return Returns nodes큦 data pointer
 * @return NULL if Vector pointer is NULL
 * @return NULL if Vector ops pointer is NULL
 * @return NULL if the vector is empty
 * @return NULL if the Vector큦 storage is NULL
 * @return NULL if the last Vector큦 data is NULL
 */
	void* (*extractLast)(MovableHeadVector *vector);

 /**
* @brief Extracts the element of the vector at the given position
* @param *Vector pointer to the vector
* @return Returns nodes큦 data pointer
* @return NULL if Vector pointer is NULL
* @return NULL if Vector ops pointer is NULL
* @return NULL if the vector is empty
* @return NULL if the Vector큦 storage is NULL
* @return NULL if the Vector큦 data is NULL at the given position
*/
	void* (*extractAt)(MovableHeadVector *vector, u16 position); 

	// Miscellaneous
   /**
* @brief Concatenates two vectors
* @param *Vector pointer to the vector
* @param *Vector_src pointer to the second vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullVectorPointer When the second Vector pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
* @return s16 kErrorCode_NullMemoryNode When the second vector큦 storage is NULL
*/
	s16 (*concat)(MovableHeadVector *vector, MovableHeadVector *vector_src); 
	
 /**
* @brief Calls to a function from all elements of the vector
* @param *Vector pointer to the vector
* @param *Void pointer to MemoryNode큦 callback
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the vector pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the new node is NULL
*/
 s16 (*traverse)(MovableHeadVector *vector, void (*callback)(MemoryNode *)); 
	
 /**
* @brief Prints the features and content of the vector
* @param *Vector pointer to the vector
*/
 void (*print)(MovableHeadVector *vector);
};
/**
* @brief Creates a new vector
* @param u16 capacity Maximum length that the list can possibly have
* @return Vector* Return a vector pointer with all variables initialized
* @return NULL If capacity parameter is 0 or there큦 no space in memory
*/
MovableHeadVector* MOVABLE_HEAD_VECTOR_create(u16 capacity); // Creates a new vector
#endif //__ADT_MOVABLE_HEAD_VECTOR_H__
