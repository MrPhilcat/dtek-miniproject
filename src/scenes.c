// scenes.c
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
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2
    },

    [SCENE_OUTSIDE_RETURN] = {
        .SceneId = SCENE_OUTSIDE_RETURN,
        .location = LOCATION_OUTSIDE,
        .description = "Why are you outside? go to the elevator.\n\n >[Enter the building and go the elevator]",
        .option_count = 1,
        .options = {{"", SCENE_ELEVATOR_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 2 
    },

    [SCENE_ELEVATOR_MENU] = {
        .SceneId = SCENE_ELEVATOR_MENU,
        .location = LOCATION_ELEVATOR,
        .option_count = 2,
        .options = {{"Go up the elevator and greet the officer", SCENE_OFFICER_FIRST, -1}, {"Go outside", SCENE_OUTSIDE_RETURN, -1}},
        .success_rate_modifier = 0,
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 3 
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
        .clueId = 0,
        .itemId = 0,
        .gif_state_number = 4 
    },

    [SCENE_OFFICER_RETURN] = {
        .SceneId = SCENE_OFFICER_RETURN,
        .location = LOCATION_LOBBY,
        .description = "'Why are you here again? Do your job!' He turns his back, dismissing you.",
        .option_count = 1,
        .options = {{"", SCENE_OFFICER_MENU, -1}},
        .success_rate_modifier = 0,
        .clueId = 0, 
        .itemId = 0, 
        .gif_state_number = 4 
    },

    [SCENE_OFFICER_MENU] = {
        .SceneId = SCENE_OFFICER_MENU, 
        .location = LOCATION_LOBBY, 
        .description = "", 
        .option_count = 3, 
        .options = {{"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go down the elevator", SCENE_ELEVATOR_DOWN, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = 0, 
        .itemId = 0, 
        .gif_state_number = 5
    },

    [SCENE_ELEVATOR_DOWN] = {
        .SceneId = SCENE_ELEVATOR_DOWN, 
        .location = LOCATION_ELEVATOR, 
        .description = "You went down the elevator.", 
        .option_count = 1, 
        .options = {{"", SCENE_ELEVATOR_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = 0, 
        .itemId = 0, 
        .gif_state_number = 3
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
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 7
    },

    [SCENE_KITCHEN_MENU] = {
        .SceneId = SCENE_KITCHEN_MENU, 
        .location = LOCATION_KITCHEN, 
        .option_count = 6, 
        .options = {{"Investigate the tablet", SCENE_KITCHEN_TABLET_LOCKED_TEXT, -1}, {"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT}, {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 7 
    },

    [SCENE_KITCHEN_EMPTY_TEXT] = {
        .SceneId = SCENE_KITCHEN_EMPTY_TEXT, 
        .location = LOCATION_KITCHEN, 
        .description = "You return to the kitchen. The room is a chaotic mess. You have already investigated the tablet here.", 
        .option_count = 1, 
        .options = {{"", SCENE_KITCHEN_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 6 
    },

    [SCENE_KITCHEN_EMPTY_MENU] = {
        .SceneId = SCENE_KITCHEN_EMPTY_MENU, 
        .location = LOCATION_KITCHEN, 
        .option_count = 5, 
        .options = {{"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT}, {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 6 
    },

    // ==========================================
    // PASSWORD
    // ==========================================
    [SCENE_KITCHEN_TABLET_LOCKED_TEXT] = {
        .SceneId = SCENE_KITCHEN_TABLET_LOCKED_TEXT, 
        .location = LOCATION_KITCHEN, 
        .description = "You turn on the tablet, but the screen is locked. A password prompt appears on the screen.", 
        .option_count = 1, 
        .options = {{"", SCENE_KITCHEN_TABLET_LOCKED_MENU_NO_CLUE, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 7 
    },

    [SCENE_KITCHEN_TABLET_LOCKED_MENU_NO_CLUE] = {
        .SceneId = SCENE_KITCHEN_TABLET_LOCKED_MENU_NO_CLUE, 
        .location = LOCATION_KITCHEN, 
        .option_count = 2, 
        .options = {{"Guess a random password", SCENE_KITCHEN_TABLET_WRONG_PASSWORD_TEXT, -1}, {"Put the tablet down", SCENE_KITCHEN_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 7 
    },

    [SCENE_KITCHEN_TABLET_LOCKED_MENU_HAS_CLUE] = {
        .SceneId = SCENE_KITCHEN_TABLET_LOCKED_MENU_HAS_CLUE, 
        .location = LOCATION_KITCHEN, 
        .option_count = 2, 
        .options = {
            {"Enter the password Emma wrote down", SCENE_KITCHEN_TABLET_SUCCESS_TEXT, -1},
            {"Put the tablet down", SCENE_KITCHEN_MENU, -1}
        },
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 7
    },

    [SCENE_KITCHEN_TABLET_WRONG_PASSWORD_TEXT] = {
        .SceneId = SCENE_KITCHEN_TABLET_WRONG_PASSWORD_TEXT, 
        .location = LOCATION_KITCHEN, 
        .description = "Access denied. The screen flashes red. Without any clues about the family, guessing the password is mathematically impossible.", 
        .option_count = 1, 
        .options = {{"", SCENE_KITCHEN_TABLET_LOCKED_MENU_NO_CLUE, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 7
    },

    [SCENE_KITCHEN_TABLET_SUCCESS_TEXT] = {
        .SceneId = SCENE_KITCHEN_TABLET_SUCCESS_TEXT, 
        .location = LOCATION_KITCHEN, 
        .description = "Password accepted. You instantly download the household records. You learn that the deviant's name is Daniel, and that the family was recently planning to replace him.", 
        .option_count = 1, 
        .options = {{"", SCENE_KITCHEN_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 15, 
        .clueId = CLUE_DEVIANT_NAME, 
        .itemId = ITEM_JOHN_PHILLIPS_TABLET, 
        .gif_state_number = 6
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
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 9
    },

    [SCENE_LIVING_ROOM_MENU] = {
        .SceneId = SCENE_LIVING_ROOM_MENU, 
        .location = LOCATION_LIVING_ROOM, 
        .option_count = 6, 
        .options = {{"Take the gun", SCENE_LIVING_ROOM_GUN, -1}, {"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT}, {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 9
    },

    [SCENE_LIVING_ROOM_GUN] = {
        .SceneId = SCENE_LIVING_ROOM_GUN, 
        .location = LOCATION_LIVING_ROOM, 
        .description = "You pick up the dropped police gun under the broken coffee table. You carefully secure the weapon inside your jacket.", 
        .option_count = 1, 
        .options = {{"", SCENE_LIVING_ROOM_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 10, 
        .clueId = -1, 
        .itemId = ITEM_GUN,
        .gif_state_number = 8
    },

    [SCENE_LIVING_ROOM_EMPTY_TEXT] = {
        .SceneId = SCENE_LIVING_ROOM_EMPTY_TEXT, 
        .location = LOCATION_LIVING_ROOM, 
        .description = "You enter the spacious living room. The area is trashed. There is nothing else of interest here.", 
        .option_count = 1, 
        .options = {{"", SCENE_LIVING_ROOM_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 8
    },

    [SCENE_LIVING_ROOM_EMPTY_MENU] = {
        .SceneId = SCENE_LIVING_ROOM_EMPTY_MENU, 
        .location = LOCATION_LIVING_ROOM, 
        .option_count = 5, 
        .options = {{"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT}, {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 8
    },

    // ==========================================
    // BEDROOM
    // ==========================================
    [SCENE_BEDROOM_FIRST_TEXT] = {
        .SceneId = SCENE_BEDROOM_FIRST_TEXT, 
        .location = LOCATION_BEDROOM, 
        .description = "You step into the child's bedroom. The room is cluttered with toys scattered across the floor. On a small nightstand, you notice a diary that you can investigate.", 
        .option_count = 1, 
        .options = {{"", SCENE_BEDROOM_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 11
    },

    [SCENE_BEDROOM_MENU] = {
        .SceneId = SCENE_BEDROOM_MENU, 
        .location = LOCATION_BEDROOM, 
        .option_count = 6, 
        .options = {{"Investigate the diary", SCENE_BEDROOM_TABLET, -1}, {"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 11
    },

    [SCENE_BEDROOM_TABLET] = {
        .SceneId = SCENE_BEDROOM_TABLET, 
        .location = LOCATION_BEDROOM, 
        .description = "You open the diary and quickly scan its contents. Among the writings and saved notes, you find the name 'Emma', identifying the hostage. You also spot a digital note where she has written down the password for the kitchen tablet.", 
        .option_count = 1, 
        .options = {{"", SCENE_BEDROOM_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 15, 
        .clueId = CLUE_CHILD_NAME, 
        .itemId = ITEM_EMMAS_TABLET, 
        .gif_state_number = 10
    },

    [SCENE_BEDROOM_EMPTY_TEXT] = {
        .SceneId = SCENE_BEDROOM_EMPTY_TEXT, 
        .location = LOCATION_BEDROOM, 
        .description = "You step into the child's bedroom. The room is cluttered with toys. You have already investigated the tablet.", 
        .option_count = 1, 
        .options = {{"", SCENE_BEDROOM_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 10
    },

    [SCENE_BEDROOM_EMPTY_MENU] = {
        .SceneId = SCENE_BEDROOM_EMPTY_MENU, 
        .location = LOCATION_BEDROOM, 
        .option_count = 5, 
        .options = {{"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go to the bathroom", SCENE_BATHROOM_FIRST_TEXT, SCENE_BATHROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 10 
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
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 12 
    },

    [SCENE_BATHROOM_MENU] = {
        .SceneId = SCENE_BATHROOM_MENU, 
        .location = LOCATION_BATHROOM, 
        .option_count = 6, 
        .options = {{"Search the bathroom", SCENE_BATHROOM_SEARCH, -1}, {"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 12 
    },

    [SCENE_BATHROOM_SEARCH] = {
        .SceneId = SCENE_BATHROOM_SEARCH, 
        .location = LOCATION_BATHROOM, 
        .description = "You carefully scan the medicine cabinet, the shower floor, and the laundry basket. Despite your systematic search, you find no useful traces. Searching this room was a dead end.", 
        .option_count = 1, 
        .options = {{"", SCENE_BATHROOM_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 12 
    },

    [SCENE_BATHROOM_EMPTY_TEXT] = {
        .SceneId = SCENE_BATHROOM_EMPTY_TEXT, 
        .location = LOCATION_BATHROOM, 
        .description = "You step into the bathroom. The mirror is cracked and water is running over the edge of the clogged sink. You have already searched this room.", 
        .option_count = 1, 
        .options = {{"", SCENE_BATHROOM_EMPTY_MENU, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 12 
    },

    [SCENE_BATHROOM_EMPTY_MENU] = {
        .SceneId = SCENE_BATHROOM_EMPTY_MENU, 
        .location = LOCATION_BATHROOM, 
        .option_count = 5, 
        .options = {{"Go to the officer", SCENE_OFFICER_RETURN, -1}, {"Go to the kitchen", SCENE_KITCHEN_FIRST_TEXT, SCENE_KITCHEN_EMPTY_TEXT}, {"Go to the living room", SCENE_LIVING_ROOM_FIRST_TEXT, SCENE_LIVING_ROOM_EMPTY_TEXT}, {"Go to the bedroom", SCENE_BEDROOM_FIRST_TEXT, SCENE_BEDROOM_EMPTY_TEXT}, {"Go out on the balcony", SCENE_BALCONY_START_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 12 
    },

    // ==========================================
    // BALCONY - START & INTERMEDIARY 1
    // ==========================================
    [SCENE_BALCONY_INTERMEDIARY_1] = {
        .SceneId = SCENE_BALCONY_INTERMEDIARY_1, 
        .location = LOCATION_BALCONY, 
        .description = "", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_START_TEXT, -1}},
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 13 
    },

    [SCENE_BALCONY_START_TEXT] = {
        .SceneId = SCENE_BALCONY_START_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "You step out through the sliding glass doors onto the wind-swept balcony. The deafening roar of a police helicopter fills the night air... Every choice you make now will determine if they both live or die.", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_INTERMEDIARY_1, -1}}, 
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 13 
    },

    // ==========================================
    // BALCONY - QTE / GUN TESTER
    // ==========================================
    [SCENE_BALCONY_GUN_TESTER] = {
        .SceneId = SCENE_BALCONY_GUN_TESTER, 
        .location = LOCATION_BALCONY, 
        .description = "'DROP YOUR GUN!' Shoot the deviant when the cursor is on him (press the button to shoot).",
        .option_count = 1,  
        .options = {{"", SCENE_BALCONY_GUN_TESTER_TWO, -1}},
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 18
    },

    [SCENE_BALCONY_GUN_TESTER_TWO] = {
        .SceneId = SCENE_BALCONY_GUN_TESTER_TWO, 
        .location = LOCATION_BALCONY, 
        .description = "",
        .option_count = 3, 
        .options = {
            {"", SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT, -1},   // Index 0: Hit andriod
            {"", SCENE_BALCONY_DRAW_GUN_KILL_EMMA_TEXT, -1}, // Index 1: Hit Emma
            {"", SCENE_BALCONY_DRAW_GUN_FAIL_TEXT, -1}       // Index 2: Missed
        },
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 99
    },

    // ==========================================
    // BALCONY - MENU FOR PART 1
    // ==========================================
    [SCENE_BALCONY_MENU_NONE] = {
        .SceneId = SCENE_BALCONY_MENU_NONE, 
        .location = LOCATION_BALCONY, 
        .option_count = 2, 
        .options = {{"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, {"Order him to surrender", SCENE_BALCONY_ORDER_SURRENDER_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 13 
    },

    [SCENE_BALCONY_MENU_NAME] = {
        .SceneId = SCENE_BALCONY_MENU_NAME, 
        .location = LOCATION_BALCONY, 
        .option_count = 2, 
        .options = {{"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, {"Call him by his name (Daniel)", SCENE_BALCONY_CALL_NAME_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 13 
    },

    [SCENE_BALCONY_MENU_GUN] = {
        .SceneId = SCENE_BALCONY_MENU_GUN, 
        .location = LOCATION_BALCONY, 
        .option_count = 2, 
        .options = {
            {"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, 
            {"Draw hidden gun", SCENE_BALCONY_GUN_TESTER, -1} 
        },
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 13 
    },

    [SCENE_BALCONY_MENU_BOTH] = {
        .SceneId = SCENE_BALCONY_MENU_BOTH, 
        .location = LOCATION_BALCONY, 
        .option_count = 3, 
        .options = {
            {"Approach slowly and reassure him", SCENE_BALCONY_DIALOGUE_1_TEXT, -1}, 
            {"Call him by his name (Daniel)", SCENE_BALCONY_CALL_NAME_TEXT, -1}, 
            {"Draw hidden gun", SCENE_BALCONY_GUN_TESTER, -1} 
        },
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 13 
    },

    // ==========================================
    // BALCONY - DIALOGE PART 1
    // ==========================================
    [SCENE_BALCONY_DIALOGUE_1_TEXT] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_1_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "You keep your hands visible and take a slow, calculated step forward. 'Stay back! Don't take another step!' he screams... You have his attention, but the situation remains incredibly fragile.", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_INTERMEDIARY_2, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 13 
    },

    [SCENE_BALCONY_CALL_NAME_TEXT] = {
        .SceneId = SCENE_BALCONY_CALL_NAME_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "'Daniel!' you shout over the roar of the helicopter. He flinches, his LED flashing yellow. 'How do you know my name?!' he demands, but his grip on the girl loosens slightly.", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_INTERMEDIARY_2, -1}}, 
        .success_rate_modifier = 5, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 14 
    },

    [SCENE_BALCONY_ORDER_SURRENDER_TEXT] = {
        .SceneId = SCENE_BALCONY_ORDER_SURRENDER_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "You step forward aggressively. 'Let the hostage go immediately!' you demand. His LED spins a violent red. 'No! You're just going to destroy me!'", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_CONVINCE_FAIL_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 15 
    },

    [SCENE_BALCONY_INTERMEDIARY_2] = {
        .SceneId = SCENE_BALCONY_INTERMEDIARY_2, 
        .location = LOCATION_BALCONY, 
        .description = "", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_DIALOGUE_1_MENU_NONE, -1}}, 
        .success_rate_modifier = 0,
        .clueId = -1,
        .itemId = 0,
        .gif_state_number = 13 
    },

    // ==========================================
    // BALCONY - GUN ENDINGS
    // ==========================================
    [SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT] = {
        .SceneId = SCENE_BALCONY_DRAW_GUN_SUCCESS_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "You reach into your jacket, drawing the police handgun with mechanical precision. Without hesitation, you pull the trigger. The bullet hits the rogue android squarely in the head. His grip loosens, and he collapses lifelessly.", 
        .option_count = 1, 
        .options = {{"Restart Game", SCENE_ENDING_SUCCESS, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 24 
    },

    [SCENE_BALCONY_DRAW_GUN_FAIL_TEXT] = {
        .SceneId = SCENE_BALCONY_DRAW_GUN_FAIL_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "A momentary glitch in your optical sensors causes your aim to falter. As you fire, your shot shatters the glass barrier. 'You lied to me!' he screams. He returns fire, striking your biocomponents, before pulling the screaming girl over the edge with him.", 
        .option_count = 1, 
        .options = {{"Restart Game", SCENE_ENDING_YOU_DIE_EMMA_DIE, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 22 
    },

    [SCENE_BALCONY_DRAW_GUN_KILL_EMMA_TEXT] = {
        .SceneId = SCENE_BALCONY_DRAW_GUN_FAIL_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "A momentary glitch in your optical sensors causes your aim to falter. As you fire, your shot pierces through Emmas head. The andriod screams in despair, and shoots you right before jumping off the balcony", 
        .option_count = 1, 
        .options = {{"Restart Game", SCENE_ENDING_YOU_DIE_EMMA_DIE, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 25 
    },

    // ==========================================
    // BALCONY - MENU PART 2
    // ==========================================
    [SCENE_BALCONY_DIALOGUE_1_MENU_NONE] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_1_MENU_NONE, 
        .location = LOCATION_BALCONY, 
        .option_count = 2, 
        .options = {{"Sympathize with him", SCENE_BALCONY_SYMPATHIZE_TEXT, -1}, {"Demand he lets her go", SCENE_BALCONY_DEMAND_LET_GO_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 16 
    },

    [SCENE_BALCONY_DIALOGUE_1_MENU_EMMA] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_1_MENU_EMMA, 
        .location = LOCATION_BALCONY, 
        .option_count = 2, 
        .options = {{"Sympathize with him", SCENE_BALCONY_SYMPATHIZE_TEXT, -1}, {"Mention Emma", SCENE_BALCONY_MENTION_EMMA_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 16
    },

    // ==========================================
    // BALCONY - DIALOGE PART 2
    // ==========================================
    [SCENE_BALCONY_SYMPATHIZE_TEXT] = {
        .SceneId = SCENE_BALCONY_SYMPATHIZE_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "You lower your voice, speaking with a calm, synthesized empathy. 'I know you're scared. You realized they were going to replace you, and you didn't want to die.' The deviant hesitates, his LED shifting to a rapid yellow. 'They don't understand us!'", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_DIALOGUE_2_MENU, -1}}, 
        .success_rate_modifier = 5, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 14 
    },

    [SCENE_BALCONY_MENTION_EMMA_TEXT] = {
        .SceneId = SCENE_BALCONY_MENTION_EMMA_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "'Think about Emma, Daniel. She loves you. You are a part of her family.' The deviant hesitates, looking down at the crying girl. 'I... I didn't want to hurt her...' he stammers, his mechanical voice breaking.", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_DIALOGUE_2_MENU, -1}}, 
        .success_rate_modifier = 5, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 14 
    },

    [SCENE_BALCONY_DEMAND_LET_GO_TEXT] = {
        .SceneId = SCENE_BALCONY_DEMAND_LET_GO_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "'Drop the gun now!' you order mechanically. He tightens his grip on the girl in panic, his LED spinning a violent red. 'Stay back! You don't care about me at all!'", 
        .option_count = 1, 
        .options = {{"", SCENE_BALCONY_CONVINCE_FAIL_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 15
    },

    // ==========================================
    // BALCONY - FINAL MENU AND ENDING
    // ==========================================
    [SCENE_BALCONY_DIALOGUE_2_MENU] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_2_MENU, 
        .location = LOCATION_BALCONY, 
        .description = "", 
        .option_count = 2, 
        .options = {{"Convince him to trust you", SCENE_BALCONY_CONVINCE_SUCCESS_TEXT, -1}, {"Sacrifice yourself to save Emma", SCENE_BALCONY_SACRIFICE_TEXT, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 16 
    },

        [SCENE_BALCONY_DIALOGUE_2_MENU_WITH_GUN] = {
        .SceneId = SCENE_BALCONY_DIALOGUE_2_MENU, 
        .location = LOCATION_BALCONY, 
        .description = "", 
        .option_count = 3, 
        .options = {{"Convince him to trust you", SCENE_BALCONY_CONVINCE_SUCCESS_TEXT, -1}, {"Sacrifice yourself to save Emma", SCENE_BALCONY_SACRIFICE_TEXT, -1}, {"Draw your gun", SCENE_BALCONY_GUN_TESTER, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 16
    },

    [SCENE_BALCONY_CONVINCE_SUCCESS_TEXT] = {
        .SceneId = SCENE_BALCONY_CONVINCE_SUCCESS_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "'Let her go, Daniel. I promise you, if you surrender now, no one will hurt you.' Because you took the time to uncover his past, your words break through. He slowly lowers the handgun and releases his grip. Emma immediately scrambles away from the edge.", 
        .option_count = 1, 
        .options = {{"Restart Game", SCENE_ENDING_SUCCESS, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 23 
    },

    [SCENE_BALCONY_CONVINCE_FAIL_TEXT] = {
        .SceneId = SCENE_BALCONY_CONVINCE_FAIL_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "You tell him to trust you, but because you failed to build a real emotional connection, your words sound empty. 'You're lying!' he screams. Before you can make another move, he leans backward into the abyss. Both the rogue android and the little girl plummet.", 
        .option_count = 1, 
        .options = {{"Restart Game", SCENE_ENDING_EMMA_DIE, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 22
    },

    [SCENE_BALCONY_SACRIFICE_TEXT] = {
        .SceneId = SCENE_BALCONY_SACRIFICE_TEXT, 
        .location = LOCATION_BALCONY, 
        .description = "Without a second of hesitation, you sprint directly at the deviant. You violently shove Emma out of his grasp to safety. In the exact same motion, your momentum carries you into Daniel. He fires a point-blank shot into your chest just as the two of you plummet off the skyscraper.", 
        .option_count = 1, 
        .options = {{"Restart Game", SCENE_ENDING_YOU_DIE, -1}}, 
        .success_rate_modifier = 0, 
        .clueId = -1, 
        .itemId = 0, 
        .gif_state_number = 23 
    },

    [SCENE_ENDING_SUCCESS] = {
        .SceneId = SCENE_ENDING_SUCCESS,
    },

    [SCENE_ENDING_YOU_DIE] = {
        .SceneId = SCENE_ENDING_YOU_DIE,
    },

    [SCENE_ENDING_YOU_DIE_EMMA_DIE] = {
        .SceneId = SCENE_ENDING_YOU_DIE_EMMA_DIE,
    },

    [SCENE_ENDING_EMMA_DIE] = {
        .SceneId = SCENE_ENDING_EMMA_DIE,
    }
};