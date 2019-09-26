// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 */
	CPrimPlane(Vec3f origin, Vec3f normal)
		: CPrim()
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		float denom = ray.dir.dot(m_normal);
		if (denom > Epsilon)
		{
			Vec3f po = m_origin - ray.org;
			float num = po.dot(m_normal);
			ray.t = num / denom;

			//check if it is in range;
			return (ray.t >= 0);
		}

		return false;
	}
	
	
private:
	Vec3f m_normal;	///< Point on the plane -- a
	Vec3f m_origin;	///< Normal to the plane -- n
};
