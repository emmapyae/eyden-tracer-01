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
		//--- PUT YOUR CODE HERE ---
		

		Vec3f pab = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f pbc = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f pca = (m_a - ray.org).cross(m_c - ray.org);

		//find the signed area
		float s_area = pab.dot(ray.dir) + pbc.dot(ray.dir) + pca.dot(ray.dir);
		float l1 = pab.dot(ray.dir) / s_area;
		float l2 = pbc.dot(ray.dir) / s_area;
		float l3 = pca.dot(ray.dir) / s_area;

		//check if it is intersected outside the triangle
		if (l1 < 0 || l2 < 0 || l3 < 0 || l1+l2+l3 != 1)
		{
			return false;
		}
		
		//given in the lecture slides
		Vec3f p = l1 * m_a + l2 * m_b + l3 * m_c;
		
		float t = p[0] / ray.dir[0];
		//check for intersection interval
		if (t < Epsilon || t > ray.t)
		{
			return false;
		}
		ray.t = t;
		return true;
	}

private:
	Vec3f m_a; ///< Position of the first vertex
	Vec3f m_b; ///< Position of the second vertex
	Vec3f m_c; ///< Position of the third vertex
};
