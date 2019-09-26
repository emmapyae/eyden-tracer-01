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
		float a, b, c;
		float t1, t2;
		a = ray.dir.dot(ray.dir);
		b = 2 * ray.dir.dot(ray.org - m_center);
		c = ((ray.org - m_center).dot(ray.org - m_center)) - (m_radius * m_radius);
		if ((b*b) - (4 * a *c) < 0){
			return false;
		}

		else if((b*b) - (4 * a *c) == 0){
		 	ray.t = (-1*b)/(2*a);
		}
		else{
			t1 = ((-1*b) + sqrt((b*b) - (4*a*c)) / (2 * a));
			t2 = ((-1*b) - sqrt((b*b) - (4*a*c)) / (2 * a));
		}
		
		// --- PUT YOUR CODE HERE ---

		return true;
	}

private:
	Vec3f m_center; ///< Position of the center of the sphere
	float m_radius; ///< Radius of the sphere
};
