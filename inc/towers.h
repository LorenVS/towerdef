#ifndef _towers_h
#define _towers_h

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef enum    tower_type_e    tower_type_t;
typedef struct  tower_s         tower_t;
typedef struct  tower_basic_s   tower_basic_t;

// -------------
// --- Tower ---
// -------------

struct tower_s
{
  tower_type_t    tower_type;
  int             x_coord;
  int             y_coord;
};

/// Deletes a tower object, freeing all resources associated with it
void tower_delete(tower_t* tower);

// -------------------
// --- Basic Tower ---
// -------------------

/// Creates a new uninitialized basic tower object
tower_t*  tower_basic_new();

/// Deletes a basic tower object
void      tower_basic_delete(tower_t* tower);



#endif
