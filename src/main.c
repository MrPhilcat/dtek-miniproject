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
volatile char render_gif_flag = 0;


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

    // Allow playing next gif frame (if any)
    render_gif_flag = 1;
    
    // Timer Logic
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

void startup(){
    clear_fullscreen();
    hide_cursor();
    draw_static_ui();
    render_success_rate();
    render_place();
    timer_interupt_initialize();

    game.scene_index = 0;
    place = (char *)get_location_name(game.location);
    render_place();
    game.inventory_count = 0;
    game.success_rate = 50;
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

void update_scene() {
    // Go to next scene based on selected option
    game.scene_index = story_scenes[game.scene_index].options[current_option].nextSceneId;
    current_option = 0;

    Scene scene_struct = story_scenes[game.scene_index];

    clear_text();
    clear_display();

    if (story_scenes[game.scene_index].option_count > 1){
        
    }
    else{
        print_text(scene_struct.description);
    }

    place = (char *)get_location_name(scene_struct.location);
    render_place();
    success_rate += scene_struct.success_rate_modifier;
    gif_state = scene_struct.gif_state_number;
}


int main(void)
{
    // Main program loop will go here
    startup();
    
    while(1) {
        int switch_state = get_switch_state();
        int button_state = get_button_state();

        if (button_state) {
            current_option = (current_option + 1) % story_scenes[game.scene_index].option_count;
        }
        
        if (switch_state) {
            update_scene();
        }

        // Check if an interrupt signaled a new frame
        if (render_gif_flag){
            render_gif_flag = 0; // Clear the flag
            play_gif_frame();
        }

        // Other non-blocking game logic goes here
        
    }
    return 0;
}