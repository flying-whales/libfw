#pragma once

#include <flyingwhales/maths/metric4.hpp>

namespace fw
{

	template<typename T>
	Metric4<T>::Metric4()
		: Metric4(T(), T(), T(), T())
	{}

	template<typename T>
	Metric4<T>::Metric4(const Metric3<T> &xyz, const T &w)
		: Metric4(xyz.x, xyz.y, xyz.z, w)
	{}

	template<typename T>
	Metric4<T>::Metric4(const Metric2<T> &xy, const T &z, const T &w)
		: Metric4(xy.x, xy.y, z, w)
	{}

	template<typename T>
	Metric4<T>::Metric4(const T &x, const T &y, const T &z, const T &w)
		: x(x), y(y), z(z), w(w)
	{}

	template<typename T>
	Metric4<T> &Metric4<T>::add(const Metric4<T> &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	template<typename T>
	Metric4<T> &Metric4<T>::subtract(const Metric4<T> &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	template<typename T>
	Metric4<T> &Metric4<T>::multiply(const Metric4<T> &other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	template<typename T>
	Metric4<T> &Metric4<T>::divide(const Metric4<T> &other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	template<typename T>
	Metric4<T> &Metric4<T>::operator+=(const Metric4<T> &other)
	{
		return add(other);
	}

	template<typename T>
	Metric4<T> &Metric4<T>::operator-=(const Metric4<T> &other)
	{
		return subtract(other);
	}

	template<typename T>
	Metric4<T> &Metric4<T>::operator*=(const Metric4<T> &other)
	{
		return multiply(other);
	}

	template<typename T>
	Metric4<T> &Metric4<T>::operator/=(const Metric4<T> &other)
	{
		return divide(other);
	}

	template<typename T>
	bool Metric4<T>::operator==(const Metric4<T> &other) const
	{
		return ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
	}

	template<typename T>
	bool Metric4<T>::operator!=(const Metric4<T> &other) const
	{
		return !(*this == other);
	}

	template<typename T>
	template<typename T2>
	Metric4<T>::operator Metric4<T2>() const
	{
		static_assert(std::is_convertible<T, T2>::value, "Cannot convert template types");
		return Metric4<T2>(static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(z), static_cast<T2>(w));
	}

	template<typename T>
	Metric4<T> operator+(Metric4<T> left, const Metric4<T> &right)
	{
		return left.add(right);
	}

	template<typename T>
	Metric4<T> operator-(Metric4<T> left, const Metric4<T> &right)
	{
		return left.subtract(right);
	}

	template<typename T>
	Metric4<T> operator*(Metric4<T> left, const Metric4<T> &right)
	{
		return left.multiply(right);
	}

	template<typename T>
	Metric4<T> operator/(Metric4<T> left, const Metric4<T> &right)
	{
		return left.divide(right);
	}

}