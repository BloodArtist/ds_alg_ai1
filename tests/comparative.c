// comparative.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// File for comparative of ADTs

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ABGS_MemoryManager/abgs_memory_manager.h"
#include "ABGS_MemoryManager/abgs_platform_types.h"
#include "common_def.h"
#include "adt_vector.h"
#include "adt_list.h"
#include "adt_queue.h"
#include "adt_stack.h"
#include "adt_dllist.h"

const u32 repetitions = 10000;

void* data1[10000];
void* data2[10000];

Vector* vector1;
Vector* vector2;

List* list;
List* list2;
DList* dlist;
Queue* queue;
Stack* stack;

void TESTBASE_generateDataForComparative() {

  for (u16 i = 0; i < repetitions; i++) {
    u8* my_str = MM->malloc(8);
    if (NULL == my_str) {
      printf("Error: [%s] not enough memory available for data 1 i = %d\n", __FUNCTION__, i);
      return;
    }
    sprintf(my_str, "1234");
    data1[i] = my_str;
  }
  for (u16 i = 0; i < repetitions; i++) {
    u8* my_str = MM->malloc(8);
    if (NULL == my_str) {
      printf("Error: [%s] not enough memory available for data 1 i = %d\n", __FUNCTION__, i);
      return;
    }
    sprintf(my_str, "5678");
    data2[i] = my_str;
  }
  vector1 = VECTOR_create(repetitions);
  vector2 = VECTOR_create(repetitions);
  list = LIST_create(repetitions);
  list2 = LIST_create(repetitions);
  dlist = DLIST_create(repetitions);
  queue = QUEUE_create(repetitions);
  stack = STACK_create(repetitions);
}

void TestVector() {
  LARGE_INTEGER frequency;				// ticks per second
  LARGE_INTEGER  time_start, time_end;    // ticks in interval
  double elapsed_time = 0.0f;
  double average_time;
  s16 error_type;

  // Frequency: ticks per second
  QueryPerformanceFrequency(&frequency);
  printf("\n\n\n -----  Start Vector Comparative  -----\n\n");
  /* START TEST */
  // execute function to meassure 'repetitions' times
  printf("\n	Start insertFirst to Vector1 for %d elemenst.", repetitions);
  // Meassurement time - start timer
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    vector1->ops_->insertFirst(vector1, data1[rep], 4);
  }
  // stop timer
  QueryPerformanceCounter(&time_end);
  // compute the elapsed time in microseconds
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nVector1 insert first: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  printf("\n	Start extractLast to Vector1 for %d elemenst.", repetitions);
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    vector1->ops_->extractLast(vector1);
  }

  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector1 extract last: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  u32 random_number = 0;
  printf("\n Start insertAt to Vector1 for %d elemenst.", repetitions);
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    random_number = rand() % repetitions;
    vector1->ops_->insertAt(vector1, data1[rep], 4, random_number);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector1 insert at: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  printf("\n Start extractAt to Vector1 for %d elemenst.", repetitions);
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    random_number = rand() % repetitions;
    vector1->ops_->extractAt(vector1, random_number);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector1 extract at: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  printf("\n Start insertLast to Vector1 for %d elemenst.", repetitions);
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    vector1->ops_->insertLast(vector1, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector1 insert last: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  printf("\n Start extractFirst to Vector1 for %d elemenst.", repetitions);
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    vector1->ops_->extractFirst(vector1);

  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector1 extract first: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  printf("\n Start insertFirst to Vector2 for %d elemenst.", repetitions);

  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    error_type = vector2->ops_->insertFirst(vector2, data2[rep], 4);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector2 insert first: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  printf("\n Start concat Vector1 to Vector2.");

  QueryPerformanceCounter(&time_start);
  vector1->ops_->concat(vector1, vector2);
  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\n Vector1 to Vector2 concat: ");
  printf("Elapsed time: %f ms.\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  // Vector Destroy
  
  error_type = vector1->ops_->destroy(vector1);
  printf("\n destroy Vector1 Operations = %d", error_type);
  error_type = vector2->ops_->destroy(vector2);
  printf("\n destroy Vector2 Operations = %d", error_type);
}

void TestList() {
  LARGE_INTEGER frequency;				// ticks per second
  LARGE_INTEGER  time_start, time_end;    // ticks in interval
  double elapsed_time = 0.0f;
  double average_time;
  s16 error_type;

  // Generate data
  /*for (u16 i = 0; i < repetitions; i++) {
    u8* my_str = MM->malloc(8);
    if (NULL == my_str) {
      printf("Error: [%s] not enough memory available for data 1 i = %d\n", __FUNCTION__, i);
      return;
    }
    sprintf(my_str, "1234");
    data1[i] = my_str;
  }
  for (u16 i = 0; i < repetitions; i++) {
    u8* my_str = MM->malloc(8);
    if (NULL == my_str) {
      printf("Error: [%s] not enough memory available for data 1 i = %d\n", __FUNCTION__, i);
      return;
    }
    sprintf(my_str, "5678");
    data2[i] = my_str;
  }*/

  // Frequency: ticks per second
  QueryPerformanceFrequency(&frequency);
  printf("\n\n\n -----  Start List Comparative  -----\n\n");

  //  List Insert First ///////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    error_type = list->ops_->insertFirst(list, data1[rep], 4);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Insert First\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  List Extract First /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    list->ops_->extractFirst(list);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Extract First\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  List Insert At  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    list->ops_->insertAt(list, data1[rep], 4, rep);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Insert At\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  List Extract At  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    list->ops_->extractAt(list, rep);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Extract At\n");
  printf("Elapsed time: %f ms\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  List Insert Last  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    list->ops_->insertLast(list, data1[rep], 4);
  }

  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Insert Last\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  List Extract Last  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    list->ops_->extractLast(list, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Extract Last\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  List Concat  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    list->ops_->concat(list, list);
  }
  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nList Concat\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  // List Destroy

  error_type = list->ops_->destroy(list);
  list2->ops_->destroy(list2);
  printf("\n Destroy List : Exited with error code %d", error_type);

}

void TestDList() {
  LARGE_INTEGER frequency;				// ticks per second
  LARGE_INTEGER  time_start, time_end;    // ticks in interval
  double elapsed_time = 0.0f;
  double average_time;


  // Frequency: ticks per second
  QueryPerformanceFrequency(&frequency);
  printf("\n\n\n -----  Start DList Comparative  -----\n\n");

  //  DList Insert First ///////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    dlist->ops_->insertFirst(dlist, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Insert First\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  DList Extract First /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    dlist->ops_->extractFirst(dlist);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Extract First\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  DList Insert At  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    dlist->ops_->insertAt(dlist, data1[rep], 4, rep);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Insert At\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  DList Extract At  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    dlist->ops_->extractAt(dlist, rep);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Extract At\n");
  printf("Elapsed time: %f ms\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  List Insert Last  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    dlist->ops_->insertLast(dlist, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Insert Last\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  DList Extract Last  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    dlist->ops_->extractLast(dlist, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Extract Last\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  DList Concat  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    list->ops_->concat(dlist, dlist);
  }
  QueryPerformanceCounter(&time_end);
  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nDList Concat\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  // DList Destroy
  s16 error_type;
  error_type = dlist->ops_->destroy(dlist);
  printf("\n Destroy DList : Exited with error code %d", error_type);
}

void TestQueue() {
  LARGE_INTEGER frequency;				// ticks per second
  LARGE_INTEGER  time_start, time_end;    // ticks in interval
  double elapsed_time = 0.0f;
  double average_time;


  // Frequency: ticks per second
  QueryPerformanceFrequency(&frequency);
  printf("\n\n\n -----  Start Queue Comparative  -----\n\n");

  //  Queue Enqueue ///////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    queue->ops_->enqueue(queue, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nQueue Enqueue\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  Queue Dequeue /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    int pos = rand() % 100;
    queue->ops_->dequeue(queue, pos);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nQueue Dequeue\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  Queue front  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    queue->ops_->front(queue);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nQueue front\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  Queue Back  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    queue->ops_->back(queue);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nQueue Back\n");
  printf("Elapsed time: %f ms\n", elapsed_time);
  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  // Queue Destroy  /////////////////////////////////////////////
  s16 error_type;
  error_type = queue->ops_->destroy(queue);
  printf("\n Destroy Queue : Exited with error code %d", error_type);
}

void TestStack() {
  LARGE_INTEGER frequency;				// ticks per second
  LARGE_INTEGER  time_start, time_end;    // ticks in interval
  double elapsed_time = 0.0f;
  double average_time;


  // Frequency: ticks per second
  QueryPerformanceFrequency(&frequency);
  printf("\n\n\n -----  Start Stack Comparative  -----\n\n");

  //  Stack Push ///////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {

    stack->ops_->push(stack, data1[rep], 4);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nStack Push\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  Stack Pop /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    int pos = rand() % 100;
    stack->ops_->pop(stack);
  }
  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nStack Pop\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);

  //  Stack Top  /////////////////////////////////////////////////////////////////////
  QueryPerformanceCounter(&time_start);
  for (u32 rep = 0; rep < repetitions; ++rep) {
    stack->ops_->top(stack);
  }

  QueryPerformanceCounter(&time_end);

  elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
  printf("\nStack Top\n");
  printf("Elapsed time: %f ms\n", elapsed_time);

  average_time = elapsed_time / repetitions;
  printf("Average time: %f ms\n", average_time);


  //  Stack Destroy  ////////////////////////////////////////////////
  s16 error_type;
  error_type = stack->ops_->destroy(stack);
  printf("\n Destroy Stack : Exited with error code %d", error_type);
}

void FreeData() {
  // Free data
  printf("\nFree data");
  for (int i = 0; i < repetitions; ++i) {
    if (data1[i] != NULL) {
      MM->free(data1[i]);
    }
  }
  printf("\nFree data2");
  /*for (int i = 0; i < repetitions; ++i) {
    if (data2[i] != NULL) {
      MM->free(data2[i]);
    }
  }*/
}

void calculateTimeForFunction() {
  
  TestVector();
  TestList();
  TestDList();
  TestQueue();
  TestStack();
  FreeData();
}

int main(int argc, char** argv) {
  srand(time(NULL));
  TESTBASE_generateDataForComparative();
  calculateTimeForFunction();


  printf("\nPress ENTER to continue\n");
  getchar();
  MM->status();
  MM->destroy();
  return 0;
}
