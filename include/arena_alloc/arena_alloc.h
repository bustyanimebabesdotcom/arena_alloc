// arena_alloc.h

#include <stddef.h>
#include <stdint.h>

#ifndef ARENA_ALLOC_H_
#define ARENA_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct arena_s {
	uint8_t *buffer;	// Pointer to memory block
	size_t size;		// Total block size
	size_t offset;		// How much we've used
} arena_s;

void arena_init			( arena_s *arena, void *buffer, size_t size );
void *arena_alloc		( arena_s *arena, size_t allocSize );
size_t arena_checkpoint	( arena_s *arena );
void arena_rewind		( arena_s *arena, size_t checkpoint );
void arena_reset		( arena_s *arena );
size_t arena_used		( arena_s *arena );
size_t arena_remaining	( arena_s *arena );

#ifdef __cplusplus
}
#endif

#endif // ARENA_ALLOC_H_
