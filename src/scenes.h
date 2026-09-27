#ifndef SCENES_H
#define SCENES_H

#include "game_state.h"

typedef struct
{
  char text[100];
  int nextSceneId;
} Option;

typedef struct
{
  int SceneId;
  LocationID location;
  char description[350];
  int option_count;
  Option options[4];
  int success_rate_modifier;
  int gif_state_number;
} Scene;

extern const Scene story_scenes[];
extern const int TOTAL_SCENES;

#endif