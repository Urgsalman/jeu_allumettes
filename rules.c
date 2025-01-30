#include "rules.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void show_rules(SDL_Renderer *renderer, TTF_Font *font) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
    SDL_RenderClear(renderer);

    // Afficher les règles
    SDL_Color color = {0, 0, 0, 255}; // Couleur noire
    const char *rules_text = "Règles du jeu :\n"
                             "- 21 allumettes sont disposées.\n"
                             "- Chaque joueur retire 1, 2 ou 3 allumettes par tour.\n"
                             "- Le joueur qui prend la dernière allumette perd.\n";

    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, rules_text, color, 600);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rules_rect = {50, 50, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rules_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Mettre à jour l'écran
    SDL_RenderPresent(renderer);
}