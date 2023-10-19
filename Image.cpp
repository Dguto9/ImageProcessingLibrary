#include "Image.h"
#include "Matrix.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <cassert>

Image::Image(int width, int height) {
	this->width = width;
	this->height = height;
	pixels = (Matrix*)calloc(3, sizeof(Matrix));
	for (int i = 0; i < 3; i++) {
		pixels[i] = Matrix(height, width);
		pixels[i].fill(0);
	}
}

Image::Image(const char* path) {
	std::ifstream file(path, std::ios::binary);
	width = imgProcUtils::varFromFile(path, 18);
	height = imgProcUtils::varFromFile(path, 22);
	pixels = (Matrix*)calloc(3, sizeof(Matrix));
	int tempbuffer = 0;
	for (int i = 0; i < 3; i++) {
		pixels[i] = Matrix(height, width);
	}
	file.seekg(imgProcUtils::varFromFile(path, 10));
	if (file.is_open()) {
		for (int i = 0; i < width*height; i++) {
			for (int j = 0; j < 3; j++) {
				tempbuffer = 0;
				file.read((char*)&tempbuffer, 1);
				pixels[j].data[i] = (float)tempbuffer * (1.0f/255.0f);
			}
			if ((!((i+1) % width))&&(width%4)) {
				file.seekg(4-((width*3)%4), std::ios_base::cur);
				std::cout << 4 - ((width * 3) % 4) << std::endl;
			}
		}
	}
	//std::cout << "width: " << width << "\n" << std::endl;
	//std::cout << "height: " << height << "\n" << std::endl;
}

Image::Image(const Matrix& r, const Matrix& g, const Matrix& b) {
	assert((r.rows == g.rows == b.rows) || (r.columns == g.columns == b.columns));
	this->width = r.columns;
	this->height = r.rows;
	pixels = (Matrix*)calloc(3, sizeof(Matrix));
	pixels[0] = b;
	pixels[1] = g;
	pixels[2] = r;
}

Image::Image(const Matrix& values) {
	this->width = values.columns;
	this->height = values.rows;
	pixels = (Matrix*)calloc(3, sizeof(Matrix));
	pixels[0] = pixels[1] = pixels[2] = values;
}

Image::~Image() {
	free(pixels);
}

void Image::saveToBMP(const char* path) {
	std::ofstream file(path, std::ios::binary);
	int filesize = 54 + (width * height * 3) + (4-((width*3)%4))*height;
	int empty = 0;
	int dataoffset = 54;
	int dibsize = 40;
	int colorplanes = 1;
	int bitperpixel = 24;
	int compression = 0;
	int datasize = filesize - 54;
	int hprintres = 2835;
	int vprintres = 2835;
	int numcolors = 0;
	int importantcolors = 0;
	file.write("BM", 2);
	file.write((char*)&filesize, 4);
	file.write((char*)&empty, 4);
	file.write((char*)&dataoffset, 4);
	file.write((char*)&dibsize, 4);
	file.write((char*)&width, 4);
	file.write((char*)&height, 4);
	file.write((char*)&colorplanes, 2);
	file.write((char*)&bitperpixel, 2);
	file.write((char*)&compression, 4);
	file.write((char*)&datasize, 4);
	file.write((char*)&hprintres, 4);
	file.write((char*)&vprintres, 4);
	file.write((char*)&numcolors, 4);
	file.write((char*)&importantcolors, 4);
	for (int i = 0; i < width * height; i++) {
		for (int j = 0; j < 3; j++) {
			int currentpixel = (int)(pixels[j].data[i] * 255);
			file.write((char*)&currentpixel, 1);
		}
		if ((!((i + 1) % width)) && (width % 4)) {
			file.write((char*)&empty, 4 - ((width * 3) % 4));
			//std::cout << 4 - ((width * 3) % 4) << std::endl;
		}
	}
	file.close();
}
