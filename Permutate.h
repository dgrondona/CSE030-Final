#pragma once

#include "GameState.h"

// rotates the board by 90 degrees
GameState rotate(GameState game) {

    int n = game.size;
    GameState rotated;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            rotated.grid[j][n - 1 - i] = game.grid[i][j];

        }

    }

    return rotated;

}

// reflects the board accross the horizontal
GameState reflectHorizontal(GameState game) {

    int n = game.size;
    GameState reflected;

    for (int i = 0; i < n/2; i++) {

        for (int j = 0; j < n; j++) {

            reflected.grid[i][j] = game.grid[n - 1 - i][j];

        }

    }

    return reflected;

}