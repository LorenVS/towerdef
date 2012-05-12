#ifndef _util_h
#define _util_h

// ------------
// --- bool ---
// ------------

typedef int bool;
#define true 1
#define false 0

// --------------
// --- errors ---
// --------------

#define die(cond, fmt) { \
	if(cond) { \
		fprintf(stderr, fmt); \
		exit(1); \
	} \
}

#define dief(cond, fmt, ...) { \
	if(cond) { \
		fprintf(stderr, fmt, __VA_ARGS__); \
		exit(1); \
	} \
}

#endif
