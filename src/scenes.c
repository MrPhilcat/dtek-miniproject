#include "scenes.h"

const Scene story_scenes[] = {
    {
      .SceneId = 20,
      .location = LOCATION_OUTSIDE,
      .description = "You are an android helping police officers. A rogue android has taken a young girl hostage on a balcony. Every second counts. \n\n >[Enter the building and go the elevator]",
      .option_count = 1,
      .options = {{"", 2}},
      .success_rate_modifier = 0,
      .gif_state_number = 2},
    {
      .SceneId = 21,
      .location = LOCATION_OUTSIDE,
      .description = "Why are you outside? go to the elevator. \n\n >[Enter the building and go the elevator]",
      .option_count = 1,
      .options = {{"", 2}},
      .success_rate_modifier = 0,
      .gif_state_number = 2},
    {
      .SceneId = 22, 
      .location = LOCATION_ELEVATOR, 
      .option_count = 2, 
      .options = {{"Greet the officer", 3}, {"Go outside", 1}}, 
      .success_rate_modifier = 0, 
      .gif_state_number = 3},
    {
        .SceneId = 2,
        .location = LOCATION_LOBBY,
        .description = "You approach the officer in charge of the operation. He glares at you with clear disgust. 'I didn't ask for a plastic detective,' he snaps.",
        .option_count = 1,
        .options = {
            {"Continue", 3} // Leads directly to Part 2
        },
        .success_rate_modifier = 0,
        .gif_state_number = 2
    },
    // Scene 3: Talking to officer - Part 2
    {
        .SceneId = 3,
        .location = LOCATION_LOBBY,
        .description = "'The deviant is on the edge of the balcony with the hostage and threatens to jump. Just do your job, machine, and get this over with.' He turns his back, dismissing you.",
        .option_count = 1,
        .options = {
            {"Go to the kitchen", 4} // Leads to the Kitchen scene
        },
        .success_rate_modifier = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 4,
        .location = LOCATION_LOBBY,
        .description = "'The deviant is on the edge of the balcony with the hostage and threatens to jump. Just do your job, machine, and get this over with.' He turns his back, dismissing you.",
        .option_count = 1,
        .options = {
            {"Go to the kitchen", 4} // Leads to the Kitchen scene
        },
        .success_rate_modifier = 0,
        .gif_state_number = 2
    },
  
  
  };
    

const int TOTAL_SCENES = sizeof(story_scenes) / sizeof(story_scenes[0]);