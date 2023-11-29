#pragma once
#include <algorithm>   
#include <map>

class Random
{
public:
	inline void seedRandom(unsigned int seed)
	{
		srand(seed);
	}

	inline float random01() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	inline float random(float min, float max) {
		if (min > max) {
			std::swap(min, max);
		}
		return min + random01() * (max - min);
	}

};
