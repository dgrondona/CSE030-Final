#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "LinkedList.h"
#include "MiniMax.h"


using namespace std;

// Ask human to input their move
// !! Make sure to check if move is valid !!
Vec askHuman(GameState game) {
    int x, y;
    cout << "Enter coordinates (" << (game.currentTurn ? "O" : "X") << "): ";
    cin >> x >> y;

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
Vec mainAI(Vertex<GameState>* gameState) {

    Vec move = bestMove(gameState, 0); // update to take max player later


    return Vec(move.x, move.y);
    // gameState->data.play(move.x, move.y);

}

int main(){

    // Setup game tree (Graph<GameState> g)
    GameState game;

    Graph<GameState> g;

    // Set the starting game state called "start"
    Vertex<GameState>* start = new Vertex<GameState>(game);
    g.addVertex(start);

    // Initialize LinkedList to manage vertices
    LinkedList<Vertex<GameState>*> toExpand;
    toExpand.append(start);

    // game loop
    while (!game.done){

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

        cout << game << endl;

        Vec AI = mainAI(v);
        game.play(AI.x, AI.y);

        cout << game << endl;

        Vec human = askHuman(game);
        game.play(human.x, human.y);
        
    }



    // system("clear");
    // cout << game << endl;
    // if (game.hasWon(0)){
    //     cout << "X wins" << endl;
    // }
    // else if (game.hasWon(1)){
    //     cout << "O wins" << endl;
    // }
    // else {
    //     cout << "It's a tie" << endl;
    // }
    // 
    // cout << endl;
    
    return 0;
}