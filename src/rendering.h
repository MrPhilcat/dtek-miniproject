#ifndef RENDERING_H
#define RENDERING_H

// Function prototypes
void hide_cursor();
void clear_fullscreen();
void clear_display();
void clear_text();
void move_cursor(unsigned int row, unsigned int col);
void draw_static_ui();
void render_succes_rate();
void render_place();
void render_time();
void print_text(const char *text);
void play_gif_frame();

#endif