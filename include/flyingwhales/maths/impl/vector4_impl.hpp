#pragma once

#include <flyingwhales/maths/vector4.hpp>
#include <cmath>

namespace fw
{

	inline Vector4::Vector4()
		: Metric4()
	{}

	inline Vector4::Vector4(const Metric4<float> &metric)
		: Metric4(metric)
	{}

	inline Vector4 &Vector4::normalize()
	{
		float scale = 1.0f / magnitude();
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;

		return *this;
	}

	inline Vector4 Vector4::normalize(Vector4 vector)
	{
		return vector.normalize();
	}

	inline float Vector4::dot(const Vector4 &other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
	}

	inline float Vector4::dot(const Vector4 &left, const Vector4 &right)
	{
		return left.dot(right);
	}

	inline float Vector4::magnitude_squared() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	inline float Vector4::magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

}