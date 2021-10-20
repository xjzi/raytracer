#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <vector>

template<typename T> struct Matrix {
	unsigned int width;
	unsigned int height;

	Matrix(unsigned int width, unsigned int height): 
		elements(std::vector<T> (width * height)),
		width(width), 
		height(height) {}

	T& operator()(int index) {
		return elements[index];
	}
	T& operator() (unsigned x, unsigned y) {
		return elements[x + y * width];
	}

private:
	std::vector<T> elements;
};
#endif // __MATRIX_HPP__

