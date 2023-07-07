#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_movable_head_vector.h"


#include "ABGS_MemoryManager/abgs_memory_manager.h"

//MovableHeadVector Declarations
static s16 MOVABLE_HEAD_VECTOR_destroy(MovableHeadVector* vector);            //Yossef
static s16 MOVABLE_HEAD_VECTOR_softReset(MovableHeadVector* vector);          //  "
static s16 MOVABLE_HEAD_VECTOR_reset(MovableHeadVector* vector);              //  "
static s16 MOVABLE_HEAD_VECTOR_resize(MovableHeadVector* vector, u16 new_size);//Davide
static s16 MOVABLE_HEAD_VECTOR_capacity(MovableHeadVector* vector);            // "
static s16 MOVABLE_HEAD_VECTOR_length(MovableHeadVector* vector);              //  "
static bool MOVABLE_HEAD_VECTOR_isEmpty(MovableHeadVector* vector);//Terminada
static bool MOVABLE_HEAD_VECTOR_isFull(MovableHeadVector* vector);//Terminada
static void* MOVABLE_HEAD_VECTOR_first(MovableHeadVector* vector);//Yossef
static void* MOVABLE_HEAD_VECTOR_last(MovableHeadVector* vector); //  "
static void* MOVABLE_HEAD_VECTOR_at(MovableHeadVector* vector, u16 position);   //  "
static s16 MOVABLE_HEAD_VECTOR_insertFirst(MovableHeadVector* vector, void* data, u16 bytes);           //Yossef
static s16 MOVABLE_HEAD_VECTOR_insertLast(MovableHeadVector* vector, void* data, u16 bytes);            //  "
static s16 MOVABLE_HEAD_VECTOR_insertAt(MovableHeadVector* vector, void* data, u16 bytes, u16 position);//  "
static void* MOVABLE_HEAD_VECTOR_extractFirst(MovableHeadVector* vector);             //Davide
static void* MOVABLE_HEAD_VECTOR_extractLast(MovableHeadVector* vector);              //  "
static void* MOVABLE_HEAD_VECTOR_extractAt(MovableHeadVector* vector, u16 position);  //  "
static s16 MOVABLE_HEAD_VECTOR_concat(MovableHeadVector* vector, MovableHeadVector* vector_src); //  "
static s16 MOVABLE_HEAD_VECTOR_traverse(MovableHeadVector* vector, void(*callback)(MemoryNode*)); //Yossef
static void MOVABLE_HEAD_VECTOR_print(MovableHeadVector* vector);//Davide

struct circular_vector_ops_s vector_ops = { .destroy = MOVABLE_HEAD_VECTOR_destroy,
								  .softReset = MOVABLE_HEAD_VECTOR_softReset,
								  .reset = MOVABLE_HEAD_VECTOR_reset,
								  .resize = MOVABLE_HEAD_VECTOR_resize,
								  .capacity = MOVABLE_HEAD_VECTOR_capacity,
								  .length = MOVABLE_HEAD_VECTOR_length,
								  .isEmpty = MOVABLE_HEAD_VECTOR_isEmpty,
								  .isFull = MOVABLE_HEAD_VECTOR_isFull,
								  .first = MOVABLE_HEAD_VECTOR_first,
								  .last = MOVABLE_HEAD_VECTOR_last,
								  .at = MOVABLE_HEAD_VECTOR_at,
								  .insertFirst = MOVABLE_HEAD_VECTOR_insertFirst,
								  .insertLast = MOVABLE_HEAD_VECTOR_insertLast,
								  .insertAt = MOVABLE_HEAD_VECTOR_insertAt,
								  .extractFirst = MOVABLE_HEAD_VECTOR_extractFirst,
								  .extractLast = MOVABLE_HEAD_VECTOR_extractLast,
								  .extractAt = MOVABLE_HEAD_VECTOR_extractAt,
								  .concat = MOVABLE_HEAD_VECTOR_concat,
								  .traverse = MOVABLE_HEAD_VECTOR_traverse,
								  .print = MOVABLE_HEAD_VECTOR_print

};

CircularVector* MOVABLE_HEAD_VECTOR_create(u16 capacity) {
	if (capacity == 0) {
		return NULL;
	}
 MovableHeadVector* new_vector = (MovableHeadVector*)MM->malloc(sizeof(MovableHeadVector));
	if (NULL == new_vector) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	MemoryNode* node = (MemoryNode*)MM->malloc(sizeof(MemoryNode) * capacity);
	if (node == NULL) {
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

s16 MOVABLE_HEAD_VECTOR_destroy(MovableHeadVector* vector) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}

	if (vector->storage_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < MOVABLE_HEAD_VECTOR_capacity(vector); ++i) {
		vector->storage_->ops_->reset(&vector->storage_[i]);
	}

	MM->free(vector->storage_);
	MM->free(vector);

	return kErrorCode_Ok;
}

s16 MOVABLE_HEAD_VECTOR_softReset(MovableHeadVector* vector) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	if (vector->storage_) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < vector->ops_->length(vector); ++i) {
		vector->storage_[i].ops_->softReset(&vector->storage_[i]);
	}
	return kErrorCode_Ok;
}

u16 MOVABLE_HEAD_VECTOR_reset(MovableHeadVector* vector) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	if (vector->storage_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < vector->tail_; ++i) {
		vector->storage_[i].ops_->softReset(&vector->storage_[i]);
	}
	vector->tail_ = 0;

	return kErrorCode_Ok;
}

/* START DIABOLIK DEVELOPMENT */
s16 MOVABLE_HEAD_VECTOR_resize(MovableHeadVector* vector, u16 new_size) {
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

s16 MOVABLE_HEAD_VECTOR_capacity(MovableHeadVector* vector) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	return vector->capacity_;
}

s16 MOVABLE_HEAD_VECTOR_length(MovableHeadVector* vector) {
	if (NULL == vector) {
		return kErrorCode_NullVectorPointer;
	}
	return vector->tail_;
}

bool MOVABLE_HEAD_VECTOR_isEmpty(MovableHeadVector* vector) {
	if (vector != NULL) {
		return vector->tail_ == 0;
	}
}

bool MOVABLE_HEAD_VECTOR_isFull(MovableHeadVector* vector) {
	if (NULL != vector) {
		return MOVABLE_HEAD_VECTOR_capacity(vector) == MOVABLE_HEAD_VECTOR_length(vector);
	}
}
//////////////////////////////
void* MOVABLE_HEAD_VECTOR_first(MovableHeadVector* vector) {
	if (vector == NULL) {
		return NULL;
	}
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (vector->storage_[0].ops_->data(&vector->storage_[0]) == NULL) {
		return NULL;
	}
	return vector->storage_[0].ops_->data(&vector->storage_[0]);
}

void* MOVABLE_HEAD_VECTOR_last(MovableHeadVector* vector) {
	if (vector == NULL) {
		return NULL;
	}
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (VECTOR_length(vector) < 1) {
		return NULL;
	}
	u16 i = MOVABLE_HEAD_VECTOR_length(vector) - 1;
	if (vector->storage_[i].ops_->data(&vector->storage_[i]) == NULL) {
		return NULL;
	}
	return vector->storage_[i].ops_->data(&vector->storage_[i]);

}

void* MOVABLE_HEAD_VECTOR_at(MovableHeadVector* vector, u16 position) {
	if (vector == NULL) {
		return NULL;
	}
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (vector->storage_[position].ops_->data(&vector->storage_[position]) == NULL) {
		return NULL;
	}
	if (position >= MOVABLE_HEAD_VECTOR_length(vector)) {
		return NULL;
	}
	return vector->storage_[position].ops_->data(&vector->storage_[position]);
}

s16 MOVABLE_HEAD_VECTOR_insertFirst(MovableHeadVector* vector, void* data, u16 bytes) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	if (MOVABLE_HEAD_VECTOR_isFull(vector)) {
		return kErrorCode_InsertionFailed;
	}
	if (data == NULL) {
		return kErrorCode_NullPointer;
	}
	if (vector->storage_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}

	for (u16 i = MOVABLE_HEAD_VECTOR_length(vector); i > 0; --i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i - 1].data_,
			vector->storage_[i - 1].size_);

	}
	vector->storage_[0].ops_->setData(&vector->storage_[0], data, bytes);

	vector->tail_++;
	return kErrorCode_Ok;
}

s16 MOVABLE_HEAD_VECTOR_insertLast(MovableHeadVector* vector, void* data, u16 bytes) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	if (MOVABLE_HEAD_VECTOR_isFull(vector)) {
		return kErrorCode_InsertionFailed;
	}
	if (data == NULL) {
		return kErrorCode_NullPointer;
	}
	if (vector->storage_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}
	u16 i = MOVABLE_HEAD_VECTOR_length(vector);
	vector->storage_[i].ops_->setData(&vector->storage_[i], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

s16 MOVABLE_HEAD_VECTOR_insertAt(MovableHeadVector* vector, void* data, u16 bytes, u16 position) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	if (MOVABLE_HEAD_VECTOR_isFull(vector)) {
		return kErrorCode_InsertionFailed;
	}
	if (data == NULL) {
		return kErrorCode_NullMemoryNode;
	}
	if (vector->storage_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}

	for (u16 i = MOVABLE_HEAD_VECTOR_length(vector); i > position; --i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i - 1].data_,
			vector->storage_[i - 1].size_);

	}
	vector->storage_[position].ops_->setData(&vector->storage_[position], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

void* MOVABLE_HEAD_VECTOR_extractFirst(MovableHeadVector* vector) {
	if (vector == NULL) {
		return NULL;
	}
 if (vector->ops_->isEmpty(&vector)) {
   return NULL;
 }
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (vector->storage_[0].ops_->data(&vector->storage_[0]) == NULL) {
		return NULL;
	}
	void* tmp_data_ = vector->storage_[0].ops_->data(&vector->storage_[0]);
	u16 j = MOVABLE_HEAD_VECTOR_length(vector) - 1;
	for (u16 i = 0; i < j; ++i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i + 1].ops_->data(&vector->storage_[i + 1]),
			vector->storage_[i + 1].ops_->size(&vector->storage_[i + 1]));
	}
	vector->storage_[j + 1].ops_->softReset(&vector->storage_[j + 1]);
	vector->tail_--;
	return tmp_data_;
}

void* MOVABLE_HEAD_VECTOR_extractLast(MovableHeadVector* vector) {
	if (vector == NULL) {
		return NULL;
	}
 if (vector->ops_->isEmpty(&vector)) {
   return NULL;
 }
	if (vector->storage_ == NULL) {
		return NULL;
	}
	u16 i = MOVABLE_HEAD_VECTOR_length(vector) - 1;
	if (vector->storage_[i].ops_->data(&vector->storage_[i]) == NULL) {
		return NULL;
	}
	void* tmp_data = vector->storage_[i].ops_->data(&vector->storage_[i]);

	vector->storage_[i].ops_->softReset(&vector->storage_[i]);
	vector->tail_--;
	return tmp_data;
}


void* MOVABLE_HEAD_VECTOR_extractAt(MovableHeadVector* vector, u16 position) {
	if (vector == NULL) {
		return NULL;
	}
 if (vector->ops_->isEmpty(&vector)) {
   return NULL;
 }
	if (vector->storage_ == NULL) {
		return NULL;
	}
	if (vector->storage_[position].ops_->data(&vector->storage_[position]) == NULL) {
		return NULL;
	}
	void* tmp_data = vector->storage_[position].ops_->data(&vector->storage_[position]);
	u16 j = MOVABLE_HEAD_VECTOR_length(vector) - 1;
	for (u16 i = position; i < j; ++i) {
		vector->storage_[i].ops_->setData(&vector->storage_[i],
			vector->storage_[i + 1].ops_->data(&vector->storage_[i + 1]),
			vector->storage_[i + 1].ops_->size(&vector->storage_[i + 1]));
	}
	vector->storage_[j + 1].ops_->softReset(&vector->storage_[j + 1]);
	vector->tail_--;
	return tmp_data;
}

s16 MOVABLE_HEAD_VECTOR_concat(MovableHeadVector* vector, MovableHeadVector* vector_src) {
  // parameter control
	if (NULL == vector) {
		return kErrorCode_NullMemoryNode;
	}
 if (NULL == vector->storage_) {
   return kErrorCode_NullMemoryNode;
 }
	if (NULL == vector_src) {
		return kErrorCode_NullMemoryNode;
	}
 if (NULL == vector_src->storage_) {
   return kErrorCode_NullMemoryNode;
 }
 // change tail vector and capacity
 u16 new_tail = vector->ops_->length(vector) + vector_src->ops_->length(vector_src);
 u16 new_capacity = vector->ops_->capacity(vector) + vector_src->ops_->capacity(vector_src);
 vector->ops_->resize(vector, new_capacity);
 // if the second vector is empty there is nothing to copy
 if (vector_src->ops_->isEmpty(&vector_src)) {
   if (vector->ops_->isEmpty(&vector)) {
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

s16 MOVABLE_HEAD_VECTOR_traverse(MovableHeadVector* vector, void(*callback)(MemoryNode*)) {
	if (vector == NULL) {
		return kErrorCode_NullVectorPointer;
	}

	if (vector->storage_ == NULL) {
		return kErrorCode_NullMemoryNode;
	}
	for (u16 i = 0; i < vector->tail_; ++i) {
		callback(&vector->storage_[i]);
	}

	return kErrorCode_Ok;
}

void MOVABLE_HEAD_VECTOR_print(MovableHeadVector* vector) {
	printf("	[Vector Info] Address: ");
	if (NULL == vector) {
		return printf(" NULL");
	}
	printf("%p\n", vector);

	printf("	[Vector Info] Head: %d\n", vector->head_);
	printf("	[Vector Info] Tail: %d\n", vector->tail_);
	printf("	[Vector Info] Length: %d\n", vector->tail_);
	printf("	[Vector Info] Capacity: %d\n", vector->capacity_);

	printf("	[Vector Info] Address: ");
	if (NULL == vector->storage_) {
		return printf(" NULL");
	}
	printf("%p\n", vector->storage_);

	for (int i = 0; i < vector->tail_; ++i) {
		printf("	[Vector Info] Storage #%d\n", i);
		vector->storage_->ops_->print(&vector->storage_[i]);
	}
	printf("\n");
}