#pragma once

#include "pch.h"
#include <iostream>
#include <vector>
#include <cassert>



class matrix2D : public std::vector<std::vector<int>>
{
public:
	matrix2D(int n, int m) : std::vector<std::vector<int>>(n, std::vector<int>(m, 0)) {};
	matrix2D(const matrix2D & m) :	std::vector<std::vector<int>>((std::vector<std::vector<int>>)(m)) {}

	matrix2D & operator=(const matrix2D & m)
	{
		if (this != &m) { 	*this = m; 	}
		return *this;
	}

	matrix2D (matrix2D&& m) noexcept
	{
		*(std::vector<std::vector<int>>*)(this) = std::move(m);
	}

	matrix2D& operator = (matrix2D && m) noexcept
	{
		if (this != &m) {
			*(std::vector<std::vector<int>>*)(this) = std::move(m);
		}
		return *this;
	}

	friend std::ostream& operator <<(std::ostream &, const matrix2D &);
	friend std::istream& operator >> (std::istream &in, matrix2D &point);
	matrix2D operator += (const matrix2D  rhs);
};

std::ostream & operator <<(std::ostream &os, const matrix2D &a)
{
	for (auto row : a)
	{
		for (auto el : row)
			os << el << " ";
		os << '\n';
	}
	return os;
}

std::istream& operator>> (std::istream &in, matrix2D &a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		for (int j = 0; j < (int)a.size(); j++)
			in >> a[i][j];
	}
	return in;
}


matrix2D matrix2D::operator += (const matrix2D  rhs) 
{

	int lines_left = (int)(*(std::vector<std::vector<int>>*)(this)).size();
	int rows_left = (int)(*(std::vector<std::vector<int>>*)(this))[0].size();
	int lines_right = (int)rhs.size();
	int rows_right = (int)rhs[0].size();
	assert(lines_left == lines_right && rows_left == rows_right);

	if (lines_left != lines_right || rows_left != rows_right)
	{
		return *this;
	}

	for (int i = 0; i < lines_left; i++)
		for (int j = 0; j < rows_left; j++)
			(*(std::vector<std::vector<int>>*)(this))[i][j] += rhs[i][j];
	return *this;
}



matrix2D operator+ (const matrix2D  lhs, const matrix2D  rhs) {
	int lines_left = (int)lhs.size();
	int rows_left = (int)lhs[0].size();
	int lines_right = (int)rhs.size();
	int rows_right = (int)rhs[0].size();
	assert(lines_left == lines_right && rows_left == rows_right);

	if (lines_left != lines_right || rows_left != rows_right)
	{
		return std::move(matrix2D(lhs));
	}

	matrix2D tmp(lhs);
	tmp += rhs;
	return std::move(tmp);
}




