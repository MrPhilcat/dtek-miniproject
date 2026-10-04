/* Below functions are external and found in other files. */
#include "dtekv-lib.h"
#include "rendering.h"
#include "graphics.h"
#include "game_state.h"
#include "scenes.h"
extern void enable_interrupt(void);

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

#define SWITCHES (*(volatile unsigned int*)(0x04000010))
#define BUTTON (*(volatile unsigned int*)(0x040000d0))

/* Code for initializing interrupts. */
void timer_interupt_initialize(void){
  
  // Set period to 10 000 000 (1/3 of frequency)
  TIMER_PERIOD_L = 0x9680;
  TIMER_PERIOD_H = 0x98;

  // Clear old timeout flag (if any)
  TIMER_STATUS = 0b0;

  // Interupts: Yes, Looping: Yes, Start: Yes, Stop: No
  TIMER_CONTROL = 0b0111;

  enable_interrupt();
}


/* Below is the function that will be called when an interrupt is triggered. */
void handle_interrupt(unsigned cause){
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

int get_switch_state(){
    static unsigned int last_switch_state = 0;
    unsigned int current_switch_state = SWITCHES & 0x1;

    if (current_switch_state && !last_switch_state) {
        last_switch_state = current_switch_state;
        return 1;
    } else {
        last_switch_state = current_switch_state;
        return 0;
    }
}

int get_button_state()
{
    static unsigned int last_button_state = 0;
    unsigned int current_button_state = BUTTON & 0x1;

    if (current_button_state && !last_button_state)
    {
        last_button_state = current_button_state;
        return 1;
    }
    else
    {
        last_button_state = current_button_state;
        return 0;
    }
}

void update_scene()
{
    int target_scene = story_scenes[game.scene_index].options[current_option].nextSceneId;

    if (target_scene == SCENE_KITCHEN_FIRST_TEXT)
    {
        if (game.inventory[ITEM_JOHN_PHILLIPS_TABLET] == ITEM_JOHN_PHILLIPS_TABLET)
        {
            target_scene = SCENE_KITCHEN_EMPTY_TEXT;
        }
    }
    
    else if (target_scene == SCENE_LIVING_ROOM_FIRST_TEXT)
    {
        if (game.inventory[ITEM_GUN] == ITEM_GUN)
        {
            target_scene = SCENE_LIVING_ROOM_EMPTY_TEXT;
        }
    }
    
    else if (target_scene == SCENE_BEDROOM_FIRST_TEXT)
    {
        if (game.clues_discovered[CLUE_CHILD_NAME] == CLUE_CHILD_NAME)
        { 
            target_scene = SCENE_BEDROOM_EMPTY_TEXT;
        }
    }


    else if (target_scene == SCENE_KITCHEN_TABLET_LOCKED_MENU_NO_CLUE)
    {
        if (game.clues_discovered[CLUE_CHILD_NAME] == CLUE_CHILD_NAME)
        {
            target_scene = SCENE_KITCHEN_TABLET_LOCKED_MENU_HAS_CLUE;
        }
    }

    else if (target_scene == SCENE_BALCONY_INTERMEDIARY_1)
    {
        int has_name = 0;
        int has_gun = 0;

        if (game.clues_discovered[CLUE_DEVIANT_NAME] == CLUE_DEVIANT_NAME)
        {
            has_name = 1;
        }
        if (game.inventory[ITEM_GUN] == ITEM_GUN)
        {
            has_gun = 1;
        }

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
    }
    else if (target_scene == SCENE_BALCONY_INTERMEDIARY_2)
    {
        int knows_emma = 0;

        if (game.clues_discovered[CLUE_CHILD_NAME] == CLUE_CHILD_NAME)
        {
            knows_emma = 1;
        }

        if (knows_emma)
        {
            target_scene = SCENE_BALCONY_DIALOGUE_1_MENU_EMMA;
        }
        else
        {
            target_scene = SCENE_BALCONY_DIALOGUE_1_MENU_NONE;
        }
    }
    else if (target_scene == SCENE_BALCONY_CONVINCE_SUCCESS_TEXT)
    {
        // Om spelaren inte har skrapat ihop minst 99% probability, misslyckas försöket!
        if (success_rate < 99)
        {
            target_scene = SCENE_BALCONY_CONVINCE_FAIL_TEXT;
        }
    }

    game.scene_index = target_scene;
    current_option = 0;

    Scene scene_struct = story_scenes[game.scene_index];

    clear_text();
    clear_display();


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
    gif_state = scene_struct.gif_state_number;
}

int main(void)
{
    int switch_state;
    int button_state;
    
    timer_interupt_initialize();
    clear_fullscreen();
    hide_cursor();
    draw_static_ui();

    int title_status = 0;
    int startwait = 0;
    gif_state = 1;
    play_gif_frame();
    while (title_status < 5)
    {
        if (timeout_flag){
            timeout_flag = 0;
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
    print_text("Use button to toggle options and switch 1 to select.\n\n\n >[Start]");
    while (!switch_state)
    {
        switch_state = get_switch_state();
    }
    move_cursor(2, 1);
    print((char*)ui_info2);
    
    
    
    
    // Main program loop will go here
    startup();
    
    while(1) {
        comeback:
        switch_state = get_switch_state();
        button_state = get_button_state();

        if (button_state) {
            if(story_scenes[game.scene_index].option_count > 1){
                current_option = (current_option + 1) % story_scenes[game.scene_index].option_count;
                print_options(story_scenes[game.scene_index]);
            }
        }
        
        if (switch_state) {
            update_scene();
        }

        // Check if an interrupt signaled a new frame
        if (timeout_flag){
            timeout_flag = 0; // Clear the flag
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
            if(game.scene_index == SCENE_BALCONY_GUN_TESTER_TWO){
                goto quicktime;
            }
        }
    }
    quicktime:
        clear_fullscreen();
        draw_static_ui();
        gif_state = 99;
        while (1){
            if (timeout_flag){
                timeout_flag = 0; // Clear the flag
                play_gif_frame();
            }
            button_state = get_button_state();
            if(button_state){
                print("\n\a");
                move_cursor(2, 1);
                print((char*)ui_info2);
                gif_frame--;
                if (gif_frame == 3 || gif_frame == 11){
                    current_option = 0;
                }
                else if (gif_frame == 4 || gif_frame == 5 || gif_frame == 9 || gif_frame == 10){
                    current_option = 1;
                }
                else{
                    current_option = 2;
                }
                update_scene();
                goto comeback;
            }
        }

    return 0;
}