#include<assert.h>
#include<stdint.h>
#include<stdio.h>
#include "util.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

static bool read_int32_text(reader_t* reader, int32_t* out);
static bool read_int64_text(reader_t* reader, int64_t* out);
static bool read_int32_binary(reader_t* reader, int32_t* out);
static bool read_int64_binary(reader_t* reader, int64_t* out);

// ------------------------
// --- Public Functions ---
// ------------------------

reader_t* reader_new()
{
	reader_t* reader = malloc(sizeof(reader_t));
	die(reader == NULL, "failed to allocate reader");
	return reader;
}

void reader_init(reader_t* reader, char* path, bool binary)
{
	assert(reader != NULL);
	assert(path != NULL);

	reader->path = path;
	reader->fp = fopen(path);

	if(binary) {
		reader->read_int32 = read_int32_binary;
		reader->read_int64 = read_int64_binary;
	} else {
		reader->read_int32 = read_int32_text;
		reader->read_int64 = read_int64_text;
	}
}

// -------------------------
// --- Private Functions ---
// -------------------------

static bool read_int32_text(reader_t* reader, int32_t* out)
{
}

static bool read_int64_text(reader_t* reader, int64_t* out)
{
}

static bool read_int32_binary(reader_t* reader, int32_t* out)
{
}

static bool read_int64_binary(reader_t* reader, int64_t* out)
{
}
