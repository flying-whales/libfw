#include <flyingwhales/core/exception.hpp>

namespace fw
{

	Exception::Exception(const std::string &message)
		: _message(message)
	{}

	const std::string &Exception::get_message() const
	{
		return _message;
	}

}