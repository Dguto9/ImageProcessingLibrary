#pragma once
class Matrix;

class Image
{
public:
	int width;
	int height;
	Matrix* pixels;
	Image(int width, int height);
	Image(const char* path);
	~Image();
	void saveToBMP(const char* path);
};

