#include<assert.h>
#include<math.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "util.h"
#include "geometry.h"

// --------------
// --- Macros ---
// --------------

#define GEOMETRY_CONSTRUCTOR(S,T) geometry_##S##_t* geometry_##S##_new() { \
	geometry_##S##_t* geo = malloc(sizeof(geometry_##S##_t)); \
	die(geo == NULL, "Error allocating new " #T " object"); \
	geo->base.geometry_type = GEOMETRY_TYPE_##T; \
	return geo; \
}

#define GEOMETRY_ARG_ASSERT(A, T) \
	assert(A != NULL); \
	assert(A->base.geometry_type = GEOMETRY_TYPE_##T);


// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef bool(*intersection_handler)		(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_point_point		(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_lineseg_lineseg(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_circle_circle	(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_square_square	(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_point_lineseg	(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_point_circle		(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_point_square		(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_lineseg_circle (geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_lineseg_square	(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);
static bool int_circle_square	(geometry_t*, geometry_point_t*, geometry_t*, geometry_point_t*);

// ---------------------------------
// --- Intersection Lookup Table ---
// ---------------------------------

intersection_handler intersection_lookup_table[4][4] = {
	{ int_point_point, 	int_point_lineseg, 		int_point_circle, 	int_point_square 		},
	{ NULL,							int_lineseg_lineseg,	int_lineseg_circle,	int_lineseg_square 	},
	{ NULL,							NULL,									int_circle_circle,	int_circle_square		},
	{ NULL,							NULL,									NULL,								int_square_square		}
};

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

bool geometry_intersects(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
	assert(geometry1 != NULL);
	assert(geometry2 != NULL);

	geometry_point_t stack_offset1;
	geometry_point_t stack_offset2;

	if(offset1 == NULL){ 
		geometry_point_init(&stack_offset1, 0, 0);
		offset1 = &stack_offset1;
	}

	if(offset2 == NULL){
		geometry_point_init(&stack_offset2, 0, 0);
		offset2 = &stack_offset2;
	}

	if(geometry1->geometry_type == GEOMETRY_TYPE_COMPLEX){
		geometry_complex_t* complex = (geometry_complex_t*)geometry1;

		for(int i = 0; i < complex->component_count; i++){
			geometry_t* component = complex->components[i];
			if(geometry_intersects(component, offset1, geometry2, offset2))
				return true;	
		}
		return false;
	}
	else if(geometry2->geometry_type == GEOMETRY_TYPE_COMPLEX){
		geometry_complex_t* complex = (geometry_complex_t*)geometry1;
	
		for(int i = 0; i < complex->component_count; i++){
			geometry_t* component = complex->components[i];
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
			clone = (geometry_t*)geometry_point_clone((geometry_point_t*)geometry);
			break;
		case GEOMETRY_TYPE_LINESEG:
			clone = (geometry_t*)geometry_lineseg_clone((geometry_lineseg_t*)geometry);
			break;
		case GEOMETRY_TYPE_CIRCLE:
			clone = (geometry_t*)geometry_circle_clone((geometry_circle_t*)geometry);
			break;
		case GEOMETRY_TYPE_SQUARE:
			clone = (geometry_t*)geometry_square_clone((geometry_square_t*)geometry);
			break;
		case GEOMETRY_TYPE_COMPLEX:
			clone = (geometry_t*)geometry_complex_clone((geometry_complex_t*)geometry);
			break;
	}
	
	return clone;
}

// -------------
// --- Point ---
// -------------

GEOMETRY_CONSTRUCTOR(point, POINT);

void geometry_point_init(geometry_point_t* point, int32_t x, int32_t y)
{
	assert(point != NULL);
	point->base.geometry_type = GEOMETRY_TYPE_POINT;

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

geometry_point_t* geometry_point_clone(geometry_point_t* point)
{
	GEOMETRY_ARG_ASSERT(point, POINT);
	
	geometry_point_t* clone = geometry_point_new();
	geometry_point_init(clone, point->x, point->y);
	return clone;
}

void geometry_point_copy(geometry_point_t* source, geometry_point_t* dest)
{
	GEOMETRY_ARG_ASSERT(source, POINT);
	assert(dest != NULL);

	geometry_point_init(dest, source->x, source->y);
}

// --------------------
// --- Line Segment ---
// --------------------

GEOMETRY_CONSTRUCTOR(lineseg, LINESEG);

void geometry_lineseg_init(geometry_lineseg_t* lineseg, int x1, int y1, int x2, int y2)
{
	assert(lineseg != NULL);

	lineseg->base.geometry_type = GEOMETRY_TYPE_LINESEG;
	geometry_point_init(&lineseg->p1, x1, y1);
	geometry_point_init(&lineseg->p2, x2, y2);		
}

void geometry_lineseg_init2(geometry_lineseg_t* lineseg, geometry_point_t* p1, geometry_point_t* p2)
{
	assert(lineseg != NULL);
	
	lineseg->base.geometry_type = GEOMETRY_TYPE_LINESEG;
	geometry_point_copy(p1, &lineseg->p1);
	geometry_point_copy(p2, &lineseg->p2);
}

void geometry_lineseg_destroy(geometry_lineseg_t* lineseg)
{
	GEOMETRY_ARG_ASSERT(lineseg, LINESEG);
	geometry_point_destroy(&lineseg->p1);
	geometry_point_destroy(&lineseg->p2);
}

void geometry_lineseg_delete(geometry_lineseg_t* lineseg)
{
	GEOMETRY_ARG_ASSERT(lineseg, LINESEG);
	free(lineseg);
}

geometry_lineseg_t* geometry_lineseg_clone(geometry_lineseg_t* lineseg)
{
	GEOMETRY_ARG_ASSERT(lineseg, LINESEG);
	
	geometry_lineseg_t* clone = geometry_lineseg_new();
	geometry_lineseg_init2(clone, &lineseg->p1, &lineseg->p2);
	return clone;
}

void geometry_lineseg_copy(geometry_lineseg_t* source, geometry_lineseg_t* dest)
{
	GEOMETRY_ARG_ASSERT(source, LINESEG);
	geometry_lineseg_init2(dest, &source->p1, &source->p2);
}



// --------------
// --- Circle ---
// --------------

GEOMETRY_CONSTRUCTOR(circle, CIRCLE)

void geometry_circle_init(geometry_circle_t* circle, int32_t x_coord, int32_t y_coord, int32_t radius)
{
	assert(circle != NULL);
	circle->base.geometry_type = GEOMETRY_TYPE_CIRCLE;
	geometry_point_init(&circle->origin, x_coord, y_coord);
	circle->radius = radius;
}

void geometry_circle_init2(geometry_circle_t* circle, geometry_point_t* p, int32_t radius)
{
	assert(circle != NULL);
	circle->base.geometry_type = GEOMETRY_TYPE_CIRCLE;
	geometry_point_copy(p, &circle->origin);
	circle->radius = radius;
}

void geometry_circle_destroy(geometry_circle_t* circle)
{
	GEOMETRY_ARG_ASSERT(circle, CIRCLE);
	geometry_point_destroy(&circle->origin);
}

void geometry_circle_delete(geometry_circle_t* circle)
{
	GEOMETRY_ARG_ASSERT(circle, CIRCLE);

	free(circle);
}

geometry_circle_t* geometry_circle_clone(geometry_circle_t* circle)
{
	GEOMETRY_ARG_ASSERT(circle, CIRCLE);

	geometry_circle_t* clone = geometry_circle_new();
	geometry_circle_init2(clone, &circle->origin, circle->radius);
	return clone;	
}

void geometry_circle_copy(geometry_circle_t* source, geometry_circle_t* dest)
{
	GEOMETRY_ARG_ASSERT(source, CIRCLE);
	assert(dest != NULL);
	geometry_circle_init2(dest, &source->origin, source->radius);
}

// --------------
// --- Square ---
// --------------

GEOMETRY_CONSTRUCTOR(square, SQUARE);

void geometry_square_init(geometry_square_t* square, int32_t x_coord, int32_t y_coord, int32_t size)
{
	assert(square != NULL);

	square->x_coord = x_coord;
	square->y_coord = y_coord;
	square->size = size;
}

void geometry_square_destroy(geometry_square_t* square)
{
	GEOMETRY_ARG_ASSERT(square, SQUARE);
}

void geometry_square_delete(geometry_square_t* square)
{
	GEOMETRY_ARG_ASSERT(square, SQUARE);
	free(square);
}

geometry_square_t* geometry_square_clone(geometry_square_t* square)
{
	GEOMETRY_ARG_ASSERT(square, SQUARE);

	geometry_square_t* clone = geometry_square_new();
	geometry_square_init(clone, square->x_coord, square->y_coord, square->size);
	return clone;
}

void geometry_square_copy(geometry_square_t* source, geometry_square_t* dest)
{
	GEOMETRY_ARG_ASSERT(source, SQUARE);
	assert(dest != NULL);
	geometry_square_init(dest, source->x_coord, source->y_coord, source->size);
}

// ---------------
// --- Complex ---
// ---------------

GEOMETRY_CONSTRUCTOR(complex, COMPLEX);

void geometry_complex_init(geometry_complex_t* complex, int component_count)
{
	complex->base.geometry_type = GEOMETRY_TYPE_COMPLEX;
	complex->component_count = component_count;

	complex->components = malloc(sizeof(*complex->components) * component_count);
	die(complex->components == NULL, "Error allocating complex components array");
	memset(complex->components, 0, sizeof(*complex->components) * component_count);
}

void geometry_complex_destroy(geometry_complex_t* complex)
{
	GEOMETRY_ARG_ASSERT(complex, COMPLEX);
}

void geometry_complex_delete(geometry_complex_t* complex)
{
	free(complex);
}

geometry_complex_t* geometry_complex_clone(geometry_complex_t* complex)
{
	GEOMETRY_ARG_ASSERT(complex, COMPLEX);

	geometry_complex_t* clone = geometry_complex_new();
	geometry_complex_init(clone, complex->component_count);
	for(int i = 0; i < complex->component_count; i++){
		clone->components[i] = geometry_clone(complex->components[i]);
	}
	return clone;
}

void geometry_complex_copy(geometry_complex_t* source, geometry_complex_t* dest)
{
	GEOMETRY_ARG_ASSERT(source, COMPLEX);
	assert(dest != NULL);

	geometry_complex_init(dest, source->component_count);
	for(int i = 0; i < source->component_count; i++) {
		dest->components[i] = geometry_clone(source->components[i]);
	}
}

// -------------------------
// --- Private Functions ---
// -------------------------

static bool int_point_point(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
	return false;
}

static bool int_lineseg_lineseg(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
	return false;
}

static bool int_circle_circle(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
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
	int32_t	delta_x = (circle1->origin.x + offset1->x) - (circle2->origin.x + offset2->x);
	int32_t delta_y = (circle1->origin.y + offset1->y) - (circle2->origin.y + offset2->y);
	float		dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	return dist > total_r;
}

static bool int_square_square(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
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

static bool int_point_lineseg(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geomtry2, geometry_point_t* offset2)
{
	return false;
}

static bool int_point_circle(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
	return false;
}

static bool int_point_square(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
	return false;
}

static bool int_lineseg_circle(geometry_t* geometry, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
  return false;
}

static bool int_lineseg_square(geometry_t* geometry, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
  return false;
}

static bool int_circle_square(geometry_t* geometry1, geometry_point_t* offset1, geometry_t* geometry2, geometry_point_t* offset2)
{
	return false;	
}


