#include<assert.h>
#include<stdlib.h>

#include "util.h"
#include "geometry.h"
#include "tower.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

static geometry_t*  get_basic_tower_shape();

// -------------
// --- Tower ---
// -------------

void tower_delete(tower_t* tower)
{
  switch(tower->tower_type)
  {
    case TOWER_TYPE_BASIC:
      tower_basic_delete((tower_basic_t*)tower);
      break;
  }
}

// -------------------
// --- Basic Tower ---
// -------------------

static geometry_t*  get_basic_tower_shape()
{
  static geometry_circle_t* shape = NULL;
  if(shape == NULL){
    shape = geometry_circle_new();
    geometry_circle_init(shape, 0, 0, 5);
  }
  return (geometry_t*)shape;
}

tower_basic_t*  tower_basic_new(geometry_point_t* position)
{
  tower_basic_t* basic = malloc(sizeof(tower_basic_t));
  basic->base.tower_type = TOWER_TYPE_BASIC;
  geometry_point_copy(position, &basic->base.position);
  basic->base.shape = get_basic_tower_shape();
  return basic;
}

void            tower_basic_delete(tower_t* tower)
{
  assert(tower != NULL);
  geometry_point_destroy(&tower->base.position);
  free(tower);
}
