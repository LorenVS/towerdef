#include<assert.h>
#include<math.h>
#include<stdint.h>
#include<stdlib.h>
#include "geometry.h"

// --------------
// --- Macros ---
// --------------

#define GEOMETRY_CONSTRUCTOR(S,T) S_t* S_new() { \
	geometry_t* geo = malloc(sizeof(S_t)); \
	die(geo == NULL, "Error allocating new " #T " object"); \
	geo->geometry_type = GEOMETRY_TYPE_T; \
	return geo; \
}

#define GEOMETRY_ARG_ASSERT(A, T) \
	assert(A != NULL); \
	assert(A->base.geometry_type = GEOMETRY_TYPE_T);


// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef bool(*intersection_handler)		(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_point_point		(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_lineseg_lineseg(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_circle_circle	(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_square_square	(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_point_lineseg	(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_point_circle		(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_point_square		(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_lineseg_circle (geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_lineseg_square	(geometry_t*, point_t*, geometry_t*, point_t*);
static bool int_circle_square	(geometry_t*, point_t*, geometry_t*, point_t*);

// ---------------------------------
// --- Intersection Lookup Table ---
// ---------------------------------

intersection_handler intersection_lookup_table[][] = {
	{ int_point_point, 	int_point_lineseg, 		int_point_circle, 	int_point_square 		},
	{ NULL,							int_lineseg_lineseg,	int_lineseg_circle,	int_lineseg_square 	},
	{ NULL,							NULL,									int_circle_circle,	int_circle_square		},
	{ NULL,							NULL,									NULL,								int_square_square		}
};

// -------------
// --- Point ---
// -------------

void point_init(point_t* point, int x, int y)
{
	assert(point != NULL);
	point->x = x;
	point->y = y;
}

// ----------------
// --- Geometry ---
// ----------------

void geometry_destroy(geometry_t* geometry)
{
	assert(geometry != NULL);

	switch(geometry->geometry_type) {
		case GEOMETRY_TYPE_POINT:
			geometry_point_destroy((geometry_point_t*)geometry);
			break;
		case GEOMETRY_TYPE_LINESEG:
			geometry_lineseg_destroy((geometry_lineseg_t*)geometry);
			break;
		case GEOMETRY_TYPE_CIRCLE:
			geometry_circle_destroy((geometry_circle_t*)geometry);
			break;
		case GEOMETRY_TYPE_SQUARE:
			geometry_square_destroy((geometry_square_t*)geometry);
			break;
		case GEOMETRY_TYPE_COMPLEX:
			geometry_complex_destroy((geometry_complex_t*)geometry);
			break;
	}
}

void geometry_delete(geometry_t* geometry)
{
	assert(geometry != NULL);

	switch(geometry->geometry_type) {
		case GEOMETRY_TYPE_POINT:
			geometry_point_delete((geometry_point_t*)geometry);
			break;
		case GEOMETRY_TYPE_LINESEG:
			geometry_lineseg_delete((geometry_lineseg_t*)geometry);
			break;
		case GEOMETRY_TYPE_CIRCLE:
			geometry_circle_delete((geometry_circle_t*)geometry);
			break;
		case GEOMETRY_TYPE_SQUARE:
			geometry_square_delete((geometry_square_t*)geometry);
			break;
		case GEOMETRY_TYPE_COMPLEX:
			geometry_complex_delete((geometry_complex_t*)geometry);
			break;
	}
}

bool geometry_intersects(geometry_t* geometry1, point_t* offset1, geometry_t* geometry2, point_t* offset2)
{
	assert(geometry1 != NULL);
	assert(geometry2 != NULL);

	point_t stack_offset1;
	point_t stack_offset2;

	if(offset1 == NULL){ 
		point_init(&stack_offset1, 0, 0);
		offset1 = &stack_offset1;
	}

	if(offset2 == NULL){
		point_init(&stack_offset2, 0, 0);
		offset2 = &stack_offset2;
	}

	if(geometry1->geometry_type == GEOMETRY_TYPE_COMPLEX){
		for(int i = 0; i < geometry1->component_count; i++){
			geometry_t* component = geometry1->components[i];
			if(geometry_intersects(component, offset1, geometry2, offset2))
				return true;	
		}
		return false;
	}
	else if(geometry2->geometry_type == GEOMETRY_TYPE_COMPLEX){
		for(int i = 0; i < geometry2->component_count; i++){
			geometry_t* component = geometry2->components[i];
			if(geometry_intersects(geometry1, offset1, component, offset2))
				return true;
		}
		return false;
	}
	else {
		
	}
}

geometry_t*	geometry_clone(geometry_t* geometry)
{
	assert(geometry != NULL);	
	geometry_t* clone = NULL;

	switch(geometry->geometry_type)
	{
		case GEOMETRY_TYPE_POINT:
			clone = geometry_point_clone((geometry_point_t*)geometry);
			break;
		case GEOMETRY_TYPE_LINESEG:
			clone = geometry_lineseg_clone((geometry_lineseg_t*)geometry);
			break;
		case GEOMETRY_TYPE_CIRCLE:
			clone = geometry_circle_clone((geometry_circle_t*)geometry);
			break;
		case GEOMETRY_TYPE_SQUARE:
			clone = geometry_square_clone((geometry_square_t*)geometry);
			break;
	}
	
	return clone;
}

// -------------
// --- Point ---
// -------------

GEOMETRY_CONSTRUCTOR(geometry_point, POINT);

void geometry_point_init(geometry_point_t* point, int32_t x, int32_t y)
{
	GEOMETRY_ARG_ASSERT(point, POINT);

	point->x = x;
	point->y = y;
}

void geometry_point_destroy(geometry_point_t* point)
{
	GEOMETRY_ARG_ASSERT(point, POINT);
}

void geometry_point_delete(geometry_point_t* point)
{
	GEOMETRY_ARG_ASSERT(point, POINT);
	free(point);
}

void geometry_point_clone(geometry_point_t* point)
{
	GEOMETRY_ARG_ASSERT(point, POINT);
	
	geometry_point_t* clone = geometry_point_new();
	geometry_point_init(clone, point->x, point->y);
	return clone;
}

void geometry_point_copy(geometry_point_t* source, geometry_point_t* dest)
{
	GEOMETRY_ARG_ASSERT(source, POINT);
	geometry_point_init(dest, source->x, source->y);
}

// --------------------
// --- Line Segment ---
// --------------------

GEOMETRY_CONSTRUCTOR(geometry_lineseg, LINESEG);

void geometry_lineseg_init(geometry_lineseg_t* lineseg, int x1, int y1, int x2, int y2)
{
	assert(lineseg != NULL);

	lineseg->base.geometry_type = GEOMETRY_TYPE_LINESEG;
	
}


// --------------
// --- Circle ---
// --------------

GEOMETRY_CONSTRUCTOR(geometry_circle, CIRCLE)

void geometry_circle_init(geometry_t* geometry, int32_t x_coord, int32_t y_coord, int32_t radius)
{
	assert(geometry != NULL);
	assert(geometry->geometry_type == GEOMETRY_TYPE_CIRCLE);
	geometry_circle_t* circle = (geometry_circle_t*)geometry;

	circle->x_coord = x_coord;
	circle->y_coord = y_coord;
	circle->radius = radius;
}

void geometry_circle_delete(geometry_t* geometry)
{
	assert(geometry != NULL);
	assert(geometry->geometry_type == GEOMETRY_TYPE_CIRCLE);
	geometry_circle_t* circle = (geometry_circle_t*)geometry;

	free(circle);	
}

// --------------
// --- Square ---
// --------------

GEOMETRY_CONSTRUCTOR(geometry_square, SQUARE);

void geometry_square_init(geometry_t* geometry, int32_t x_coord, int32_t y_coord, int32_t size)
{
	assert(geometry != NULL);
	assert(geometry->geometry_type == GEOMETRY_TYPE_SQUARE);
	geometry_square_t* square = (geometry_square_t*)geometry;

	square->x_coord = x_coord;
	square->y_coord = y_coord;
	square->size = size;
}

void geometry_square_delete(geometry_t* geometry)
{
	assert(geometry != NULL);	
	assert(geometry->geometry_type == GEOMETRY_TYPE_SQUARE);
	geometry_square_t* square = (geometry_square_t*)geometry;
	
	free(square);
}

// ---------------
// --- Complex ---
// ---------------

geometry_t* geometry_complex_new()
{
	geometry_t* geometry = malloc(sizeof(geometry_complex_t));
	die(geometry == NULL, "Failed to allocate complex geometry object");
	memset(geometry, 0, sizeof(geometry_complex_t));
	geometry->geometry_type = GEOMETRY_TYPE_COMPLEX;
	return geometry;
}

void geometry_complex_init(geometry_t* geometry, int component_count)
{
	assert(geometry != NULL);
	assert(geometry->geometry_type == GEOMETRY_TYPE_COMPLEX);
	geometry_complex_t* complex = (geometry_complex_t*)geometry;

	complex->component_count = component_count;
	complex->components = malloc(sizeof(*complex->components) * component_count);
	die(complex->components == NULL, "Error allocating complex components array");
}

void geometry_complex_delete(geometry_t* geometry)
{
	assert(geometry != NULL);
	assert(geometry->geometry_type == GEOMETRY_TYPE_COMPLEX);
	geometry_complex_t* complex = (geometry_complex_t*)geometry;

	if(complex->component_count > 0 && complex->components != NULL) {
		for(int i = 0; i < complex->component_count; i++){
			geometry_delete(complex->components[i]);
			complex->components[i] = NULL;
		}
	}

	free(complex);
}

// -------------------------
// --- Private Functions ---
// -------------------------

static bool intersects_circle_circle(geometry_t* geometry1, point_t* offset1, geometry_t* geometry2, point_t* offset2)
{
	assert(geometry1 != NULL);
	assert(offset1 != NULL);
	assert(geometry2 != NULL);
	assert(offset2 != NULL);
	assert(geometry1->geometry_type = GEOMETRY_TYPE_CIRCLE);
	assert(geometry2->geometry_type = GEOMETRY_TYPE_CIRCLE);
	
	geometry_circle_t* circle1 = (geometry_circle_t*)geometry1;
	geometry_circle_t* circle2 = (geometry_circle_t*)geometry2;

	int32_t total_r = circle1->radius + circle2->radius;
	int32_t	delta_x = (circle1->x_coord + offset1->x) - (circle2->x_coord + offset2->x);
	int32_t delta_y = (circle1->y_coord + offset1->y) - (circle2->y_coord + offset2->y);
	float		dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	return dist > total_r;
}

static bool intersects_square_square(geometry_t* geometry1, point_t* offset1, geometry_t* geometry2, point_t* offset2)
{
	assert(geometry1 != NULL);
	assert(offset1 != NULL);
	assert(geometry2 != NULL);
	assert(offset2 != NULL);
	assert(geometry1->geometry_type = GEOMETRY_TYPE_SQUARE);
	assert(geometry2->geometry_type = GEOMETRY_TYPE_SQUARE);

	geometry_square_t* square1 = (geometry_square_t*)geometry1;
	geometry_square_t* square2 = (geometry_square_t*)geometry2;

	int32_t x1 = square1->x_coord + offset1->x;
	int32_t y1 = square1->y_coord + offset1->y;
	int32_t s1 = square1->size;
	int32_t x2 = square2->x_coord + offset2->x;
	int32_t y2 = square2->y_coord + offset2->y;
	int32_t s2 = square2->size;
	
	bool x_intersects = (x1 <= x2 && x1 + s1 >= x2)
										||(x2 <= x1 && x2 + s2 >= x1);

	bool y_intersects = (y1 <= y2 && y1 + s1 >= y2)
										||(y2 <= y1 && y2 + s2 >= y1);

	return x_intersects && y_intersects;
}

static bool intersects_circle_square(geometry_t* geometry1, point_t* offset1, geometry_t* geometry2, point_t* offset2)
{
	
}

