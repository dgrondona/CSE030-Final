#pragma once

enum playerType{

    HUMAN, AI, INVALID_PLAYER

};

struct Options {

    int player0;
    int player1;

    Options() {

        player0 = HUMAN;
        player1 = HUMAN;

    }

    Options(int player0, int player1) {

        this->player0 = player0;
        this->player1 = player1;

    }

};