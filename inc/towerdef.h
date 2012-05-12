#ifndef _towerdef_h
#define _towerdef_h

/** @file */

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef struct	map_s					map_t;
typedef	struct	path_s				path_t;
typedef struct	program_s			program_t;
typedef	struct	wave_s				wave_t;
typedef struct	spawn_s				spawn_t;
typedef enum		tile_type_e		tile_type_t;
typedef struct 	tile_s				tile_t;
typedef	enum		tower_type_e	tower_type_t;
typedef struct 	tower_s				tower_t;
typedef	enum		creep_type_e	creep_type_t;
typedef	struct 	creep_s				creep_t;
typedef	enum		bullet_type_e	bullet_type_t;
typedef struct 	bullet_s			bullet_t;

// -----------
// --- Map ---
// -----------

/// A map in the towerdef game
struct map_s
{
	int 				width;			///< The width of the map
	int 				height;			///< The height of the map
	tile_t			**tiles;		///< A 2d array of tiles in the map
	int					path_count;	///< The number of creep paths in the map
	path_t			*paths;			///< The creep paths in the map
	program_t		*program;		///< The program used to generate creeps
	
};

/// Creates a new uninitialized map object
map_t*		map_new();

/// Deletes a map object, freeing all resources associated with it
void			map_delete(map_t* map);

/// Loads a map from the supplied path
void			map_load(map_t* map, reader_t* path);

/// A linked-list of path coordinates that form a creep path
struct path_s
{
	int 		x;		///< The x coordinate of this entry in the path
	int 		y;		///< The y coordinate of this entry in the path
	path_t* next; ///< The next coordinate in the path
};

/// Creates a new uninitialized path object
path_t*		path_new();

/// Initializes a path object with the supplied field values
void			path_init(int x, int y, path_t* next);

/// Deletes a path object, freeing all resources associated with it
void			path_delete(path_t* path);


// ---------------
// --- Program ---
// ---------------

/// A program describes the rate and type of creeps that spawn on a map
struct program_s
{
	int				wave_count;		///< The total number of waves
	wave_t		*waves;				///< The waves in the program
};

/// Creates an uninitialized program object
program_t*		program_new();

/// Loads a program from the supplied reader
void					program_load(program_t* program, reader_t* reader);

/// Deletes a program, freeing all resources associated with it
void					program_delete(program_t* program);

/// A wave is a single level within the map
struct wave_s
{
	int 			spawn_count;	///< The total number of spawns
	spawn_t		*spawns;			///< The creep spawns
};

/// Initializes a wave object to a default state
void		wave_init(wave_t* wave);

/// Loads a wave from the supplied reader
void		wave_load(wave_t* wave, reader_t* reader);

/// Deletes a wave, freeing all resources associated with it
void		wave_delete(wave_t* wave);

/// A spawn is the generation of a single creep
struct spawn_s
{
	int 					delay; 				///< Time since the start of the wave
	creep_type_t 	creep_type;		///< The type of creep to spawn
	int						path;					///< path to spawn the creep on
};

/// Initializes a spawn object to a default state
void		spawn_init(spawn_t* spawn);

/// Loads a spawn from the supplied reader
void		spawn_load(spawn_t* spawn, reader_t* reader);

/// Deletes a spawn object, freeing all resources associated with it
void		spawn_delete(spawn_t* spawn);

// ------------
// --- Tile ---
// ------------

/// The possible types of tile
enum tile_type_e
{
	TILE_TYPE_GRASS		///< A grass tile
};

/// A single tile on a map
struct tile_s
{
	tile_type_e		tile_type;	///< The type of tile
};

// -------------
// --- Tower ---
// -------------

/// The possible types of tower
enum tower_type_e
{
	TOWER_TYPE_BASIC	///< A basic tower
};

/// A single tower on a map
struct tower_s
{
	tower_type_t 	tower_type;	///< The type of tower
	int						x_coord;		///< The x coordinate of the tower
	int						y_coord;		///< The y coordinate of the tower
};

// -------------
// --- Creep ---
// -------------

/// The possible types of creep
enum creep_type_e
{
	CREEP_TYPE_BASIC	///< A basic creep
};

/// A single creep on a map
struct creep_s
{
	creep_type_e		creep_type;		///< The type of creep
	path_t*					path;					///< The path that the creep spawned on
	int							x_coord;			///< The current x coordinate of the creep
	int							y_coord;			///< The current y coordinate of the creep
};

// --------------
// --- Bullet ---
// --------------

/// The possible types of bullet
enum bullet_type_e
{
	BULLET_TYPE_BASIC	///< A basic bullet
};

/// A single bullet on a map
struct bullet_s
{
	bullet_type_e		bullet_type;		///< The type of bullet
	int							x_coord;				///< The x coordinate of the bullet
	int							y_coord;				///< The y coordinate of the bullet
};

#endif
