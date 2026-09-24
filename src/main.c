/* Below functions are external and found in other files. */
#include "dtekv-lib.h"
#include "rendering.h"
extern void enable_interrupt(void);

// Stub for the interrupt handler expected by boot.S
void handle_interrupt(void) {
    // Interrupt logic will go here
}

int main(void) {
    // Main program loop will go here
    while(1) {
        
    }
    return 0;
}