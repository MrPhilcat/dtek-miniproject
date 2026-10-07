// game_state.h
// Joint effort by Philipp & Aron
#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#define INVENTORY_CAPACITY 3
#define TOTAL_CLUES 4

// Rendering Logic
extern int gif_state;
extern int gif_frame;
extern volatile int current_option;

// Game Logic
extern unsigned int success_rate;
extern char *place;
extern unsigned int time;

typedef enum
{
  ITEM_NONE = 0,
  ITEM_EMMAS_TABLET,
  ITEM_JOHN_PHILLIPS_TABLET,
  ITEM_GUN,
  TOTAL_ITEMS
} ItemID;

typedef enum
{
  CLUE_NONE = 0,
  CLUE_CHILD_NAME,
  CLUE_DEVIANT_NAME,
  CLUE_WEAPON_MISSING,
  CLUE_FAMILY_CONFLICT
} ClueID;

typedef enum
{
  LOCATION_OUTSIDE = 0,
  LOCATION_ELEVATOR,
  LOCATION_LOBBY,
  LOCATION_KITCHEN,
  LOCATION_LIVING_ROOM,
  LOCATION_BEDROOM,
  LOCATION_BATHROOM,
  LOCATION_BALCONY
} LocationID;

typedef struct
{
  int scene_index;
  LocationID location;
  int clues_discovered[TOTAL_CLUES];
  ItemID inventory[TOTAL_ITEMS];
  int inventory_count;
  int success_rate;
  int time;
} GameContext;

const char *get_location_name(LocationID location);
extern GameContext game;

#endif