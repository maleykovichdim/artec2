// artec.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "pch.h"
#include <iostream>
#include <vector>

#include "artec.h"


int main()
{
	matrix2D a(8, 10);
	a[2][3] = 5;
	matrix2D aa(8, 10);
	aa[2][3] = 7;
	matrix2D b = a;
	a[2][3] = 6;
	std::cout << "a ::" << std::endl;
	std::cout << a;
	std::cout << "a :: end" << std::endl;
	std::cout << "b ::" << std::endl;
	std::cout << b;
	std::cout << "b :: end" << std::endl;
	matrix2D c = std::move(b);
	std::cout << "c ::" << std::endl;
	std::cout << c;
	std::cout << "c :: end" << std::endl;
	std::cout << "b after mov begin" << std::endl;
	std::cout << b;
	std::cout << "b after mov end" << std::endl;
	matrix2D cc = a + aa;
	std::cout << cc;
	std::cout << std::endl;
	cc += a;
	std::cout << cc;
	std::cout << std::endl;
}

