#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "menu.h"
#include "game.h"
#include "rules.h"
#include "credits.h"
#include "ai.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int SDL_main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow(
        "Jeu des Allumettes",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Chargement de la police
    TTF_Font *font = TTF_OpenFont("resources/fonts/arial.ttf", 24);
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Variables du jeu
    int quit = 0;
    int selected_option = 0;
    int in_menu = 1;
    int in_game = 0;
    int in_rules = 0;
    int in_credits = 0;

    int total_sticks = 21;
    int player_turn = 0;
    int game_mode = 0; // 0: Joueur vs Joueur, 1: Joueur vs IA Facile, 2: Joueur vs IA Moyen, 3: Joueur vs IA Difficile

    // Boucle principale du jeu
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }

            if (in_menu) {
                if (handle_menu_events(&event, &selected_option)) {
                    if (selected_option == 0) {
                        in_menu = 0;
                        in_game = 1;
                        game_mode = 0; // Joueur vs Joueur
                    } else if (selected_option == 1) {
                        in_menu = 0;
                        in_game = 1;
                        game_mode = 1; // Joueur vs IA Facile
                    } else if (selected_option == 2) {
                        in_menu = 0;
                        in_game = 1;
                        game_mode = 2; // Joueur vs IA Moyen
                    } else if (selected_option == 3) {
                        in_menu = 0;
                        in_game = 1;
                        game_mode = 3; // Joueur vs IA Difficile
                    } else if (selected_option == 4) {
                        in_menu = 0;
                        in_rules = 1;
                    } else if (selected_option == 5) {
                        in_menu = 0;
                        in_credits = 1;
                    } else if (selected_option == 6) {
                        quit = 1;
                    }
                }
            } else if (in_game) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x = event.button.x;
                    int y = event.button.y;

                    // Vérifier si un bouton est cliqué pour retirer des allumettes
                    if (x >= 100 && x <= 150 && y >= 550 && y <= 600) {
                        total_sticks -= 1;
                        player_turn = !player_turn; // Changer de joueur
                    } else if (x >= 200 && x <= 250 && y >= 550 && y <= 600) {
                        total_sticks -= 2;
                        player_turn = !player_turn;
                    } else if (x >= 300 && x <= 350 && y >= 550 && y <= 600) {
                        total_sticks -= 3;
                        player_turn = !player_turn;
                    }

                    // Vérifier si le jeu est terminé
                    if (check_winner(total_sticks)) {
                        in_game = 0;
                        in_menu = 1;
                        total_sticks = 21; // Réinitialiser le jeu
                    }

                    // Tour de l'IA si en mode Joueur vs IA
                    if (game_mode != 0 && player_turn == 1) {
                        int sticks_to_remove = 0;
                        if (game_mode == 1) {
                            sticks_to_remove = ai_easy(total_sticks);
                        } else if (game_mode == 2) {
                            sticks_to_remove = ai_medium(total_sticks);
                        } else if (game_mode == 3) {
                            sticks_to_remove = ai_hard(total_sticks);
                        }
                        total_sticks -= sticks_to_remove;
                        player_turn = !player_turn;

                        // Vérifier si le jeu est terminé après le tour de l'IA
                        if (check_winner(total_sticks)) {
                            in_game = 0;
                            in_menu = 1;
                            total_sticks = 21; // Réinitialiser le jeu
                        }
                    }
                }
            } else if (in_rules) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    in_rules = 0;
                    in_menu = 1;
                }
            } else if (in_credits) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    in_credits = 0;
                    in_menu = 1;
                }
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
        SDL_RenderClear(renderer);

        if (in_menu) {
            show_menu(renderer, font, selected_option);
        } else if (in_game) {
            play_game(renderer, font, &total_sticks, &player_turn); // Correction ici
        } else if (in_rules) {
            show_rules(renderer, font);
        } else if (in_credits) {
            show_credits(renderer, font);
        }

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }

    // Nettoyage des ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}