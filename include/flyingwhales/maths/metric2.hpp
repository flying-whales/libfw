#pragma once

namespace fw
{

	template<typename T>
	class Metric2
	{
	public:
		T x;
		T y;
	public:
		Metric2();
		Metric2(const T &x, const T &y);

		Metric2<T> &add(const Metric2<T> &other);
		Metric2<T> &subtract(const Metric2<T> &other);
		Metric2<T> &multiply(const Metric2<T> &other);
		Metric2<T> &divide(const Metric2<T> &other);

		Metric2<T> &operator+=(const Metric2<T> &other);
		Metric2<T> &operator-=(const Metric2<T> &other);
		Metric2<T> &operator*=(const Metric2<T> &other);
		Metric2<T> &operator/=(const Metric2<T> &other);

		bool operator==(const Metric2<T> &other) const;
		bool operator!=(const Metric2<T> &other) const;

		template<typename T2>
		explicit operator Metric2<T2>() const;
	};

	template<typename T>
	Metric2<T> operator+(Metric2<T> left, const Metric2<T> &right);
	template<typename T>
	Metric2<T> operator-(Metric2<T> left, const Metric2<T> &right);
	template<typename T>
	Metric2<T> operator*(Metric2<T> left, const Metric2<T> &right);
	template<typename T>
	Metric2<T> operator/(Metric2<T> left, const Metric2<T> &right);

}

// implementation file
#include <flyingwhales/maths/impl/metric2_impl.hpp>