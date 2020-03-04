//matrix n x m
#pragma once

#include <iostream>
#include <vector>
#include <cassert>

/////////////////////////////////////////////////////////////// block for templates only
template <typename T, int N, int M>
class Matrix;
template <typename T, int N, int M>
using MATR = Matrix<T,N,M>;

template <typename T, int N, int M>
std::ostream& operator<< (std::ostream& os, const Matrix<T, N, M>& L);
template <typename T, int N, int M>
std::istream& operator >> (std::istream &in, Matrix<T, N, M> & point);
////////////////////////////////////////////////////////////////

//iterator class for matrix class
template <typename T>
class matr_iterator 
{
	T * p_data;
public:
	matr_iterator(T * data) : p_data(data) {}
	matr_iterator(const matr_iterator &it) : p_data(it.p_data) {};
	T& operator*() const { return *p_data; };
	matr_iterator& operator++() {
		++p_data;
		return *this;
	}
	bool operator!=(const matr_iterator &other) const {
		return p_data != other.p_data;
	}
	bool operator==(const matr_iterator &other) const {
		return (p_data == other.p_data);
	}
};

namespace std {
	template <typename T>
	struct iterator_traits<matr_iterator<T>> {
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = T;
		using pointer = const T*;
		using	reference = const T&;
	};
}


///////////////////////////////////////////////////////////////////////
// MATRIX CLASS
template <typename T, int N, int M>
class Matrix {
public:
	//constructors
	Matrix() {} ;
	~Matrix() {} ;

	Matrix(const Matrix & matr) noexcept;
	Matrix & operator=(const Matrix & matr) noexcept;
	Matrix(Matrix&& matr) noexcept;
	Matrix& operator = (Matrix && matr) noexcept;

public:
	//operators

	inline T& operator[] (int i) { return m_data[i]; }
	inline const T& operator[] (int i) const { return m_data[i]; }

	friend std::ostream& operator << <>(std::ostream &os, const Matrix & matr);
	friend std::istream& operator >> <>(std::istream &in, Matrix &point);
	Matrix & operator += (const Matrix  & rhs);

public:
	//iterator

	typedef matr_iterator<T> var_matr_iterator;
	typedef matr_iterator<const T> const_matr_iterator;
	const_matr_iterator begin() const { return const_matr_iterator(m_data); };
	const_matr_iterator end() const { return const_matr_iterator(m_data +N*M); };
	var_matr_iterator begin()  { return var_matr_iterator(m_data ); };
	var_matr_iterator end()  { return var_matr_iterator(m_data+ N*M); };

public:
	//work with data
	void copyFrom(const Matrix & matr) noexcept;
	void copyFrom(const T * ext_data, int width, int own_offset);
	void clear() noexcept;
	const T * getData() const { return &m_data[0]; }

protected:
	//matrix data
	T m_data[N*M];
};

/////////////////////////////////////////////////////////////////////////////////////

template<typename T, int N, int M>
inline Matrix<T, N, M>::Matrix(const Matrix<T, N, M> & matr) noexcept
{
	copyFrom(matr);
}

template<typename T, int N, int M>
inline Matrix<T, N, M> & Matrix<T, N, M>::operator=(const Matrix<T, N, M> & matr) noexcept
{
	if (this != &matr) copyFrom(matr);
	return *this;
}

template<typename T, int N, int M>
inline Matrix<T, N, M>::Matrix(Matrix && matr) noexcept
{
	copyFrom(matr);
	matr.clear();
}

template<typename T, int N, int M>
inline Matrix<T, N, M> & Matrix<T, N, M>::operator=(Matrix<T, N, M> && matr) noexcept
{
	if (this != &matr)
	{
		copyFrom(matr);
		matr.clear();
	}
	return *this;
}



template<typename T, int N, int M>
inline void Matrix<T, N, M>::copyFrom(const Matrix<T, N, M> & matr) noexcept
{
	memcpy(m_data, matr.m_data, N *M * sizeof(T));//  i use C-style because it is faster
}

template<typename T, int N, int M>
inline void Matrix<T, N, M>::copyFrom(const T * ext_data, int width,  int own_offset) 
{
	for (int i =0; i < N; i++)
		memcpy((m_data + i * M + own_offset), ext_data + i * width, width * sizeof(T));//  i use C-style because it is faster
}


template<typename T, int N, int M>
inline void Matrix<T, N, M>::clear() noexcept
{
	memset(m_data, 0, N * M * sizeof(T));
}

template<typename T, int N, int M>
std::ostream & operator<< (std::ostream & os, const Matrix<T, N, M> & matr)
{
	int i = 0;
	for (auto a : matr) { os << a << " "; if ((++i) % M == 0) os << '\n'; }
	return os;
}

template<typename T, int N, int M>
std::istream & operator>> (std::istream & in, Matrix<T, N, M> & matr)
{
	for (auto iter = matr.begin(); iter != matr.end(); ++iter)
		in >> *iter;
	return in;
}

template<typename T, int N, int M>
inline Matrix<T, N, M> &  Matrix<T, N, M>::operator+=(const Matrix<T, N, M>  & rhs)
{
	auto iter = this->begin();
	auto iter_r = rhs.begin();
	for (; iter != this->end(); ++iter, ++iter_r)
		*iter += *iter_r;
	return *this;
}

template<typename T, int N, int M>
inline Matrix<T, N, M> operator+ (const Matrix<T, N, M> & lhs, const Matrix<T, N, M>  & rhs) 
{
	Matrix<T, N, M> tmp(lhs);
	tmp += rhs;
	return tmp;// todo: check std move. last time i have the comment : not do it
}


template<typename T, int N, int M1, int M2>
Matrix<T, N, M1+M2> operator|(const Matrix<T, N, M1> & lhs, const Matrix<T, N, M2> & rhs)
{
	Matrix<T, N, M1 + M2> tmp;
	tmp.copyFrom(lhs.getData(), M1, 0);
	tmp.copyFrom(rhs.getData(), M2, M1);
	return tmp; // todo: check std move. last time i have the comment : not do it
}


////////////////////////////////////////////////////////////////////////////////////

template  class Matrix <double, 8, 10>;
template  class Matrix <double, 2, 2>;
template  class Matrix <double, 10, 8>;

using MAT8_10 = Matrix<double, 8, 10>;
using MAT10_8 = Matrix<double, 10, 8>;