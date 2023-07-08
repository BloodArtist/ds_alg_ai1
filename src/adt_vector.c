#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_vector.h"


#include "ABGS_MemoryManager/abgs_memory_manager.h"

//Vector Declarations
static s16 VECTOR_destroy(Vector* vector);            
static s16 VECTOR_softReset(Vector* vector);          
static s16 VECTOR_reset(Vector* vector);              
static s16 VECTOR_resize(Vector* vector, u16 new_size)
static u16 VECTOR_capacity(Vector* vector);           
static u16 VECTOR_length(Vector* vector);             
static bool VECTOR_isEmpty(Vector* vector);
static bool VECTOR_isFull(Vector* vector);
static void* VECTOR_first(Vector* vector);
static void* VECTOR_last(Vector* vector); /
static void* VECTOR_at(Vector* vector, u16 position);  
static s16 VECTOR_insertFirst(Vector* vector, void* data, u16 bytes);           
static s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes);            
static s16 VECTOR_insertAt(Vector* vector, void* data, u16 bytes, u16 position);
static void* VECTOR_extractFirst(Vector* vector);             
static void* VECTOR_extractLast(Vector* vector);              
static void* VECTOR_extractAt(Vector* vector, u16 position);  
static s16 VECTOR_concat(Vector* vector, Vector* vector_src); 
static s16 VECTOR_traverse(Vector* vector, void(*callback)(MemoryNode*)); 
static void VECTOR_print(Vector* vector);

struct vector_ops_s vector_ops = { .destroy = VECTOR_destroy,
								  .softReset = VECTOR_softReset,
								  .reset = VECTOR_reset,
								  .resize = VECTOR_resize,
								  .capacity = VECTOR_capacity,
								  .length = VECTOR_length,
								  .isEmpty = VECTOR_isEmpty,
								  .isFull = VECTOR_isFull,
								  .first = VECTOR_first,
								  .last = VECTOR_last,
								  .at = VECTOR_at,
								  .insertFirst = VECTOR_insertFirst,
								  .insertLast = VECTOR_insertLast,
								  .insertAt = VECTOR_insertAt,
								  .extractFirst = VECTOR_extractFirst,
								  .extractLast = VECTOR_extractLast,
								  .extractAt = VECTOR_extractAt,
								  .concat = VECTOR_concat,
								  .traverse = VECTOR_traverse,
								  .print = VECTOR_print

};

Vector* VECTOR_create(u16 capacity) {
	if (0 == capacity) {
		return NULL;
	}
	Vector* new_vector = (Vector*)MM->malloc(sizeof(Vector));
	if (NULL == new_vector) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	MemoryNode* node = (MemoryNode*)MM->malloc(sizeof(MemoryNode) * capacity);
	if (NULL == node) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
  MM->free(new_vector);
		return NULL;
	}
	new_vector->storage_ = node;
	new_vector->head_ = 0;
	new_vector->tail_ = 0;
	new_vector->capacity_ = capacity;
	new_vector->ops_ = &vector_ops;
	for (u16 i = 0; i < capacity; ++i) {
		MEMNODE_createLite(&new_vector->storage_[i]);
	}
	return new_vector;
}

s16 VECTOR_destroy(Vector* vector) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL != vector->storage_) {
		for (u16 i = 0; i < vector->ops_->capacity(vector); ++i) {
			vector->storage_->ops_->reset(&vector->storage_[i]);
		}
		MM->free(vector->storage_);
	}
	MM->free(vector);

	return kErrorCode_Ok;
}

s16 VECTOR_softReset(Vector* vector) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < vector->ops_->length(vector); ++i) {
		vector->storage_[i].ops_->softReset(&vector->storage_[i]);
	}
	vector->tail_ = 0;
	return kErrorCode_Ok;
}

s16 VECTOR_reset(Vector* vector) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < vector->tail_; ++i) {
		vector->storage_[i].ops_->reset(&vector->storage_[i]);
	}
	vector->tail_ = 0;
	return kErrorCode_Ok;
}

/* START DIABOLIK DEVELOPMENT */
s16 VECTOR_resize(Vector* vector, u16 new_size) {
	// parameter control
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	if (0 == new_size) {
		return kErrorCode_InvalidValue;
	}
	if (new_size == vector->ops_->capacity(vector)) {
		return kErrorCode_Ok;
	}
	// new node and reserved memory check
	MemoryNode* node = (MemoryNode*)MM->malloc(sizeof(MemoryNode) * new_size);
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_NullMemoryAllocation;
	}
	//data copied to the new node
	for (u16 i = 0; i < new_size; ++i) {
		if (i < vector->ops_->length(vector)) {
			*(node + i) = vector->storage_[i];
		}
		else {
			MEMNODE_createLite(&*(node + i));
		}
	}
	// free excess data
	if (vector->ops_->length(vector) > new_size) {
		for (u16 i = new_size; i < vector->ops_->length(vector); ++i) {
			vector->storage_[i].ops_->reset(&vector->storage_[i]);
		}
		vector->tail_ = new_size;
	}

	vector->capacity_ = new_size;
	MM->free(vector->storage_);
	vector->storage_ = node;
	return kErrorCode_Ok;
}

u16 VECTOR_capacity(Vector* vector) {
	if (NULL == vector) {
		return 0;
	}
	return vector->capacity_;
}

u16 VECTOR_length(Vector* vector) {
	if (NULL == vector) {
		return 0;
	}
	return vector->tail_;
}

bool VECTOR_isEmpty(Vector* vector) {
	if (vector != NULL) {
		return vector->ops_->length(vector) == 0;
	}
	else {
		return false;
	}
}

bool VECTOR_isFull(Vector* vector) {
	if (NULL != vector) {
		return vector->ops_->capacity(vector) == vector->ops_->length(vector);
	}
	else {
		return false;
	}
}
//////////////////////////////
void* VECTOR_first(Vector* vector) {
	if (vector == NULL) {
		return NULL;
	}
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (vector->ops_->isEmpty(vector)) {
		return NULL;
	}
	if (vector->storage_[0].ops_->data(&vector->storage_[0]) == NULL) {
		return NULL;
	}
	return vector->storage_[0].ops_->data(&vector->storage_[0]);
}

void* VECTOR_last(Vector* vector) {
	if (vector == NULL) {
		return NULL;
	}
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (vector->ops_->isEmpty(vector)) {
		return NULL;
	}
	if (vector->ops_->length(vector) < 1) {
		return vector->ops_->first(vector);
	}
	u16 i = vector->ops_->length(vector) - 1;
	if (NULL == vector->storage_[i].ops_->data(&vector->storage_[i])) {
		return NULL;
	}
	return vector->storage_[i].ops_->data(&vector->storage_[i]);
}

void* VECTOR_at(Vector* vector, u16 position) {
	if (NULL == vector) {
		return NULL;
	}
	if (NULL == vector->storage_) {
		return NULL;
	}
	if (vector->ops_->isEmpty(vector)) {
		return NULL;
	}
	if (position >= vector->ops_->length(vector)) {
		return vector->ops_->last(vector);
	}
	if (NULL == vector->storage_[position].ops_->data(&vector->storage_[position])) {
		return NULL;
	}
	return vector->storage_[position].ops_->data(&vector->storage_[position]);
}

s16 VECTOR_insertFirst(Vector* vector, void* data, u16 bytes) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (vector->ops_->isFull(vector)) {
		return kErrorCode_InsertionFailed;
	}
	if (NULL == data) {
		return kErrorCode_NullPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = vector->ops_->length(vector); i > 0; --i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i - 1].data_,
			vector->storage_[i - 1].size_);
	}
	vector->storage_[0].ops_->setData(&vector->storage_[0], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (vector->ops_->isFull(vector)) {
		return kErrorCode_InsertionFailed;
	}
	if (NULL == data) {
		return kErrorCode_NullPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	u16 i = vector->ops_->length(vector);
	vector->storage_[i].ops_->setData(&vector->storage_[i], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

s16 VECTOR_insertAt(Vector* vector, void* data, u16 bytes, u16 position) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (vector->ops_->isFull(vector)) {
		return kErrorCode_InsertionFailed;
	}
	if (NULL == data) {
		return kErrorCode_NullPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	if (position > vector->ops_->length(vector)) {
		vector->ops_->insertLast(vector, data, bytes);
		return kErrorCode_Ok;
	}
	for (u16 i = vector->ops_->length(vector); i > position; --i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i - 1].data_,
			vector->storage_[i - 1].size_);

	}
	vector->storage_[position].ops_->setData(&vector->storage_[position], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

void* VECTOR_extractFirst(Vector* vector) {
	if (NULL == vector) {
		return NULL;
	}
	if (vector->ops_->isEmpty(vector)) {
	  return NULL;
	}
	if (NULL == vector->storage_) {
		return NULL;
	}
	if (NULL == vector->storage_[0].ops_->data(&vector->storage_[0])) {
		return NULL;
	}
	void* tmp_data_ = vector->storage_[0].ops_->data(&vector->storage_[0]);
	u16 j = vector->ops_->length(vector) - 1;
	for (u16 i = 0; i < j; ++i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i + 1].ops_->data(&vector->storage_[i + 1]),
			vector->storage_[i + 1].ops_->size(&vector->storage_[i + 1]));
	}
	vector->storage_[j].ops_->softReset(&vector->storage_[j + 1]);
	vector->tail_--;
	return tmp_data_;
}

void* VECTOR_extractLast(Vector* vector) {
	if (NULL == vector) {
		return NULL;
	}
	if (vector->ops_->isEmpty(vector)) {
		return NULL;
	}
	if (NULL == vector->storage_) {
		return NULL;
	}
	u16 i = vector->ops_->length(vector) - 1;
	if (NULL == vector->storage_[i].ops_->data(&vector->storage_[i])) {
		return NULL;
	}
	void* tmp_data = vector->storage_[i].ops_->data(&vector->storage_[i]);
	vector->storage_[i].ops_->softReset(&vector->storage_[i]);
	vector->tail_--;
	return tmp_data;
}


void* VECTOR_extractAt(Vector* vector, u16 position) {
	if (NULL == vector) {
		return NULL;
	}
	if (vector->ops_->isEmpty(vector)) {
		return NULL;
	}
	if (NULL == vector->storage_) {
		return NULL;
	}
	if (NULL == vector->storage_[position].ops_->data(&vector->storage_[position])) {
		return NULL;
	}
	void* tmp_data = vector->storage_[position].ops_->data(&vector->storage_[position]);
	u16 j = vector->ops_->length(vector) - 1;
	for (u16 i = position; i < j; ++i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i + 1].ops_->data(&vector->storage_[i + 1]),
			vector->storage_[i + 1].ops_->size(&vector->storage_[i + 1]));
	}
	vector->storage_[j].ops_->softReset(&vector->storage_[j + 1]);
	vector->tail_--;
	return tmp_data;
}

s16 VECTOR_concat(Vector* vector, Vector* vector_src) {
	// parameter control
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	if (NULL == vector_src) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL == vector_src->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	// change tail vector and capacity
	u16 new_tail = vector->ops_->length(vector) + vector_src->ops_->length(vector_src);
	u16 new_capacity = vector->ops_->capacity(vector) + vector_src->ops_->capacity(vector_src);
	vector->ops_->resize(vector, new_capacity);
	// if the second vector is empty there is nothing to copy
	if (vector_src->ops_->isEmpty(vector_src)) {
		if (vector->ops_->isEmpty(vector)) {
			return kErrorCode_Ok;
		}
		return kErrorCode_Ok;
	}
	// data from the second vector copied to the first
	u16 j = 0;
	for (u16 i = vector->ops_->length(vector); i < new_tail; ++i) {
		vector->storage_->ops_->memCopy(vector->storage_ + i,
			vector_src->storage_[j].ops_->data(vector_src->storage_ + j),
			vector_src->storage_[j].ops_->size(vector_src->storage_ + j));
		j++;
	}
	vector->tail_ = new_tail;
	vector->capacity_ = new_capacity;
	return kErrorCode_Ok;
}

s16 VECTOR_traverse(Vector* vector, void(*callback)(MemoryNode*)) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	if (NULL == vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < vector->tail_; ++i) {
		callback(&vector->storage_[i]);
	}
	return kErrorCode_Ok;
}

void VECTOR_print(Vector* vector) {
	printf("	[Vector Info] Address: ");
	if (NULL == vector) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", vector);
	printf("	[Vector Info] Head: %d\n", vector->head_);
	printf("	[Vector Info] Tail: %d\n", vector->tail_);
	printf("	[Vector Info] Length: %d\n", vector->tail_);
	printf("	[Vector Info] Capacity: %d\n", vector->capacity_);

	printf("	[Vector Info] Address: ");
	if (NULL == vector->storage_) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", vector->storage_);

	for (int i = 0; i < vector->tail_; ++i) {
		printf("	[Vector Info] Storage #%d\n", i);
		vector->storage_->ops_->print(&vector->storage_[i]);
	}
	printf("\n");
}