## 42 | Unix project
# malloc
_This project is about implementing a dynamic memory allocation mechanism._
[Subject](ft_malloc.en.pdf)

---

### Overview

This repository contains the source code of my thread-safe memory management
library `libft_malloc.so`.  
The supplied shell script allows to run any program with the shared library:

> `./loader.sh <cmd>`

### APIs

The library provides an implementation of the libc functions `malloc`, `free`,
`calloc` and `realloc`, and the libbsd function `reallocf`:

```c
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocf(void *ptr, size_t size);
```

It also offers two functions that allow visual on the state of the allocated
memory:

```c
void show_alloc_mem();
void show_alloc_mem_free();
```

### Implementation

Every pointeurs are 16 bytes aligned.
Inspired by `ptmalloc2`, this malloc handles 3 types of allocations:

* `TINY` allocations, from 16 to 128 bytes, are stored in larger `arenas` to
avoid requesting pages too often.
* `SMALL` allocations contain between 129 and 4096 bytes and are stored in
`arenas` for the same reason.
* `LARGE` allocations, over 4096 bytes, are directly `mmap()`'ed as needed.

Each allocation is associated with an overhead to form a `chunk`.
The sizes of the chunk and of the previous chunk are always accessible and allow
to move from chunk to chunk in both direction.
If a chunk is `free()`'d, it also possesses pointers to its next and to its
previous free chunks.
Given that the pointers are relevant only in the case of a free chunk, the data
of the end-user in an allocated chunk begins right where these pointers begin.
Large chunks being not contiguous, their two pointers are however necessary.

Tiny free chunks are store in 8 distinct lists, one for each size (16 bytes
step). This makes the transition from allocated to free - and inversly - really
fast.  
Small free chunks have a similar functioning but are inserted in one doubly
linked and circular list, in which they are sorted by increasing size.
Large free chunks are `munmap()`'ed.

### Environment variables

The following environment variables changes the behaviour of the allocation
related functions:

> `MALLOC_VERBOSE`  
   Ouptut information about what happens in the functions. If set to
`` `all` ``, display all level of messages.

> `MALLOC_LOG_FILE`  
   Append verbosity messages to the specified file.

> `MALLOC_ERROR_ABORT`  
   Make the program `abort()` in case of an error in the memory management.
   
> `MALLOC_CORRUPTION_ABORT`  
   Same as above, but only in case of memory corruption (a failed `malloc()`
won't `abort` the program).

> `MALLOC_SCRIBBLE`  
   Fill newly allocated memory with 0xaa bytes, and fill newly released memory
with 0x55 bytes. This makes sure a program doesn't make an assumption about the
content of the memory, nor try to access data it just free'd.
