#pragma once

#include "GameState.h"

class Permutate {

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

    // reflects the board accross the vertical
    GameState reflectVertical(GameState game) {

        int n = game.size;
        GameState reflected;

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n/2; j++) {

                reflected.grid[i][j] = game.grid[i][n - 1 - j];

            }

        }

        return reflected;

    }

    // determine if the value of game state a is less than game state b
    bool isLess(GameState a, GameState b) {

        int n = a.size; // get the size of the game states. a.size and b.size should just be the same

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (a.grid[i][j] < b.grid[i][j]) return true; // return true if a is less than b


            }

        }

        return false; // otherwise return false

    }

};
