#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "util.h"
#include "geometry.h"
#include "texture.h"
#include "tile.h"
#include "tower.h"
#include "creep.h"
#include "map.h"
#include "towerdef.h"
#include "window.h"

int width = 50;
int height = 50;
map_t*      map;
creep_t*    creeps[5];
int frame = 0;

void draw_cb(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      tile_t* tile = map_get_tile(map, x, y);
      if(tile != NULL)
        texture_draw(tile->texture, x * TILE_WIDTH, 800 - (y + 1) * TILE_HEIGHT);
    }
  }

  for(int i = 0; i < 5; i++)
  {
    if(creeps[i] == NULL)
      continue;

    texture_draw(
      creeps[i]->texture, 
      creeps[i]->position.x - creeps[i]->center.x,
      creeps[i]->position.y - creeps[i]->center.y);


    creeps[i]->position.x++;
    creeps[i]->position.y++;

    if(creeps[i]->position.x >= 800)
    {
      creep_delete(creeps[i]);
      creeps[i] = NULL;
    }
  }

  ++frame;

  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  map = map_new(width, height);
  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      map_set_tile(map, x, y, (tile_t*)tile_grass_new());
    }
  }

  for(int i = 0; i < 5; i++)
  {
    creeps[i] = (creep_t*)creep_basic_new();
    creeps[i]->position.x = i * 100;
    creeps[i]->position.y = i * 100;
  }

  window_t* window = window_new();
  window_init(window);
  window->draw_cb = draw_cb;

  window_run(window, &argc, argv);
  window_delete(window);

  return 0;
}
