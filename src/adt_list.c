#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_list.h"


#include "ABGS_MemoryManager/abgs_memory_manager.h"

//List Declarations
static s16 LIST_destroy(List* list); 
static s16 LIST_softReset(List* list); 
static s16 LIST_reset(List* list); 
static s16 LIST_resize(List* list, u16 new_size);
static u16 LIST_capacity(List* list); 
static u16 LIST_length(List* list);   
static bool LIST_isEmpty(List* list);
static bool LIST_isFull(List* list);
static void* LIST_first(List* list);
static void* LIST_last(List* list);
static void* LIST_at(List* list, u16 position);  
static s16 LIST_insertFirst(List* list, void* data, u16 bytes);  
static s16 LIST_insertLast(List* list, void* data, u16 bytes);   
static s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position);
static void* LIST_extractFirst(List* list);            
static void* LIST_extractLast(List* list);             
static void* LIST_extractAt(List* list, u16 position);  
static s16 LIST_concat(List* list, List* list_src); 
static s16 LIST_traverse(List* list, void(*callback)(MemoryNode*)); 
static void LIST_print(List* list);

struct list_ops_s list_ops = { .destroy = LIST_destroy,
								  .softReset = LIST_softReset,
								  .reset = LIST_reset,
								  .resize = LIST_resize,
								  .capacity = LIST_capacity,
								  .length = LIST_length,
								  .isEmpty = LIST_isEmpty,
								  .isFull = LIST_isFull,
								  .first = LIST_first,
								  .last = LIST_last,
								  .at = LIST_at,
								  .insertFirst = LIST_insertFirst,
								  .insertLast = LIST_insertLast,
								  .insertAt = LIST_insertAt,
								  .extractFirst = LIST_extractFirst,
								  .extractLast = LIST_extractLast,
								  .extractAt = LIST_extractAt,
								  .concat = LIST_concat,
								  .traverse = LIST_traverse,
								  .print = LIST_print

};

List* LIST_create(u16 capacity) {
	if (capacity == 0) {
		return NULL;
	}
	List *list = MM->malloc(sizeof(List));
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	list->head_ = NULL;
	list->tail_ = NULL;
	list->capacity_ = capacity;
	list->length_ = 0;
	list->ops_ = &list_ops;

	return list;
}

s16 LIST_destroy(List* list) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (list->ops_->isEmpty(list)) {
		MM->free(list);
		return kErrorCode_Ok;
	}
	MemoryNode* tmp = list->head_;
	MemoryNode* tmp_next = NULL;
	for (u16 i = 0; i < list->ops_->length(list); ++i) {
		tmp_next = tmp->ops_->getNext(tmp);
		tmp->ops_->free(tmp);
		tmp = tmp_next;
	}
	MM->free(list);
	return kErrorCode_Ok;
}

s16 LIST_softReset(List* list) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (list->ops_->capacity(list) == 0 || list->ops_->length(list) == 0) {
		return kErrorCode_Ok;
	}
	if (NULL != list->head_) {
		MemoryNode* tmp = list->head_;
		for (u16 i = 0; i < list->ops_->length(list); ++i) {
			tmp->ops_->softFree(tmp);
			tmp = tmp->next_;
		}
		list->head_ = NULL;
	}
	list->length_ = 0;
	list->tail_ = NULL;
	return kErrorCode_Ok;
}

s16 LIST_reset(List* list) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (list->ops_->capacity(list) == 0 || list->ops_->length(list) == 0) {
		return kErrorCode_Ok;
	}
	if (NULL != list->head_) {
		MemoryNode* tmp = list->head_;
		MemoryNode* tmp_next = NULL;
		for (u16 i = 0; i < list->ops_->length(list); ++i) {
			tmp_next = tmp->ops_->getNext(tmp);
			tmp->ops_->free(tmp);
			tmp = tmp_next;
		}
		list->head_ = NULL;
	}
	list->length_ = 0;
	list->tail_ = NULL;
	return kErrorCode_Ok;
}

s16 LIST_resize(List* list, u16 new_size) {
	// parameter control
	if (0 == new_size) {
		return kErrorCode_InvalidValue;
	}
	if (NULL == list) {
		return kErrorCode_NullListPointer;
	}
	if (list->ops_->capacity(list) == new_size) {
		return kErrorCode_Ok;
	}
	if (NULL == list->head_) {
		list->capacity_ = new_size;
		return kErrorCode_Ok;
	}
	// if it is less than the lenght_, I have to delete data
	if (new_size < list->ops_->length(list)) {
		// A temporary MemoryNode that points to the first and one that runs through
		MemoryNode* tmp_node = list->head_;
		MemoryNode* tmp_next = NULL;
		for (u16 i = 0; i < list->ops_->length(list); ++i) {
			tmp_next = tmp_node->ops_->getNext(tmp_node);
			if (i < new_size) {
				// the tail_ points to the last
				list->tail_ = tmp_node;
			} else {
				// exceeds the new capacity and is released
				tmp_node->ops_->free(tmp_node);
			}
			tmp_node = tmp_next;
		}
		// I make sure that the next_ of the tail_ is null
		list->tail_->ops_->setNext(list->tail_, NULL);
		// The length_ is equal to the capacity_
		list->length_ = new_size;
	}
	list->capacity_ = new_size;
	return kErrorCode_Ok;
}

u16 LIST_capacity(List* list) {
	if (NULL == list) {
		return 0;  // kErrorCode_NullListPointer
	}
	return list->capacity_;
}

u16 LIST_length(List* list) {
	if (NULL == list) {
		return  0;  //kErrorCode_NullListPointer
	}
	return list->length_;
}

bool LIST_isEmpty(List* list) {
	if (NULL != list) {
		return 0 == list->ops_->length(list);
	}
	else {
		return false;
	}
}

bool LIST_isFull(List* list) {
	if (NULL != list) {
		return list->ops_->capacity(list) <= list->ops_->length(list);
	}
	else {
		return false;
	}
}

void* LIST_first(List* list) {
	if (NULL == list) {
		return NULL;        // kErrorCode_NullListPointer
	}
	if (NULL == list->head_) {
		return NULL;        // kErrorCode_NullListPointer
	}
	return list->head_->ops_->data(list->head_);
}

void* LIST_last(List* list) {
	if (NULL == list) {
		return NULL;        // kErrorCode_NullListPointer
	}
	if (NULL == list->tail_) {
		return NULL;        // kErrorCode_NullListPointer
	}
	return list->tail_->ops_->data(list->tail_);
}

void* LIST_at(List* list, u16 position) {
	if (NULL == list) {
		return NULL;        // kErrorCode_NullListPointer
	}
	if (NULL == list->head_) {
		return NULL;        // kErrorCode_NullListPointer
	}
	if (position >= list->ops_->length(list)) {
		return NULL;        // kErrorCode_InvalidValue;
	}
	if (position < 1) {
		return list->ops_->first(list);
	}
	if (position == (list->ops_->length(list) - 1)) {
		return list->ops_->last(list);
	}
	MemoryNode* tmp_node = list->head_;
	for (u16 i = 0; i < position; i++)
	{
		tmp_node = tmp_node->ops_->getNext(tmp_node);
	}
	if (NULL == tmp_node) {
		return NULL;        // kErrorCode_NullListPointer
	}
	return tmp_node->ops_->data(tmp_node);
}

s16 LIST_insertFirst(List* list, void* data, u16 bytes) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (NULL == data) {
		return kErrorCode_NullMemoryNode;
	}
	if (list->ops_->isFull(list)) {
		return kErrorCode_InsertionFailed;
	}
	MemoryNode* new_node = MEMNODE_create();
	if (new_node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_NullMemoryNode;
	}
	MEMNODE_createLite(new_node);
	new_node->ops_->setData(new_node, data, bytes);
	if (NULL == new_node->ops_->data(new_node)) {
		return kErrorCode_InsertionFailed;
	}
	if (list->head_ == NULL) {
		list->tail_ = new_node;
	}
	else {
		new_node->ops_->setNext(new_node, list->head_);
	}
	list->head_ = new_node;
	list->length_++;
	return kErrorCode_Ok;
}

s16 LIST_insertLast(List* list, void* data, u16 bytes) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (NULL == data) {
		return kErrorCode_NullMemoryNode;
	}
	if (0 == bytes) {
		return kErrorCode_InvalidValue;
	}
	if (list->ops_->isFull(list)) {
		return kErrorCode_InsertionFailed;
	}
	if (list->ops_->isEmpty(list)) {
		list->ops_->insertFirst(list, data, bytes);
		return kErrorCode_Ok;
	}
	if (NULL == list->tail_) {
		return kErrorCode_NullDoubleLPointer;
	}
	// creo el nuevo nodo
 MemoryNode* new_node = MEMNODE_create();
	if (new_node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_NullMemoryNode;
	}
	MEMNODE_createLite(new_node);
	new_node->ops_->setData(new_node, data, bytes);
	if (NULL == new_node->ops_->data(new_node)) {
		return kErrorCode_InsertionFailed;
	}
	// el nuevo nodo apuntará a NULL
	new_node->ops_->setNext(new_node, list->tail_->ops_->getNext(list->tail_));
	list->tail_->ops_->setNext(list->tail_, new_node);
	list->tail_ = new_node;
	list->length_++;
	return kErrorCode_Ok;
}


s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (NULL == data) {
		return kErrorCode_NullMemoryNode;
	}
	if (list->ops_->isFull(list)) {
		return kErrorCode_InsertionFailed;
	}
	if (position > (list->ops_->length(list)-1)) {
		list->ops_->insertLast(list, data, bytes);
		return kErrorCode_Ok;
	}
	if (list->ops_->length(list) == 0 || position == 0) {
		list->ops_->insertFirst(list, data, bytes);
		return kErrorCode_Ok;
	}
	if (NULL == list->head_ || NULL == list->tail_) {
		return kErrorCode_NullDoubleLPointer;
	}
	MemoryNode* tmp_node = list->head_;
	// percorro los MemoryNodes hasta lo de antes que vamos a desplazar
	for (u16 i = 1; (i < position); i++)
	{
		tmp_node = tmp_node->ops_->getNext(tmp_node);
	}
	// creo el nuevo nodo
	MemoryNode* new_node = MEMNODE_create();

	if (new_node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_NullMemoryNode;
	}
	MEMNODE_createLite(new_node);
	new_node->ops_->setData(new_node, data, bytes);
	if (NULL == new_node->ops_->data(new_node)) {
		return kErrorCode_InsertionFailed;
	}
	new_node->ops_->setNext(new_node, tmp_node->ops_->getNext(tmp_node));
	tmp_node->ops_->setNext(tmp_node, new_node);
	list->length_++;
	return kErrorCode_Ok;
}

void* LIST_extractFirst(List* list) {
	if (NULL == list) {
		return NULL;
	}
	if (list->ops_->isEmpty(list)) {
		return NULL;
	}
	if (NULL == list->head_) {
		return NULL;
	}
	// save the data_ of the first node in the list
	void* tmp_data = list->head_->ops_->data(list->head_);
	MemoryNode* tmp_node = list->head_;
	list->head_ = list->head_->ops_->getNext(list->head_);
	if (list->head_ == NULL) {
		list->tail_ = NULL;
	}
	tmp_node->ops_->softFree(tmp_node);
	list->length_--;
	return tmp_data;
}

void* LIST_extractLast(List* list) {
	if (NULL == list) {
		return NULL;
	}
	if (list->ops_->isEmpty(list)) {
		return NULL;
	}
	if (NULL == list->head_ || NULL == list->tail_){
		return NULL;
	}
	if (list->ops_->length(list) <= 1) {
		return list->ops_->extractFirst(list);
	}
	// copio el último data que voy a devolver
	void* tmp_data = list->tail_->ops_->data(list->tail_);
	// apunto al primero y repercorro toda la lista hasta el penúltimo
	MemoryNode* tmp_node = list->head_;
	for (u16 i = 1; i < list->ops_->length(list) - 1; i++)
	{
		tmp_node = tmp_node->ops_->getNext(tmp_node);
	}
	// tail ahora apunta al penúltimo
	list->tail_ = tmp_node;
	tmp_node = tmp_node->ops_->getNext(tmp_node);
	tmp_node->ops_->softFree(tmp_node);
	list->tail_->ops_->setNext(list->tail_, NULL);
	list->length_--;
	return tmp_data;
}

void* LIST_extractAt(List* list, u16 position) {
	if (NULL == list) {
		return NULL;
	}
	if (list->ops_->isEmpty(list)) {
		return NULL;
	}
	if (list->head_ == NULL) {
		return NULL;
	}
	if (position >= list->ops_->length(list)) {
		return NULL;
	}
	if (position == 0) {
		return list->ops_->extractFirst(list);
	}
	if (position == (list->ops_->length(list)-1)) {
		return list->ops_->extractLast(list);
	}
	MemoryNode* tmp_node = list->head_;
	MemoryNode* tmp_next = tmp_node->ops_->getNext(tmp_node);
	for (u16 i = 1; i < position; ++i) {
		tmp_node = tmp_node->ops_->getNext(tmp_node);
		tmp_next = tmp_next->ops_->getNext(tmp_next);
	}
	void* tmp_data = tmp_next->ops_->data(tmp_next);
	tmp_node->ops_->setNext(tmp_node, tmp_next->ops_->getNext(tmp_next));
	tmp_next->ops_->softFree(tmp_next);
	list->length_--;
	return tmp_data;
}

s16 LIST_concat(List* list, List* list_src) {
	if (NULL == list || NULL == list_src) {
		return kErrorCode_NullMemoryNode;
	}
	if (list_src->ops_->isEmpty(list_src)) {
		// if the second list is empty I add the capacity and exit
		list->capacity_ += list_src->ops_->capacity(list_src);
		list->length_ += list_src->ops_->length(list_src);
		return kErrorCode_Ok;
	}
	if (NULL == list_src->head_) {
		return kErrorCode_NullDoubleLPointer;
	}
	// I copy and run through the new node
	MemoryNode* tmp_node = MEMNODE_create();
 if (tmp_node == NULL) {
#ifdef VERBOSE_
   printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
   return kErrorCode_NullMemoryNode;
 }
 MEMNODE_createLite(tmp_node);
	// I create a node that points to the head_
	MemoryNode* head_node = tmp_node;
 int i = 0;
	for (MemoryNode* node = list_src->head_; node != NULL; node = node->ops_->getNext(node)) {
		tmp_node->ops_->memCopy(tmp_node, node->ops_->data(node), node->ops_->size(node));
		if (NULL != node->ops_->getNext(node)) {
			tmp_node->ops_->setNext(tmp_node, MEMNODE_create());
			tmp_node = tmp_node->ops_->getNext(tmp_node);
		}
  ++i;
	}
	if (list->ops_->isEmpty(list)) {
		// If the first is empty I change the head_
		list->head_ = head_node;
	}
	else {
		// I add it to the next_ of the tail_
		list->tail_->ops_->setNext(list->tail_, head_node);
	}
	list->capacity_ += list_src->ops_->capacity(list_src);
	list->length_ += list_src->ops_->length(list_src);
	list->tail_ = tmp_node;
	return kErrorCode_Ok;
}


s16 LIST_traverse(List* list, void(*callback)(MemoryNode*)) {
	if (list == NULL) {
		return kErrorCode_NullListPointer;
	}
	if (list->head_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}
	MemoryNode* tmp = list->head_;
	for (u16 i = 0; i < list->ops_->length(list); i++)
	{
		callback(tmp);
		tmp = tmp->next_;
	}

	return kErrorCode_Ok;
}

void LIST_print(List* list) {
	printf("	[List Info] Address: ");
	if (NULL == list) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", list);
	printf("	[List Info] Length: %d\n", list->length_);
	printf("	[List Info] Capacity: %d\n", list->capacity_);
	printf("	[List Info] First address: ");
	if (NULL == list->head_) {
		printf(" NULL\n");
	}
	else {
		printf("%p\n", list->head_);
	}

	printf("	[List Info] Last address: ");
	if (NULL == list->tail_) {
		printf(" NULL\n");
	}
	else {
		printf("%p\n", list->tail_);
	}

	MemoryNode* otherNode = list->head_;
	if (NULL == otherNode) {
		printf("\n");
		return;
	}
	u16 listLenght = list->ops_->length(list);
	for (u16 i = 0; i < listLenght; ++i) {
		if (NULL == otherNode) {
			otherNode = NULL;
			printf("\n");
			return;
		}
		printf("		[List Info] Storage #%d\n", i);
		otherNode->ops_->print(otherNode);
		otherNode = otherNode->ops_->getNext(otherNode);
	}
	otherNode = NULL;
	printf("\n");
}
