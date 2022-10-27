#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "geometry.h"
#include "stb_image.h"

// A class for reading and writing .png images
class Image {
	// private members
	const int width, height;
	std::vector<Vec3f> framebuffer;
public:
	// constructor
	Image(int width, int height) : width(width), height(height) {
		framebuffer.resize(width * height);
	}
	// set pixel color
	void set(int x, int y, const Vec3f& color) {
		framebuffer[y * width + x] = color;
	}
	// write image to file
	void save(const char* filename, int format) {
		std::ofstream ofs;
		ofs.open(filename);

		// switch (format) {
		// case 0: stbi_write_png(filename, width, height, 3, &framebuffer[0], 0); break;


		ofs.close();
	}
};