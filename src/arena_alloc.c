// arena_alloc.c

#define alwaysInline	__attribute__((always_inline)) inline
#define unlikely(x)		__builtin_expect(!!(x), 0)

#include <arena_alloc/arena_alloc.h>

static alwaysInline size_t align_up ( size_t n, size_t align ) {

	return ( n+( align-1 )) & ~( align-1 );
}

void arena_init ( arena_s *arena, void *buffer, size_t size ) {

	if ( unlikely( !arena || !buffer || size == 0 )) return;
	arena->buffer = buffer;		// Store user-provided buffer
	arena->size = size;			// Store size of buffer
	arena->offset = 0;			// Start fresh
}

void *arena_alloc ( arena_s *arena, size_t allocSize ) {

	allocSize = align_up( allocSize, 16 );
	size_t currentOffset = align_up( arena->offset, 16 );	// Align offset
	size_t newOffset = currentOffset + allocSize;

	if ( unlikely( newOffset > arena->size ))
		return NULL; // Out of memory

	void *ptr = arena->buffer+currentOffset;	// Allocate at current offset
	arena->offset = newOffset;					// Move the offset forward

	return ptr;
}



size_t arena_checkpoint ( arena_s *arena ) {

	return arena->offset;
}

void arena_rewind ( arena_s *arena, size_t checkpoint ) {

	if ( unlikely( checkpoint <= arena->offset )) arena->offset = checkpoint;
}



void arena_reset ( arena_s *arena ) {

	arena->offset = 0;
}

size_t arena_used ( arena_s *arena ) {

	return arena->offset;
}

size_t arena_remaining ( arena_s *arena ) {

	return arena->size-arena->offset;
}
