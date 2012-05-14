#include<assert.h>
#include<math.h>
#include<stdint.h>
#include<stdlib.h>
#include "geometry.h"

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef bool(*intersection_handler)(shape_t*, point_t*, shape_t*, point_t*);
static bool intersects_circle_circle(shape_t*, point_t*, shape_t*, point_t*);
static bool intersects_square_square(shape_t*, point_t*, shape_t*, point_t*);
static bool intersects_circle_square(shape_t*, point_t*, shape_t*, point_t*);

// ---------------------------------
// --- Intersection Lookup Table ---
// ---------------------------------

intersection_handler intersection_lookup_table[][] = {
	{ intersects_circle_circle, intersects_circle_square },
	{ NULL, 										intersects_square_square }
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

// -------------
// --- Shape ---
// -------------

void shape_delete(shape_t* shape)
{
	assert(shape != NULL);

	switch(shape->shape_type) {
		case SHAPE_TYPE_CIRCLE:
			shape_circle_delete(shape);
			break;
		case SHAPE_TYPE_SQUARE:
			shape_square_delete(shape);
			break;
		case SHAPE_TYPE_COMPLEX:
			shape_complex_delete(shape);
			break;
	}
}

bool shape_intersects(shape_t* shape1, point_t* offset1, shape_t* shape2, point_t* offset2)
{
	assert(shape1 != NULL);
	assert(shape2 != NULL);

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

	if(shape1->shape_type == SHAPE_TYPE_COMPLEX){
		for(int i = 0; i < shape1->component_count; i++){
			shape_t* component = shape1->components[i];
			if(shape_intersects(component, offset1, shape2, offset2))
				return true;	
		}
		return false;
	}
	else if(shape2->shape_type == SHAPE_TYPE_COMPLEX){
		for(int i = 0; i < shape2->component_count; i++){
			shape_t* component = shape2->components[i];
			if(shape_intersects(shape1, offset1, component, offset2))
				return true;
		}
		return false;
	}
	else {
		
	}
}

// --------------
// --- Circle ---
// --------------

shape_t* shape_circle_new()
{
	shape_t* shape = malloc(sizeof(shape_circle_t));
	die(shape == NULL, "Failed to allocate circle object");
	shape->shape_type = SHAPE_TYPE_CIRCLE;
	return shape;
}

void shape_circle_init(shape_t* shape, int32_t x_coord, int32_t y_coord, int32_t radius)
{
	assert(shape != NULL);
	assert(shape->shape_type == SHAPE_TYPE_CIRCLE);
	shape_circle_t* circle = (shape_circle_t*)shape;

	circle->x_coord = x_coord;
	circle->y_coord = y_coord;
	circle->radius = radius;
}

void shape_circle_delete(shape_t* shape)
{
	assert(shape != NULL);
	assert(shape->shape_type == SHAPE_TYPE_CIRCLE);
	shape_circle_t* circle = (shape_circle_t*)shape;

	free(circle);	
}

// --------------
// --- Square ---
// --------------

shape_t* shape_square_new()
{
	shape_t* shape = malloc(sizeof(shape_square_t));
	die(shape == NULL, "Failed to allocate square object");
	shape->shape_type = SHAPE_TYPE_SQUARE;
	return shape;
}

void shape_square_init(shape_t* shape, int32_t x_coord, int32_t y_coord, int32_t size)
{
	assert(shape != NULL);
	assert(shape->shape_type == SHAPE_TYPE_SQUARE);
	shape_square_t* square = (shape_square_t*)shape;

	square->x_coord = x_coord;
	square->y_coord = y_coord;
	square->size = size;
}

void shape_square_delete(shape_t* shape)
{
	assert(shape != NULL);	
	assert(shape->shape_type == SHAPE_TYPE_SQUARE);
	shape_square_t* square = (shape_square_t*)shape;
	
	free(square);
}

// ---------------
// --- Complex ---
// ---------------

shape_t* shape_complex_new()
{
	shape_t* shape = malloc(sizeof(shape_complex_t));
	die(shape == NULL, "Failed to allocate complex shape object");
	memset(shape, 0, sizeof(shape_complex_t));
	shape->shape_type = SHAPE_TYPE_COMPLEX;
	return shape;
}

void shape_complex_init(shape_t* shape, int component_count)
{
	assert(shape != NULL);
	assert(shape->shape_type == SHAPE_TYPE_COMPLEX);
	shape_complex_t* complex = (shape_complex_t*)shape;

	complex->component_count = component_count;
	complex->components = malloc(sizeof(*complex->components) * component_count);
	die(complex->components == NULL, "Error allocating complex components array");
}

void shape_complex_delete(shape_t* shape)
{
	assert(shape != NULL);
	assert(shape->shape_type == SHAPE_TYPE_COMPLEX);
	shape_complex_t* complex = (shape_complex_t*)shape;

	if(complex->component_count > 0 && complex->components != NULL) {
		for(int i = 0; i < complex->component_count; i++){
			shape_delete(complex->components[i]);
			complex->components[i] = NULL;
		}
	}

	free(complex);
}

// -------------------------
// --- Private Functions ---
// -------------------------

static bool intersects_circle_circle(shape_t* shape1, point_t* offset1, shape_t* shape2, point_t* offset2)
{
	assert(shape1 != NULL);
	assert(offset1 != NULL);
	assert(shape2 != NULL);
	assert(offset2 != NULL);
	assert(shape1->shape_type = SHAPE_TYPE_CIRCLE);
	assert(shape2->shape_type = SHAPE_TYPE_CIRCLE);
	
	shape_circle_t* circle1 = (shape_circle_t*)shape1;
	shape_circle_t* circle2 = (shape_circle_t*)shape2;

	int32_t total_r = circle1->radius + circle2->radius;
	int32_t	delta_x = (circle1->x_coord + offset1->x) - (circle2->x_coord + offset2->x);
	int32_t delta_y = (circle1->y_coord + offset1->y) - (circle2->y_coord + offset2->y);
	float		dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	return dist > total_r;
}

static bool intersects_square_square(shape_t* shape1, point_t* offset1, shape_t* shape2, point_t* offset2)
{
	assert(shape1 != NULL);
	assert(offset1 != NULL);
	assert(shape2 != NULL);
	assert(offset2 != NULL);
	assert(shape1->shape_type = SHAPE_TYPE_SQUARE);
	assert(shape2->shape_type = SHAPE_TYPE_SQUARE);

	shape_square_t* square1 = (shape_square_t*)shape1;
	shape_square_t* square2 = (shape_square_t*)shape2;

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

static bool intersects_circle_square(shape_t* shape1, point_t* offset1, shape_t* shape2, point_t* offset2)
{
	
}

