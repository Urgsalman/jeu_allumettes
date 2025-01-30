#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Dessine les allumettes
void draw_sticks(SDL_Renderer *renderer, int total_sticks);

// Dessine un bouton avec du texte
void draw_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int w, int h, int selected);

#endif // GRAPHICS_H