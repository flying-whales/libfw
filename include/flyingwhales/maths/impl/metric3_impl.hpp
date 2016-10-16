#pragma once

#include <flyingwhales/maths/metric3.hpp>

namespace fw
{

	template<typename T>
	inline Metric3<T>::Metric3()
		: Metric3(T(), T(), T())
	{}

	template<typename T>
	inline Metric3<T>::Metric3(const Metric2<T> &xy, const T &z)
		: Metric3(xy.x, xy.y, z)
	{}

	template<typename T>
	inline Metric3<T>::Metric3(const T &x, const T &y, const T &z)
		: x(x), y(y), z(z)
	{}

	template<typename T>
	inline Metric3<T> &Metric3<T>::add(const Metric3<T> &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::subtract(const Metric3<T> &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::multiply(const Metric3<T> &other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::divide(const Metric3<T> &other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::operator+=(const Metric3<T> &other)
	{
		return add(other);
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::operator-=(const Metric3<T> &other)
	{
		return subtract(other);
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::operator*=(const Metric3<T> &other)
	{
		return multiply(other);
	}

	template<typename T>
	inline Metric3<T> &Metric3<T>::operator/=(const Metric3<T> &other)
	{
		return divide(other);
	}

	template<typename T>
	inline bool Metric3<T>::operator==(const Metric3<T> &other) const
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}

	template<typename T>
	inline bool Metric3<T>::operator!=(const Metric3<T> &other) const
	{
		return !(*this == other);
	}

	template<typename T>
	template<typename T2>
	inline Metric3<T>::operator Metric3<T2>() const
	{
		static_assert(std::is_convertible<T, T2>::value, "Cannot convert template types");
		return Metric3<T2>(static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(z));
	}

	template<typename T>
	inline Metric3<T> operator+(Metric3<T> left, const Metric3<T> &right)
	{
		return left.add(right);
	}

	template<typename T>
	inline Metric3<T> operator-(Metric3<T> left, const Metric3<T> &right)
	{
		return left.subtract(right);
	}

	template<typename T>
	inline Metric3<T> operator*(Metric3<T> left, const Metric3<T> &right)
	{
		return left.multiply(right);
	}

	template<typename T>
	inline Metric3<T> operator/(Metric3<T> left, const Metric3<T> &right)
	{
		return left.divide(right);
	}

}