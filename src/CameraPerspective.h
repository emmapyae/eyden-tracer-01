// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
	
public:
	float angle_in_rad;
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		printf("Resolution is %d\n", getResolution().width);
		m_zAxis = normalize(dir);
		m_xAxis = normalize(m_zAxis *  up);
		m_yAxis = normalize(m_xAxis * m_zAxis);
		m_aspect = resolution.width / float(resolution.height);
		angle_in_rad = angle * (float)M_PI / 180.f;
		m_focus = 1.f / tan(angle_in_rad / 2.f);
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// ray.org = m_pos;
		// float ndcx, ndcy, sscx, sscy; 
		// for(int y=0; y<getResolution().height; y++)
		// {
		// 	for(int x=0; x<getResolution().width; x++)
		// 	{
		// 		ndcx= (x + 0.5) / getResolution().width;
		// 		ndcy= (y + 0.5) /getResolution().height;

		// 		sscx= 2 * ndcx-1;  
		// 		sscy= 2 * ndcy-1;
				
		// 		ray.dir = (sscx * m_xAxis) + (sscy * m_yAxis) + (m_focus * m_zAxis);
		// 		ray.dir = normalize(ray.dir);
				
		// 	}
		// }
		ray.org = m_pos;
		ray.dir = ( m_xAxis * (2.0f * ((x/(float)getResolution().width - .5f) * m_aspect)))
		+ ( m_yAxis * (2.0f * (y/(float)getResolution().height- .5f)))
    	+ ( m_zAxis * m_focus);
		ray.dir = normalize(ray.dir);
		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

