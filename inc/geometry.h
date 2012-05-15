#ifndef _geometry_h
#define _geometry_h

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef enum    geometry_type_e     	geometry_type_t;
typedef struct  geometry_s          	geometry_t;
typedef struct	geometry_point_s			geometry_point_t;
typedef	struct	geometry_lineseg_s		geometry_lineseg_t;
typedef struct  geometry_circle_s   	geometry_circle_t;
typedef struct  geometry_square_s   	geometry_square_t;
typedef struct  geometry_complex_s  	geometry_complex_t;

// ---------------------
// --- Geometry Type ---
// ---------------------

/// The possible types of geometry
enum geometry_type_e
{
	GEOMETRY_TYPE_POINT = 0,			///< A single point
	GEOMETRY_TYPE_LINESEG = 1,		///< A line segment
  GEOMETRY_TYPE_CIRCLE = 2,   	///< A circle
  GEOMETRY_TYPE_SQUARE = 3,   	///< A square
  GEOMETRY_TYPE_COMPLEX = 255,	///< A combination of geometrys
};

// ----------------
// --- Geometry ---
// ----------------

struct geometry_s
{
  geometry_type_t    	geometry_type; ///< The type of geometry
};

/// Frees all resources associated with a geometry object
void	geometry_destroy(geometry_t* geometry);

/// Deletes a geometry object
void  geometry_delete(geometry_t* geometry);

/// Clones a geometry object
geometry_t*	geometry_clone(geometry_t* geometry);

/// Checks whether two geometrys intersect
bool	geometry_intersects(geometry_t* geometry, geometry_point_t* offset, geometry_t* other, geometry_point_t* other_offset);

// -------------
// --- Point ---
// -------------

/// A two dimensional integer point
struct geometry_point_s
{
	geometry_t 	base;	// the base geometry object
	int32_t 		x;		// the x coordinate of the point
	int32_t 		y;		// the y coordinate of the point
};

/// Initializes a point to the supplied integer values
void geometry_point_init(geometry_point_t* point, int32_t x, int32_t y);

/// Frees all resources associated with a point
void geometry_point_destroy(geometry_point_t* point);

/// Deletes a point object
void geometry_point_delete(geometry_point_t* point);

/// Clones a point object
geometry_point_t*	geometry_point_clone(geometry_point_t* point);

/// Copies a point object to another
void geometry_point_copy(geometry_point_t* source, geometry_point_t* dest);

// --------------------
// --- Line Segment ---
// --------------------

/// A line segment between two points
struct geometry_lineseg_s
{
	geometry_t				base; /// the base geometry object
	geometry_point_t	p1;		///< the first point
	geometry_point_t	p2; 	///< the second point
};

/// initializes a lineseg object with the supplied values
void geometry_lineseg_init(geometry_lineseg_t* lineseg, int x1, int y1, int x2, int y2);

/// initializes a lineseg object with the supplied values
void geometry_lineseg_init2(geometry_lineseg_t* lineseg, geometry_point_t* p1, geometry_point_t* p2);

/// Frees all resources associated with a lineseg
void geometry_lineseg_destroy(geometry_lineseg_t* lineseg);

/// Deletes a lineseg object
void geometry_lineseg_delete(geometry_lineseg_t* lineseg);

/// Clones a lineseg object
geometry_lineseg_t* geometry_lineseg_clone(geometry_lineseg_t* lineseg);

/// Copies a lineseg object to another
void geometry_lineseg_copy(geometry_lineseg_t* source, geometry_lineseg_t* dest);


// --------------
// --- Circle ---
// --------------

struct geometry_circle_s
{
  geometry_t base;    			///< The base geometry object
  geometry_point_t	origin; ///< The origin of the circle
	int32_t radius;     			///< The radius of the circle
};

/// Creates a new uninitialized circle object
geometry_circle_t* 	geometry_circle_new();

/// Initializes a circle object with the supplied values
void     	geometry_circle_init(geometry_circle_t* circle, int32_t x_coord, int32_t y_coord, int32_t radius);

/// Initializes a circle object with the supplied values
void			geometry_circle_init2(geometry_circle_t* circle, geometry_point_t* origin, int32_t radius);

/// Frees all resources associated with a circle object
void			geometry_circle_destroy(geometry_circle_t* circle);

/// Deletes a circle object
void     	geometry_circle_delete(geometry_circle_t* geometry);

/// Clones a circle object
geometry_circle_t*	geometry_circle_clone(geometry_circle_t* circle);

/// Copies a circle object to another
void			geometry_circle_copy(geometry_circle_t* source, geometry_circle_t* dest);

// --------------
// --- Square ---
// --------------

struct geometry_square_s
{
	geometry_t base;	///< The base geometry object
	int32_t x_coord;	///< The x coordinate of the square
	int32_t y_coord;	///< The y coordinate of the square
	int32_t	size;			///< The size of the square
	};

/// Creates a new uninitialized square object
geometry_square_t* 	geometry_square_new();

/// Initializes a square object with the supplied values
void			geometry_square_init(geometry_square_t* square, int x_coord, int y_coord, int size);

/// Frees all resources associated with a square object
void			geometry_square_destroy(geometry_square_t* square);

/// Deletes a square object, freeing all resources associated with it
void			geometry_square_delete(geometry_square_t* square);

/// Clones a square object
geometry_square_t* geometry_square_clone(geometry_square_t* square);

/// Copies a square object to another
void geometry_square_copy(geometry_square_t* source, geometry_square_t* dest);

// ---------------
// --- Complex ---
// ---------------

struct geometry_complex_s
{
	geometry_t		base;					///< The base geometry object
	int32_t		component_count;	///< The number of geometry components
	geometry_t** components;		///< The component geometrys
};

/// Creates a new uninitialized complex geometry
geometry_complex_t*	geometry_complex_new();

/// Initializes a complex geometry with the supplied values
void			geometry_complex_init(geometry_complex_t* complex, int component_count);

/// Frees all resources associated with a complex geometry
void			geometry_complex_destroy(geometry_complex_t* complex);

/// Deletes a complex geometry
void 			geometry_complex_delete(geometry_complex_t* complex);

/// Clones a complex geometry object
geometry_complex_t* geometry_complex_clone(geometry_complex_t* complex);

/// Copies a complex geometry object to another
void geometry_complex_copy(geometry_complex_t* source, geometry_complex_t* dest);

#endif
