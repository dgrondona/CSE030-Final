#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>

// Represents a a 2D coordinate
struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }

    // Overload == for comparing Vec
    bool operator==(const Vec& other){

        if (this->x == other.x && this->y == other.y) {

            return true;

        }

        return false;

    }

};

// Enable printing formatted (x, y) coordinates with overload operator
inline std::ostream& operator<<(std::ostream& os, const Vec& v){
    os << "(" << v.x << ", " << v.y << ")";

    return os;
}

// Forward declaration of GameState struct for overload operator
struct GameState;
std::ostream& operator<<(std::ostream& os, const GameState& state);

// Represents the state of the game
struct GameState{

    // Initialize grid, currentTurn, size, turnCount, done, and lastMove to use later in struct
    int** grid;
    bool currentTurn;
    int size;
    int turnCount;

    bool done;
    Vec lastMove;

    // Constructor
    GameState(int size = 3){
        this->size = size;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        // Allocate memory for 2D grid and initialize cells to empty (-1)
        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    // Copy constructor
    GameState(const GameState& other){
        size = other.size;
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    // Overload operator for comparing two GameState objects
    bool operator==(const GameState& other){
        bool sizeMatch = size == other.size;
        bool currentTurnMatch = currentTurn == other.currentTurn;
        bool turnCountMatch = turnCount == other.turnCount;
        bool doneMatch = done == other.done;
        bool lastMoveMatch = lastMove.x == other.lastMove.x && lastMove.y == other.lastMove.y;
        if (sizeMatch && currentTurnMatch && turnCountMatch && doneMatch && lastMoveMatch){

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (grid[i][j] != other.grid[i][j]){
                        return false;
                    }
                }
            }

            return true;
        }
        else{
            return false;
        }
    }

    // For deep copying another GameState
    GameState& operator=(const GameState& other){
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        if (size == other.size){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }
        else{
            size = other.size;
            for (int i = 0; i < size; i++){
                delete[] grid[i];
            }
            delete[] grid;

            grid = new int*[size];

            for (int i = 0; i < size; i++){
                grid[i] = new int[size];
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }

        return *this;
    }

    // Check if specific player has won
    bool hasWon(int player){
        for (int i = 0; i < size; i++){
            bool winRow = true;
            for (int j = 0; j < size; j++){
                if (grid[i][j] != player){
                    winRow = false;
                    break;
                }
            }
            if (winRow){
                return true;
            }
        }
        for (int i = 0; i < size; i++){
            bool winCol = true;
            for (int j = 0; j < size; j++){
                if (grid[j][i] != player){
                    winCol = false;
                    break;
                }
            }
            if (winCol){
                return true;
            }
        }

        bool winDiag = true;
        for (int i = 0; i < size; i++){
            if (grid[i][i] != player){
                winDiag = false;
                break;
            }
        }
        if (winDiag){
            return true;
        }
        
        bool winAntiDiag = true;
        for (int i = 0; i < size; i++){
            if (grid[i][size-1-i] != player){
                winAntiDiag = false;
                break;
            }
        }
        if (winAntiDiag){
            return true;
        }

        return false;
    }

    // Play a move at the given position
    bool play(int x, int y){
        if (grid[x][y] != -1){
            return false;
        }

        grid[x][y] = currentTurn;
        currentTurn = !currentTurn;
        turnCount++;
        lastMove.set(x, y);

        if (turnCount == size * size){
            done = true;
        }
        else if (hasWon(0) || hasWon(1)){
            done = true;
        }

        return true;
    }

    // Destructor
    ~GameState(){
        for (int i = 0; i < size; i++){
            delete[] grid[i];
        }
        delete[] grid;
    }
};

// Overload operator to display the board on screen
inline std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << "--- ";
    }
    os << std::endl;
    for (int i = 0; i < state.size; i++){
        os << i << " ";
        for (int j = 0; j < state.size; j++){
            char c = ' ';
            if (state.grid[i][j] == 0){
                c = 'X';
            }
            else if (state.grid[i][j] == 1){
                c = 'O';
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif