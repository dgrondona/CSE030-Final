#pragma once

#include <iostream>
#include "Graph.h"
#include "GameState.h"

#define MAXSCORE 50000
#define MINSCORE -50000
#define ALPHA (MAXSCORE + 1000)
#define BETA (MINSCORE - 1000)

enum AIType {

    DEFAULT_AI, // choose path with most wins attached
    AB_AI, // prune game tree branches that don't need to be traversed
    MOSTLOSS, // choose path that minimizes opponents wins
    UNSET_AI // nothing set

};

class AIPlayer {

private:

    int type; // type of AI

    int winCount; // number of win conditions found
    int lossCount; // number of loss conditions found

    int depth;

public:

    AIPlayer() {

        type = DEFAULT_AI;

        winCount = 0;
        lossCount = 0;

        depth = 0;

    }

    void setType(int type) {

        this->type = type;

    }

    void resetWinLoss() {

        this->winCount = 0;
        this->lossCount = 0;

    }

    // Function runs recursively and returns the score of the game state.
    int minimax(Vertex<GameState>* v, int maxPlayer, int depth = 0, int a = ALPHA, int b = BETA) {

        // If game state is terminal.
        if (v->data.done) {

            int score;

            // If the max player has won (0 for X and 1 for O).
            if (v->data.hasWon(maxPlayer)) {

                this->winCount++;

                return MAXSCORE;

            // If the min player has won (opposite of the max player).
            } else if (v->data.hasWon(maxPlayer ? 0 : 1)) {

                this->lossCount++;

                return MINSCORE;

            // Game ends in tie.
            } else {

                return 0;

            }

        }

        // If it is currently the max players turn.
        if (v->data.currentTurn == maxPlayer) {

            // Set score to a number lower than possible.
            // Any value will automatically be bigger than this.
            int score = BETA;

            // Iterate through the edge list.
            for (int i = 0; i < v->edgeList.size(); i++) {

                // The child of the current edge is set to child.
                Vertex<GameState>* child = v->edgeList[i]->to;

                // Score is set to the max between the current score and the best score from running minimax again.
                score = std::max(score, minimax(child, maxPlayer, depth + 1, a, b));

                if (score > b && this->type == AB_AI) {

                    break;

                } else if (this->type == AB_AI) {

                    a = std::max(a, score);

                }

            }

            return score;

        // else, it is the min players turn.
        } else {

            // Set the score to a number higher than possible.
            int score = ALPHA;

            // Iterate through the edges.
            for (int i = 0; i < v->edgeList.size(); i++) {

                // The child of the current edge is stored.
                Vertex<GameState>* child = v->edgeList[i]->to;

                // We set score to the minimum between the current score and the score given by running minimax again
                score = std::min(score, minimax(child, maxPlayer, depth + 1, a, b));

                if (score < a && this->type == AB_AI) {

                    break;

                } else if (this->type == AB_AI) {

                    b = std::min(b, score);

                }

            }

            return score;

        }

    }

    Vec bestMove(Vertex<GameState>* v, int maxPlayer) {

        int bestScore = BETA;
        Vertex<GameState>* bestState;

        // Iterate through all children.
        for (int i = 0; i < v->edgeList.size(); i++) {

            Vertex<GameState>* child = v->edgeList[i]->to;

            resetWinLoss();
            int score = minimax(child, maxPlayer);

            // adjust score based on 
            if (score == 0 && this->type == DEFAULT_AI) {

                score += winCount; // prioritize children with more win conditions

            }else if (score == 0 && this->type == MOSTLOSS) {

                score -= lossCount; // prioritize children with more loss conditions for opponent

            }

            // If this score is the best we've seen, set this child to our best state and update score.
            if (score > bestScore) {

                bestState = child;

                bestScore = score;

            }

        }

        return bestState->data.lastMove;

    }

    Vec handleMove(Vertex<GameState>* v, int maxPlayer) {

        if (this->type == DEFAULT_AI || this->type == AB_AI || this->type == MOSTLOSS) {

            return bestMove(v, maxPlayer);

        }

        std::cerr << "Invalid AI type" << std::endl;
        return Vec(-1, -1); // this means that the type is invalid

    }

};