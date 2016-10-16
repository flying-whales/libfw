#pragma once

#include <flyingwhales/maths/matrix4.hpp>
#include <cmath>

namespace fw
{

	inline Matrix4::Matrix4()
		: elements{ 0 }
	{}

	inline Matrix4::Matrix4(const float &diagonal)
		: Matrix4()
	{
		blocks[0].x = diagonal;
		blocks[1].y = diagonal;
		blocks[2].z = diagonal;
		blocks[3].w = diagonal;
	}

	inline Matrix4 &Matrix4::multiply(const Matrix4 &other)
	{
		Matrix4 buffer;
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
			{
				float sum = 0;
				for (int e = 0; e < 4; e++)
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				buffer.elements[x + y * 4] = sum;
			}
		*this = buffer;
		return *this;
	}

	inline Matrix4 &Matrix4::operator*=(const Matrix4 &other)
	{
		return multiply(other);
	}

	inline float Matrix4::trace() const
	{
		return blocks[0].x + blocks[1].y + blocks[2].z + blocks[3].w;
	}

	inline Matrix4 Matrix4::orthographic(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
	{
		Matrix4 result(1.0f);

		result.blocks[0].x = 2.0f / (right - left);
		result.blocks[1].y = 2.0f / (top - bottom);
		result.blocks[2].z = 2.0f / (near - far);

		result.blocks[3].x = (left + right) / (left - right);
		result.blocks[3].y = (bottom + top) / (bottom - top);
		result.blocks[3].z = (far + near) / (far - near);

		return result;
	}

	inline Matrix4 Matrix4::perspective_field_of_view(const float &fov, const float &aspect, const float &near, const float &far)
	{
		auto ymax = near * std::tan(fov / 2.0f);
		auto ymin = -ymax;
		auto xmin = ymin * aspect;
		auto xmax = ymax * aspect;

		return perspective_off_center(xmin, xmax, ymin, ymax, near, far);
	}

	inline Matrix4 Matrix4::perspective_off_center(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
	{
		Matrix4 result(1.0f);

		result.blocks[0].x = (2.0f * near) / (right - left);
		result.blocks[1].y = (2.0f * near) / (top - bottom);

		result.blocks[2].x = (right + left) / (right - left);
		result.blocks[2].y = (top + bottom) / (top - bottom);
		result.blocks[2].z = -(far + near) / (far - near);
		result.blocks[2].w = -1.0f;

		result.blocks[3].z = -(2.0f * far * near) / (far - near);
		result.blocks[3].w = 0.0f;

		return result;
	}

	inline Matrix4 Matrix4::look_at(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
	{
		auto z = Vector3::normalize(eye - target);
		auto x = Vector3::normalize(Vector3::cross(up, z));
		auto y = Vector3::normalize(Vector3::cross(z, x));

		Matrix4 result(1.0f);

		result.blocks[0].x = x.x;
		result.blocks[0].y = y.x;
		result.blocks[0].z = z.x;

		result.blocks[1].x = x.y;
		result.blocks[1].y = y.y;
		result.blocks[1].z = z.y;

		result.blocks[2].x = x.z;
		result.blocks[2].y = y.z;
		result.blocks[2].z = z.z;

		result.blocks[3].x = -((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z));
		result.blocks[3].y = -((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z));
		result.blocks[3].z = -((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z));

		return result;
	}

	inline Matrix4 Matrix4::translation(const Vector3 &translation)
	{
		Matrix4 result(1.0f);
		result.blocks[3].xyz = translation;
		return result;
	}

	inline Matrix4 Matrix4::rotation(const float &angle, const Vector3 &axis)
	{
		float r = angle;
		float c = std::cos(r);
		float s = std::sin(r);
		float omc = 1.0f - c;

		Matrix4 result(1.0f);

		result.blocks[0].x = axis.x * omc + c;
		result.blocks[0].y = axis.y * axis.x * omc + axis.z * s;
		result.blocks[0].z = axis.x * axis.z * omc - axis.y * s;

		result.blocks[1].x = axis.x * axis.y * omc - axis.z * s;
		result.blocks[1].y = axis.y * omc + c;
		result.blocks[1].z = axis.y * axis.z * omc + axis.x * s;

		result.blocks[2].x = axis.x * axis.z * omc + axis.y * s;
		result.blocks[2].y = axis.y * axis.z * omc - axis.x * s;
		result.blocks[2].z = axis.z * omc + c;

		return result;
	}

	inline Matrix4 Matrix4::scale(const Vector3 &scale)
	{
		Matrix4 result(1.0f);
		result.blocks[0].x = scale.x;
		result.blocks[1].y = scale.y;
		result.blocks[2].z = scale.z;
		return result;
	}

	inline Matrix4 operator*(Matrix4 left, const Matrix4 &right)
	{
		return left.multiply(right);
	}

}