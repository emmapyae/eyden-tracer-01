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
		/*
		In Problem 1.2, we got t = (m_origin - ray.org).dot(m_normal) 
		/(ray.dir).dot(m_normal).
		*/
		float num = (m_origin - ray.org).dot(m_normal);
		float den = (ray.dir).dot(m_normal);
		float t;
		//if den == 0, then we will not get a real number.
		if (den == 0){
			return false;
		}
		t = num / den;

		if (t < Epsilon || t > ray.t){
			return false;
		}
		ray.t = t;
		return true;
	}
	
	
private:
	Vec3f m_normal;	//< Normal to the plane -- n 
	Vec3f m_origin;	//< Point on the plane -- a
};
