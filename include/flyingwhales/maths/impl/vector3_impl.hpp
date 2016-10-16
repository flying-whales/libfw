#pragma once

#include <flyingwhales/maths/vector3.hpp>
#include <cmath>

namespace fw
{

	inline Vector3::Vector3()
		: Metric3()
	{}

	inline Vector3::Vector3(const Metric3<float> &metric)
		: Metric3(metric)
	{}

	inline Vector3 &Vector3::multiply(const float &scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	inline Vector3 &Vector3::operator*=(const float &scalar)
	{
		return multiply(scalar);
	}

	inline Vector3 &Vector3::normalize()
	{
		float scale = 1.0f / magnitude();
		x *= scale;
		y *= scale;
		z *= scale;

		return *this;
	}

	inline Vector3 Vector3::normalize(Vector3 vector)
	{
		return vector.normalize();
	}

	inline Vector3 Vector3::cross(const Vector3 &left, const Vector3 &right)
	{
		return Vector3(
			(left.y * right.z) - (left.z * right.y),
			(left.z * right.x) - (left.x * right.z),
			(left.x * right.y) - (left.y * right.x));
	}

	inline float Vector3::dot(const Vector3 &other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	inline float Vector3::dot(const Vector3 &left, const Vector3 &right)
	{
		return left.dot(right);
	}

	inline float Vector3::magnitude_squared() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	inline float Vector3::magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

	inline Vector3 operator*(Vector3 vector, const float &scalar)
	{
		return vector.multiply(scalar);
	}

	inline Vector3 operator*(const float &scalar, Vector3 vector)
	{
		return vector.multiply(scalar);
	}

}