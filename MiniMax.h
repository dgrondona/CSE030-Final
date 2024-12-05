#pragma once

#include <iostream>
#include "Graph.h"
#include "GameState.h"

// Function runs recursively and returns the score of the game state.
int minimax(Vertex<GameState>* v, int maxPlayer, int depth = 0, int a = -15, int b = 15) {

    // If game state is terminal.
    if (v->data.done) {

        // If the max player has won (0 for X and 1 for O).
        if (v->data.hasWon(maxPlayer)) {

            return 10 - depth; // penalize move score if it takes too long

        // If the min player has won (opposite of the max player).
        } else if (v->data.hasWon(maxPlayer ? 0 : 1)) {

            return -10;

        // Game ends in tie.
        } else {

            return 0

        }

    }

    // If it is currently the max players turn.
    if (v->data.currentTurn == maxPlayer) {

        // Set score to a number lower than possible.
        // Any value will automatically be bigger than this.
        int score = -15;

        // Iterate through the edge list.
        for (int i = 0; i < v->edgeList.size(); i++) {

            // The child of the current edge is set to child.
            Vertex<GameState>* child = v->edgeList[i]->to;

            // Score is set to the max between the current score and the best score from running minimax again.
            score = std::max(score, minimax(child, maxPlayer, depth++, a, b));

            if (score > b) {

                break;

            }

            a = std::max(a, score);

        }

        return score;

    // else, it is the min players turn.
    } else {

        // Set the score to a number higher than possible.
        int score = 15;

        // Iterate through the edges.
        for (int i = 0; i < v->edgeList.size(); i++) {

            // The child of the current edge is stored.
            Vertex<GameState>* child = v->edgeList[i]->to;

            // We set score to the minimum between the current score and the score given by running minimax again
            score = std::min(score, minimax(child, maxPlayer, depth++, a, b));

            if (score < a) {

                break;

            }

            b = std::min(b, score);

        }

        return score;

    }

}

Vec bestMove(Vertex<GameState>* v, int maxPlayer) {

    int bestScore = -15;
    Vertex<GameState>* bestState;

    // Iterate through all children.
    for (int i = 0; i < v->edgeList.size(); i++) {

        Vertex<GameState>* child = v->edgeList[i]->to;
        int score = minimax(child, maxPlayer);

        std::cout << "score: " << score << std::endl;

        // If this score is the best we've seen, set this child to our best state and update score.
        if (score > bestScore) {

            bestState = child;

            bestScore = score;

        }

    }

    return bestState->data.lastMove;

}