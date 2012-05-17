#ifndef _window_h
#define _window_h

/** @file */

// -----------------
// --- Constants ---
// -----------------

/// the width of the window
#define WINDOW_DEFAULT_WIDTH  800

/// the default height of the window
#define WINDOW_DEFAULT_HEIGHT 800

/// The default title of the window
#define WINDOW_DEFAULT_TITLE "Tower Defence"

// -----------------
// --- Delegates ---
// -----------------

typedef void(*window_draw_cb)(void);

// ----------------------------
// --- Forward Declarations ---
// ----------------------------

typedef struct window_s window_t;

// --------------
// --- Window ---
// --------------

/// Stores information about the application's window
struct window_s {
  int             width;    ///< The width of the window
  int             height;   ///< The height of the window
  const char*     title;    ///< The title of the window
  window_draw_cb  draw_cb;  ///< The draw callback for the window
};

// -----------------
// --- Functions ---
// -----------------

/// Creates a new, uninitialized window object:
window_t*   window_new();

/// Initializes the window object, setting its default values:
void        window_init(window_t* window);

/// Deletes a window, freeing any resources associated with it
void        window_delete(window_t* window);

/// Runs the window, causing it to begin rendering
void        window_run(window_t* window, int* argc, char** argv);


#endif
