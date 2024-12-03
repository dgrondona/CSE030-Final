#pragma once

#include <iostream>
#include "Graph.h"
#include "GameState.h"

int minimax(Vertex<GameState>* v, int maxPlayer) {

    if (v->data.done) {

        if (v->data.hasWon(maxPlayer)) {

            return 1;

        } else if (v->data.hasWon(maxPlayer ? 0 : 1)) {

            return -1;

        } else {

            return 0;

        }

    }

    if (v->data.currentTurn == maxPlayer) {

        int score = -2;

        for (int i = 0; i < v->edgeList.size(); i++) {

            Vertex<GameState>* child = v->edgeList[i]->to;

            score = std::max(score, minimax(child, maxPlayer));

        }

        return score;

    } else {

        int score = 2;

        for (int i = 0; i < v->edgeList.size(); i++) {

            Vertex<GameState>* child = v->edgeList[i]->to;

            score = std::min(score, minimax(child, maxPlayer));

        }

        return score;

    }

}