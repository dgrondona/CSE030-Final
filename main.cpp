#include <iostream>
#include "GameState.h"


using namespace std;

int main(){

    GameState game;

    while (!game.done){
        system("clear");
        cout << game << endl;

        int x, y;

        cout << "Enter coordinates (" << (game.currentTurn ? "O" : "X") << "): ";
        cin >> x >> y;

        game.play(x, y);
    }

    system("clear");
    cout << game << endl;

    if (game.hasWon(0)){
        cout << "X wins" << endl;
    }
    else if (game.hasWon(1)){
        cout << "O wins" << endl;
    }
    else {
        cout << "It's a tie" << endl;
    }
    cout << endl;
    
    return 0;
}