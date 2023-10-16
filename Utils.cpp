#include "Utils.h"

#include <fstream>
#include <cmath>

int imgProcUtils::varFromFile(const char* path, int offset) {
	std::ifstream file(path, std::ios::binary);
	int32_t buffer;
	if (file.is_open()) {
		file.seekg(offset, file.beg);
		file.read((char*)&buffer, sizeof(buffer));
	}
	else {
		throw std::runtime_error("File not found");
	}
	return buffer;
}

float imgProcUtils::clamp(float val, float bottom, float top){
	return (val < bottom) ? bottom : (val > top) ? top : val;
}

float imgProcUtils::gaussian2D(float x, float y, float sigma) {
	return (1.0f / (2.0f * pi * pow(sigma, 2))) * exp(-(((pow(x, 2)) + (pow(y, 2))) / (2.0f * (pow(sigma, 2)))));
}
