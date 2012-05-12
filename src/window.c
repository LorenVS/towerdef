#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "window.h"
#include "util.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

static void window_enable_2d();
static void window_disable_2d();
static void window_draw();

// ------------------------
// --- Public Functions ---
// ------------------------

window_t* window_new()
{
  window_t* window = malloc(sizeof(window_t));
  die(window == NULL, "Failed to allocate the application window");
  return window;
}

void window_init(window_t* window)
{
  assert(window != NULL);
  window->width = WINDOW_DEFAULT_WIDTH;
  window->height = WINDOW_DEFAULT_HEIGHT;
  window->title = WINDOW_DEFAULT_TITLE;
  window->draw_cb = window_draw;
}

void window_delete(window_t* window)
{
  assert(window != NULL);
  free(window);
}

void window_run(window_t* window, int* argc, char** argv)
{
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow(window->title);
  glutDisplayFunc(window->draw_cb);

  // enable alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  window_enable_2d();
  glutMainLoop();
  window_disable_2d();
}

// -------------------------
// --- Private Functions ---
// -------------------------

static void window_enable_2d()
{
  int vPort[4];
  glGetIntegerv(GL_VIEWPORT, vPort);
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // 2d texture parameters
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);
}

static void window_disable_2d()
{
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

static void window_draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}
