#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "util.h"
#include "geometry.h"
#include "texture.h"
#include "creep.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

static geometry_t*  get_basic_creep_shape();
static texture_t*   get_basic_creep_texture();

// -------------
// --- Creep ---
// -------------

void creep_delete(creep_t* creep)
{
  assert(creep != NULL);
  
  switch(creep->creep_type)
  {
    case CREEP_TYPE_BASIC:
      creep_basic_delete((creep_basic_t*)creep);
      break;
  }
}

// -------------------
// --- Basic Creep ---
// -------------------

static geometry_t*  get_basic_creep_shape()
{
  /* TODO: Rectangle support in geometry */
  return NULL;
}

static texture_t* get_basic_creep_texture()
{
  static texture_t* texture = NULL;
  if(texture == NULL){
    texture = texture_new();
    texture_load(texture, "res/creep.png");
  }
  return texture;
}

creep_basic_t* creep_basic_new()
{
  creep_basic_t* creep = malloc(sizeof(creep_basic_t));
  die(creep == NULL, "Error allocating basic creep");

  creep->base.creep_type = CREEP_TYPE_BASIC;
  creep->base.shape = get_basic_creep_shape();
  geometry_point_init(&creep->base.center, 9, 3);
  creep->base.texture = get_basic_creep_texture();
  geometry_point_init(&creep->base.position, 0, 0);

  return creep;
}

void creep_basic_delete(creep_basic_t* creep)
{
  assert(creep != NULL);
  assert(creep->base.creep_type == CREEP_TYPE_BASIC);
  free(creep);
}
