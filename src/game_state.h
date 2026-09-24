#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#define INVENTORY_CAPACITY 3
#define TOTAL_CLUES 4

int success_rate = 50;
char *place = "Elevator";
int time = 0;

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
  CLUE_CHILD_NAME = 0,
  CLUE_DEVIANT_NAME,
  CLUE_WEAPON_MISSING,
  CLUE_FAMILY_CONFLICT
} ClueID;

typedef enum
{
  STATE_INTRO = 0,
  STATE_INVESTIGATION,
  STATE_BALCONY_STANDOFF,
  STATE_ENDING
} MainStateID;

typedef enum
{
  DIALOGUE_APPROACH = 0,
  DIALOGUE_DEMAND_COPTER,
  DIALOGUE_GUN_DECISION,
  DIALOGUE_FINAL_CHOICE
} BalconyStageID;

typedef struct
{
  MainStateID current_state;
  BalconyStageID balcony_stage;

  int location;
  int clues_discovered[TOTAL_CLUES];
  ItemID inventory[INVENTORY_CAPACITY];
  int inventory_count;

  int success_rate;
  int time;
} GameContext;

#endif