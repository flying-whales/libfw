#pragma once

#include <flyingwhales/maths/metric2.hpp>
#include <type_traits>

namespace fw
{

	template<typename T>
	inline Metric2<T>::Metric2()
		: Metric2(T(), T())
	{}

	template<typename T>
	inline Metric2<T>::Metric2(const T &x, const T &y)
		: x(x), y(y)
	{}

	template<typename T>
	inline Metric2<T> &Metric2<T>::add(const Metric2<T> &other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::subtract(const Metric2<T> &other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::multiply(const Metric2<T> &other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::divide(const Metric2<T> &other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::operator+=(const Metric2<T> &other)
	{
		return add(other);
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::operator-=(const Metric2<T> &other)
	{
		return subtract(other);
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::operator*=(const Metric2<T> &other)
	{
		return multiply(other);
	}

	template<typename T>
	inline Metric2<T> &Metric2<T>::operator/=(const Metric2<T> &other)
	{
		return divide(other);
	}

	template<typename T>
	inline bool Metric2<T>::operator==(const Metric2<T> &other) const
	{
		return ((x == other.x) && (y == other.y));
	}

	template<typename T>
	inline bool Metric2<T>::operator!=(const Metric2<T> &other) const
	{
		return !(*this == other);
	}

	template<typename T>
	template<typename T2>
	inline Metric2<T>::operator Metric2<T2>() const
	{
		static_assert(std::is_convertible<T, T2>::value, "Cannot convert template types");
		return Metric2<T2>(static_cast<T2>(x), static_cast<T2>(y));
	}

	template<typename T>
	inline Metric2<T> operator+(Metric2<T> left, const Metric2<T> &right)
	{
		return left.add(right);
	}

	template<typename T>
	inline Metric2<T> operator-(Metric2<T> left, const Metric2<T> &right)
	{
		return left.subtract(right);
	}

	template<typename T>
	inline Metric2<T> operator*(Metric2<T> left, const Metric2<T> &right)
	{
		return left.multiply(right);
	}

	template<typename T>
	inline Metric2<T> operator/(Metric2<T> left, const Metric2<T> &right)
	{
		return left.divide(right);
	}

}