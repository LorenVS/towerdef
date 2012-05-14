#ifndef _geometry_h
#define _geometry_h

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef	struct	point_s						point_t;
typedef enum    shape_type_e     	shape_type_t;
typedef struct  shape_s          	shape_t;
typedef struct  shape_circle_s   	shape_circle_t;
typedef struct  shape_square_s   	shape_square_t;
typedef struct  shape_complex_s  	shape_complex_t;

// -------------
// --- Point ---
// -------------

/// A two dimensional integer point
struct point_s
{
	int x;
	int y;
};

/// Initializes a point to the supplied integer values
void point_init(point_t* point, int x, int y);

// ------------------
// --- Shape Type ---
// ------------------

/// The possible types of shape
enum shape_type_e
{
  SHAPE_TYPE_CIRCLE = 0,   	///< A circle
  SHAPE_TYPE_SQUARE = 1,   	///< A square
  SHAPE_TYPE_COMPLEX = 255,	///< A combination of shapes
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

/// Checks whether two shapes intersect
bool	shape_intersects(shape_t* shape, point_t* offset, shape_t* other, point_t* other_offset);

// --------------
// --- Circle ---
// --------------

struct shape_circle_s
{
  shape_t base;       ///< The base shape object
  int32_t x_coord;    ///< The X coordinate of the circle
  int32_t y_coord;    ///< The Y coordinate of the circle
  int32_t radius;     ///< The radius of the circle
};

/// Creates a new uninitialized circle object
shape_t* 	shape_circle_new();

/// Initializes a circle object with the supplied values
void     	shape_circle_init(shape_t* shape, int32_t x_coord, int32_t y_coord, int32_t radius);

/// Deletes a circle object, freeing all reources associated with it
void     	shape_circle_delete(shape_t* shape);

/// Checks whether a circle intersects another shape
bool			shape_circle_intersects(shape_t* shape, point_t* offset, shape_t* other, point_t* other_offset);

// --------------
// --- Square ---
// --------------

struct shape_square_s
{
	shape_t base;			///< The base shape object
	int32_t x_coord;	///< The x coordinate of the square
	int32_t y_coord;	///< The y coordinate of the square
	int32_t	size;			///< The size of the square
	};

/// Creates a new uninitialized square object
shape_t* 	shape_square_new();

/// Initializes a square object with the supplied values
void			shape_square_init(shape_t* shape, int x_coord, int y_coord, int size);

/// Deletes a square object, freeing all resources associated with it
void			shape_square_delete(shape_t* shape);

/// Checks to see if a square intersects another shape
bool			shape_square_intersects(shape_t* shape, point_t* offset, shape_t* other, point_t* other_offset);

// ---------------
// --- Complex ---
// ---------------

struct shape_complex_s
{
	shape_t		base;							///< The base shape object
	int32_t		component_count;	///< The number of shape components
	shape_t** components;				///< The component shapes
};

/// Creates a new uninitialized complex shape
shape_t*	shape_complex_new();

/// Initializes a complex shape with the supplied values
void			shape_complex_init(shape_t* shape, int component_count);

/// Deletes a complex shape
void 			shape_complex_delete(shape_t* shape);

/// Checks to see whether a complex shape intersects another shape
void			shape_complex_intersects(shape_t* shape, point_t* offset, shape_t* other, point_t* other_offset);

#endif
