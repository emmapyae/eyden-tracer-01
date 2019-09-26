// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f a, Vec3f b, Vec3f c)
		: CPrim(), m_a(a), m_b(b), m_c(c)
	{
	}
	virtual ~CPrimTriangle(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---
		Vec3f ab = m_b - m_a;
		Vec3f ac = m_c - m_a;
		Vec3f N = ab.cross(ac);
		
		float NdotRayDirection = N.dot(ray.dir);
		if (fabs(NdotRayDirection) < Epsilon) // almost 0
			return false;					  // they are parallel so they don't intersect !

		float d = N.dot(m_a);
		ray.t = (N.dot(ray.org) + d) / NdotRayDirection;
		if (ray.t < 0)
			return false; // the triangle is behind

		// compute the intersection point using equation 1
		Vec3f P = ray.org + ray.t * ray.dir;

		// Step 2: inside-outside test
		Vec3f C; // vector perpendicular to triangle's plane

		// edge 0
		Vec3f edge0 = m_b - m_a;
		Vec3f vp0 = P - m_b;
		C = edge0.cross(vp0);
		if (N.dot(C) < 0)
			return false; // P is on the right side

		// edge 1
		Vec3f edge1 = m_c - m_b;
		Vec3f vp1 = P - m_b;
		C = edge1.cross(vp1);
		if (N.dot(C) < 0)
			return false; // P is on the right side

		// edge 2
		Vec3f edge2 = m_a - m_c;
		Vec3f vp2 = P - m_c;
		C = edge2.cross(vp2);
		if (N.dot(C) < 0)
			return false; // P is on the right side;

		return true;
	}

private:
	Vec3f m_a; ///< Position of the first vertex
	Vec3f m_b; ///< Position of the second vertex
	Vec3f m_c; ///< Position of the third vertex
};
