#pragma once

#include <exception>
#include <string>

namespace fw
{

	class Exception
	{
	protected:
		std::string _message;
	public:
		Exception(const std::string &message);
		virtual ~Exception() = default;

		const std::string &get_message() const; 
	};

}