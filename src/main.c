#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "util.h"
#include "geometry.h"
#include "texture.h"
#include "tile.h"
#include "tower.h"
#include "towerdef.h"
#include "window.h"

texture_t* texture;

void draw_cb(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  texture_draw(texture, 0, 0);
  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  texture = texture_new();
  bool success = texture_load(texture, "res/tower.png");
  die(!success, "Failed to load texture");

  window_t* window = window_new();
  window_init(window);
  window->draw_cb = draw_cb;

  window_run(window, &argc, argv);
  window_delete(window);

  texture_delete(texture);
  return 0;
}
