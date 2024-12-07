#pragma once

#include "GameState.h"

GameState rotate(GameState game) {

    int n = game.size;
    GameState rotated;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            rotated[j][n - 1 - i] = game[i][j];

        }

    }

    return rotated;

}