#pragma once

#include <flyingwhales/maths/metric2.hpp>

namespace fw
{

	template<typename T>
	class Metric3
	{
	public:
		union
		{
			struct
			{
				T x;
				T y;
			};
			Metric2<T> xy;
		};
		T z;
	public:
		Metric3();
		Metric3(const Metric2<T> &xy, const T &z);
		Metric3(const T &x, const T &y, const T &z);

		Metric3<T> &add(const Metric3<T> &other);
		Metric3<T> &subtract(const Metric3<T> &other);
		Metric3<T> &multiply(const Metric3<T> &other);
		Metric3<T> &divide(const Metric3<T> &other);

		Metric3<T> &operator+=(const Metric3<T> &other);
		Metric3<T> &operator-=(const Metric3<T> &other);
		Metric3<T> &operator*=(const Metric3<T> &other);
		Metric3<T> &operator/=(const Metric3<T> &other);

		bool operator==(const Metric3<T> &other) const;
		bool operator!=(const Metric3<T> &other) const;

		template<typename T2>
		explicit operator Metric3<T2>() const;
	};

	template<typename T>
	Metric3<T> operator+(Metric3<T> left, const Metric3<T> &right);
	template<typename T>
	Metric3<T> operator-(Metric3<T> left, const Metric3<T> &right);
	template<typename T>
	Metric3<T> operator*(Metric3<T> left, const Metric3<T> &right);
	template<typename T>
	Metric3<T> operator/(Metric3<T> left, const Metric3<T> &right);

}

// implementation file
#include <flyingwhales/maths/impl/metric3_impl.hpp>