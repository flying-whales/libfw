#pragma once

#include <flyingwhales/maths/vector2.hpp>
#include <cmath>

namespace fw
{

	Vector2::Vector2()
		: Metric2()
	{}

	Vector2::Vector2(const Metric2<float> &metric)
		: Metric2(metric)
	{}

	Vector2 &Vector2::normalize()
	{
		float scale = 1.0f / magnitude();
		x *= scale;
		y *= scale;

		return *this;
	}

	Vector2 Vector2::normalize(Vector2 vector)
	{
		return vector.normalize();
	}

	float Vector2::dot(const Vector2 &other) const
	{
		return (x * other.x) + (y * other.y);
	}

	float Vector2::dot(const Vector2 &left, const Vector2 &right)
	{
		return left.dot(right);
	}

	float Vector2::magnitude_squared() const
	{
		return (x * x) + (y * y);
	}

	float Vector2::magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

}