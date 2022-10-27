#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.cpp"

void render() {
    const int width = 1024;
    const int height = 768;
	const char* filename = "out.png";
	int format = 0;
    
	// create an red colored image and store it in Image object
	Image image(width, height);
	
	// set pixel color
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			image.set(i, j, Vec3f(1, 0, 0));
		}
	}
	
	// write image to file
	image.save(filename, format);
}

int main() {
    render();
    return 0;
}