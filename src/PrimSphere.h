// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f center, float radius)
		: CPrim(), m_center(center), m_radius(radius)
	{
	}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		/*In problem 1.2, we got a quadratic equation for t. 
		(t*t)*ray.dir.dot(ray.dir) + 2*t*ray.dir.dot(ray.org-m_center) + 
		(ray.org - m_center).dot(ray.org - m_center) - (m_radius * m_radius) = 0
		So, the quadratic formula is used to find t. 
		*/
		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(ray.org - m_center);
		float c = (ray.org - m_center).dot(ray.org - m_center) - (m_radius * m_radius);
		//value inside the square root
		float value = (b*b) - (4*a*c);
		float t1, t2 = 0;
		//negative value inside a square root will not produce a real number
		if (value < 0)
		{
			return false;
		}
		else if (value == 0)
		{
			t1 = (-1 * b) / (2 * a);
		}
		else
		{
			t1 = ((-b) - sqrt(value)) / (2 * a);
			t2 = ((-b) + sqrt(value)) / (2 * a);
			if (t1 > t2)
			std::swap(t1, t2);
			else if (t1 < 0)
			{
				t1 = t2;
				if (t1 < 0)
					return false;
			}
		}
		if (t1 < Epsilon || t1 > ray.t)
		{
			return false;
		}
		ray.t = t1;
		return true;
	}

private:
	Vec3f m_center; ///< Position of the center of the sphere
	float m_radius; ///< Radius of the sphere
};
