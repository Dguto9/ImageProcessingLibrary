#pragma once
class Matrix;

class Image
{
public:
	int width;
	int height;
	Matrix* pixels;
	Image(int width, int height);
	Image(const Image& copy);
	Image(const char* path);
	Image(const Matrix& r, const Matrix& g, const Matrix& b);
	Image(const Matrix& values);
	~Image();
	void saveToBMP(const char* path);
};

