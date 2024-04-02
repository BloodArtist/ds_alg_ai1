/**********************************************************************************
* Copyright ***. All rights reserved.
*
* Contains all essential declaration functions required for the "Double List" data type
*
*
*
*
* Code by Yossef Rubalcava & Davide Pietro
* Code Maintained by Yossef R.
**********************************************************************************/

#ifndef __ADT_DLLIST_H__
#define __ADT_DLLIST_H__ 1

#include "adt_vector.h"

/**
* @brief Structure representing a DList with variables and callbacks.
*/
typedef struct adt_dlist_s {
  // @brief First node element of the list
 MemoryNode *head_;
  // @brief Corresponds to the first free place of the list
 MemoryNode *tail_;
  // @brief Maximum length that the list can possibly have, cannot be 0
 u16 capacity_;
  // @brief Current number of elements in the list
 u16 length_;
  // @brief Pointer to callback functions
 struct dlist_ops_s *ops_;
} DList;

/**
* @brief Struct that contains all functions attached to the List
*/
struct dlist_ops_s {
/**
* @brief Destroys the list and its data
* @param *List pointer to the list
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullListPointer When the list pointer is NULL
*/
	s16 (*destroy)(DList *list);

/**
* @brief Soft resets list's data
* @param *List pointer to the list
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullListPointer When the list pointer is NULL
*/
	s16 (*softReset)(DList *list);

 /**
 * @brief Resets list's data (frees the data pointer)
 * @param *List pointer to the list
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullListPointer When the list pointer is NULL
 */
	s16 (*reset)(DList *list);

 /**
 * @brief Resizes the capacity of the list. Some elements can be lost
 * @param *List pointer to the list
 * @param u16 new_size New size 
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullListPointer When the list pointer is NULL
 * @return s16 kErrorCode_InvalidValue When the new_size value is 0
 */
	s16 (*resize)(DList *list, u16 new_size); 

	// State queries
 /**
 * @brief Returns the maximum number of elemets to store
 * @param *List pointer to the list
 * @return u16 list큦 capacity, returns 0 if list pointer is NULL
 */
	u16 (*capacity)(DList *list);

 /**
 * @brief Current number of elements
 * @param *List pointer to the list
 * @return u16 list큦 length, returns 0 if list pointer is NULL
 */
	u16 (*length)(DList *list);

 /**
 * @brief Checks if the List is empty
 * @param *List pointer to the list
 * @return bool Returns 0 if list pointer is NULL, otherwise checks and returns comprobation with length and 0
 */
	bool (*isEmpty)(DList *list);

 /**
 * @brief Checks if the List is full
 * @param *List pointer to the list
 * @return bool Returns 0 if list pointer is NULL, otherwise checks and returns comprobation with capacity and length
 */
	bool (*isFull)(DList *list);

	// Data queries
 /**
 * @brief Returns a reference to the first node큦 data of the list
 * @param *List pointer to the list
 * @return Returns nodes큦 data pointer, if List pointer is NULL, returns NULL
 */
	void* (*first)(DList *list);
 /**
 * @brief Returns a reference to the last node큦 data of the list
 * @param *List pointer to the list
 * @return Returns nodes큦 data pointer, if List pointer is NULL, returns NULL
 */
	void* (*last)(DList *list);

 /**
 * @brief Returns a reference to the node큦 data at a given position
 * @param *List pointer to the list
 * @return Returns nodes큦 data pointer, if List pointer is NULL, returns NULL
 */
	void* (*at)(DList *list, u16 position);

	// Insertion
 /**
 * @brief Inserts an element in the first position of the list
 * @param *List pointer to the list
 * @param void* data pointer
 * @param u16 bytes size
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullListPointer When the list pointer is NULL
 * @return s16 kErrorCode_NullPointer When the data pointer is NULL
 * @return s16 kErrorCode_InsertionFailed When the list is full
 * @return s16 kErrorCode_NullMemoryNode When the new node is NULL
 */
	s16 (*insertFirst)(DList *list, void *data, u16 bytes); 

 /**
* @brief Inserts an element in the last position of the list
* @param *List pointer to the list
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullListPointer When the list pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the list is full
* @return s16 kErrorCode_NullMemoryNode When the new node is NULL
*/
	s16 (*insertLast)(DList *list, void *data, u16 bytes);

 /**
* @brief Inserts an element at the given position of the list
* @param *List pointer to the list
* @param void* data pointer
* @param u16 bytes size
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullListPointer When the list pointer is NULL
* @return s16 kErrorCode_NullPointer When the data pointer is NULL
* @return s16 kErrorCode_InsertionFailed When the list is full
* @return s16 kErrorCode_NullMemoryNode When the new node is NULL
*/
	s16 (*insertAt)(DList *list, void *data, u16 bytes, u16 position);

	// Extraction
 /**
 * @brief Extracts the first element of the list
 * @param *List pointer to the list
 * @return Returns nodes큦 data pointer, if List pointer or list head is NULL, returns NULL
 */
	void* (*extractFirst)(DList *list);
  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(List *list, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(List *list
#if DEBUG
	, u16 *size
#endif // DEBUG
		);
  */

 /**
 * @brief Extracts the last element of the list
 * @param *List pointer to the list
 * @return Returns nodes큦 data pointer, if List pointer or list head is NULL, returns NULL
 */
	void* (*extractLast)(DList *list); 

 /**
* @brief Extracts the element of the list at the given position
* @param *List pointer to the list
* @return Returns nodes큦 data pointer, if List pointer or list head is NULL, returns NULL
*/
	void* (*extractAt)(DList *list, u16 position);

	// Miscellaneous
 /**
 * @brief Concatenates two lists
 * @param *List pointer to the list
 * @param *List_src pointer to the second list
 * @return s16 kErrorCode_Ok When the function has exited successfully
 * @return s16 kErrorCode_NullListPointer When the list pointer is NULL
 */
	s16 (*concat)(DList *list, DList *list_src);

 /**
* @brief Calls to a function from all elements of the list
* @param *List pointer to the list
* @param *Void pointer to MemoryNode큦 callback
* @return s16 kErrorCode_Ok When the function has exited successfully
* @return s16 kErrorCode_NullListPointer When the list pointer is NULL
* @return s16 kErrorCode_NullMemoryNode When the new node is NULL
*/
	s16 (*traverse)(DList *list, void (*callback)(MemoryNode *));
	
 /**
* @brief Prints the features and content of the list
* @param *List pointer to the list
*/
	void (*print)(DList *list);

};

/**
* @brief Creates a new list
* @param u16 capacity Maximum length that the list can possibly have
* @return List* Return a list pointer with all variables initialized
* @return NULL If capacity parameter is 0 or there큦 no space in memory
*/
DList* DLIST_create(u16 capacity);
#endif //__ADT_DLLIST_H__
