// adt_memory_node.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__ 1

#include "ABGS_MemoryManager/abgs_platform_types.h"

/**
* @brief Memory Node struct that contains all variables and callbacks
*/
typedef struct memory_node_s {
  // @brief void* data Contains the information stored in the node
  void *data_;
  // @brief u16 size_ Defines the size of the info
  u16 size_;
  // @brief memory_node_ops_s *ops_ Pointer to callbacks
  struct memory_node_ops_s *ops_;
  // @brief memory_node_ops_s *next_ Pointer to the next node (List use only)
  struct memory_node_s *next_;
  // @brief memory_node_ops_s *prev_ Pointer to the previous node (List use only)
  struct memory_node_s *prev_;
} MemoryNode;

// Memory Node's API Declarations
/**
* @brief Struct that contains all functions attached to the Memory Node
*/
struct memory_node_ops_s {
/**
* @brief Returns a reference of the node큦 data
* @param MemoryNode *node pointer to the node
* @return Returns nodes큦 data pointer
* @return NULL If node pointer is null
* @return NULL If node큦 data pointer is null
*/
  void*(*data) (MemoryNode *node);

/**
* @brief Sets the node큦 data pointer with the given information 
* @param MemoryNode *node pointer to the node
* @param void* src pointer to the data
* @param u16 bytes size of data
* @return Returns nodes큦 data pointer
* @return NULL If node pointer is null
* @return NULL If node큦 data pointer is null
*/
  s16(*setData) (MemoryNode *node, void *src, u16 bytes);

/**
* @brief Getter for Memnode size
* @param MemoryNode *node pointer to the node
* @return Returns nodes큦 size
* @return Returns 0 if node pointer is NULL
*/
  u16(*size) (MemoryNode *node);

  // List methods
/**
* @brief Getter for Memnode next pointer
* @param MemoryNode *node pointer to the node
* @return Returns nodes큦 next pointer
* @return NULL If node pointer is NULL
*/
  MemoryNode*(*getNext) (MemoryNode *node);

  /**
  * @brief Setter for Memnode next pointer
  * @param MemoryNode *node pointer to the node
  * @return s16 kErrorCode_Ok If nodes큦 next pointer is valid
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  u16(*setNext) (MemoryNode* node, MemoryNode* next_node);

  // Double list methods
  /**
  * @brief Getter for Memnode prev pointer
  * @param MemoryNode *node pointer to the node
  * @param MemoryNode *next_node pointer to the next node
  * @return Returns nodes큦 prev pointer
  * @return NULL If node pointer is NULL
  */
  MemoryNode*(*getPrev) (MemoryNode *node);

  /**
  * @brief Setter for Memnode prev pointer
  * @param MemoryNode *node pointer to the node
  * @param MemoryNode *prev_node pointer to the previous node
  * @return s16 kErrorCode_Ok If nodes큦 prev pointer is valid
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  u16(*setPrev) (MemoryNode* node, MemoryNode* prev_node);

  
  /**
  * @brief Resets content of memory node
  * @param MemoryNode *node pointer to the node
  * @return s16 kErrorCode_Ok If the operation was successful
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*reset) (MemoryNode *node);   // (ptr a void. mm->free(data), data = null, size = 0)
 
  /**
  * @brief Resets content of memory node without freeing the node
  * @param MemoryNode *node pointer to the node
  * @return s16 kErrorCode_Ok If the operation was successful
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*softReset) (MemoryNode *node);	

  /**
  * @brief Frees memory node, both data and node
  * @param MemoryNode *node pointer to the node
  * @return s16 kErrorCode_Ok If the operation was successfull
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*free) (MemoryNode *node);		

  /**
  * @brief Frees only the node
  * @param MemoryNode *node pointer to the node
  * @return s16 kErrorCode_Ok If the operation was successful
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*softFree) (MemoryNode *node);	

  /**
  * @brief Sets the node's data from the given value
  * @param MemoryNode *node pointer to the node
  * @return s16 kErrorCode_Ok If the operation was successful
  * @return s16 kErrorCode_NullPointer If the node's data is NULL
  * @return s16 kErrorCode_InvalidValue If the given node's size is less than 0
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*memSet) (MemoryNode *node, u8 value); 

  /**
  * @brief Copies the given information into the node's data
  * @param MemoryNode *node pointer to the node
  * @param void *src Data pointer with the new information
  * @param u16 bytes Size of the given information
  * @return s16 kErrorCode_Ok If the operation was successful
  * @return s16 kErrorCode_NullPointer If the node's data is NULL
  * @return s16 kErrorCode_InvalidValue If the bytes value is 0
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*memCopy) (MemoryNode *node, void *src, u16 bytes); //mm->free node.data, then = src to node.data and node.size = byte
  
  //mm->malloc(bytes + node.size), free old node, then mempcy to new size 
  /**
  * @brief Concatenates two nodes, the second node's information into the first one
  * @param MemoryNode *node Pointer to the main node
  * @param void *src Data pointer with the new information
  * @param u16 bytes Size of the given information
  * @return s16 kErrorCode_Ok If the operation was successful
  * @return s16 kErrorCode_NullPointer If the node's data is NULL
  * @return s16 kErrorCode_InvalidValue If the bytes value is 0
  * @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
  */
  s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);
  //apply & mask
  s16(*memMask) (MemoryNode *node, u8 mask);

/**
* @brief Prints the information of the node
* @param MemoryNode *node Pointer to the node
*/
  void(*print) (MemoryNode *node);
};
/**
* @brief Creates a new node
* @return MemoryNode* node Returns a node pointer with all variables initialized
* @return NULL If there is not enough memory available
*/
MemoryNode* MEMNODE_create();

s16 MEMNODE_createFromRef(MemoryNode **node);

/**
* @brief Creates a memory node without memory allocation
* @param MemoryNode *node Pointer to the main node
* @return s16 kErrorCode_Ok If the operation was successful
* @return s16 kErrorCode_NullMemoryNode If node pointer is NULL
*/
s16 MEMNODE_createLite(MemoryNode *node);

#endif // __ADT_MEMORY_NODE_H__
