#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "LinkedList.h"
#include "MiniMax.h"


using namespace std;

// update the current game state pointer
Vertex<GameState>* getCurrent(Vertex<GameState>* current, Vec move) {

    for (int i = 0; i < current->edgeList.size(); i++) {

            Vertex<GameState>* child = current->edgeList[i]->to;

            if (child->data.lastMove == move) {

                return child;

            }

    }

    return nullptr;

}

// Ask human to input their move
// !! Make sure to check if move is valid !!
Vec askHuman(GameState game) {

    std::string a;
    std::string b;
    int x, y;

    while(true) {

        cout << "Enter coordinates (" << (game.currentTurn ? "O" : "X") << "): ";
        cin >> a >> b;

        try {

            x = std::stoi(a);
            y = std::stoi(b);

            break;

        } catch (std::exception& ex) {

            cerr << "Invalid Coordinates" << endl;

        }

    }

    return Vec(x, y);
}

// Simple AI that plays in the first open space :: remove after testing
Vec simpleAI(GameState game) {

    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if(game.play(i,j)) {
                return Vec(i,j);
            }
        }
    }

    return Vec(0,0);

}

// Main AI using MiniMax algorithm.
Vec mainAI(Vertex<GameState>* gameState, int maxPlayer) {

    Vec move = bestMove(gameState, maxPlayer); // update to take max player later

    return move;

}

Vertex<GameState>* buildTree(GameState game) {

    Graph<GameState> g;

    // Set the starting game state called "start"
    Vertex<GameState>* start = new Vertex<GameState>(game);
    g.addVertex(start);

    // Initialize LinkedList to manage vertices
    LinkedList<Vertex<GameState>*> toExpand;
    toExpand.append(start);

    // build tree
    while (!game.done && !toExpand.isEmpty()){

        // remove first vertex
        Vertex<GameState>* v = toExpand.removeFirst();

        // if vertex represents an ongoing game state
        if(!v->data.done) {

            // explore possible moves from current state
            for (int i = 0; i < game.size; i++) {

                for (int j = 0; j < game.size; j++) {

                    GameState temp = v->data;
                    bool valid = temp.play(i, j);

                    if (valid) {
                        // This was a valid move, so we can create a child vertex
                        Vertex<GameState>* u = new Vertex<GameState>(temp);
                        g.addVertex(u);

                        g.addDirectedEdge(v,u,0);

                        // Add this child to the list of vertices to expand
                        toExpand.append(u);

                    }
                }
            }


        }
        
    }

    return start;

}

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

// menu for choosing different game options
void menu(Options &options) {

    std::string option;
    int optNum;

    cout << "Hello and Welcome to Tic-Tac-Toe!" << endl;
    cout << endl;
    cout << "Game Options:" << endl;
    cout << "1. start game" << endl;
    cout << "2. change players" << endl;

    cout << endl;

    cout << "Select an Option:  ";

    cin >> option;

    try {

        optNum = std::stoi(option);

    } catch(std::exception& ex) {

        cerr << "Invalid Option. Starting Game." << endl;
        optNum = 1;

    }

    cout << endl;

    if (optNum == 2) { // change player bool in options

        // set values for player 0 and 1 to invalid
        int player0 = INVALID_PLAYER;
        int player1 = INVALID_PLAYER;

        cout << HUMAN << " - Human" << endl;
        cout << AI << " - AI" << endl;
        cout << endl;

        // ask player to input player type until they enter in a valid number
        while(player0 >= INVALID_PLAYER || player0 < 0) {

            cout << "Player 1: ";
            cin >> player0;

        }

        cout << endl;

        // ask player to input player type until they enter in a valid number
        while(player1 >= INVALID_PLAYER || player1 < 0) {

            cout << "Player 2: ";
            cin >> player1;

        }

        // update options
        options.player0 = player0;
        options.player1 = player1;

        menu(options); // call the menu recursively

    } else {

        return;

    }

}

int main(){

    Options options;

    // Setup game tree (Graph<GameState> g)
    GameState game;

    Vertex<GameState>* current = buildTree(game); // current vertex is outputted by the buildTree function.
    game = current->data;

    menu(options); // run the menu

    while (!game.done) { // main game loop

        // initialize Vec for both players
        Vec player0;
        Vec player1;

        // determine if player is human or AI
        if (options.player0 == AI) {

            player0 = mainAI(current, 0);

            game.play(player0.x, player0.y);

        } else if (options.player0 == HUMAN) {

            cout << game << endl; // only output the game before human's turn   !! make sure to update for case where there are 2 AIs !!

            player0 = askHuman(game);

            while(!game.play(player0.x, player0.y)) {

                cout << "Invalid Move! Try again buddy" << endl;

                player0 = askHuman(game);

            }

        }

        current = getCurrent(current, player0);

        // check if the game is terminal or not
        if (!game.done) {

            // determine if player is human or AI
            if (options.player1) {

                player1 = mainAI(current, 1);

                game.play(player1.x, player1.y);

            } else {

                cout << game << endl; // only output the game before human's turn

                player1 = askHuman(game);

                while(!game.play(player1.x, player1.y)) {

                    cout << "Invalid Move! Try again buddy" << endl;

                    player1 = askHuman(game);

                }

            }

            current = getCurrent(current, player1);

        }

    }

    // clear terminal
    system("clear");

    cout << game << endl;

    // announce who won once game loop ends
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