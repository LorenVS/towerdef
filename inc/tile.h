#ifndef _tile_h
#define _tile_h

/** @file */

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef enum    tile_type_e   tile_type_t;
typedef struct  tile_s        tile_t;
typedef struct  tile_grass_s  tile_grass_t;

// -----------------
// --- Tile Type ---
// -----------------

/// The possible types of tile
enum tile_type_e
{
  TILE_TYPE_GRASS
};

// ------------
// --- Tile ---
// ------------

/// An individual tile on a map
struct tile_s
{
  tile_type_t   tile_type;  ///< The type of tile
  texture_t*    texture;    ///< The texture used to render the tile
};

/// Deletes a tile object, freeing all resources associated with it
void        tile_delete(tile_t* tile);

// ------------------
// --- Grass Tile ---
// ------------------

struct tile_grass_s
{
  tile_t        base;     ///< The base tile object
};

/// Constructs a new grass tile instance
tile_grass_t*   tile_grass_new();

/// Deletes a grass tile instance
void            tile_grass_delete(tile_grass_t* tile);

#endif
