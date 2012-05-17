#ifndef _towerdef_h
#define _towerdef_h

/** @file */

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef struct  path_s        path_t;
typedef struct  program_s     program_t;
typedef struct  wave_s        wave_t;
typedef struct  spawn_s       spawn_t;
typedef enum    creep_type_e  creep_type_t;
typedef struct  creep_s       creep_t;
typedef enum    bullet_type_e bullet_type_t;
typedef struct  bullet_s      bullet_t;

// -------------
// --- Enums ---
// -------------

/// The possible types of creep
enum creep_type_e
{
	CREEP_TYPE_BASIC ///< A basic creep
};

/// The possible types of bullet
enum bullet_type_e
{
	BULLET_TYPE_BAISC ///< A basic bullet
};

// ------------
// --- Path ---
// ------------

struct path_s
{
  int     x;    ///< The x coordinate of this entry in the path
  int     y;    ///< The y coordinate of this entry in the path
  path_t* next; ///< The next coordinate in the path
};

/// Creates a new uninitialized path object
path_t*   path_new();

/// Initializes a path object with the supplied field values
void      path_init(int x, int y, path_t* next);

/// Deletes a path object, freeing all resources associated with it
void      path_delete(path_t* path);


// ---------------
// --- Program ---
// ---------------

/// A program describes the rate and type of creeps that spawn on a map
struct program_s
{
  int       wave_count;   ///< The total number of waves
  wave_t    *waves;       ///< The waves in the program
};

/// Creates an uninitialized program object
program_t*    program_new();

/// Loads a program from the supplied reader
void          program_load(program_t* program, reader_t* reader);

/// Deletes a program, freeing all resources associated with it
void          program_delete(program_t* program);

/// A wave is a single level within the map
struct wave_s
{
  int       spawn_count;  ///< The total number of spawns
  spawn_t   *spawns;      ///< The creep spawns
};

/// Initializes a wave object to a default state
void    wave_init(wave_t* wave);

/// Loads a wave from the supplied reader
void    wave_load(wave_t* wave, reader_t* reader);

/// Deletes a wave, freeing all resources associated with it
void    wave_delete(wave_t* wave);

/// A spawn is the generation of a single creep
struct spawn_s
{
  int           delay;        ///< Time since the start of the wave
  creep_type_t  creep_type;   ///< The type of creep to spawn
  int           path;         ///< path to spawn the creep on
};

/// Initializes a spawn object to a default state
void    spawn_init(spawn_t* spawn);

/// Loads a spawn from the supplied reader
void    spawn_load(spawn_t* spawn, reader_t* reader);

/// Deletes a spawn object, freeing all resources associated with it
void    spawn_delete(spawn_t* spawn);

// -------------
// --- Creep ---
// -------------

/// A single creep on a map
struct creep_s
{
  creep_type_t    creep_type;   ///< The type of creep
  path_t*         path;         ///< The path that the creep spawned on
  int             x_coord;      ///< The current x coordinate of the creep
  int             y_coord;      ///< The current y coordinate of the creep
};

// --------------
// --- Bullet ---
// --------------

/// A single bullet on a map
struct bullet_s
{
  bullet_type_t   bullet_type;    ///< The type of bullet
  int             x_coord;        ///< The x coordinate of the bullet
  int             y_coord;        ///< The y coordinate of the bullet
};

#endif
