#pragma once

#include <iostream>
#include "Graph.h"
#include "GameState.h"

enum AI {

    DEFAULT_AI, AB_AI, UNSET_AI

};

class Minimax {

private:

    int type;

    int winCount;
    int lossCount;

public:

    Minimax() {

        type = DEFAULT_AI;

        winCount = 0;
        lossCount = 0;

    }

    void setType(int type) {

        this->type = type;

    }

    // Function runs recursively and returns the score of the game state.
    int minimax(Vertex<GameState>* v, int maxPlayer, int depth = 0, int a = -500, int b = 500) {

        if (this->type == DEFAULT_AI) {

            a = -500;
            b = 500;

        }

        // If game state is terminal.
        if (v->data.done) {

            // If the max player has won (0 for X and 1 for O).
            if (v->data.hasWon(maxPlayer)) {

                return 100 - depth; // penalize move score if it takes too long

            // If the min player has won (opposite of the max player).
            } else if (v->data.hasWon(maxPlayer ? 0 : 1)) {

                return -100;

            // Game ends in tie.
            } else {

                return 0;

            }

        }

        // If it is currently the max players turn.
        if (v->data.currentTurn == maxPlayer) {

            // Set score to a number lower than possible.
            // Any value will automatically be bigger than this.
            int score = -500;

            // Iterate through the edge list.
            for (int i = 0; i < v->edgeList.size(); i++) {

                // The child of the current edge is set to child.
                Vertex<GameState>* child = v->edgeList[i]->to;

                // Score is set to the max between the current score and the best score from running minimax again.
                score = std::max(score, minimax(child, maxPlayer, depth + 1, a, b));

                if (score > b) {

                    break;

                }

                a = std::max(a, score);

            }

            return score;

        // else, it is the min players turn.
        } else {

            // Set the score to a number higher than possible.
            int score = 500;

            // Iterate through the edges.
            for (int i = 0; i < v->edgeList.size(); i++) {

                // The child of the current edge is stored.
                Vertex<GameState>* child = v->edgeList[i]->to;

                // We set score to the minimum between the current score and the score given by running minimax again
                score = std::min(score, minimax(child, maxPlayer, depth + 1, a, b));

                if (score < a) {

                    break;

                }

                b = std::min(b, score);

            }

            return score;

        }

    }

    Vec bestMove(Vertex<GameState>* v, int maxPlayer) {

        int bestScore = -500;
        Vertex<GameState>* bestState;

        // Iterate through all children.
        for (int i = 0; i < v->edgeList.size(); i++) {

            Vertex<GameState>* child = v->edgeList[i]->to;
            int score = minimax(child, maxPlayer);

            //std::cout << "score: " << score << std::endl;

            // If this score is the best we've seen, set this child to our best state and update score.
            if (score > bestScore) {

                bestState = child;

                bestScore = score;

            }

        }

        return bestState->data.lastMove;

    }

};