#pragma once

#include <flyingwhales/maths/vector4.hpp>

namespace fw
{

	class Quaternion
	{
	public:
		Vector3 xyz;
		float w;
	public:
		Quaternion(const float &x, const float &y, const float &z, const float &w);
		Quaternion(const Vector3 &xyz, const float &w);

		float magnitude_squared() const;
		float magnitude() const;

		Quaternion &normalize();
		static Quaternion normalize(Quaternion quaternion);

		Quaternion &add(const Quaternion &other);
		Quaternion &subtract(const Quaternion &other);
		Quaternion &multiply(const Quaternion &other);
		Quaternion &multiply(const float &scale);

		Quaternion &operator+=(const Quaternion &other);
		Quaternion &operator-=(const Quaternion &other);
		Quaternion &operator*=(const Quaternion &other);
		Quaternion &operator*=(const float &scale);

		bool operator==(const Quaternion &other) const;
		bool operator!=(const Quaternion &other) const;
	};

	Quaternion operator+(Quaternion left, const Quaternion &right);
	Quaternion operator-(Quaternion left, const Quaternion &right);
	Quaternion operator*(Quaternion left, const Quaternion &right);
	Quaternion operator*(Quaternion quaternion, const float &scale);
	Quaternion operator*(const float &scale, Quaternion quaternion);

}

// implementation file
#include <flyingwhales/maths/impl/quaternion_impl.hpp>