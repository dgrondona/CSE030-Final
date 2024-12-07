#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <GL/freeglut.h>
#include "AppController.h"
#include "Square.h"
#include "Texture.h"

class Controller : public AppController {
    Square* square;
    Texture* texture;

public:
    Controller(){
        // Initialize your state variables
        square = new Square();
        texture = new Texture(0.5f, 0.5f, 0.2f, 0.2f, "./assets/pencil.png");
    }

    void render() {
        // Render some graphics
        square->draw();
        texture->draw();
    }

    void leftMouseDown(float mx, float my) {
        if (square->contains(mx, my)) {
            std::cout << "Square was clicked" << std::endl;
        }
        else if (texture->contains(mx, my)) {
            std::cout << "Texture was clicked" << std::endl;
        }
    }

    ~Controller(){
        // Release memory
        delete square;
        delete texture;
    }
};

#endif