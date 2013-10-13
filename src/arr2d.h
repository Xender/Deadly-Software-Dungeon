#pragma once

#include <vector>

// Column order
template<typename T>
class Arr2d
{
	std::vector<T> v;

public:
	const std::size_t width, height;

	Arr2d(std::size_t width, std::size_t height)
	: v(width*height), width(width), height(height)
	{}

	T* operator[] (std::size_t x)
	{
		return &v[x*height];
	}

	const T* operator[] (std::size_t x) const
	{
		return &v[x*height];
	}
};
