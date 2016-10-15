#pragma once

#include <flyingwhales/maths/vector2.hpp>
#include <flyingwhales/maths/metric3.hpp>

namespace fw
{

	class Vector3 : public Metric3<float>
	{
	public:
		using Metric3<float>::Metric3;
		Vector3();
		Vector3(const Metric3<float> &metric);

		Vector3 &multiply(const float &scalar);
		Vector3 &operator*=(const float &scalar);

		Vector3 &normalize();
		static Vector3 normalize(Vector3 vector);

		static Vector3 cross(const Vector3 &left, const Vector3 &right);

		float dot(const Vector3 &other) const;
		static float dot(const Vector3 &left, const Vector3 &right);

		float magnitude_squared() const;
		float magnitude() const;
	};

	Vector3 operator*(Vector3 vector, const float &scalar);
	Vector3 operator*(const float &scalar, Vector3 vector);

}

// implementaion file
#include <flyingwhales/maths/impl/vector3_impl.hpp>