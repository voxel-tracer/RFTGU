#pragma once

class RenderThread {
public:
	virtual void setPixel(int x, int y, int red, int green, int blue) = 0;
};
