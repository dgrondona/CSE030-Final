//  _____ _           _____               _____          
// |_   _(_)         |_   _|             |_   _|         
//   | |  _  ___ ______| | __ _  ___ ______| | ___   ___ 
//   | | | |/ __|______| |/ _` |/ __|______| |/ _ \ / _ \
//   | | | | (__       | | (_| | (__       | | (_) |  __/
//   \_/ |_|\___|      \_/\__,_|\___|      \_/\___/ \___|
//                                                       
// ______                             _____                     _                               _____ _                      _        ___  ___            _          _              
// |  _  \                           |  __ \                   | |                       _     /  ___| |                    (_)       |  \/  |           (_)        | |             
// | | | |_ __ __ ___   _____ _ __   | |  \/_ __ ___  _ __   __| | ___  _ __   __ _    _| |_   \ `--.| |__   __ _ _ ____   ___ _ __   | .  . | __ _ _ __  _ _ __ ___| | ____ _ _ __ 
// | | | | '__/ _` \ \ / / _ \ '_ \  | | __| '__/ _ \| '_ \ / _` |/ _ \| '_ \ / _` |  |_   _|   `--. \ '_ \ / _` | '__\ \ / / | '_ \  | |\/| |/ _` | '_ \| | '__/ _ \ |/ / _` | '__|
// | |/ /| | | (_| |\ V /  __/ | | | | |_\ \ | | (_) | | | | (_| | (_) | | | | (_| |    |_|    /\__/ / | | | (_| | |   \ V /| | | | | | |  | | (_| | | | | | | |  __/   < (_| | |   
// |___/ |_|  \__,_| \_/ \___|_| |_|  \____/_|  \___/|_| |_|\__,_|\___/|_| |_|\__,_|           \____/|_| |_|\__,_|_|    \_/ |_|_| |_| \_|  |_/\__,_|_| |_| |_|  \___|_|\_\__,_|_|   
//                                                                                                                                                      _/ |                        
//                                                                                                                                                     |__/                                                             

// Tic-Tac-Toe; Created by Draven Grondona and Sharvin Manjrekar. Base Project provided by Dr. Angelo Kyrilov.


#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Menu.h"
#include "AIPlayer.h"


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

Vertex<GameState> *buildTree(GameState &game)
{
    Graph<GameState> g;

    // The current state is the root of the tree
    Vertex<GameState> *start = new Vertex<GameState>(game);
    g.addVertex(game);

    // Dynamically expand the tree as the game progresses
    while (!game.done)
    {

        // Get the current game state
        GameState &currentState = current->data;

        // Evaluate the current game state using the countWinningChances function
        int maxPlayer = currentState.currentTurn ? 0 : 1; // Max player is 0, Min player is 1
        int minPlayer = 1 - maxPlayer;
        int maxWinningChances = currentState.countWinningChances(maxPlayer);
        int minWinningChances = currentState.countWinningChances(minPlayer);

        // Store heuristic value based on winning chances
        currentState.heuristicValue = maxWinningChances - minWinningChances;

        // If the current game state is terminal, break the loop
        if (currentState.done)
            break;

        // Explore possible moves from the current state
        bool moveFound = false;
        for (int i = 0; i < currentState.size; i++)
        {
            for (int j = 0; j < currentState.size; j++)
            {
                GameState tempState = currentState;

                // Attempt to make a move and check validity
                if (tempState.play(i, j))
                {
                    moveFound = true;

                    // Create a new child vertex
                    Vertex<GameState> *child = new Vertex<GameState>(tempState);
                    g.addVertex(child);
                    g.addDirectedEdge(current, child, 0);

                    // Update the current vertex to the child (for the next iteration of dynamic expansion)
                    current = child;

                    // Once a valid move is found, break out of the loop and proceed
                    break;
                }
            }

            if (moveFound)
                break;
        }
    }

    return current;
}

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
    AIPlayer ai;

    ai.setType(MOSTLOSS);

    // Setup game tree (Graph<GameState> g)
    GameState game;

    menu(options); // run the menu

    Vertex<GameState>* current = buildTree(game); // current vertex is outputted by the buildTree function.
    game = current->data;

    cout << game << endl;

    while (!game.done) { // main game loop

        // initialize Vec for both players
        Vec player0;
        Vec player1;

        // determine if player is human or AI
        if (options.player0 == AI) {

            player0 = ai.handleMove(current, 0);

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

                player1 = ai.handleMove(current, 1);

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