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

Vertex<GameState> *buildTree(GameState &game, Vertex<GameState> *current)
{
    Graph<GameState> g;

    // Add the current state as the root of the tree
    g.addVertex(current);

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

        // Calculate heuristic value based on the difference in winning chances
        int heuristicValue = maxWinningChances - minWinningChances;

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

    return current; // Return the last current state after all moves have been played
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

int main()
{
    Options options;
    AIPlayer ai;

    ai.setType(DEFAULT_AI);

    GameState game;

    menu(options); // run the menu

    Vertex<GameState> *current = new Vertex<GameState>(game);

    // Build the tree dynamically after every move
    while (!game.done)
    { // main game loop

        // Get the current game state reference
        GameState &currentState = current->data;

        // Check whose turn it is and handle move accordingly
        Vec player0, player1;
        if (options.player0 == AI)
        {

            player0 = ai.handleMove(current, 0);
            game.play(player0.x, player0.y);
        }
        else if (options.player0 == HUMAN)
        {

            cout << game << endl;
            player0 = askHuman(game);

            while (!game.play(player0.x, player0.y))
            {
                cout << "Invalid Move! Try again buddy" << endl;
                player0 = askHuman(game);
            }
        }

        // Update current vertex by finding the corresponding child
        current = buildTree(game, current);

        // Now the current vertex represents the new game state after player 0's move

        if (!game.done)
        { 

            if (options.player1 == AI)
            {

                player1 = ai.handleMove(current, 1);
                game.play(player1.x, player1.y);
            }
            else if (options.player1 == HUMAN)
            {
                cout << game << endl;
                player1 = askHuman(game);

                while (!game.play(player1.x, player1.y))
                {
                    cout << "Invalid Move! Try again buddy" << endl;
                    player1 = askHuman(game);
                }
            }

            // Update current vertex again after player 1's move
            current = buildTree(game, current);
        }
    }

    // Clear terminal
    system("clear");

    cout << game << endl;

    
    if (game.hasWon(0))
    {
        cout << "X wins" << endl;
    }
    else if (game.hasWon(1))
    {
        cout << "O wins" << endl;
    }
    else
    {
        cout << "It's a tie" << endl;
    }

    return 0;
}