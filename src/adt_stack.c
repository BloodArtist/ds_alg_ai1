#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_stack.h"


#include "ABGS_MemoryManager/abgs_memory_manager.h"

//Stack Declarations
static s16 STACK_destroy(Stack* stack);
static s16 STACK_softReset(Stack* stack);
static s16 STACK_reset(Stack* stack);
static s16 STACK_resize(Stack* stack, u16 new_size);
static u16 STACK_capacity(Stack* stack);
static u16 STACK_length(Stack* stack);
static bool STACK_isEmpty(Stack* stack);
static bool STACK_isFull(Stack* stack);
static void* STACK_top(Stack* stack);
static s16 STACK_push(Stack* stack, void* data, u16 bytes);
static void* STACK_pop(Stack* stack);
static s16 STACK_concat(Stack* stack, Stack* stack_src);
static void STACK_print(Stack* stack);

struct stack_ops_s stack_ops = { .destroy = STACK_destroy,
								  .softReset = STACK_softReset,
								  .reset = STACK_reset,
								  .resize = STACK_resize,
								  .capacity = STACK_capacity,
								  .length = STACK_length,
								  .isEmpty = STACK_isEmpty,
								  .isFull = STACK_isFull,
								  .top = STACK_top,
								  .push = STACK_push,
								  .pop = STACK_pop,
								  .concat = STACK_concat,
								  .print = STACK_print

};

Stack* STACK_create(u16 capacity) {
	if (capacity == 0) {
		return NULL;
	}
	Stack* new_stack = (Stack*)MM->malloc(sizeof(Stack));
	if (NULL == new_stack) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	Vector* vector = VECTOR_create(capacity);
	if (vector == NULL) {
		MM->free(new_stack);
		return NULL;
	}
	new_stack->storage_ = vector;
	new_stack->ops_ = &stack_ops;

	return new_stack;
}

s16 STACK_destroy(Stack* stack) {
	if (NULL == stack) {
		return kErrorCode_NullStackPointer;
	}
	if (NULL != stack->storage_) {
		stack->storage_->ops_->destroy(stack->storage_);
	}
	MM->free(stack);

	return kErrorCode_Ok;
}

s16 STACK_softReset(Stack* stack) {
	if (stack == NULL) {
		return kErrorCode_NullStackPointer;
	}
	if (NULL == stack->storage_) {
		return kErrorCode_NullVectorPointer;
	}
	stack->storage_->ops_->softReset(stack->storage_);
	return kErrorCode_Ok;
}

s16 STACK_reset(Stack* stack) {
	if (stack == NULL) {
		return kErrorCode_NullStackPointer;
	}
	if (stack->storage_ == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	stack->storage_->ops_->reset(stack->storage_);

	return kErrorCode_Ok;
}


s16 STACK_resize(Stack* stack, u16 new_size) {

	if (NULL == stack) {
		return kErrorCode_NullStackPointer;
	}
	if (NULL == stack->storage_) {
		return kErrorCode_NullVectorPointer;
	}
	if (0 == new_size) {
		return kErrorCode_InvalidValue;
	}
	if (stack->ops_->capacity(stack) == new_size) {
		return kErrorCode_Ok;
	}
	stack->storage_->ops_->resize(stack->storage_, new_size);

	return kErrorCode_Ok;
}

u16 STACK_capacity(Stack* stack) {
	if (NULL == stack) {
		return 0;  // kErrorCode_NullStackPointer
	}
	if (NULL == stack->storage_) {
		return 0;
	}
	return stack->storage_->ops_->capacity(stack->storage_);
}

u16 STACK_length(Stack* stack) {
	if (NULL == stack) {
		return  0;  //kErrorCode_NullStackPointer
	}
	if (NULL == stack->storage_) {
		return 0;
	}
	return stack->storage_->ops_->length(stack->storage_);
}

bool STACK_isEmpty(Stack* stack) {
	if (NULL != stack) {
		if (NULL == stack->storage_) {
			return false;
		}
		return stack->storage_->ops_->isEmpty(stack->storage_);
	}
	return false;
}

bool STACK_isFull(Stack* stack) {
	if (NULL != stack) {
		if (NULL == stack->storage_) {
			return false;
		}
		return stack->storage_->ops_->isFull(stack->storage_);
	}
	return false;
}

void * STACK_top(Stack * stack) {
	if (NULL == stack) {
		return NULL;
	}
	if (NULL == stack->storage_) {
		return NULL;
	}
	return stack->storage_->ops_->last(stack->storage_);
}

s16 STACK_push(Stack* stack, void* data, u16 bytes) {
	if (NULL == stack) {
		return kErrorCode_NullStackPointer;
	}
	if (NULL == stack->storage_) {
		return kErrorCode_NullVectorPointer;
	}
	if (stack->storage_->ops_->isFull(stack->storage_)) {
		return kErrorCode_InsertionFailed;
	}
	if (NULL == data) {
		return kErrorCode_NullPointer;
	}
	if (0 == bytes) {
		return kErrorCode_InvalidValue;
	}
	return stack->storage_->ops_->insertLast(stack->storage_, data, bytes);
}

void* STACK_pop(Stack* stack) {
	if (stack == NULL) {
		return NULL;
	}
	if (stack->ops_ == NULL) {
		return NULL;
	}
	if (stack->ops_->isEmpty(stack)) {
		return NULL;
	}
	if (stack->storage_ == NULL) {
		return NULL;
	}

	return stack->storage_->ops_->extractLast(stack->storage_);
}

s16 STACK_concat(Stack * stack, Stack * stack_src)
{
	if (stack == NULL) {
		return kErrorCode_NullStackPointer;
	}
	if (stack_src == NULL) {
		return kErrorCode_NullStackPointer;
	}
	if (stack->storage_ == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	if (stack_src->storage_ == NULL) {
		return kErrorCode_NullVectorPointer;
	}
	s16 result = stack->storage_->ops_->concat(stack->storage_, stack_src->storage_);

	return result;
}

void STACK_print(Stack* stack) {
	printf("	[Stack Info] Address: ");
	if (NULL == stack) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", stack);
	printf("	[Stack Info] Storage Address: ");
	if (NULL == stack) {
		printf(" NULL\n");
		return;
	}
	printf("%p\n", stack->storage_);

	stack->storage_->ops_->print(stack->storage_);
}