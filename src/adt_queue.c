#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_queue.h"


#include "ABGS_MemoryManager/abgs_memory_manager.h"

//Queue Declarations
static s16 QUEUE_destroy(Queue* queue);
static s16 QUEUE_reset(Queue* queue);
static s16 QUEUE_resize(Queue* queue, u16 new_size);
static u16 QUEUE_capacity(Queue* queue);
static u16 QUEUE_length(Queue* queue);
static bool QUEUE_isEmpty(Queue* queue);
static bool QUEUE_isFull(Queue* queue);
static void* QUEUE_front(Queue* queue);
static void* QUEUE_back(Queue* queue);
static s16 QUEUE_enqueue(Queue* queue, void* data, u16 bytes);
static void* QUEUE_dequeue(Queue* queue, u16 position);
static s16 QUEUE_concat(Queue* queue, Queue* queue_src);
static void QUEUE_print(Queue* queue);

struct queue_ops_s queue_ops = { .destroy = QUEUE_destroy,
								  .reset = QUEUE_reset,
								  .resize = QUEUE_resize,
								  .capacity = QUEUE_capacity,
								  .length = QUEUE_length,
								  .isEmpty = QUEUE_isEmpty,
								  .isFull = QUEUE_isFull,
								  .front = QUEUE_front,
								  .back = QUEUE_back,
								  .enqueue = QUEUE_enqueue,
								  .dequeue = QUEUE_dequeue,
								  .concat = QUEUE_concat,
								  .print = QUEUE_print
};

Queue* QUEUE_create(u16 capacity) {
	if (capacity == 0) {
		return NULL;
	}
	Queue* new_queue = (Queue*)MM->malloc(sizeof(Queue));
	if (NULL == new_queue) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	List* list = LIST_create(capacity);
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
		MM->free(new_queue);
#endif
		return NULL;
	}
	new_queue->storage_ = list;
	new_queue->ops_ = &queue_ops;

	return new_queue;
}

s16 QUEUE_destroy(Queue* queue) {
	if (NULL == queue) {
		return kErrorCode_NullQueuePointer;
	}
	if (NULL != queue->storage_) {
		queue->storage_->ops_->destroy(queue->storage_);
	}
	MM->free(queue);

	return kErrorCode_Ok;
}

s16 QUEUE_reset(Queue* queue) {
	if (NULL == queue) {
		return kErrorCode_NullQueuePointer;
	}
	if (NULL == queue->storage_) {
		return kErrorCode_NullListPointer;
	}
	queue->storage_->ops_->reset(queue->storage_);

	return kErrorCode_Ok;
}

s16 QUEUE_resize(Queue* queue, u16 new_size) {
	// parameter control
	if (NULL == queue) {
		return kErrorCode_NullQueuePointer;
	}
	if (NULL == queue->storage_) {
		return kErrorCode_NullListPointer;
	}
	if (0 == new_size) {
		return kErrorCode_InvalidValue;
	}
	if (queue->ops_->capacity(queue) == new_size) {
		return kErrorCode_Ok;
	}
	queue->storage_->ops_->resize(queue->storage_, new_size);

	return kErrorCode_Ok;
}

u16 QUEUE_capacity(Queue* queue) {
	if (NULL == queue) {
		return 0;  // kErrorCode_NullStackPointer
	}
 if (NULL == queue->storage_) {
   return 0;  // kErrorCode_NullListPointer
 }
	return queue->storage_->ops_->capacity(queue->storage_);
}

u16 QUEUE_length(Queue* queue) {
	if (NULL == queue) {
		return  0;  //kErrorCode_NullStackPointer
	}
 if (NULL == queue->storage_) {
   return 0;  // kErrorCode_NullListPointer
 }
	return queue->storage_->ops_->length(queue->storage_);
}

bool QUEUE_isEmpty(Queue* queue) {
	if (NULL == queue) {
		return false;
	}
	if (queue->storage_ == NULL) {
		return false;
	}
	return queue->storage_->ops_->isEmpty(queue->storage_);
}

bool QUEUE_isFull(Queue* queue) {
	if (NULL == queue) {
		return false;
	}
 if (queue->storage_ == NULL) {
   return false;
 }
	return queue->storage_->ops_->isFull(queue->storage_);
}

void* QUEUE_front(Queue* queue) {
	if (NULL == queue) {
		return NULL;
	}
	if (NULL == queue->storage_) {
		return NULL;
	}
	return queue->storage_->ops_->first(queue->storage_);
}

void* QUEUE_back(Queue* queue) {
	if (NULL == queue) {
		return NULL;
	}
	if (NULL == queue->storage_) {
		return NULL;
	}
	return queue->storage_->ops_->last(queue->storage_);
}

s16 QUEUE_enqueue(Queue* queue, void* data, u16 bytes) {
	if (NULL == queue) {
		return kErrorCode_NullQueuePointer;
	}
	if (NULL == queue->storage_) {
		return kErrorCode_NullListPointer;
	}
	if (NULL == data) {
		return kErrorCode_NullPointer;
	}
	if (0 == bytes) {
		return kErrorCode_InvalidValue;
	}
	return queue->storage_->ops_->insertLast(queue->storage_, data, bytes);
}

void* QUEUE_dequeue(Queue* queue, u16 position) {
	if (NULL == queue) {
		return NULL;
	}
	if (NULL == queue->storage_) {
		return NULL;
	}
	if (queue->ops_->isEmpty(queue)) {
		return NULL;
	}
	return queue->storage_->ops_->extractFirst(queue->storage_);
}

s16 QUEUE_concat(Queue* queue, Queue* queue_src) {
	if (NULL == queue) {
		return kErrorCode_NullQueuePointer;
	}
	if (NULL == queue->storage_) {
		return kErrorCode_NullListPointer;
	}
	if (NULL == queue_src) {
		return kErrorCode_NullQueuePointer;
	}
	if (NULL == queue_src->storage_) {
		return kErrorCode_NullListPointer;
	}
	return queue->storage_->ops_->concat(queue->storage_, queue_src->storage_);
}

void QUEUE_print(Queue* queue) {
	printf("	[Queue Info] Address: ");
	if (NULL == queue) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", queue);


	printf("	[Queue Info] Storage address: ");
	if (NULL == queue->storage_) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", queue->storage_);
	queue->storage_->ops_->print(queue->storage_);
}