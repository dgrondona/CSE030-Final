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

    // determine if the value of game state a is less than game state b lexicographically
    bool isLess(GameState a, GameState b) {

        int n = a.size; // get the size of the game states. a.size and b.size should just be the same

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (a.grid[i][j] < b.grid[i][j]) return true; // return true if a is less than b


            }

        }

        return false; // otherwise return false

    }

    // find the canonical state for a given game state
    void findCanonical(GameState game) {

        // find rotations
        GameState rotated90 = rotate(game);
        GameState rotated180 = rotate(rotated90);
        GameState rotated270 = rotate(rotated180);

        // find reflections
        GameState reflectedH = reflectHorizontal(game);
        GameState reflectedV = reflectVertical(game);


        // find reflections combined with rotations

        GameState rotated90H = reflectHorizontal(rotated90);
        GameState rotated90V = reflectVertical(rotated90);

        GameState rotated180H = reflectHorizontal(rotated180);
        GameState rotated180V = reflectVertical(rotated180);

        GameState rotated270H = reflectHorizontal(rotated270);
        GameState rotated270V = reflectVertical(rotated270);


        // Compare all transformations lexicographically and find smallest one
        GameState canonical = game;

        if (isLess(rotated90, canonical)) canonical = rotated90;
        if (isLess(rotated180, canonical)) canonical = rotated180;
        if (isLess(rotated270, canonical)) canonical = rotated270;

        if (isLess(reflectedH, canonical)) canonical = reflectedH;
        if (isLess(reflectedV, canonical)) canonical = reflectedV;

        if (isLess(rotated90H, canonical)) canonical = rotated90H;
        if (isLess(rotated90V, canonical)) canonical = rotated90V;

        if (isLess(rotated180H, canonical)) canonical = rotated180H;
        if (isLess(rotated180V, canonical)) canonical = rotated180V;

        if (isLess(rotated270H, canonical)) canonical = rotated270H;
        if (isLess(rotated270V, canonical)) canonical = rotated270V;


        // canonical is now lexicographically the smallest game state



    }

};
