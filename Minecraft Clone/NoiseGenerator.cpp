#include "NoiseGenerator.h"

NoiseGenerator::NoiseGenerator(const float AMPLITUDE) : AMPLITUDE(AMPLITUDE) {
	seed = random.getInt(0, 1000000000);
}

float NoiseGenerator::generateHeight(GLint x, GLint z) {
	float total = 0;
	float d = (float)pow(2, OCTAVES - 1);
	
	for (size_t i = 0; i < OCTAVES; i++) {
		float frequency = (float)(pow(2, i) / d);
		float amplitude = (float)pow(ROUGHNESS, i) * AMPLITUDE;
		total += getInterpolatedNoise((x + xOffSet) * frequency, (z + zOffSet) * frequency) * amplitude;
	}

	return total;
}

float NoiseGenerator::getInterpolatedNoise(GLfloat x, GLfloat z) {
	GLint intX = (int)x;
	GLint intZ = (int)z;
	GLfloat fracX = x - intX;
	GLfloat fracZ = z - intZ;

	float v1 = getSmoothNoise(intX,     intZ);
	float v2 = getSmoothNoise(intX + 1, intZ);
	float v3 = getSmoothNoise(intX,     intZ + 1);
	float v4 = getSmoothNoise(intX + 1, intZ + 1);
	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);

	return interpolate(i1, i2, fracZ);
}

float NoiseGenerator::interpolate(GLfloat a, GLfloat b, GLfloat blend) {
	double theta = blend * PI;
	float f = (float)(1.f - cos(theta)) * 0.5f;
	return a * (1.f - f) + b * f;
}

float NoiseGenerator::getSmoothNoise(GLint x, GLint z) {
	float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1) + getNoise(x - 1, z + 1) 
		+ getNoise(x + 1, z + 1)) / 16.f;
	float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1)
		+ getNoise(x, z + 1)) / 8.f;
	float center = getNoise(x, z) / 4.f;

	return corners + sides + center;
}

float NoiseGenerator::getNoise(GLint x, GLint z) {
	GLsizei noiseSeed = x * 49632 + z * 325176 + seed;
	random = Random<>(noiseSeed);

	return random.getFloat(0, 1) * 2.f - 1.f;
}
