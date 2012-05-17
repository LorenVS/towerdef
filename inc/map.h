#ifndef _map_h
#define _map_h

// --------------
// --- Macros ---
// --------------

#define TILE_WIDTH  16
#define TILE_HEIGHT 16

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef struct map_s map_t;

// -----------
// --- Map ---
// -----------

/// A tower defence map
struct map_s
{
  tile_t**  tiles;  ///< the tiles of the map
  int32_t   width;  ///< the width of the map in tiles
  int32_t   height; ///< the height of the map in tiles
  int32_t   pwidth; ///< the width of the map in pixels
  int32_t   pheight;///< the height of the map in pixels
};

/// Creates a new map object
map_t*  map_new(int32_t width, int32_t height);

/// Deletes a map object, freeing all resources associated with it
void    map_delete(map_t* map);

/// Gets a tile at the supplied tile coordinates from map
tile_t* map_get_tile(map_t* map, int32_t x, int32_t y);

/// Sets a tile at the supplied tile coordinates in a map
void    map_set_tile(map_t* map, int32_t x, int32_t y, tile_t* tile);

#endif
