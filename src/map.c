#include<assert.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "util.h"
#include "geometry.h"
#include "texture.h"
#include "tile.h"
#include "map.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

// -----------
// --- Map ---
// -----------

map_t*  map_new(int32_t width, int32_t height)
{
  map_t* map = malloc(sizeof(map_t));
  die(map == NULL, "Error allocating map object");

  map->tiles = malloc(sizeof(tile_t*) * width * height);
  die(map->tiles == NULL, "Error allocating tiles array");
  memset(map->tiles, 0, sizeof(tile_t*) * width * height);

  map->width = width;
  map->height = height;
  map->pwidth = width * TILE_WIDTH;
  map->pheight = height * TILE_HEIGHT;
  return map;
}

void map_delete(map_t* map)
{
  assert(map != NULL);

  if(map->tiles != NULL)
    free(map->tiles);
  free(map);
}

tile_t* map_get_tile(map_t* map, int32_t x, int32_t y)
{
  assert(map != NULL);
  assert(x >= 0 && x < map->width);
  assert(y >= 0 && y < map->height);

  return map->tiles[y * map->width + x];
}

void map_set_tile(map_t* map, int32_t x, int32_t y, tile_t* tile)
{
  assert(map != NULL);
  assert(x >= 0 && x < map->width);
  assert(y >= 0 && y < map->height);
  
  map->tiles[y * map->width + x] = tile;
}
