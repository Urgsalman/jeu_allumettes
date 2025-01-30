#include "game.h"
#include "graphics.h"
#include <SDL2/SDL.h>

int check_winner(int total_sticks) {
    return total_sticks <= 0; // Le joueur qui prend la dernière allumette perd
}

void play_game(SDL_Renderer *renderer, TTF_Font *font, int *total_sticks, int *player_turn) {
    // Afficher les allumettes
    draw_sticks(renderer, *total_sticks);

    // Afficher le tour du joueur
    char message[50];
    sprintf(message, "Tour du joueur %d", *player_turn + 1);
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect message_rect = {300, 500, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &message_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Gérer les événements du jeu
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;

            // Vérifier si un bouton est cliqué pour retirer des allumettes
            if (x >= 100 && x <= 150 && y >= 550 && y <= 600) {
                *total_sticks -= 1;
                *player_turn = !(*player_turn); // Changer de joueur
            } else if (x >= 200 && x <= 250 && y >= 550 && y <= 600) {
                *total_sticks -= 2;
                *player_turn = !(*player_turn);
            } else if (x >= 300 && x <= 350 && y >= 550 && y <= 600) {
                *total_sticks -= 3;
                *player_turn = !(*player_turn);
            }
        }
    }
}