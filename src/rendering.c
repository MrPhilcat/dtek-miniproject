#include "rendering.h"
#include "graphics.h"
#include "game_state.h"
#include "dtekv-lib.h"

// Call to hide terminal cursor
void hide_cursor(){
    print("\x1b[?25l");
}

// Helper function to move cursor to designated row and column
static void move_cursor(unsigned int row, unsigned int col) {
    print("\x1b[");    // 1. Start the ANSI escape sequence
    print_dec(row);    // 2. Insert the Y coordinate
    printc(';');       // 3. Separator
    print_dec(col);    // 4. Insert the X coordinate
    printc('H');       // 5. Execute the move command
}

// Call to delete ALL text on entire screen
void clear_fullscreen() {
    // \x1b[   -> Start escape sequence
    // 2J      -> Clear entire display
    print("\x1b[2J");
    // \x1b[H  -> Move cursor to home position (Row 1, Col 1)
    print("\x1b[H"); 
}

// Call to delete all text on the graphical display part of the screen
void clear_display() {
    // Display region sits between rows 4 and 16, columns 2 to 79 (78 characters wide)
    for (int i = 4; i <= 16; i++) {
        move_cursor(i, 2);
        for (int j = 0; j < 78; j++) {
            printc(' ');
        }
    }
}

// Call to delete all text on the text display part of the screen
void clear_text() {
    // Text region sits between rows 18 and 23, columns 2 to 79 (78 characters wide)
    for (int i = 18; i <= 23; i++) {
        move_cursor(i, 2);
        for (int j = 0; j < 78; j++) {
            printc(' ');
        }
    }
}

// Draw the UI background box with empty graphical/text display and placeholder info bar (XXX)
void draw_static_ui() {
    // Draw Borders (Rows 1, 3, 17 & 24)
    int rows[] = {1, 3, 17, 24};
    for(int j = 0; j < 4; j++){
        move_cursor(rows[j], 1);
        print(ui_line);
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

// Update info bar to display the current value of success_rate (1 - 3 digits)
void render_succes_rate(){
    // Update Success rate
    move_cursor(2, 20);
    if (success_rate < 100 ) {printc(' ');}
    print_dec(success_rate);
    if (success_rate < 10 ) {printc(' ');}
}

// Update info bar to display the current value of *place (0 - 11 characters)
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

// Update info bar to display the current value of time (0 - 5999 <=> 00:00 - 99:59)
void render_time(){
    move_cursor(2, 70);
    if(time < 600) {printc('0');}
    print_dec((time - (time % 60))/60);
    printc(':');
    if((time % 60) < 10) {printc('0');}
    print_dec(time % 60);
}

// Helper function to check if to strings ("rows") are the same
static int rows_match(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return 0;
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}

// Print the input string in the text box with proper formating (string must fit in box)
// OBS! Doesn't automatically clear old text in the window, make sure to use clear_text();
void print_text(const char *text) {
    int row = 18;
    int col = 2;
    const int MAX_COL = 79;
    const int MAX_ROW = 23;

    move_cursor(row, col);

    while (*text != '\0') {
        // 1. Skip leading spaces if we are at the very start of a line
        while (col == 2 && *text == ' ') {
            text++;
        }

        if (*text == '\0') break;

        // 2. Find the length of the current word
        // (A word ends at a space, a newline, or the null terminator)
        int word_len = 0;
        while (text[word_len] != ' ' && text[word_len] != '\n' && text[word_len] != '\0') {
            word_len++;
        }

        // 3. Check if the word fits on the current line
        if (col + word_len - 1 > MAX_COL) {
            // If we are not already at the start of the line, wrap down
            if (col > 2) {
                row++;
                if (row > MAX_ROW) return; // Reached the end of the 6x78 text box, stop printing
                col = 2;
                move_cursor(row, col);
                continue; // Re-evaluate this exact same word on the new line
            }
            // If col == 2, the word itself is larger than 78 characters.
            // We fall through and let the print loop truncate/force-break it.
        }

        // 4. Print the word character by character
        for (int i = 0; i < word_len; i++) {
            printc(*text);
            text++;
            col++;

            // Failsafe: force a line break if a single massive word exceeds the right edge
            if (col > MAX_COL && i < word_len - 1) {
                row++;
                if (row > MAX_ROW) return; // Text box full
                col = 2;
                move_cursor(row, col);
            }
        }

        // 5. Handle the space or newline immediately following the word
        if (*text == ' ') {
            // Only print the space if it won't bleed past our bounding box
            if (col <= MAX_COL) {
                printc(' ');
                col++;
            }
            text++; // Consume the space character
        } 
        else if (*text == '\n') {
            // Respect intentional line breaks in the string
            row++;
            if (row > MAX_ROW) return;
            col = 2;
            move_cursor(row, col);
            text++; // Consume the newline character
        }
    }
}

// Helper function to draw the next animation frame by only updating rows that changed (delta rendering)
static void render_gif_delta(const char **gif_data, int rows, int total_frames, int start_row, int start_col, int force_redraw) {
    // Find the previous frame index (wraps around to the last frame)
    int prev_frame;
    if (gif_frame == 0) {
        prev_frame = total_frames - 1; 
    } else {
        prev_frame = gif_frame - 1;
    }

    for (int i = 0; i < rows; i++) {
        // Interprit input array according to its totalt amount of rows
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

// Global variable to keep track if gif has changed
static int prev_gif_state = -1;

// Call to render the next frame of the currently active ASCII animation.
//
// HOW TO ADD A NEW GIF:
// 1. Create 'const char *new_gif[][...]' in graphics.c and graphics.h
// 2. Add a new case below and call render_gif_delta() with the new GIF's specifications
// 3. Start the GIF by setting 'gif_state = [case_num]' anywhere in your code (0 = no GIF playing)
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