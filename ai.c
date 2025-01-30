#include "ai.h"
#include <stdlib.h>
#include <time.h>

int ai_easy(int total_sticks) {
    (void)total_sticks;
    srand(time(NULL));
    return (rand() % 3) + 1; // Retire 1, 2 ou 3 allumettes au hasard
}

int ai_medium(int total_sticks) {
    if (total_sticks % 4 == 0) {
        return (rand() % 3) + 1; // Si le nombre d'allumettes est un multiple de 4, choix aléatoire
    } else {
        return total_sticks % 4; // Sinon, retirer le nombre nécessaire pour que le total soit un multiple de 4
    }
}

int ai_hard(int total_sticks) {
    if (total_sticks == 21) {
        return 1; // Toujours retirer 1 allumette au début
    } else {
        return (total_sticks - 1) % 4; // Stratégie gagnante
    }
}