#ifndef RENDERING_H
#define RENDERING_H

// =========================
// Terminal & Screen Control
// =========================

// Call to hide terminal cursor
void hide_cursor();

// Call to delete ALL text on entire screen
void clear_fullscreen();

// Call to delete all text on the graphical display part of the screen
void clear_display();

// Call to delete all text on the text display part of the screen
void clear_text();


// =========================
// Static UI & Info Bar
// =========================

// Draw the UI background box with empty graphical/text display and placeholder info bar (XXX)
void draw_static_ui();

// Update info bar to display the current value of success_rate (1 - 3 digits)
void render_succes_rate();

// Update info bar to display the current value of *place (0 - 11 characters)
void render_place();

// Update info bar to display the current value of time (0 - 5999 <=> 00:00 - 99:59)
void render_time();


// =========================
// Text & Animation Rendering
// =========================

// Print the input string in the text box with proper formatting (string must fit in box).
// OBS! Doesn't automatically clear old text in the window; make sure to use clear_text() first.
void print_text(const char *text);

// Call to render the next frame of the currently active ASCII animation.
//
// HOW TO ADD A NEW GIF:
// 1. Create 'const char *new_gif[][...]' in graphics.c and graphics.h
// 2. Add a new case inside play_gif_frame() in rendering.c and call render_gif_delta() 
//    with the new GIF's specifications
// 3. Start the GIF by setting 'gif_state = [case_num]' anywhere in your code (0 = no GIF playing)
void play_gif_frame();

#endif // RENDERING_H