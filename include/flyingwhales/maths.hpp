#pragma once

#include <flyingwhales/maths/metric2.hpp>
#include <flyingwhales/maths/metric3.hpp>
#include <flyingwhales/maths/metric4.hpp>

#include <flyingwhales/maths/vector2.hpp>
#include <flyingwhales/maths/vector2.hpp>
#include <flyingwhales/maths/vector2.hpp>

#include <flyingwhales/maths/matrix4.hpp>
#include <flyingwhales/maths/quaternion.hpp>

// type aliases

#include <cstdint>

namespace fw
{

	using Size2 = Metric2<uint32_t>;
	using Size3 = Metric3<uint32_t>;
	using Size4 = Metric4<uint32_t>;

}