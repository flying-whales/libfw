#pragma once

#include <flyingwhales/maths/vector3.hpp>
#include <flyingwhales/maths/metric4.hpp>

namespace fw
{

	class Vector4 : public Metric4<float>
	{
	public:
		using Metric4<float>::Metric4;
		Vector4();
		Vector4(const Metric4<float> &metric);

		Vector4 &normalize();
		static Vector4 normalize(Vector4 vector);

		float dot(const Vector4 &other) const;
		static float dot(const Vector4 &left, const Vector4 &right);

		float magnitude_squared() const;
		float magnitude() const;
	};

}

// implementation file
#include <flyingwhales/maths/impl/vector4_impl.hpp>