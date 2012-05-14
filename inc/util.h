#ifndef _util_h
#define _util_h

/** @file */

// ------------
// --- bool ---
// ------------

/// Simple boolean type for use in C
typedef int bool;

/// Boolean constant for true
#define true 1

/// Boolean constant for false
#define false 0

// ----------
// --- io ---
// ----------

typedef struct reader_s reader_t;

/// Abstract reader for reading integers from a file
struct reader_s
{
	bool(*read_int32)(reader_t*, int32_t* out); ///< Read delegate for int32
	bool(*read_int64)(reader_t*, int64_t* out);	///< Read delegate for int64
	char* path; 																///< Path to the file to read
	FILE* fp;																		///< File pointer of the opened file
};

/// Creates a new uninitialized reader object
reader_t*		reader_new();

/// Initializes a reader using the supplied values
void				reader_init(reader_t* reader, char* path, bool binary);

/// Deletes a reader, freeing all resources associated with it
void				reader_delete(reader_t* reader);


// --------------
// --- errors ---
// --------------

/// Fail-fast for errors with a constant error message
#define die(cond, fmt) { \
  if(cond) { \
    fprintf(stderr, fmt); \
    exit(1); \
  } \
}

/// Fail-fast for errors with a formatted error message
#define dief(cond, fmt, ...) { \
  if(cond) { \
    fprintf(stderr, fmt, __VA_ARGS__); \
    exit(1); \
  } \
}

#endif
