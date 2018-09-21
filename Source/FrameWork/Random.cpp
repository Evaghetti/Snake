#include "Random.h"

Random::Random(int seed) {
	if (seed == -1) {
		std::random_device rd;
		mt = std::mt19937(rd());
	}
	else
		mt = std::mt19937(seed);
}

float Random::range(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

int Random::range(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}