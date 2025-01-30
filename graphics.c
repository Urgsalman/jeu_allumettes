#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_sticks(SDL_Renderer *renderer, int total_sticks) {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Couleur marron pour les allumettes
    int x = 100, y = 100; // Position de départ
    int spacing = 20; // Espacement entre les allumettes

    for (int i = 0; i < total_sticks; i++) {
        SDL_Rect stick = {x + i * spacing, y, 10, 50}; // Rectangle pour une allumette
        SDL_RenderFillRect(renderer, &stick);
    }
}

void draw_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int w, int h, int selected) {
    // Dessiner un rectangle pour le bouton
    SDL_SetRenderDrawColor(renderer, selected ? 255 : 0, 0, 0, 255); // Couleur rouge si sélectionné
    SDL_Rect button = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &button);

    // Afficher le texte du bouton
    SDL_Color color = {0, 0, 0, 255}; // Couleur noire
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect text_rect = {x + 10, y + 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}