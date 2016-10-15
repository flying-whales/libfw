#pragma once

#include <flyingwhales/maths/metric2.hpp>

namespace fw
{

	class Vector2 : public Metric2<float>
	{
	public:
		using Metric2<float>::Metric2;
		Vector2();
		Vector2(const Metric2<float> &metric);

		Vector2 &normalize();
		static Vector2 normalize(Vector2 vector);

		float dot(const Vector2 &other) const;
		static float dot(const Vector2 &left, const Vector2 &right);

		float magnitude_squared() const;
		float magnitude() const;
	};

}

// implementation file
#include <flyingwhales/maths/impl/vector2_impl.hpp>