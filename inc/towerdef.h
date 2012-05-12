#ifndef _towerdef_h
#define _towerdef_h

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

struct map_s
{
	int 				width;
	int 				height;
	tile_t			**tiles;
	int					path_count;
	path_t			*paths;
	program_t		*program;
	
};

struct path_s
{
	int 		x;		///< The x coordinate of this entry in the path
	int 		y;		///< The y coordinate of this entry in the path
	path_t* next; ///< The next coordinate in the path
};

// ---------------
// --- Program ---
// ---------------

struct program_s
{
	int				wave_count;		///< The total number of waves
	wave_t		*waves;				///< The waves in the program
};

struct wave_s
{
	int 			spawn_count;	///< The total number of spawns
	spawn_t		*spawns;			///< The creep spawns
};

struct spawn_s
{
	int 					delay; 				///< Time since the start of the wave
	creep_type_t 	creep_type;		///< The type of creep to spawn
	int						path;					///< path to spawn the creep on
};

// ------------
// --- Tile ---
// ------------

enum tile_type_e
{
	TILE_TYPE_GRASS
};

struct tile_s
{
	tile_type_e		tile_type;
};

// -------------
// --- Tower ---
// -------------

enum tower_type_e
{
	TOWER_TYPE_BASIC
};

struct tower_s
{
	tower_type_t 	tower_type;
	int						x_coord;
	int						y_coord;
};

// -------------
// --- Creep ---
// -------------

enum creep_type_e
{
	CREEP_TYPE_BASIC
};

struct creep_s
{
	creep_type_e		creep_type;
	path_t*					path;
	int							x_coord;
	int							y_coord;
};

// --------------
// --- Bullet ---
// --------------

enum bullet_type_e
{
	BULLET_TYPE_BASIC
};

struct bullet_s
{
	bullet_type_e		bullet_type;
	int							x_coord;
	int							y_coord;
};

#endif
