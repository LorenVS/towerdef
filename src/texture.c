#include<assert.h>
#include<png.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include "util.h"
#include "texture.h"

texture_t* texture_new()
{
  texture_t* texture = malloc(sizeof(texture_t));
  die(texture == NULL, "Error allocating texture");
}

bool texture_load(texture_t* texture, char* path)
{
  assert(texture != NULL);
  assert(path != NULL);

  // this code is taken nearly verbatim from
  // a blog article by Morten Nobel-Joergensen.
  // the article can be found at:
  //  http://blog.nobel-joergensen.com/2010/11/07/loading-a-png-as-texture-in-opengl-using-libpng
  
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned int sig_read = 0;
  int color_type, interlace_type;
  FILE* fp;

  if((fp = fopen(path, "rb")) == NULL)
    return false;

  /* Create and initialize the png_struct with
   * the desired error handler functions. If you want
   * to use the default stderr and longjump method,
   * you can supply NULL for the last three parameters. We
   * also supply the compiler header file version, so that we
   * know if the application was compiled with a compatable
   * version of the library. REQUIRED
  */

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(png_ptr == NULL) {
    fclose(fp);
    return false;
  }

  /* Allocate/initialize the memory for the image information. REQUIRED */
  info_ptr = png_create_info_struct(png_ptr);
  if(info_ptr == NULL) {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
    return false;
  }

  /* Set error handling if you are using the setjmp/longjmp method
   * (this is the normal method of doing things with libpng).
   * REQUIRED unless you set up your own error handlers in the 
   * png_create_read_struct() earlier */

  if(setjmp(png_jmpbuf(png_ptr))) {
    /* Free all of the memory associated with the png_ptr and info_ptr */
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
    fclose(fp);
    return false;
  }

  /* Set up the output control if you are using standard C streams */
  png_init_io(png_ptr, fp);

  /* If we have already read some of the signature */
  png_set_sig_bytes(png_ptr, sig_read);

  /* If you have enough memory to read in the entire image at once, and you
   * need to specifiy only transforms that can be controlled with one of the
   * PNG_TRANSFORM_* bits (this presently excludes dithering, filling, setting
   * background, and doing gamma adjustment), then you can read the entire image
   * (including pixels) into the info structure with this call
   *
   * PNG_TRANSFORM_STRIP_16 |
   * PNG_TRANSFORM_PACKING forces 8 bit
   * PNG_TRANFORM_EXPAND forces to expand a palette into RGB
   */

  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

  texture->width = info_ptr->width;
  texture->height = info_ptr->height;
  switch(info_ptr->color_type) {
    case PNG_COLOR_TYPE_RGBA:
      texture->has_alpha = true;
      break;
    case PNG_COLOR_TYPE_RGB:
      texture->has_alpha = false;
      break;
    default:
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(fp);
      return false;
  } 

  unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
  texture->data = (unsigned char*)malloc(row_bytes * texture->height);

  png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
  for(int i = 0; i < texture->height; i++) {
    // note that png is ordered top to bottom, but
    // OpenGL expects it bottom to top so the order must
    // be swapped
    memcpy(texture->data+(row_bytes * (texture->height - i - 1)), row_pointers[i], row_bytes);
  }

  /* Clean up after the read,
   * and free any memory allocated */
  png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

  /* Close the file */
  fclose(fp);

  return true;
}

void texture_delete(texture_t* texture)
{
  assert(texture != NULL);
  
  if(texture->data != NULL) {
    free(texture->data);
    texture->data = NULL;
  }

  free(texture);
}

void texture_draw(texture_t* texture, int x, int y)
{
  glTexImage2D(GL_TEXTURE_2D, 0, texture->has_alpha ? 4 : 3, texture->width,
    texture->height, 0, texture->has_alpha ? GL_RGBA : GL_RGB,
    GL_UNSIGNED_BYTE, texture->data);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
      glVertex2f(x, y);
    glTexCoord2f(0.0, 1.0);
      glVertex2f(x, y + texture->height);
    glTexCoord2f(1.0, 1.0);
      glVertex2f(x + texture->width, y + texture->height);
    glTexCoord2f(1.0, 0.0);
      glVertex2f(x + texture->width, y);
  glEnd();
}
