#pragma once

#include <flyingwhales/maths/vector4.hpp>
#include <array>

namespace fw
{

	class Matrix4
	{
	public:
		union
		{
			Vector4 blocks[4];
			std::array<float, 16> elements;
		};
	public:
		Matrix4();
		Matrix4(const float &diagonal);

		Matrix4 &multiply(const Matrix4 &other);
		Matrix4 &operator*=(const Matrix4 &other);

		float trace() const;

		static Matrix4 orthographic(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);
		static Matrix4 perspective_field_of_view(const float &fov, const float &aspect, const float &near, const float &far);
		static Matrix4 perspective_off_center(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);

		static Matrix4 look_at(const Vector3 &eye, const Vector3 &target, const Vector3 &up);

		static Matrix4 translation(const Vector3 &translation);
		static Matrix4 rotation(const float &angle, const Vector3 &axis);
		static Matrix4 scale(const Vector3 &scale);
	};

	Matrix4 operator*(Matrix4 left, const Matrix4 &right);

}

// implementation file
#include <flyingwhales/maths/impl/matrix4_impl.hpp>