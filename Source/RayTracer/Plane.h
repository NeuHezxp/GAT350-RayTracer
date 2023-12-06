#pragma once
#include "Object.h"

namespace ray
{
	class Plane : public Object
	{
	public:
		Plane() = default;
		Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
			Object{ material },  // Call the constructor of the base class (Object) with the material
			m_center{ center },    // Set the center of the plane 
			m_normal{ glm::normalize(normal) }     // Set the normal of the plane 
		{
		}

		bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

	private:
		glm::vec3 m_center{ 0, 0, 0 };  //<center of the plane>
		glm::vec3 m_normal{ 0, 0, 0 };  //<normal of the plane>
	};
}