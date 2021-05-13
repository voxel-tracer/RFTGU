// rftu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "rftu.h"

#include "raytracer/World/World.h"

class RenderThreadImpl : public RenderThread {
public:

    virtual void setPixel(int x, int y, int red, int green, int blue) {
        std::cout << "[" << x << ", " << y << "]\n";
    }
};

int main() {
    RenderThreadImpl rThread;

    World world;
    
    world.build();
    world.paintArea = &rThread;

    world.render_scene();
}
