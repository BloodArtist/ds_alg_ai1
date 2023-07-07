/*! \mainpage ABGS Memory Manager Index Page
 
	Memory Manager - Artificial Bytes Game Studio
	\par Description:
	ABGS Memory Manager is a storage allocator library. The essential requirement of this software is to provide 
	dynamic allocatations of portions of memory	to programs at their request, and free them for reuse when no longer needed.
	In this system, memory is pre-allocated into several pools of fixed-size blocks of memory. All blocks of a particular
  size are kept in a kind of sorted linked list for later use. When a request for allocation is done, the allocator will 
  provide the smallest sufficiently large block. Furthermore, ABGS Memory Manager allows to check the status of the 
  memory to detect memory leaks or corrupted blocks of memory. 

	\details
	\li \c thread-safe :
	ABGS Memory Manager allows code to run in multithreaded environments. A program can allocate or free memory
	in several threads simultaneously.

	\li \c memory \c alignment :
	Reads and writes to allocated memory are most efficient because blocks of memory are naturally aligned.
	
  \li \c memory \c configuration :
  The number of blocks and the size of each block is defined in the configuration file 
  \c<b>abgs_memory_configuration.cfg</b>.
  This file can be modified by users to ajust the number of blocks (for each size) required according to the 
  execution of their applications to get a better performance.\n 
  <em>This file has to be located in the same directory where the application is executed.</em>

	\note 
	It is also included a source code file showing an example of how to use the Memory Manager.\n
	In a future version, a statistic module will be added to help user to define the number of blocks of each size needed by 
  a specific application or program.

	\author Toni Barella \<barella (dot) toni (at) gmail (dot) com\>
	\version 1.2.0
	\date Dec, 2016
	\copyright Artificial Bytes Game Studio (C) 2016-2020

	\note
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	1. Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
	2. The name of the above contributors may not be
	used to endorse or promote products derived from this software
	without specific prior written permission.
	\par
	THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.
 */

 /*!
\file abgs_memory_manager.h
\brief Header file of Interface for the Memory Manager.
\par Description:
		Interface for the Memory Manager
\version 1.2.0
\author Toni Barella \<barella (dot) toni (at) gmail (dot) com\>
\date Dec, 2016
\copyright Artificial Bytes Game Studio (C) 2016-2020
*/

#ifndef __ABGS_MEMORY_MANAGER_H__
#define __ABGS_MEMORY_MANAGER_H__

#include "abgs_platform_types.h"

/*!
	\struct ABGS_MemoryManager
	\par Description:
	ABGS Memory Manager is a storage allocator that provides dynamic allocatations of portions of memory
	to programs at their request, and free them for reuse when no longer needed.
	\note:
*/
typedef struct abgs_memory_manager_s
{
	/*!
	\var ops_
	\brief Pointer to the operations user can call to work with dynamic memory.
	*/
	struct memory_manager_ops_s *ops_;
} ABGS_MemoryManager;

// Memory Manager's API Declarations
struct memory_manager_ops_s
{
	/*!
	\name malloc
	\fn void* malloc(size_t size)
	\brief Allocate memory block
	\par Description:
	Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
	\param size
	\par Size of the memory block, in bytes. size_t is an unsigned integral type.
	\return void *
	\details
	The content of the newly allocated block of memory is not initialized, remaining with indeterminate values.
	If size is zero, the return value is a null pointer.
	\par On success, a pointer to the memory block allocated by the function.
	The type of this pointer is always void*, which can be cast to the desired type of data pointer in order
	to be dereferenceable.
	If the function failed to allocate the requested block of memory, a null pointer is returned.
	*/
	void*(*malloc) (size_t size);
	/*!
	\name free
	\fn void free(void *ptr)
	\brief Deallocate memory block
	\par Description:
	A block of memory previously allocated by a call to malloc, calloc or realloc is deallocated,
	making it available again for further allocations.
	\param ptr
	\par Pointer to a memory block previously allocated with ABGS malloc.
	\details
	If ptr does not point to a block of memory allocated with the above functions, it causes undefined behavior.
	If ptr is a null pointer, the function does nothing.
	Notice that this function does not change the value of ptr itself, hence it still points to the same (now invalid) location.
	\return none.
	*/
	void(*free) (void *ptr);
	/*!
	\name status
	\brief Print memory status.
	\return none
	*/
	void(*status) ();
	/*!
	\name destroy
	\brief Deallocates all resource Memory Manager has used.
	\return none
	*/
	void(*destroy) ();
};

/*!
\var instance
\brief Reference to MemoryManager singleton.
*/
ABGS_MemoryManager* ABGS_MemMngrInstance();
/*!
  \def MM
  Shortcut to access to Memory Manager singleton.
*/
#define MM (ABGS_MemMngrInstance()->ops_)

#endif  // __ABGS_MEMORY_MANAGER_H__


