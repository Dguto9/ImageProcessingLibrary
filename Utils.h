#pragma once

namespace imgProcUtils {
	const double pi = 3.14159265358979323846;
	int varFromFile(const char* path, int offset);
	float clamp(float value, float bottom, float top);
	float gaussian2D(float x, float y, float sigma);
}