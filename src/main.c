/* Below functions are external and found in other files. */
#include "dtekv-lib.h"
#include "rendering.h"
#include "graphics.h"
#include "game_state.h"
extern void enable_interrupt(void);

// Global variables
unsigned int success_rate = 50;
char *place = "Elevator";
unsigned int time = 0;
int gif_state = 0;
int gif_frame = 0;
GameContext game;

//Local Variables
char timeoutcount = 0;
volatile char render_gif_flag = 0;

// Define addrsses for timer values
#define TIMER_STATUS   (*(volatile unsigned short*)(0x04000020))
#define TIMER_CONTROL  (*(volatile unsigned short*)(0x04000024))
#define TIMER_PERIOD_L (*(volatile unsigned short*)(0x04000028))
#define TIMER_PERIOD_H (*(volatile unsigned short*)(0x0400002C))

#define BUTTON (*(volatile unsigned int*)(0x04000010))

/* Code for initializing interrupts. */
void timer_interupt_initialize(void){
  
  // Set period to 3 000 000 (1/10 of frequency)
  TIMER_PERIOD_L = 0xC6C0;
  TIMER_PERIOD_H = 0x2D;

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
    if(timeoutcount % 2){
        render_gif_flag = 1;
    }
    
    // Timer Logic
    timeoutcount++;
    if(timeoutcount >= 10){
        timeoutcount = 0; 
        time++;
        render_time();
    }
}

void startup(){
    clear_fullscreen();
    hide_cursor();
    draw_static_ui();
    render_success_rate();
    render_place();
    timer_interupt_initialize();
}

void init_game(void){
    game.location = LOCATION_ELEVATOR;
    game.inventory_count = 0;
    game.success_rate = 0;
}

int get_button_state(){
    static unsigned int last_button_state = 0;
    unsigned int current_button_state = BUTTON & 0x1;

    if (current_button_state && !last_button_state) {
        last_button_state = current_button_state;
        return 1;
    } else {
        last_button_state = current_button_state;
        return 0;
    }
}

int main(void) {
    // Main program loop will go here
    startup();
    init_game();
    const char *text = "The deviant is on the edge of the balcony with the hostage and threatens to jump. Just do your job, machine, and get this over with.' He turns his back, dismissing you.";
    print_text(text);


    gif_state = 2;
    while(1) {
        // Check if an interrupt signaled a new frame
        if (render_gif_flag) {
            render_gif_flag = 0; // Clear the flag
            play_gif_frame();
        }

        // Other non-blocking game logic goes here
        
    }
    return 0;
}