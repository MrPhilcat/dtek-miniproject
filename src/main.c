// Below functions are external and found in other files
#include "dtekv-lib.h"
#include "rendering.h"
#include "graphics.h"
#include "game_state.h"
#include "scenes.h"

// Global variables
unsigned int success_rate = 50;
char *place = "Placeholder";
unsigned int time = 0;
int gif_state = 0;
int gif_frame = 0;
GameContext game;
volatile int current_option = 0;


//Local Variables
char timeoutcount = 0;
volatile char timeout_flag = 0; 


// Define addrsses for timer values
#define TIMER_STATUS   (*(volatile unsigned short*)(0x04000020))
#define TIMER_CONTROL  (*(volatile unsigned short*)(0x04000024))
#define TIMER_PERIOD_L (*(volatile unsigned short*)(0x04000028))
#define TIMER_PERIOD_H (*(volatile unsigned short*)(0x0400002C))

// Define addrsses for input IO
#define SWITCHES (*(volatile unsigned int*)(0x04000010))
#define BUTTON (*(volatile unsigned int*)(0x040000d0))

// How many while loop cycles before secondary input can be registered?
#define DEBOUNCE_COOLDOWN 10000 


/* Code for initializing timer. */
void timer_initialize(void) {
  
  // Set period to 10 000 000 (1/3 of frequency)
  TIMER_PERIOD_L = 0x9680;
  TIMER_PERIOD_H = 0x98;

  // Clear old timeout flag (if any)
  TIMER_STATUS = 0b0;

  // Interupts: No, Looping: Yes, Start: Yes, Stop: No
  TIMER_CONTROL = 0b0110;
}


/* Below is the function that will be called when an interrupt is triggered. */
// UNUSED, replaced with direct timeout flag polling
void handle_interrupt(unsigned cause) {
    // Reset the interrupt
    TIMER_STATUS = 0;
    // Indicate timeout
    timeout_flag = 1;
}

void startup(){
    clear_display();
    clear_text();
    render_success_rate();
    render_place();

    game.scene_index = 0;
    place = (char *)get_location_name(game.location);
    render_place();
    game.inventory_count = 0;
    game.success_rate = 50;
    game.time = 0;
    print_text(story_scenes[game.scene_index].description);
    gif_state = story_scenes[game.scene_index].gif_state_number;
}

int get_switch_state() {
    static unsigned int last_switch_state = 0;
    static int initialized = 0;
    static unsigned int cooldown = 0;

    unsigned int current_switch_state = SWITCHES & 0x1;

    // On the very first run, record the physical state of the switch so it doesn't auto trigger.
    if (!initialized) {
        last_switch_state = current_switch_state;
        initialized = 1;
        return 0;
    }

    // If the cooldown timer is active, the switch recently triggered, block input.
    if (cooldown > 0) {
        cooldown--;
        return 0;
    }

    // Edge Detection
    if (current_switch_state != last_switch_state) {
        last_switch_state = current_switch_state;
        cooldown = DEBOUNCE_COOLDOWN; // Start the debounce timer agian
        
        if (current_switch_state == 1) {
            return 1; // Trigger on the rising edge
        }
    }
    
    return 0;
}


int get_button_state()
{
    static unsigned int last_button_state = 0;
    static int initialized = 0;
    static unsigned int cooldown = 0;

    unsigned int current_button_state = BUTTON & 0x1;

    // On the very first run, record the physical state of the button so it doesn't auto trigger.
    if (!initialized)
    {
        last_button_state = current_button_state;
        initialized = 1;
        return 0;
    }

    // If the cooldown timer is active, the button recently triggered, block input.
    if (cooldown > 0)
    {
        cooldown--;
        return 0;
    }

    if (current_button_state != last_button_state)
    {
        last_button_state = current_button_state;
        cooldown = DEBOUNCE_COOLDOWN; // Start the debounce timer
        
        if (current_button_state == 1)
        {
            return 1;
        }
    }
    
    return 0;
}

void update_scene()
{
    int target_scene = story_scenes[game.scene_index].options[current_option].nextSceneId;

    switch (target_scene)
    {
        
        case SCENE_KITCHEN_FIRST_TEXT:
            if (game.inventory[ITEM_JOHN_PHILLIPS_TABLET] == ITEM_JOHN_PHILLIPS_TABLET)
            {
                target_scene = SCENE_KITCHEN_EMPTY_TEXT;
            }
            break;

        case SCENE_LIVING_ROOM_FIRST_TEXT:
            if (game.inventory[ITEM_GUN] == ITEM_GUN)
            {
                target_scene = SCENE_LIVING_ROOM_EMPTY_TEXT;
            }
            break;

        case SCENE_BEDROOM_FIRST_TEXT:
            if (game.clues_discovered[CLUE_CHILD_NAME] == CLUE_CHILD_NAME)
            { 
                target_scene = SCENE_BEDROOM_EMPTY_TEXT;
            }
            break;

        case SCENE_KITCHEN_TABLET_LOCKED_MENU_NO_CLUE:
            if (game.clues_discovered[CLUE_CHILD_NAME] == CLUE_CHILD_NAME)
            {
                target_scene = SCENE_KITCHEN_TABLET_LOCKED_MENU_HAS_CLUE;
            }
            break;

        case SCENE_BALCONY_INTERMEDIARY_1:
        {
            // Braces are required here to declare variables inside a case statement
            int has_name = (game.clues_discovered[CLUE_DEVIANT_NAME] == CLUE_DEVIANT_NAME);
            int has_gun = (game.inventory[ITEM_GUN] == ITEM_GUN);

            if (has_name && has_gun)
            {
                target_scene = SCENE_BALCONY_MENU_BOTH;
            }
            else if (has_name)
            {
                target_scene = SCENE_BALCONY_MENU_NAME;
            }
            else if (has_gun)
            {
                target_scene = SCENE_BALCONY_MENU_GUN;
            }
            else
            {
                target_scene = SCENE_BALCONY_MENU_NONE;
            }
            break;
        }

        case SCENE_BALCONY_INTERMEDIARY_2:
            // Condensed to remove the need for a local variable and brackets
            if (game.clues_discovered[CLUE_CHILD_NAME] == CLUE_CHILD_NAME)
            {
                target_scene = SCENE_BALCONY_DIALOGUE_1_MENU_EMMA;
            }
            else
            {
                target_scene = SCENE_BALCONY_DIALOGUE_1_MENU_NONE;
            }
            break;

        case SCENE_BALCONY_CONVINCE_SUCCESS_TEXT:
            if (success_rate < 88)
            {
                target_scene = SCENE_BALCONY_CONVINCE_FAIL_TEXT;
            }
            break;

        case SCENE_BALCONY_DIALOGUE_2_MENU:
            if (game.inventory[ITEM_GUN] == ITEM_GUN)
            {
                target_scene = SCENE_BALCONY_DIALOGUE_2_MENU_WITH_GUN;
            }
            // The original 'else' block assigning it to itself was removed as redundant
            break;
    }

    game.scene_index = target_scene;
    current_option = 0;

    Scene scene_struct = story_scenes[game.scene_index];

    clear_text();

    // Only wipe the screen and redraw if the image is ACTUALLY changing
    if (gif_state != scene_struct.gif_state_number){
        clear_display();
        gif_state = scene_struct.gif_state_number; 
        play_gif_frame(); // Draw the new image IMMEDIATELY, don't wait for the timer
    }
    
    if (scene_struct.option_count > 1)
    {
        print_options(scene_struct);
    }
    else
    {
        print_text(scene_struct.description);
    }


    if (scene_struct.itemId != 0)
    {
        game.inventory[scene_struct.itemId] = scene_struct.itemId;
    }


    if (scene_struct.clueId != 0 && scene_struct.clueId != -1)
    {
        game.clues_discovered[scene_struct.clueId] = scene_struct.clueId;
    }


    place = (char *)get_location_name(scene_struct.location);
    render_place();
    success_rate += scene_struct.success_rate_modifier;
}

int main(void) {
    // Variables used for storing IO polling
    int switch_state = 0;
    int button_state = 0;
    
    // Start the timer and draw the UI
    timer_initialize();
    clear_fullscreen();
    hide_cursor();
    draw_static_ui();

    // Special logic for loaging title screen with slower fps and sound effect
    int title_status = 0;
    int startwait = 0;
    gif_state = 1;
    play_gif_frame();
    while (title_status < 5)
    {
        if (TIMER_STATUS & 0b1){
            TIMER_STATUS = 0b0;
            startwait++;
            if (startwait == 3)
            {
                print("\n\a");
                startwait = 0;
                play_gif_frame();
                title_status++;
            }
        }
    }

    // Reset variable for ending
    title_status = 0;

    // Wait for input to leave title screen
    print_text("Use button to toggle options and switch 1 to select.\n\n\n >[Start]");
    while (!switch_state)
    {
        switch_state = get_switch_state();
    }
    
    // Update infobar format to show information, instead of placeholder
    move_cursor(2, 1);
    print((char*)ui_info2);
    

    
    // Intitialize core gameloop
    startup();
    while(1) {
        comeback: //After quicktime event

        // Update button values through polling
        switch_state = get_switch_state();
        button_state = get_button_state();

        // If button pressed and scene has multiple options; switch selected option and rerender the option select
        if (button_state) {
            if(story_scenes[game.scene_index].option_count > 1){
                current_option = (current_option + 1) % story_scenes[game.scene_index].option_count;
                print_options(story_scenes[game.scene_index]);
            }
        }
        
        // Switch moves the game forward (next text or choose selected option)
        if (switch_state) {
            update_scene();
        }

        // Check for timeout flag through polling
        if (TIMER_STATUS & 0b1){
            TIMER_STATUS = 0; // Clear the flag

            // Check for two special scenes with custom logic
            if(game.scene_index == SCENE_BALCONY_GUN_TESTER_TWO){
                goto quicktime;
            }
            if (game.scene_index == SCENE_ENDING_SUCCESS || game.scene_index == SCENE_ENDING_EMMA_DIE || game.scene_index == SCENE_ENDING_YOU_DIE || game.scene_index == SCENE_ENDING_YOU_DIE_EMMA_DIE)
            {
                goto ending;
            }

            // Play next frame of current GIF
            play_gif_frame();

            // Update timer
            timeoutcount++;
            if(timeoutcount >= 3){
                timeoutcount = 0; 
                time++;
                render_time();
                if (!(time % 10)){
                    success_rate--;
                    render_success_rate();
                }
            }
        }
    }
    quicktime:
        gif_state = 0;
        play_gif_frame();
        gif_state = 99;
        while (1){
            if (TIMER_STATUS & 0b1){
                TIMER_STATUS = 0; // Clear the flag
                play_gif_frame();
            }

            button_state = get_button_state();
            if(button_state){
                // Make a sound (shot)
                print("\n\a"); 
                
                // Clear terminal and redraw UI (which was "broken" by large image), no info bar needed
                clear_fullscreen();
                draw_static_ui();
                
                // Outccome based on what the player shot
                gif_frame--;
                if (gif_frame == 4 || gif_frame == 5 || gif_frame == 9 || gif_frame == 10){
                    // Shot deviant
                    current_option = 0;
                }
                else if (gif_frame == 3 || gif_frame == 11){
                    // Shot girl
                    current_option = 1;
                }
                else{
                    // Missed
                    current_option = 2;
                }
                
                // Go to next scene
                update_scene();
                goto comeback;
            }
        }
    
    ending:
        clear_fullscreen();
        draw_static_ui();
        if (game.scene_index == SCENE_ENDING_SUCCESS){
            gif_state = 17;
        }
        else if (game.scene_index == SCENE_ENDING_YOU_DIE){
            gif_state = 19;
        }
        else if (game.scene_index == SCENE_ENDING_YOU_DIE_EMMA_DIE){
            gif_state = 20;
        }
        else if (game.scene_index == SCENE_ENDING_EMMA_DIE)
        {
            gif_state = 21;
        }
        play_gif_frame();
        while (title_status < 2)
        {
            if (TIMER_STATUS & 0b1){
                TIMER_STATUS = 0;
                startwait++;
                if (startwait == 3)
                {
                    print("\n\a");
                    startwait = 0;
                    play_gif_frame();
                    title_status++;
                }
            }
        }
    while(!get_button_state()) {
        // Väntar i en oändlig loop tills knappen trycks ner
    }
        
    // 2. Rensa hela terminalen så den blir svart och tom
    clear_fullscreen();
    
    // 3. Återställ terminalens markör (motsatsen till hide_cursor)
    print("\x1b[?25h");
    
    // 4. Stäng programmet och ge tillbaka kommandotolken till användaren
    return 0;
    
}