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

public:

    void setPlayer0(int value) {

        player0 = value;

    }

    void setPlayer1(int value) {

        player1 = value;

    }

};