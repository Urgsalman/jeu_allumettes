#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Affiche le menu principal
void show_menu(SDL_Renderer *renderer, TTF_Font *font, int selected_option);

// Gère les événements du menu
int handle_menu_events(SDL_Event *event, int *selected_option);

#endif // MENU_H