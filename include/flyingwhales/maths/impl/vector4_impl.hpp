#pragma once

#include <flyingwhales/maths/vector4.hpp>
#include <cmath>

namespace fw
{

	Vector4::Vector4()
		: Metric4()
	{}

	Vector4::Vector4(const Metric4<float> &metric)
		: Metric4(metric)
	{}

	Vector4 &Vector4::normalize()
	{
		float scale = 1.0f / magnitude();
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;

		return *this;
	}

	Vector4 Vector4::normalize(Vector4 vector)
	{
		return vector.normalize();
	}

	float Vector4::dot(const Vector4 &other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
	}

	float Vector4::dot(const Vector4 &left, const Vector4 &right)
	{
		return left.dot(right);
	}

	float Vector4::magnitude_squared() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	float Vector4::magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

}