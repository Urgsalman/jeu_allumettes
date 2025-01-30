#include "credits.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void show_credits(SDL_Renderer *renderer, TTF_Font *font) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
    SDL_RenderClear(renderer);

    // Afficher les crédits
    SDL_Color color = {0, 0, 0, 255}; // Couleur noire
    const char *credits_text = "Crédits :\n"
                               "- Développé par [Votre Nom].\n"
                               "- Utilise SDL2 pour l'interface graphique.\n";

    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, credits_text, color, 600);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect credits_rect = {50, 50, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &credits_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Mettre à jour l'écran
    SDL_RenderPresent(renderer);
}