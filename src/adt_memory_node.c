// adt_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "ABGS_MemoryManager/abgs_memory_manager.h"


// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode* node);
static void* MEMNODE_data(MemoryNode* node);	
static s16 MEMNODE_setData(MemoryNode* node, void* src, u16 bytes);
static u16 MEMNODE_size(MemoryNode* node);

static MemoryNode* MEMNODE_getNext(MemoryNode *node);
static u16 MEMNODE_setNext(MemoryNode* node, MemoryNode* next_node);

static MemoryNode* MEMNODE_getPrev(MemoryNode *node);
static u16 MEMNODE_setPrev(MemoryNode* node, MemoryNode* prev_node);

static s16 MEMNODE_reset(MemoryNode* node);

static s16 MEMNODE_softReset(MemoryNode* node);
static s16 MEMNODE_free(MemoryNode* node);
static s16 MEMNODE_softFree(MemoryNode* node);

static s16 MEMNODE_memSet(MemoryNode* node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_memConcat(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_memMask(MemoryNode* node, u8 mask);

static void MEMNODE_print(MemoryNode* node);

// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops = { .data = MEMNODE_data,
	 .setData = MEMNODE_setData,
	 .size = MEMNODE_size,
	 .getNext = MEMNODE_getNext,
	 .setNext = MEMNODE_setNext,
	 .getPrev = MEMNODE_getPrev,
	 .setPrev = MEMNODE_setPrev,
	 .reset = MEMNODE_reset,
	 .softReset = MEMNODE_softReset,
	 .free = MEMNODE_free,
	 .softFree = MEMNODE_softFree,
	 .memSet = MEMNODE_memSet,
	 .memCopy = MEMNODE_memCopy,
	 .memConcat = MEMNODE_memConcat,
	 .memMask = MEMNODE_memMask,
	 .print = MEMNODE_print
};

// Memory Node Definitions
s16 MEMNODE_initWithoutCheck(MemoryNode* node) {
	node->data_ = NULL;
	node->size_ = 0;
	node->next_ = NULL;
	node->prev_ = NULL;
	node->ops_ = &memory_node_ops;
	return kErrorCode_Ok;
}

MemoryNode* MEMNODE_create() {
	MemoryNode* node = NULL;
	node = MM->malloc(sizeof(MemoryNode));
	if (NULL == node) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	MEMNODE_initWithoutCheck(node);
	return node;
}

s16 MEMNODE_createFromRef(MemoryNode** node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	*node = MM->malloc(sizeof(MemoryNode));

	if (NULL == *node) {
		return kErrorCode_NullMemoryNode;
	}
	MEMNODE_initWithoutCheck(*node);
	return kErrorCode_Ok;
}

s16 MEMNODE_createLite(MemoryNode* node) {
	if (node != NULL) {
		MEMNODE_initWithoutCheck(node);
		return kErrorCode_Ok;
	}
	return kErrorCode_NullMemoryNode;
}

void* MEMNODE_data(MemoryNode* node) { // returns a reference to data_
	if (NULL == node) {
		return NULL;
	}
	if (node->data_ == NULL) {
		return NULL;
	}
	return node->data_;
}

s16 MEMNODE_setData(MemoryNode* node, void* src, u16 bytes) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == src) {
		return kErrorCode_NullPointer;
	}
	if (0 == bytes) {
		return kErrorCode_InvalidValue;
	}
	node->data_ = src;
	node->size_ = bytes;
	return kErrorCode_Ok;
}

u16	MEMNODE_size(MemoryNode* node) {
	if (NULL == node) {
		return 0;
	}
	return node->size_;
}

MemoryNode* MEMNODE_getNext(MemoryNode * node) {
  if (NULL == node) {
    return NULL;
  }
  return node->next_;
}

u16 MEMNODE_setNext(MemoryNode* node, MemoryNode* next_node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == next_node) {
		node->next_ = NULL;
		return kErrorCode_Ok;
	}
	node->next_ = next_node;
	return kErrorCode_Ok;
}

MemoryNode* MEMNODE_getPrev(MemoryNode * node) {
	if (NULL == node) {
		return NULL;
	}
	return node->prev_;
}

u16 MEMNODE_setPrev(MemoryNode* node, MemoryNode* prev_node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == prev_node) {
		node->prev_ = NULL;
		return kErrorCode_Ok;
	}
	node->prev_ = prev_node;
	return kErrorCode_Ok;
}

s16 MEMNODE_reset(MemoryNode* node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL != node->ops_->data(node)) {
		MM->free(node->data_);
		node->data_ = NULL;
	}
	node->size_ = 0;
	return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode* node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	node->data_ = NULL;
	node->size_ = 0;
	return kErrorCode_Ok;
}

s16 MEMNODE_free(MemoryNode* node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL != node->ops_->data(node)) {
		MM->free(node->data_);
		node->data_ = NULL;
	}
	node->size_ = 0;
	MM->free(node);
	node = NULL;
	return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode* node) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	MM->free(node);
	node = NULL;
	return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode* node, u8 value) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}

	if (NULL == node->ops_->data(node)) {
		return kErrorCode_NullPointer;
	}

	if (0 >= node->ops_->size(node)) {
		return kErrorCode_InvalidValue;
	}

	memset(node->ops_->data(node), value, node->ops_->size(node));

	return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode* node, void* src, u16 bytes) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == src) {
		return kErrorCode_NullPointer;
	}
	if (0 == bytes) {
		return kErrorCode_InvalidValue;
	}
	void* new_data = MM->malloc(bytes);
	if (NULL != node->data_) {
		MM->free(node->data_);
		node->data_ = NULL;
	}
	memcpy(new_data, src, bytes);
	node->data_ = new_data;
	node->size_ = bytes;

	return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode* node, void* src, u16 bytes) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == src) {
		return kErrorCode_NullPointer;
	}
	if (0 == bytes) {
		return kErrorCode_InvalidValue;
	}
	if (NULL == node->ops_->data(node)) {
		return kErrorCode_NullPointer;
	}

	u16 tmp_size = node->size_ + bytes;
	void* tmp = MM->malloc(tmp_size);
	if (tmp == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_NullMemoryAllocation;
	}
	void* tmp1 = src;
	void* tmp2 = node->data_;
	for (u16 i = 0; i < (tmp_size); ++i)
	{
		if (i < node->size_) {
			*((u8*)tmp + i) = *((u8*)tmp2 + i);
		}
		else {
			*((u8*)tmp + i) = *((u8*)tmp1 + (i - node->size_));
		}
	}
	if (node->ops_->data(node) != NULL) {
		MM->free(node->data_);
		node->data_ = NULL;
	}
	node->data_ = tmp;
	node->size_ = tmp_size;

	return kErrorCode_Ok;
}

s16 MEMNODE_memMask(MemoryNode* node, u8 mask) {
	if (NULL == node) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == node->data_) {
		return kErrorCode_NullMemoryNode;
	}
	if (0 == node->size_) {
		return kErrorCode_NullMemoryNode;
	}
	if (8 > mask) {

		return kErrorCode_InvalidValue;
	}
	void* tmp = node->data_;
	for (u16 i = 0; i < node->size_; ++i)
	{
		*((u8*)tmp + i) = (*((u8*)tmp + i) & (mask));
	}
	return kErrorCode_Ok;
}

void printaux(MemoryNode* aux) {
	if (NULL == aux) {
		printf("NULL\n");
	}
	else {
		printf("%p\n", aux);
	}
}

void MEMNODE_print(MemoryNode* node) {
	printf("			[Node Info] Address: ");
	if (NULL == node) {
		printf("NULL\n");
		return;
	}
	else {
		printf("%p\n", node);
	}
	printf("			[Node Info] Size: %d\n", node->size_);
	printf("			[Node Info] Data address: ");
	if (NULL == node->data_) {
		printf("NULL\n");
		return;
	}
	else {
		printf("%p\n", node->data_);
	}

	printf("			[Node Info] Data content: ");
	u8* ptr_iterator = (u8*)node->data_;
	if (node->size_ > 0) {
		for (u16 i = 0; i < node->size_; ++i)
		{
			printf("%c", *(ptr_iterator++));
		}
	}
	else {
		printf("NULL\n");
		return;
	}
	printf("\n");
	printf("			[Node Info] Next address: ");
	if (NULL == node->next_) {
		printf("NULL\n");
	}
	else {
		printf("%p\n", node->next_);
	}
	printf("			[Node Info] Prev address: ");
	if (NULL == node->prev_) {
		printf("NULL\n");
	}
	else {
		printf("%p\n", node->prev_);
	}
}
