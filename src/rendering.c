// rendering.c
#include "rendering.h"
#include "graphics.h"
#include "game_state.h"
#include "dtekv-lib.h"

// Call to hide terminal cursor
void hide_cursor(){
    print("\x1b[?25l");
}

// Helper function to move cursor to designated row and column
void move_cursor(unsigned int row, unsigned int col) {
    print("\x1b[");    // 1. Start the ANSI escape sequence
    print_dec(row);    // 2. Insert the Y coordinate
    printc(';');       // 3. Separator
    print_dec(col);    // 4. Insert the X coordinate
    printc('H');       // 5. Execute the move command
}

// Call to delete ALL text on entire screen
void clear_fullscreen() {
    print("\x1b[2J"); // Clear entire display
    print("\x1b[H"); // Move cursor to home position (Row 1, Col 1)
}

// Call to delete all text on the graphical display part of the screen
void clear_display() {
    // Display region sits between rows 4 and 16, columns 2 to 79 (78 characters wide)
    for (int i = 4; i <= 16; i++) {
        move_cursor(i, 2);
        print((char*)empty_row78);
    }
}

// Call to delete all text on the text display part of the screen
void clear_text() {
    // Text region sits between rows 18 and 23, columns 2 to 79 (78 characters wide)
    for (int i = 18; i <= 23; i++) {
        move_cursor(i, 2);
        print((char*)empty_row78);
    }
}

// Draw the UI background box with empty graphical/text display and placeholder info bar (XXX)
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

// Update info bar to display the current value of success_rate (1 - 3 digits)
void render_success_rate(){
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
    int col = 3;
    const int MAX_COL = 79;
    const int MAX_ROW = 23;

    move_cursor(row, col);

    while (*text != '\0') {
        // 1. Skip leading spaces if we are at the very start of a line
        while (col == 3 && *text == ' ') {
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
            if (col > 3) {
                row++;
                if (row > MAX_ROW) return; // Reached the end of the 6x78 text box, stop printing
                col = 3;
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
                col = 3;
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
            col = 3;
            move_cursor(row, col);
            text++; // Consume the newline character
        }
    }
}

void print_options(Scene scene) {
    for(int i = 0; i < scene.option_count; i++){
        move_cursor(18 + i, 3);
        if(i == current_option){
            printc('>');
        } 
        else{
            printc(' ');
        }
        print(scene.options[i].text);
    }
    
}



// Draws a static, single-frame ASCII image at the specified coordinates.
// OBS! This function does not perform bounds checking. The user is responsible 
// for ensuring the image does not overwrite UI borders or other parts of the screen.
void draw_image(const char **image, int num_rows, int start_row, int start_col) {
    for (int i = 0; i < num_rows; i++) {
        move_cursor(start_row + i, start_col);
        print((char*)image[i]);
    }
}

// Helper function to draw the next animation frame by only updating rows that changed (delta rendering)
static void render_gif_delta(const char **gif_data, int rows, int total_frames, int start_row, int start_col, int force_redraw) {
    // Not waste comute if its a single frame GIF (image)
    if (total_frames <= 1 && !force_redraw) {
        return;
    }
    
    // Find the previous frame index (wraps around to the last frame)
    int prev_frame;
    if (gif_frame == 0) {
        prev_frame = total_frames - 1; 
    } else {
        prev_frame = gif_frame - 1;
    }

    for (int i = 0; i < rows; i++) {
        // Find correct frames and go through its rows, based on rows per frame.
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
static int prev_gif_state = -1; // Always starts as dfferent

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
            // detroit_loading_gif: 6 frames total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)detroit_loading_gif, 13, 6, 4, 2, force_redraw);
            break;

        case 2:
            // skyscraper_wide_gif: 4 frames total, 13 rows each, 54 chars wide
            render_gif_delta((const char **)skyscraper_wide_gif, 13, 4, 4, 14, force_redraw);
            break;

        case 3:
            // elevator_gif: 3 frames total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)elevator_gif, 13, 3, 4, 2, force_redraw);
            break;

        case 4:
            // animal_head: 1 frame total, 9 rows each, 18 chars wide
            render_gif_delta((const char **)animal_head, 9, 1, 6, 30, force_redraw);
            break;

        case 5:
            // library_hallway_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)library_hallway_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 6:
            // kitchen_scene_empty: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)kitchen_scene_empty, 13, 1, 4, 2, force_redraw);
            break;

        case 7:
            // kitchen_scene (with tablet): 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)kitchen_scene, 13, 1, 4, 2, force_redraw);
            break;
            
        case 8:
            // sofa_and_table_scene_empty: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)sofa_and_table_scene_empty, 13, 1, 4, 2, force_redraw);
            break;

        case 9:
            // sofa_and_table_scene (with gun): 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)sofa_and_table_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 10:
            // desk_book_apple_scene_empty: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)desk_book_apple_scene_empty, 13, 1, 4, 2, force_redraw);
            break;

        case 11:
            // desk_book_apple_scene (with book): 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)desk_book_apple_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 12:
            // bathroom_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)bathroom_scene, 13, 1, 4, 2, force_redraw);
            break;
        
        case 13:
            // balcony_standoff_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_standoff_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 14:
            // balcony_empathetic_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_empathetic_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 15:
            // balcony_aggressive_scene: 2 frames total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_aggressive_scene, 13, 2, 4, 2, force_redraw);
            break;

        case 16:
            // balcony_hesitation_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_hesitation_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 17:
            // success_survived_gif: 3 frames total, 19 rows each, 78 chars wide
            render_gif_delta((const char **)success_survived_gif, 19, 3, 4, 2, force_redraw);
            break;

        case 18:
            // custom_art_frame: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)custom_art_frame, 13, 1, 4, 2, force_redraw);
            break;

        case 19:
            // game_over_sacrifice_gif: 3 frames total, 19 rows each, 78 chars wide
            render_gif_delta((const char **)game_over_sacrifice_gif, 19, 3, 4, 2, force_redraw);
            break;

        case 20:
            // game_over_fail_gif: 3 frames total, 19 rows each, 78 chars wide
            render_gif_delta((const char **)game_over_fail_gif, 19, 3, 4, 2, force_redraw);
            break;

        case 21:
            // game_over_survived_alone_gif: 3 frames total, 19 rows each, 78 chars wide
            render_gif_delta((const char **)game_over_survived_alone_gif, 19, 3, 4, 2, force_redraw);
            break;

        case 22:
            // balcony_empty_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_empty_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 23:
            // balcony_daniel_alone_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_daniel_alone_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 24:
            // balcony_daniel_dead_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_daniel_dead_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 25:
            // balcony_emma_alone_scene: 1 frame total, 13 rows each, 78 chars wide
            render_gif_delta((const char **)balcony_emma_alone_scene, 13, 1, 4, 2, force_redraw);
            break;

        case 99:
            // aiming_gif: 14 frames total, 19 rows each, 78 chars wide
            render_gif_delta((const char **)aiming_gif, 19, 14, 4, 2, force_redraw);
            break;
        
        default:
            break;
    }
}