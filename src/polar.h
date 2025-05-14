#pragma once
#include "raylib.h"
#include <math.h>

struct Polar
{
public:
	Polar() = default;
	Polar(float angle, float radius) :
		angle{ angle },
		radius{ radius }
	{}

	Polar(const Vector2& v) :
		angle{ (float)atan2(v.y, v.x) },
		radius{ sqrtf((v.x * v.x) + (v.y * v.y)) }
	{}

	Polar& operator = (const Vector2& v)
	{
		angle = atan2(v.y, v.x);
		radius = sqrtf((v.x * v.x) + (v.y * v.y));

		return *this;
	}

	operator Vector2() const
	{
		Vector2 v;
		v.x = (float)cos(angle)* radius;
		v.y = (float)sin(angle)* radius;

		return v;
	}

public:
	float angle{ 0 };
	float radius{ 0 };
};