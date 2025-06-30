[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue)](https://unlicense.org/)
![Language](https://img.shields.io/badge/language-C-blue)
![Status](https://img.shields.io/badge/status-stable-brightgreen)
![Version](https://img.shields.io/badge/version-1.0.0-orange)
# arena_alloc

**Version:** 1.0.0  
**License:** [The Unlicense](https://unlicense.org/)  
**Author:** [bustyanimebabesdotcom](https://github.com/bustyanimebabesdotcom)

---

### What is this?

`arena_alloc` is a minimal, fast, branch-predictable arena allocator for C.  
It uses a linear bump pointer and optional rewinding or resetting to allocate memory without malloc overhead, fragmentation, or cache-thrashing.

Perfect for high-performance applications where you allocate a bunch of memory and free it all at once — like parsing, rendering, or any time you want maximum memory control without juggling `malloc()` around.

---

### Features

- Branch-predictable with [`__builtin_expect()`](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html) on failure paths.
- 16-byte alignment by default.
- Cold-path-optimized: no bloated control flow.
- Zero overhead when preallocating buffers.
- Rewind or reset the arena at any time.
- Minimal: 1 `.c` and 1 `.h` file.
- Zero dependencies. Drop-in ready.
- Works anywhere C99 is supported.

---

### Functions

```c
void   arena_init      ( arena_s *arena, void *buffer, size_t size );
void  *arena_alloc     ( arena_s *arena, size_t size );

size_t arena_checkpoint( arena_s *arena );
void   arena_rewind    ( arena_s *arena, size_t checkpoint );

void   arena_reset     ( arena_s *arena );

size_t arena_used      ( arena_s *arena );
size_t arena_remaining ( arena_s *arena );
```

---

### Example Usage

```c
#include <stdio.h>
#include <stdlib.h>
#include <arena_alloc/arena_alloc.h>

#define ARENA_SIZE ( 1024 )

int main ( void ) {

	arena_s arena;
	void *buf = malloc( ARENA_SIZE );
	if ( !buf ) return 1;

	arena_init( &arena, buf, ARENA_SIZE );

	char *input = arena_alloc( &arena, 128 );
	if ( fgets( input, 256, stdin )) {
		printf( "You typed: %s", input );
	}

	free(buf);
	return 0;
}
```

---

### Building

Drop `arena_alloc.c` and `arena_alloc.h` into your project.  
Or use `make` if you want a `.o` or `.a` file for linking.

---

### License

[The Unlicense](https://unlicense.org/)  
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

