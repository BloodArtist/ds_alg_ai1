// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__ 1

#include "adt_memory_node.h"

/**
* @brief Vector struct that contains all variables and callbacks
*/
typedef struct adt_vector_s {
 // @brief u16 head_ First element in the vector
	u16 head_;
 // @brief u16 tail_ Corresponds to the first free place of the vector
	u16 tail_;
 // @brief u16 capacity Maximum length that the list can possibly have, cannot be 0
	u16 capacity_;
 // @brief MemoryNode *storage_ Container of all elements of the vector
	MemoryNode *storage_;
 // @brief vector_ops_s *ops_ Pointer to callback 
	struct vector_ops_s *ops_;
} Vector;

/**
* @brief Struct that contains all functions attached to the Vector
*/
struct vector_ops_s {
/**
* @brief Destroys the vector and its data
* @param *Vector vector Pointer to the vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the vector pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage pointer is NULL
*/
	s16 (*destroy)(Vector *vector);

/**
* @brief Soft resets vector's data
* @param *Vector vector Pointer to the vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullListPointer When the List pointer(storage) is NULL
*/
	s16 (*softReset)(Vector *vector);

 /**
* @brief Resets vector's data
* @param *Vector vector Pointer to the vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullListPointer When the List pointer(storage) is NULL
*/
	s16 (*reset)(Vector *vector);

/**
 * @brief Resizes the capacity of the vector. Some elements can be lost
 * @param *Vector vector Pointer to the vector
 * @param u16 new_size New size
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
 * @return s16 kErrorCode_NullListPointer When the list pointer(storage) is NULL
 * @return s16 kErrorCode_InvalidValue When the new_size value is 0
 * @return s16 kErrorCode_NullMemoryAllocation When there is no memory to allocate
 */
	s16 (*resize)(Vector *vector, u16 new_size);

	// State queries
  /**
* @brief Returns the maximum number of elements that can be store
* @param *Vector vector Pointer to the vector
* @return u16 Vector큦 capacity
* @return u16 0 If Vector pointer is NULL
*/
	u16 (*capacity)(Vector *vector);

 /**
* @brief Current number of elements (<= capacity)
* @param *Vector vector Pointer to the vector
* @return u16 Vector큦 length
* @return u16 0 If Vector pointer is NULL
*/
	u16 (*length)(Vector *vector);

 /**
* @brief Verifies is the Vector is empty
* @param *Vector vector Pointer to the vector
* @return bool Returns false if Vector pointer is NULL, otherwise checks and returns comprobation with tail and 0
*/
	bool (*isEmpty)(Vector *vector);

 /**
* @brief Verifies is the Vector is full
* @param *Vector vector Pointer to the vector
* @return bool Returns false if Vector pointer is NULL, otherwise checks and returns comprobation with capacity and length
*/
	bool (*isFull)(Vector *vector);

	// Data queries
/**
* @brief Returns a reference to the first element of the vector
* @param *Vector vector Pointer to the vector
* @return Returns nodes큦 data pointer, if Vector pointer is NULL, returns NULL
*/
	void* (*first)(Vector *vector);

 /**
* @brief Returns a reference to the last element of the vector
* @param *Vector vector Pointer to the vector
* @return Returns nodes큦 data pointer, if Vector pointer is NULL, returns NULL
*/
	void* (*last)(Vector *vector);

 /**
* @brief Returns a reference to the element at a given position
* @param *Vector vector Pointer to the vector
* @return Returns nodes큦 data pointer, if Vector pointer is NULL, returns NULL
*/
	void* (*at)(Vector *vector, u16 position);

	// Insertion
/**
* @brief Inserts an element in the first position of the vector
* @param *Vector vector Pointer to the vector
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the vector is full
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
*/
	s16 (*insertFirst)(Vector *vector, void *data, u16 bytes);

 /**
* @brief Inserts an element in the last position of the vector
* @param *Vector vector Pointer to the vector
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the vector is full
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
*/
	s16 (*insertLast)(Vector *vector, void *data, u16 bytes);

 /**
* @brief Inserts an element at the given position of the vector
* @param *Vector vector Pointer to the vector
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the vector is full
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
*/
	s16 (*insertAt)(Vector *vector, void *data, u16 bytes, u16 position);

	// Extraction
  /**
 * @brief Extracts the first element of the vector
 * @param *Vector vector Pointer to the vector
 * @return Returns nodes큦 data pointer
 * @return NULL if Vector pointer is NULL
 * @return NULL if Vector ops pointer is NULL
 * @return NULL if the vector is empty
 * @return NULL if the Vector큦 storage is NULL
 * @return NULL if the first Vector큦 data is NULL
 */
	void* (*extractFirst)(Vector *vector);
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
* @param *Vector vector Pointer to the vector
* @return Returns nodes큦 data pointer
* @return NULL if Vector pointer is NULL
* @return NULL if Vector ops pointer is NULL
* @return NULL if the vector is empty
* @return NULL if the Vector큦 storage is NULL
* @return NULL if the last Vector큦 data is NULL
*/
	void* (*extractLast)(Vector *vector);

 /**
* @brief Extracts the element of the vector at the given position
* @param *Vector vector Pointer to the vector
* @return Returns nodes큦 data pointer
* @return NULL if Vector pointer is NULL
* @return NULL if Vector ops pointer is NULL
* @return NULL if the vector is empty
* @return NULL if the Vector큦 storage is NULL
* @return NULL if the Vector큦 data is NULL at the given position
*/
	void* (*extractAt)(Vector *vector, u16 position);

	// Miscellaneous
  /**
* @brief Concatenates two vectors
* @param *Vector vector Pointer to the vector
* @param *Vector_src pointer to the second vector
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the Vector pointer is NULL
* @return s16 kErrorCode_NullVectorPointer When the second Vector pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the vector큦 storage is NULL
* @return s16 kErrorCode_NullMemoryNode When the second vector큦 storage is NULL
*/
	s16 (*concat)(Vector *vector, Vector *vector_src); 

 /**
* @brief Calls to a function from all elements of the vector
* @param *Vector vector Pointer to the vector
* @param *Void Pointer to MemoryNode큦 callback
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullVectorPointer When the vector pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the new node is NULL
*/
	s16 (*traverse)(Vector *vector, void (*callback)(MemoryNode *));

 /**
* @brief Prints the features and content of the vector
* @param *Vector vector Pointer to the vector
*/
	void (*print)(Vector *vector);
};
/**
* @brief Creates a new vector
* @param u16 capacity Maximum length that the list can possibly have
* @return Vector* Return a vector pointer with all variables initialized
* @return NULL If capacity parameter is 0 or there큦 no space in memory
*/
Vector* VECTOR_create(u16 capacity);
#endif //__ADT_VECTOR_H__
