#include "rendering.h"
#include "graphics.h"
#include "game_state.h"
#include "dtekv-lib.h"

void hide_cursor(){
    print("\x1b[?25l");
}

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

void render_succes_rate(){
    // Update Success rate
    move_cursor(2, 20);
    if (success_rate < 100 ) {printc(' ');}
    print_dec(success_rate);
    if (success_rate < 10 ) {printc(' ');}
}

void render_place(){
    // Calculate word length of place
    int length = 0;
    while (place[length] != '\0') {
        length++;
    }

    // Print place with spaces to center it (11 chars total)
    move_cursor(2, 43);
    int spaces1 = 0;
    for(int i = 0; i < ((11 - length + 1)/2); i++){ // +1 for round up
        printc(' ');
        spaces1++;
    }
    print((char*)place);
    for(int i = 0; i < (11 - length - spaces1); i++){
        printc(' ');
    }
}

void render_time(){
    move_cursor(2, 70);
    if(time < 600) {printc('0');}
    print_dec((time - (time % 60))/60);
    printc(':');
    if((time % 60) < 10) {printc('0');}
    print_dec(time % 60);
}

static int rows_match(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return 0;
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}

// Universal "delta-render" gif frame
static void render_gif_delta(const char **gif_data, int rows, int total_frames, int start_row, int start_col, int force_redraw) {
    // Find the previous frame index (wraps around to the last frame)
    int prev_frame;
    if (gif_frame == 0) {
        prev_frame = total_frames - 1; 
    } else {
        prev_frame = gif_frame - 1;
    }

    for (int i = 0; i < rows; i++) {
        // Flatten the 2D array index mathematically to support any row count
        const char *current_row_str = gif_data[gif_frame * rows + i];
        const char *prev_row_str    = gif_data[prev_frame * rows + i];

        // Redraw the row only if forced (new state) or if the characters changed
        if (force_redraw || !rows_match(current_row_str, prev_row_str)) {
            move_cursor(start_row + i, start_col);
            print((char*)current_row_str);
        }
    }

    gif_frame++;
    if (gif_frame >= total_frames) {
        gif_frame = 0;
    }
}

static int prev_gif_state = -1;

void play_gif_frame() {
    int force_redraw = 0;

    // Detect if the gif is new
    if (gif_state != prev_gif_state) {
        gif_frame = 0;             // Reset to first frame
        force_redraw = 1;          // Invalidate cache: redraw all rows
        prev_gif_state = gif_state;
    }

    switch (gif_state) {
        case 1:
            // test_gif: 12 rows, 5 frames. Drawn at row 4, col 27.
            render_gif_delta((const char **)test_gif, 12, 5, 4, 27, force_redraw);
            break;

        case 2:
            break;

        case 3:
            break;

        default:
            break;
    }
}