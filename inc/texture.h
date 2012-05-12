#ifndef _texture_h
#define _texture_h

/** @file */

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef struct texture_s texture_t;

// ---------------
// --- Texture ---
// ---------------

/// A single 2d texture used for drawing (basically a sprite)
struct texture_s
{
	GLubyte*	data;				///< the raw image data of the texture
	int				width;			///< the width of the texture
	int				height; 		///< the height of the texture
	bool			has_alpha;	///< true if the texture has alpha values
};

// -----------------
// --- Functions ---
// -----------------

/// creates a new uninitialized texture
texture_t*	texture_new();

/// loads texture data from a file
bool				texture_load(texture_t* texture, char* path);

/// Deletes a texture, freeing all resources associated with it
void				texture_delete(texture_t* texture);

/// Draws the texture at the supplied coordinates
void				texture_draw(texture_t* texture, int x, int y);

#endif
