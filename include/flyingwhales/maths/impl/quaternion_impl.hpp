#pragma once

#include <flyingwhales/maths/quaternion.hpp>
#include <cmath>

namespace fw
{

	inline Quaternion::Quaternion(const float &x, const float &y, const float &z, const float &w)
		: Quaternion(Vector3(x, y, z), w)
	{}

	inline Quaternion::Quaternion(const Vector3 &xyz, const float &w)
		: xyz(xyz), w(w)
	{}

	inline float Quaternion::magnitude_squared() const
	{
		return (w * w) + xyz.magnitude_squared();
	}

	inline float Quaternion::magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

	inline Quaternion &Quaternion::normalize()
	{
		auto scale = 1.0f / magnitude();
		xyz *= scale;
		w *= scale;

		return *this;
	}

	inline Quaternion Quaternion::normalize(Quaternion quaternion)
	{
		return quaternion.normalize();
	}

	inline Quaternion &Quaternion::add(const Quaternion &other)
	{
		xyz += other.xyz;
		w += other.w;

		return *this;
	}

	inline Quaternion &Quaternion::subtract(const Quaternion &other)
	{
		xyz -= other.xyz;
		w -= other.w;

		return *this;
	}

	inline Quaternion &Quaternion::multiply(const Quaternion &other)
	{
		auto buffer = *this;

		buffer.xyz = Vector3((xyz * other.w) + (other.xyz * w) + Vector3::cross(xyz, other.xyz));
		buffer.w = (w * other.w) - Vector3::dot(xyz, other.xyz);

		*this = buffer;
		return *this;
	}

	inline Quaternion &Quaternion::multiply(const float &scale)
	{
		xyz *= scale;
		w *= scale;

		return *this;
	}

	inline Quaternion &Quaternion::operator+=(const Quaternion &other)
	{
		return add(other);
	}

	inline Quaternion &Quaternion::operator-=(const Quaternion &other)
	{
		return subtract(other);
	}

	inline Quaternion &Quaternion::operator*=(const Quaternion &other)
	{
		return multiply(other);
	}

	inline Quaternion &Quaternion::operator*=(const float &scale)
	{
		return multiply(scale);
	}

	inline bool Quaternion::operator==(const Quaternion &other) const
	{
		return (xyz == other.xyz) && (w == other.w);
	}

	inline bool Quaternion::operator!=(const Quaternion &other) const
	{
		return !(*this == other);
	}

	inline Quaternion operator+(Quaternion left, const Quaternion &right)
	{
		return left.add(right);
	}

	inline Quaternion operator-(Quaternion left, const Quaternion &right)
	{
		return left.subtract(right);
	}

	inline Quaternion operator*(Quaternion left, const Quaternion &right)
	{
		return left.multiply(right);
	}

	inline Quaternion operator*(Quaternion quaternion, const float &scale)
	{
		return quaternion.multiply(scale);
	}

	inline Quaternion operator*(const float &scale, Quaternion quaternion)
	{
		return quaternion.multiply(scale);
	}

}