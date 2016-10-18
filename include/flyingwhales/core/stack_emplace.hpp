#pragma once

#include <flyingwhales/core/noncopyable.hpp>
#include <cstdint>
#include <new>

namespace fw
{

	template<typename T>
	class StackEmplace : public Noncopyable
	{
	private:
		uint8_t _buffer[sizeof(T)];
		bool _constructed;
	public:
		StackEmplace();

		template<typename ...A>
		StackEmplace(A &&...args);

		~StackEmplace();

		template<typename ...A>
		void emplace(A &&...args);
		void reset();

		T &get();
		T &operator*();
		T *operator->();

		operator bool() const;
	};

	template<typename T>
	StackEmplace<T>::StackEmplace()
		: _buffer{ 0 }, _constructed(false)
	{}

	template<typename T>
	template<typename ...A>
	StackEmplace<T>::StackEmplace(A &&...args)
		: StackEmplace()
	{
		emplace(std::forward<A>(args)...);
	}

	template<typename T>
	StackEmplace<T>::~StackEmplace()
	{
		reset();
	}

	template<typename T>
	template<typename ...A>
	void StackEmplace<T>::emplace(A &&...args)
	{
		reset();
		new (&get()) T(std::forward<A>(args)...);
		_constructed = true;
	}

	template<typename T>
	void StackEmplace<T>::reset()
	{
		if (!_constructed)
			return;

		get().~T();
		_constructed = false;
	}

	template<typename T>
	T &StackEmplace<T>::get()
	{
		return *static_cast<T *>(static_cast<void *>(_buffer));
	}

	template<typename T>
	T &StackEmplace<T>::operator*()
	{
		return get();
	}

	template<typename T>
	T *StackEmplace<T>::operator->()
	{
		return &get();
	}

	template<typename T>
	StackEmplace<T>::operator bool() const
	{
		return _constructed;
	}

}