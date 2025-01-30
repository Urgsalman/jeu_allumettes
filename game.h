#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Vérifie si le jeu est terminé
int check_winner(int total_sticks);

// Gère le déroulement du jeu
void play_game(SDL_Renderer *renderer, TTF_Font *font, int *total_sticks, int *player_turn);

#endif // GAME_H