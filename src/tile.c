#include<assert.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "util.h"
#include "texture.h"
#include "tile.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

static texture_t* get_grass_tile_texture();

// ------------
// --- Tile ---
// ------------

void  tile_delete(tile_t* tile)
{
  assert(tile != NULL);
  switch(tile->tile_type)
  {
    case TILE_TYPE_GRASS:
      tile_grass_delete((tile_grass_t*)tile);
      break;
  }
}

// ------------------
// --- Grass Tile ---
// ------------------

texture_t* get_grass_tile_texture()
{
  static texture_t* texture = NULL;
  if(texture == NULL) {
    texture = texture_new();
    texture_load(texture, "res/grass.png");
  }
  return texture;
}

tile_grass_t*   tile_grass_new()
{
  tile_grass_t* tile = malloc(sizeof(tile_grass_t));
  tile->base.tile_type = TILE_TYPE_GRASS;
  tile->base.texture = get_grass_tile_texture();
  return tile;  
}

void tile_grass_delete(tile_grass_t* tile)
{
  assert(tile != NULL);
  free(tile);
}
