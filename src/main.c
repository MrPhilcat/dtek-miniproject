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

//Local Variables
char timeoutcount = 0;
volatile char render_gif_flag = 0;

// Define addrsses for timer values
#define TIMER_STATUS   (*(volatile unsigned short*)(0x04000020))
#define TIMER_CONTROL  (*(volatile unsigned short*)(0x04000024))
#define TIMER_PERIOD_L (*(volatile unsigned short*)(0x04000028))
#define TIMER_PERIOD_H (*(volatile unsigned short*)(0x0400002C))

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
    render_succes_rate();
    render_place();
    timer_interupt_initialize();
}

int main(void) {
    // Main program loop will go here
    startup();

    gif_state = 1;
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