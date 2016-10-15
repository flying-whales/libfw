#pragma once

#include <flyingwhales/maths/quaternion.hpp>
#include <cmath>

namespace fw
{

	Quaternion::Quaternion(const float &x, const float &y, const float &z, const float &w)
		: Quaternion(Vector3(x, y, z), w)
	{}

	Quaternion::Quaternion(const Vector3 &xyz, const float &w)
		: xyz(xyz), w(w)
	{}

	float Quaternion::magnitude_squared() const
	{
		return (w * w) + xyz.magnitude_squared();
	}

	float Quaternion::magnitude() const
	{
		return std::sqrt(magnitude_squared());
	}

	Quaternion &Quaternion::normalize()
	{
		auto scale = 1.0f / magnitude();
		xyz *= scale;
		w *= scale;

		return *this;
	}

	Quaternion Quaternion::normalize(Quaternion quaternion)
	{
		return quaternion.normalize();
	}

	Quaternion &Quaternion::add(const Quaternion &other)
	{
		xyz += other.xyz;
		w += other.w;

		return *this;
	}

	Quaternion &Quaternion::subtract(const Quaternion &other)
	{
		xyz -= other.xyz;
		w -= other.w;

		return *this;
	}

	Quaternion &Quaternion::multiply(const Quaternion &other)
	{
		auto buffer = *this;

		buffer.xyz = Vector3((xyz * other.w) + (other.xyz * w) + Vector3::cross(xyz, other.xyz));
		buffer.w = (w * other.w) - Vector3::dot(xyz, other.xyz);

		*this = buffer;
		return *this;
	}

	Quaternion &Quaternion::multiply(const float &scale)
	{
		xyz *= scale;
		w *= scale;

		return *this;
	}

	Quaternion &Quaternion::operator+=(const Quaternion &other)
	{
		return add(other);
	}

	Quaternion &Quaternion::operator-=(const Quaternion &other)
	{
		return subtract(other);
	}

	Quaternion &Quaternion::operator*=(const Quaternion &other)
	{
		return multiply(other);
	}

	Quaternion &Quaternion::operator*=(const float &scale)
	{
		return multiply(scale);
	}

	bool Quaternion::operator==(const Quaternion &other) const
	{
		return (xyz == other.xyz) && (w == other.w);
	}

	bool Quaternion::operator!=(const Quaternion &other) const
	{
		return !(*this == other);
	}

	Quaternion operator+(Quaternion left, const Quaternion &right)
	{
		return left.add(right);
	}

	Quaternion operator-(Quaternion left, const Quaternion &right)
	{
		return left.subtract(right);
	}

	Quaternion operator*(Quaternion left, const Quaternion &right)
	{
		return left.multiply(right);
	}

	Quaternion operator*(Quaternion quaternion, const float &scale)
	{
		return quaternion.multiply(scale);
	}

	Quaternion operator*(const float &scale, Quaternion quaternion)
	{
		return quaternion.multiply(scale);
	}

}