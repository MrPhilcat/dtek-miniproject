#include "scenes.h"

const Scene story_scenes[TOTAL_SCENES] = {
    
    // ==========================================
    // OUTSIDE & ELEVATOR
    // ==========================================
    [SCENE_OUTSIDE_START] = {
        .SceneId = SCENE_OUTSIDE_START,
        .location = LOCATION_OUTSIDE,
        .description = "You are an android helping police officers. A rogue android has taken a young girl hostage on a balcony. Every second counts.\n\n >[Enter the building and go the elevator]",
        .option_count = 1,
        .options = {{"", SCENE_ELEVATOR_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0, .itemId = 0, .gif_state_number = 2
    },
    
    [SCENE_OUTSIDE_RETURN] = {
        .SceneId = SCENE_OUTSIDE_RETURN,
        .location = LOCATION_OUTSIDE,
        .description = "Why are you outside? go to the elevator.\n\n >[Enter the building and go the elevator]",
        .option_count = 1,
        .options = {{"", SCENE_ELEVATOR_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0, .itemId = 0, .gif_state_number = 2},
    
    [SCENE_ELEVATOR_MENU] = {
        .SceneId = SCENE_ELEVATOR_MENU, 
        .location = LOCATION_ELEVATOR, 
        .option_count = 2, 
        .options = {
            {"Go up the elevator and greet the officer", SCENE_OFFICER_FIRST, -1}, 
            {"Go outside", SCENE_OUTSIDE_RETURN, -1}
        }, 
        .success_rate_modifier = 0, 
        .clueId = 0, .itemId = 0, .gif_state_number = 3
    },

    // ==========================================
    // LOBBY / OFFICER
    // ==========================================
    [SCENE_OFFICER_FIRST] = {
        .SceneId = SCENE_OFFICER_FIRST,
        .location = LOCATION_LOBBY,
        .description = "You go up the elevator and approach the officer in charge of the operation. He glares at you with clear disgust. 'I didn't ask for a plastic detective,' he snaps. 'The deviant is on the edge of the balcony... Just do your job, machine.'",
        .option_count = 1,
        .options = {{"", SCENE_OFFICER_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_OFFICER_RETURN] = {
        .SceneId = SCENE_OFFICER_RETURN,
        .location = LOCATION_LOBBY,
        .description = "'Why are you here again? Do your job!' He turns his back, dismissing you.",
        .option_count = 1,
        .options = {{"", SCENE_OFFICER_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_OFFICER_MENU] = {
        .SceneId = SCENE_OFFICER_MENU,
        .location = LOCATION_LOBBY,
        .description = "",
        .option_count = 3,
        .options = {
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, 
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go down the elevator", SCENE_ELEVATOR_DOWN, -1}
        },
        .success_rate_modifier = 0,
        .clueId = 0, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_ELEVATOR_DOWN] = {
        .SceneId = SCENE_ELEVATOR_DOWN,
        .location = LOCATION_ELEVATOR,
        .description = "You went down the elevator.",
        .option_count = 1,
        .options = {{"", SCENE_ELEVATOR_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0, .itemId = 0, .gif_state_number = 2
    },

    // ==========================================
    // KITCHEN
    // ==========================================
    [SCENE_KITCHEN_FIRST_TEXT] = {
        .SceneId = SCENE_KITCHEN_FIRST_TEXT,
        .location = LOCATION_KITCHEN,
        .description = "You enter the kitchen. The room is a chaotic mess... On the sleek marble kitchen island, you spot a cracked tablet that you can investigate.",
        .option_count = 1,
        .options = {{"", SCENE_KITCHEN_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_KITCHEN_MENU] = {
        .SceneId = SCENE_KITCHEN_MENU,
        .location = LOCATION_KITCHEN,
        .option_count = 6,
        .options = {
            {"Investigate the tablet", SCENE_KITCHEN_TABLET, -1},
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT},
            {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_KITCHEN_TABLET] = {
        .SceneId = SCENE_KITCHEN_TABLET,
        .location = LOCATION_KITCHEN,
        .description = "You instantly download the household records. You learn that the deviant's name is Daniel, and that the family was recently planning to replace him. This may come in use later.",
        .option_count = 1,
        .options = {{"", SCENE_KITCHEN_EMPTY_MENU, -1}},
        .success_rate_modifier = 15,
        .clueId = CLUE_DEVIANT_NAME, .itemId = ITEM_JOHN_PHILLIPS_TABLET, .gif_state_number = 2
    },

    [SCENE_KITCHEN_EMPTY_TEXT] = {
        .SceneId = SCENE_KITCHEN_EMPTY_TEXT,
        .location = LOCATION_KITCHEN,
        .description = "You return to the kitchen. The room is a chaotic mess. You have already investigated the tablet here.",
        .option_count = 1,
        .options = {{"", SCENE_KITCHEN_EMPTY_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_KITCHEN_EMPTY_MENU] = {
        .SceneId = SCENE_KITCHEN_EMPTY_MENU,
        .location = LOCATION_KITCHEN,
        .option_count = 5, 
        .options = {
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT},
            {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    // ==========================================
    // LIVING ROOM
    // ==========================================
    [SCENE_LIVING_ROOM_FIRST_TEXT] = {
        .SceneId = SCENE_LIVING_ROOM_FIRST_TEXT,
        .location = LOCATION_LIVING_ROOM,
        .description = "You enter the spacious living room. The area is trashed. As you scan the room, you spot a dropped police gun hidden under a broken coffee table.",
        .option_count = 1,
        .options = {{"", SCENE_LIVING_ROOM_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_LIVING_ROOM_MENU] = {
        .SceneId = SCENE_LIVING_ROOM_MENU,
        .location = LOCATION_LIVING_ROOM,
        .option_count = 6,
        .options = {
            {"Take the gun", SCENE_LIVING_ROOM_GUN, -1},
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT},
            {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT},
            {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_LIVING_ROOM_GUN] = {
        .SceneId = SCENE_LIVING_ROOM_GUN,
        .location = LOCATION_LIVING_ROOM,
        .description = "You pick up the dropped police gun under the broken coffee table. You carefully secure the weapon inside your jacket.",
        .option_count = 1,
        .options = {{"", SCENE_LIVING_ROOM_EMPTY_MENU, -1}},
        .success_rate_modifier = 10,
        .clueId = -1, .itemId = ITEM_GUN,
        .gif_state_number = 2
    },

    [SCENE_LIVING_ROOM_EMPTY_TEXT] = {
        .SceneId = SCENE_LIVING_ROOM_EMPTY_TEXT,
        .location = LOCATION_LIVING_ROOM,
        .description = "You enter the spacious living room. The area is trashed. There is nothing else of interest here.",
        .option_count = 1,
        .options = {{"", SCENE_LIVING_ROOM_EMPTY_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_LIVING_ROOM_EMPTY_MENU] = {
        .SceneId = SCENE_LIVING_ROOM_EMPTY_MENU,
        .location = LOCATION_LIVING_ROOM,
        .option_count = 5, 
        .options = {
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT},
            {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT},
            {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    // ==========================================
    // BEDROOM
    // ==========================================
    [SCENE_BEDROOM_FIRST_TEXT] = {
        .SceneId = SCENE_BEDROOM_FIRST_TEXT,
        .location = LOCATION_BEDROOM,
        .description = "You step into the child's bedroom. The room is cluttered with toys scattered across the floor. On a small nightstand, you notice a tablet that you can investigate.",
        .option_count = 1,
        .options = {{"", SCENE_BEDROOM_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BEDROOM_MENU] = {
        .SceneId = SCENE_BEDROOM_MENU,
        .location = LOCATION_BEDROOM,
        .option_count = 6,
        .options = {
            {"Investigate the tablet", SCENE_BEDROOM_TABLET, -1},
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT},
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BEDROOM_TABLET] = {
        .SceneId = SCENE_BEDROOM_TABLET,
        .location = LOCATION_BEDROOM,
        .description = "You turn on the tablet and quickly scan its contents. Among the writings and saved notes, you find the name 'Emma', identifying the hostage. The files also reveal her deep affection for Daniel.",
        .option_count = 1,
        .options = {{"", SCENE_BEDROOM_EMPTY_MENU, -1}},
        .success_rate_modifier = 15,
        .clueId = CLUE_CHILD_NAME, .itemId = ITEM_EMMAS_TABLET, .gif_state_number = 2
    },

    [SCENE_BEDROOM_EMPTY_TEXT] = {
        .SceneId = SCENE_BEDROOM_EMPTY_TEXT,
        .location = LOCATION_BEDROOM,
        .description = "You step into the child's bedroom. The room is cluttered with toys. You have already investigated the tablet.",
        .option_count = 1,
        .options = {{"", SCENE_BEDROOM_EMPTY_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BEDROOM_EMPTY_MENU] = {
        .SceneId = SCENE_BEDROOM_EMPTY_MENU,
        .location = LOCATION_BEDROOM,
        .option_count = 5, 
        .options = {
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT},
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    // ==========================================
    // BATHROOM
    // ==========================================
    [SCENE_BATHROOM_FIRST_TEXT] = {
        .SceneId = SCENE_BATHROOM_FIRST_TEXT,
        .location = LOCATION_BATHROOM,
        .description = "You step into the bathroom. The mirror is cracked and water is running over the edge of the clogged sink. Every second counts, and you can choose to search the room.",
        .option_count = 1,
        .options = {{"", SCENE_BATHROOM_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BATHROOM_MENU] = {
        .SceneId = SCENE_BATHROOM_MENU,
        .location = LOCATION_BATHROOM,
        .option_count = 6,
        .options = {
            {"Search the bathroom", SCENE_BATHROOM_SEARCH, -1},
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT},
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BATHROOM_SEARCH] = {
        .SceneId = SCENE_BATHROOM_SEARCH,
        .location = LOCATION_BATHROOM,
        .description = "You carefully scan the medicine cabinet, the shower floor, and the laundry basket. Despite your systematic search, you find no useful traces. Searching this room was a dead end.",
        .option_count = 1,
        .options = {{"", SCENE_BATHROOM_EMPTY_MENU, -1}},
        .success_rate_modifier = 0, 
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BATHROOM_EMPTY_TEXT] = {
        .SceneId = SCENE_BATHROOM_EMPTY_TEXT,
        .location = LOCATION_BATHROOM,
        .description = "You step into the bathroom. The mirror is cracked and water is running over the edge of the clogged sink. You have already searched this room.",
        .option_count = 1,
        .options = {{"", SCENE_BATHROOM_EMPTY_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BATHROOM_EMPTY_MENU] = {
        .SceneId = SCENE_BATHROOM_EMPTY_MENU,
        .location = LOCATION_BATHROOM,
        .option_count = 5, 
        .options = {
            {"Go to the officer", SCENE_OFFICER_RETURN, -1}, 
            {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT},
            {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT},
            {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT},
            {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    // ==========================================
    // BALCONY
    // ==========================================
    [SCENE_BALCONY_INTERMEDIARY_1] = {
        .SceneId = SCENE_BALCONY_INTERMEDIARY_1,
        .location = LOCATION_BALCONY,
        .description = "", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_START_TEXT, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_START_TEXT] = {
        .SceneId = SCENE_BALCONY_START_TEXT,
        .location = LOCATION_BALCONY,
        .description = "You step out through the sliding glass doors onto the wind-swept balcony. The deafening roar of a police helicopter fills the night air... Every choice you make now will determine if they both live or die.",
        .option_count = 2,
        .options = {{"", SCENE_BALCONY_GUN_TESTER, -1}, {"", SCENE_KITCHEN_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    
    [SCENE_BALCONY_GUN_TESTER] = {
        .SceneId = SCENE_BALCONY_GUN_TESTER,
        .location = LOCATION_BALCONY,
        .description = "'DROP YOUR GUN', shoot the guy when the cursor is on him",
        .option_count = 2,
        .options = {{"", SCENE_BALCONY_GUN_TESTER_TWO, -1}}
    },

    [SCENE_BALCONY_GUN_TESTER_TWO] = {
        .SceneId = SCENE_BALCONY_GUN_TESTER_TWO,

    },
    

    [SCENE_BALCONY_MENU_NONE] = {
        .SceneId = SCENE_BALCONY_MENU_NONE,
        .location = LOCATION_BALCONY,
        .option_count = 2, 
        .options = {
            {"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, 
            {"Order him to surrender", SCENE_BALCONY_CONVINCE_FAIL_TEXT, -1} 
        },
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_MENU_NAME] = {
        .SceneId = SCENE_BALCONY_MENU_NAME,
        .location = LOCATION_BALCONY,
        .option_count = 2, 
        .options = {
            {"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, 
            {"Call him by his name (Daniel)", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}
        },
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_MENU_GUN] = {
        .SceneId = SCENE_BALCONY_MENU_GUN,
        .location = LOCATION_BALCONY,
        .option_count = 2, 
        .options = {
            {"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, 
            {"Draw hidden gun", SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT, -1}
        },
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_MENU_BOTH] = {
        .SceneId = SCENE_BALCONY_MENU_BOTH,
        .location = LOCATION_BALCONY,
        .option_count = 3, 
        .options = {
            {"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, 
            {"Call him by his name (Daniel)", SCENE_BALCONY_DIALOGUE_1_TEXT, -1},
            {"Draw hidden gun", SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT, -1}
        },
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT] = {
        .SceneId = SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT,
        .location = LOCATION_BALCONY,
        .description = "You reach into your jacket, drawing the police handgun with mechanical precision. Without hesitation, you pull the trigger. The bullet hits the rogue android squarely in the head. His grip loosens, and he collapses lifelessly. The terrified girl scrambles away from the edge and runs crying into your arms.",
        .option_count = 1,
        .options = {{"Restart Game", SCENE_OUTSIDE_START, -1}}, 
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DRAW_GUN_FAIL_TEXT] = {
        .SceneId = SCENE_BALCONY_DRAW_GUN_FAIL_TEXT,
        .location = LOCATION_BALCONY,
        .description = "A momentary glitch in your optical sensors causes your aim to falter. As you fire, your shot shatters the glass barrier. 'You lied to me!' he screams. He returns fire, striking your biocomponents, before pulling the screaming girl over the edge with him.",
        .option_count = 1,
        .options = {{"Restart Game", SCENE_OUTSIDE_START, -1}}, 
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DIALOGUE_1_TEXT] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_1_TEXT,
        .location = LOCATION_BALCONY,
        .description = "You keep your hands visible and take a slow, calculated step forward. 'Stay back! Don't take another step!' he screams... You have his attention, but the situation remains incredibly fragile.",
        .option_count = 1,
        .options = {{"", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}},
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_INTERMEDIARY_2] = {
        .SceneId = SCENE_BALCONY_INTERMEDIARY_2,
        .location = LOCATION_BALCONY,
        .description = "", 
        .option_count = 1,
        .options = {{"", SCENE_BALCONY_DIALOGUE_1_MENU_NONE, -1}}, 
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DIALOGUE_1_MENU_NONE] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_1_MENU_NONE,
        .location = LOCATION_BALCONY,
        .option_count = 2, 
        .options = {
            {"Sympathize with him", SCENE_BALCONY_DIALOGUE_2_TEXT, -1}, 
            {"Demand he lets her go", SCENE_BALCONY_CONVINCE_FAIL_TEXT, -1} 
        },
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DIALOGUE_1_MENU_EMMA] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_1_MENU_EMMA,
        .location = LOCATION_BALCONY,
        .option_count = 2, 
        .options = {
            {"Sympathize with him", SCENE_BALCONY_DIALOGUE_2_TEXT, -1}, 
            {"Mention Emma", SCENE_BALCONY_DIALOGUE_2_TEXT, -1}
        },
        .success_rate_modifier = 0, .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DIALOGUE_2_TEXT] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_2_TEXT,
        .location = LOCATION_BALCONY,
        .description = "You lower your voice, speaking with a calm, synthesized empathy. 'I know you're scared. You realized they were going to replace you, and you didn't want to die.' The deviant hesitates, his LED shifting from a frantic red to a rapid yellow. 'They don't understand us!' he cries out.",
        .option_count = 1,
        .options = {{"", SCENE_BALCONY_DIALOGUE_2_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_DIALOGUE_2_MENU] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_2_MENU,
        .location = LOCATION_BALCONY,
        .description = "",
        .option_count = 2,
        .options = {
            {"Convince him to trust you", SCENE_BALCONY_CONVINCE_SUCCESS_TEXT, -1}, 
            {"Sacrifice yourself to save Emma", SCENE_BALCONY_SACRIFICE_TEXT, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_CONVINCE_SUCCESS_TEXT] = {
        .SceneId = SCENE_BALCONY_CONVINCE_SUCCESS_TEXT,
        .location = LOCATION_BALCONY,
        .description = "'Let her go, Daniel. I promise you, if you surrender now, no one will hurt you.' Because you took the time to uncover his past, your words break through. He slowly lowers the handgun and releases his grip. Emma immediately scrambles away from the edge and runs to safety.",
        .option_count = 1,
        .options = {{"Restart Game", SCENE_OUTSIDE_START, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_CONVINCE_FAIL_TEXT] = {
        .SceneId = SCENE_BALCONY_CONVINCE_FAIL_TEXT,
        .location = LOCATION_BALCONY,
        .description = "You tell him to trust you, but because you failed to build a real emotional connection, your words sound empty. 'You're lying!' he screams. Before you can make another move, he leans backward into the abyss. Both the rogue android and the little girl plummet into the darkness below.",
        .option_count = 1,
        .options = {{"Restart Game", SCENE_OUTSIDE_START, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    },

    [SCENE_BALCONY_SACRIFICE_TEXT] = {
        .SceneId = SCENE_BALCONY_SACRIFICE_TEXT,
        .location = LOCATION_BALCONY,
        .description = "Without a second of hesitation, you sprint directly at the deviant. You violently shove Emma out of his grasp to safety. In the exact same motion, your momentum carries you into Daniel. He fires a point-blank shot into your chest just as the two of you break through the glass barrier and plummet off the skyscraper.",
        .option_count = 1,
        .options = {{"Restart Game", SCENE_OUTSIDE_START, -1}},
        .success_rate_modifier = 0,
        .clueId = -1, .itemId = 0, .gif_state_number = 2
    }
};