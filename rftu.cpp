// rftu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "rftu.h"

#include "raytracer/World/World.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


class RenderThreadImpl : public RenderThread {
public:
    char* data;
    unsigned width;

    RenderThreadImpl(unsigned width, unsigned height): width(width) {
        data = new char[width * height * 3];
    }

    ~RenderThreadImpl() {
        delete data;
    }

    virtual void setPixel(int x, int y, int red, int green, int blue) {
        data[(y * width + x) * 3] = red;
        data[(y * width + x) * 3 + 1] = green;
        data[(y * width + x) * 3 + 2] = blue;
    }
};

int main() {

    World world;
    
    world.build();

    RenderThreadImpl rThread(world.vp.vres, world.vp.hres);
    world.paintArea = &rThread;

    world.render_scene();

    if (!stbi_write_png("out.png", world.vp.vres, world.vp.hres, 3, rThread.data, world.vp.vres * 3)) {
        cerr << "Failed to save image\n";
        return -1;
    }
}
