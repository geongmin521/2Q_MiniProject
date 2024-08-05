#pragma once

using namespace MathHelper;

class Circle //원끼리의 충돌이 잘 되는지 테스트 먼저진행하기 
{
public:
	Circle() : Center{ 0,0 }, radius(0) {}
public:
	Vector2F Center; 
	float radius;
	
	Circle(const Circle&) = default;
	Circle& operator=(const Circle&) = default;
	Circle(Circle&&) = default;
	Circle& operator=(Circle&&) = default;
	~Circle() = default;

	void SetCenter(float x, float y) { Center = { x, y }; }
	void SetRadius(float _radius) { radius = _radius; } 

	bool CheckIntersect(const Circle& other) const
	{
		Vector2F distance = Center - other.Center;
		
		if (distance.Length() < radius + other.radius) //중심끼리의 거리보다 반지름의 합이 	크면 충돌안함
			return false;		
		else
			return true;
	}

	bool CheckPoint(const Vector2F& point) const
	{
		Vector2F distance = Center - point;

		if (distance.Length() < radius ) //중심과 특정 점의 거리보다 반지름이 크면 충돌안함
			return false;
		else
			return true;
	}
};

