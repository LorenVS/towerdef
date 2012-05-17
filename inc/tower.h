#ifndef _towers_h
#define _towers_h

/** @file */

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef enum    tower_type_e    tower_type_t;
typedef struct  tower_s         tower_t;
typedef struct  tower_basic_s   tower_basic_t;

// ------------------
// --- Tower Type ---
// ------------------

enum tower_type_e
{
  TOWER_TYPE_BASIC
};

// -------------
// --- Tower ---
// -------------

/// The base type for a tower
struct tower_s
{
  tower_type_t      tower_type;   ///< The type of tower
  geometry_point_t  position;     ///< The position of the tower
  geometry_t*       shape;        ///< The shape of the tower
};

/// Deletes a tower object, freeing all resources associated with it
void tower_delete(tower_t* tower);

// -------------------
// --- Basic Tower ---
// -------------------

struct tower_basic_s
{
  tower_t base;   ///< The base tower object
};

/// Creates a new uninitialized basic tower object
tower_basic_t*  tower_basic_new(geometry_point_t* position);

/// Deletes a basic tower object
void            tower_basic_delete(tower_basic_t* tower);



#endif
