#pragma once

#include <flyingwhales/maths/metric3.hpp>

namespace fw
{

	template<typename T>
	class Metric4
	{
	public:
		union
		{
			struct
			{
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
			};
			Metric3<T> xyz;
		};
		T w;
	public:
		Metric4();
		Metric4(const Metric3<T> &xyz, const T &w);
		Metric4(const Metric2<T> &xy, const T &z, const T &w);
		Metric4(const T &x, const T &y, const T &z, const T &w);

		Metric4<T> &add(const Metric4<T> &other);
		Metric4<T> &subtract(const Metric4<T> &other);
		Metric4<T> &multiply(const Metric4<T> &other);
		Metric4<T> &divide(const Metric4<T> &other);

		Metric4<T> &operator+=(const Metric4<T> &other);
		Metric4<T> &operator-=(const Metric4<T> &other);
		Metric4<T> &operator*=(const Metric4<T> &other);
		Metric4<T> &operator/=(const Metric4<T> &other);

		bool operator==(const Metric4<T> &other) const;
		bool operator!=(const Metric4<T> &other) const;

		template<typename T2>
		explicit operator Metric4<T2>() const;
	};

	template<typename T>
	Metric4<T> operator+(Metric4<T> left, const Metric4<T> &right);
	template<typename T>
	Metric4<T> operator-(Metric4<T> left, const Metric4<T> &right);
	template<typename T>
	Metric4<T> operator*(Metric4<T> left, const Metric4<T> &right);
	template<typename T>
	Metric4<T> operator/(Metric4<T> left, const Metric4<T> &right);

}

// implementation file
#include <flyingwhales/maths/impl/metric4_impl.hpp>