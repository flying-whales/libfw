#pragma once

namespace fw
{

	class Noncopyable
	{
	protected:
		Noncopyable() = default;
		~Noncopyable() = default;

		Noncopyable(const Noncopyable &) = delete;
		Noncopyable &operator=(const Noncopyable &) = delete;
	};

}