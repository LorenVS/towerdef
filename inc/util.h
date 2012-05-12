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
