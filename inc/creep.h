#ifndef _creep_h
#define _creep_h

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef enum    creep_type_e  creep_type_t;
typedef struct  creep_s       creep_t;
typedef struct  creep_basic_s creep_basic_t;

// ------------------
// --- Creep Type ---
// ------------------

/// The various types of possible creeps
enum creep_type_e
{
  CREEP_TYPE_BASIC  ///< A basic creep
};

// -------------
// --- Creep ---
// -------------

/// A creep in a tower defence game
struct creep_s
{
  creep_type_t      creep_type; ///< The type of creep
  geometry_t*       shape;      ///< The bounds of the creep
  geometry_point_t  center;     ///< The center of the creep within the texture
  texture_t*        texture;    ///< The texture to draw for the creep

  geometry_point_t  position;   ///< The current position of the creep
};

/// Deletes a creep object, freeing all resources associated with it
void  creep_delete(creep_t* creep);

// -------------------
// --- Basic Creep ---
// -------------------

/// A basic creep
struct creep_basic_s
{
  creep_t   base; ///< The base creep object
};

/// Constructs a new basic creep
creep_basic_t*  creep_basic_new();

/// Deletes a basic creep
void            creep_basic_delete(creep_basic_t* creep);

#endif
