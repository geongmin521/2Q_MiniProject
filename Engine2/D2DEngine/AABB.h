#pragma once
#include "MathHelper.h"
#include "Collider.h" 

class AABB
{
public:
	AABB() : Center{ 0,0 }, Extent{ 0,0 } { }
public:
	MathHelper::Vector2F Center; // 중앙
	MathHelper::Vector2F Extent; // x,y축 확장값	

	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	AABB(AABB&&) = default;
	AABB& operator=(AABB&&) = default;
	~AABB() = default;

	void SetCenter(float x, float y) { Center = { x, y }; }
	void SetExtent(float x, float y) { Extent = { x, y }; }
	float GetMinX() const { return Center.x - Extent.x; }
	float GetMaxX() const { return Center.x + Extent.x; }
	float GetMinY() const { return Center.y - Extent.y; }
	float GetMaxY() const { return Center.y + Extent.y; }

	bool CheckIntersect(const AABB& other) const
	{
		// self min,max
		float BoxA_xmin = Center.x - Extent.x;
		float BoxA_xmax = Center.x + Extent.x;
		float BoxA_ymin = Center.y - Extent.y;
		float BoxA_ymax = Center.y + Extent.y;

		// other min,max
		float BoxB_xmin = other.Center.x - other.Extent.x;
		float BoxB_xmax = other.Center.x + other.Extent.x;
		float BoxB_ymin = other.Center.y - other.Extent.y;
		float BoxB_ymax = other.Center.y + other.Extent.y;

		// Check for no overlap conditions
		if (BoxA_xmax < BoxB_xmin ||  // 오른쪽에 있으면 겹칠수가 없음
			BoxA_xmin > BoxB_xmax ||  // 왼쪽에 있으면 겹칠수가 없음
			BoxA_ymax < BoxB_ymin ||  // 아래에 있으면 겹칠수가 없음
			BoxA_ymin > BoxB_ymax)	  // 위에 있으면 겹칠수가 없음
		{
			return false;
		}

		return true;

	}

	bool CheckPoint(const MathHelper::Vector2F& other) const
	{
		// self min,max
		float BoxA_xmin = Center.x - Extent.x;
		float BoxA_xmax = Center.x + Extent.x;
		float BoxA_ymin = Center.y - Extent.y;
		float BoxA_ymax = Center.y + Extent.y;
		if (other.x > BoxA_xmin && other.x < BoxA_xmax &&
			other.y > BoxA_ymin && other.y < BoxA_ymax) //점하나가 모든값의 안쪽이면 부딪힘
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

