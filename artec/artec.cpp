// main function for test
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

#include "artec.h"

int main()
{

	MAT8_10 * a = new MAT8_10();
	int i = 0;
	for (auto iter = a->begin(); iter != a->end(); ++iter) *iter = i++;
	std::cout << "a matrix:\n" << *a << std::endl;

	MAT8_10  b;
	i = 100;
	for (auto iter =b.begin(); iter != b.end(); ++iter) *iter = i++;
	std::cout << "b matrix:\n" << b << std::endl;

	MAT8_10  c = *a;
	std::cout << "c copy matrix:\n" << c << std::endl;

	MAT8_10  d = std::move(b);
	std::cout << "d moved matrix:\n" << d << std::endl;
	std::cout << "b after move matrix:\n" << b << std::endl;

	std::cout <<"accumulate d=" << std::accumulate(d.begin(),d.end(),0.0) << std::endl << std::endl;

	Matrix <double, 8, 10> f = c + d;
	std::cout << "f =c + d matrix:\n" << f << std::endl;
	std::cout <<  '\n';

	Matrix <double, 8, 10+10> e = (c | f);
	std::cout << "e = (c | f) matrix:\n" << e << std::endl;

	e[15] = 0.0;

	std::cout << "enter matrix 2x2:" << std::endl;
	Matrix <double, 2, 2> j;
	std::cin >> j;
	std::cout <<" j matrix:\n" << j << std::endl;

}


