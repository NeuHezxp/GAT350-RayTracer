#pragma once

#include <cstdlib>  // For rand and srand
#include <algorithm> // For std::swap
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

namespace ray
{
    // Seed the random number generator
    inline void seedRandom(unsigned int seed) {
        std::srand(seed);
    }

    // Generate a random float between 0 and 1
    inline float random01() {
        return static_cast<float>(std::rand()) / RAND_MAX;
    }

    // Generate a random float between min and max
    inline float random(float min, float max) {
        if (min > max) {
            std::swap(min, max);
        }
        return min + (max - min) * random01();
    }

    inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max) {
        return glm::vec3(
            random(min.x, max.x),
            random(min.y, max.y),
            random(min.z, max.z)
        );
    }

    // Generate a random vector in the unit sphere
    inline glm::vec3 randomInUnitSphere() {
        glm::vec3 p;
        do {
            p = glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1) };
        } while (glm::length2(p) >= 1.0f);
        return p;
    }
}
