#include "Scene.h"

#include <iomanip>

#include "Canvas.h"
#include "MathUtils.h"
#include <glm/gtc/random.hpp>

namespace ray
{
	void Scene::Render(Canvas& canvas, int numSamples, int depth)
	{
		// cast ray for each point (pixel) on the canvas
		for (int y = 0; y < canvas.GetSize().y; y++)
		{
			for (int x = 0; x < canvas.GetSize().x; x++)
			{
				// create vec2 pixel from canvas x,y
				glm::vec2 pixel = glm::vec2{ x, y };

				// set initial color
				color3_t color{ 0 };
				// cast a ray for each sample, accumulate color value for each sample
				// each ray will have a random offset
				for (int i = 0; i < numSamples; i++)
				{
					// get normalized (0 - 1) point coordinates from pixel
					glm::vec2 point = (pixel + glm::vec2{ random01(), random01() }) / canvas.GetSize();
					// flip y
					point.y = 1.0f - point.y;

					// create ray from camera
					ray_t ray = m_camera->GetRay(point);

					// cast ray into scene
					// set color value from trace
					raycastHit_t raycastHit;
					color += Trace(ray, 0, 100, raycastHit, depth);
				}

				// draw color to canvas point (pixel)
				// get average color (average = (color + color + color) / number of samples)
				color /= numSamples;
				canvas.DrawPoint(pixel, color4_t(color, 1));
			}

			// Display progress percentage
			std::cout << std::setprecision(2) << std::setw(5) << ((y / (float)canvas.GetSize().y) * 100) << "%\n";
		}
	}
	color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
	{
		bool rayHit = false;
		float closestDistance = maxDistance;

		// check if scene objects are hit by the ray
		for (auto& object : m_objects)
		{
			// when checking objects don't include objects farther than closest hit (starts at max distance)
			if (object->Hit(ray, minDistance, closestDistance, raycastHit))
			{
				rayHit = true;
				// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
				closestDistance = raycastHit.distance;
			}
		}

		// if ray hit object, scatter (bounce) ray and check for next hit
		if (rayHit)
		{
			ray_t scattered;
			color3_t color;

			if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
			{
				return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
				// Depth Color
				//return raycastHit.normal * 0.5f + 0.5f;
				// Grayscale
				//float distanceColorScale = raycastHit.distance / 10.0f;
				//color = ray::color3_t{ distanceColorScale, distanceColorScale, distanceColorScale };

				//return color;
			}
			else
			{
				//return color3_t{ 0, 0, 0 };
				// reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
				return raycastHit.material->GetEmissive();
			}
		}

		// if ray not hit, return scene sky color
		glm::vec3 direction = glm::normalize(ray.direction);
		float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
		color3_t color = lerp(m_bottomColor, m_topColor, t);

		return color;
	}
}