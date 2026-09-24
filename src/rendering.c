#include "rendering.h"
#include "graphics.h"
#include "dtekv-lib.h" // Include this if your rendering logic needs print()

void clear_screen() {
    // \x1b[   -> Start escape sequence
    // 2J      -> Clear entire display
    print("\x1b[2J");
    // \x1b[H  -> Move cursor to home position (Row 1, Col 1)
    print("\x1b[H"); 
}

void move_cursor(unsigned int row, unsigned int col) {
    print("\x1b[");    // 1. Start the ANSI escape sequence
    print_dec(row);    // 2. Insert the Y coordinate
    printc(';');       // 3. Separator
    print_dec(col);    // 4. Insert the X coordinate
    printc('H');       // 5. Execute the move command
}

void draw_static_ui() {
    // Draw Borders (Rows 1, 3, 17 & 24)
    int rows[] = {1, 3, 17, 24};
    for(int j = 0; j < 4; j++){
        move_cursor(rows[j], 1);
        print((char*)ui_line);
    }
    
    // Draw Info (Row 2)
    move_cursor(2, 1);
    print((char*)ui_info);
    
    // Draw the vertical walls for the visual screen and text box
    for (int i = 4; i <= 23; i++) {
        if (i == 17) continue; // Skip the divider rows
        
        move_cursor(i, 1);  // Left wall
        printc('|');
        
        move_cursor(i, 80); // Right wall
        printc('|');
    }
}

void update_info(){
    
}