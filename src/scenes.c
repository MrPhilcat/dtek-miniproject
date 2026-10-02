#include "scenes.h"

const Scene story_scenes[] = {
    {
        .SceneId = 0,
        .location = LOCATION_OUTSIDE,
        .description = "You are an android helping police officers. A rogue android has taken a young girl hostage on a balcony. Every second counts. \n\n >[Enter the building and go the elevator]",
        .option_count = 1,
        .options = {{"", 2, -1}},
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2},
    {
        .SceneId = 1,
        .location = LOCATION_OUTSIDE,
        .description = "Why are you outside? go to the elevator. \n\n >[Enter the building and go the elevator]",
        .option_count = 1,
        .options = {{"", 2, -1}},
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2},
    {
        .SceneId = 2, 
        .location = LOCATION_ELEVATOR, 
        .option_count = 2, 
        .options = {{"Go up the elevator and greet the officer", 3, -1}, {"Go outside", 1, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 3},
    {
        .SceneId = 3,
        .location = LOCATION_LOBBY,
        .description = "You go up the elevator and approach the officer in charge of the operation. He glares at you with clear disgust. 'I didn't ask for a plastic detective,' he snaps. 'The deviant is on the edge of the balcony with the hostage and threatens to jump. Just do your job, machine' He turns his back, dismissing you to start your investigation.",
        .option_count = 1,
        .options = {
            {"", 4, -1},
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
        {
        .SceneId = 4,
        .location = LOCATION_LOBBY,
        .description = "",
        .option_count = 2,
        .options = {
            {"Go to the kitchen", 6, -1}, {"Go down the elevator", 7, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    
    {
        .SceneId = 5,
        .location = LOCATION_LOBBY,
        .description = "'Why are you here again? Do your job!' He turns his back, dismissing you.",
        .option_count = 2,
        .options = {
            {"Go to the kitchen", 6, -1}, {"Go down with the elevator", 7, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 6,
        .location = LOCATION_KITCHEN,
        .description = "You enter the kitchen. The room is a chaotic mess with shattered glass scattered across the floor, overturned chairs, and a flickering overhead light. On the sleek marble kitchen island, you immediately spot a cracked tablet that you can investigate to gain crucial knowledge about the perpetrator, such as his name.",
        .option_count = 1,
        .options = {
            {"", 9, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 7,
        .location = LOCATION_ELEVATOR,
        .description = "You went down the elevator",
        .option_count = 1,
        .options = {
            {"", 8, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 8,
        .location = LOCATION_ELEVATOR,
        .option_count = 2,
        .options = {
            {"Go up the elevator and greet the officer", 3, -1}, {"Go outside", 1, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 9,
        .location = LOCATION_KITCHEN,
        .option_count = 5,
        .options = {
            {"Go to the officer", 5, -1}, {"Go to the living room", 999, -1}, {"Go to the bedroom", 999, -1}, {"Go to the bathroom", 999, -1}, {"Investigate the tablet", 10, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 10,
        .location = LOCATION_KITCHEN,
        .description = "You pick up the cracked tablet from the floor and interface with its memory. You instantly download the household records. You learn that the deviant's name is Daniel, and that the family was recently planning to replace him with a newer model. This may come in use later.",
        .option_count = 1,
        .options = {
            {"", 11, -1}
        },
        .success_rate_modifier = 15,
        .clueId = CLUE_DEVIANT_NAME,
        .itemId = ITEM_JOHN_PHILLIPS_TABLET,
        .gif_state_number = 2
    },
    {
        .SceneId = 11,
        .location = LOCATION_KITCHEN,
        .option_count = 5,
        .options = {
            {"Go to the officer", 5, -1}, {"Go to the living room", 12, -1}, {"Go to the bedroom", 999, -1}, {"Go to the bathroom", 999, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 12,
        .location = LOCATION_LIVING_ROOM,
        .description = "You step out of the kitchen and enter the spacious living room. The area is trashed, with overturned furniture and shattered glass reflecting the flashing police lights from outside. As you scan the room, you spot a dropped police gun hidden under a broken coffee table.",
        .option_count = 1,
        .options = {
            {"", 13, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
    {
        .SceneId = 13,
        .location = LOCATION_LIVING_ROOM,
        .option_count = 5,
        .options = {
            {"Go to the officer", 5, -1}, {"Go to the kitchen, 14", -1}, {"Go to the living room", 12, -1}, {"Go to the bedroom", 999, -1}, {"Go to the bathroom", 999, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },
  };
    

const int TOTAL_SCENES = sizeof(story_scenes) / sizeof(story_scenes[0]);