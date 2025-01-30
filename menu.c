#include "menu.h"
#include "graphics.h"

void show_menu(SDL_Renderer *renderer, TTF_Font *font, int selected_option) {
    // Afficher le titre du jeu
    SDL_Color color = {0, 0, 0, 255}; // Couleur noire
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Jeu des Allumettes", color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect title_rect = {200, 50, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &title_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Afficher les boutons du menu
    draw_button(renderer, font, "Jouer", 300, 200, 200, 50, selected_option == 0);
    draw_button(renderer, font, "Règles", 300, 300, 200, 50, selected_option == 1);
    draw_button(renderer, font, "Quitter", 300, 400, 200, 50, selected_option == 2);
}

int handle_menu_events(SDL_Event *event, int *selected_option) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        // Vérifier si un bouton est cliqué
        if (x >= 300 && x <= 500) {
            if (y >= 200 && y <= 250) {
                *selected_option = 0; // Jouer
                return 1;
            } else if (y >= 300 && y <= 350) {
                *selected_option = 1; // Règles
                return 1;
            } else if (y >= 400 && y <= 450) {
                *selected_option = 2; // Quitter
                return 1;
            }
        }
    }
    return 0;
}