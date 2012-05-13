#ifndef _geometry_h
#define _geometry_h

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef enum    shape_type_e     shape_type_t;
typedef struct  shape_s          shape_t;
typedef struct  shape_circle_s   shape_circle_t;
typedef struct  shape_square_s   shape_square_t;
typedef struct  shape_complex_s  shape_complex_t;

// ------------------
// --- Shape Type ---
// ------------------

/// The possible types of shape
enum shape_type_e
{
  SHAPE_TYPE_CIRCLE,   ///< A circle
  SHAPE_TYPE_SQUARE,   ///< A square
  SHAPE_TYPE_COMPLEX   ///< A combination of geometries
};

// -------------
// --- Shape ---
// -------------

struct shape_s
{
  shape_type_t    shape_type; ///< The type of shape
};

/// Deletes a shape object, freeing all resources associated with it
void  shape_delete(shape_t* shape);

// --------------
// --- Circle ---
// --------------

struct shape_circle_s
{
  shape_s base;       ///< The base shape object
  int     x_coord;    ///< The X coordinate of the circle
  int     y_coord;    ///< The Y coordinate of the circle
  int     radius;     ///< The radius of the circle
};

/// Creates a new uninitialized circle object
shape_t* shape_circle_new();

/// Initializes a circle object with the supplied values
void            shape_circle_init(shape_t* shape, int x_coord, int y_coord, int radius);

/// Deletes a circle object, freeing all reources associated with it
void            shape_circle_delete(shape_t* shape);






#endif
