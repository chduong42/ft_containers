/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:45:09 by alilin            #+#    #+#             */
/*   Updated: 2021/11/15 11:36:48 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TEST for Vector:
//	Constructors
//		default, fill, range, copy, assignation operator
//	Accessors, iterators, getters, setters:
//		iterator, const_iterator, reverse_iterator, const_reverse_iterator, begin, end, rbegin, rend
//		size, max_size, resize, capacity, empty, reserve
//		operator[], at, front, back
//		assign, push_back, pop_back, insert, erase, swap, clear

#include "tester.hpp"

void print_vector(ft::vector<int> vector, std::string name)
{
	std::cout << name << ": ";
	for (ft::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void print_size(ft::vector<int> vector, std::string name)
{
	std::cout << name << " size: " << vector.size() << ", capacity: " << vector.capacity() << ", max_size: " << vector.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << vector.empty() << std::endl;
}

void test_vector()
{
	/********************************/
	/*		DEFAULT CONSTRUCTOR		*/
	/********************************/
	print_title("DEFAULT CONSTRUCTOR", "vector");
	ft::vector<int> ft_vector;
	print_size(ft_vector, "vector");

	print_title("FILL CONSTRUCTOR", "vector");
	ft::vector<int> ft_vector_fill(10, 42);
	print_size(ft_vector_fill, "vector_fill");
	print_vector(ft_vector_fill, "vector_fill");

	print_title("RANGE CONSTRUCTOR", "vector");
	ft::vector<int> ft_vector_range(ft_vector_fill.begin(), ft_vector_fill.end());
	print_size(ft_vector_range, "vector_range");
	print_vector(ft_vector_range, "vector_range");

	print_title("COPY CONSTRUCTOR (copy of range)", "vector");
	ft::vector<int> ft_vector_copy(ft_vector_range);
	print_size(ft_vector_copy, "vector_copy");
	print_vector(ft_vector_copy, "vector_copy");

	print_title("ASSIGNATION OPERATOR", "vector");
	ft::vector<int> ft_vector_assignation;
	ft_vector_assignation = ft_vector_copy;
	print_size(ft_vector_assignation, "vector_assignation");
	print_vector(ft_vector_assignation, "vector_assignation");

	ft_vector = ft_vector_assignation;


	print_title("ITERATOR TEST");
	std::cout << "vector (iterator): ";
	for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;
	std::cout << "vector (const_iterator): ";
	for (ft::vector<int>::const_iterator it = ft_vector.begin(); it != ft_vector.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;
	std::cout << "vector (reverse_iterator): ";
	for (ft::vector<int>::reverse_iterator rit = ft_vector.rbegin(); rit != ft_vector.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << "\n" << std::endl;
	std::cout << "vector (const_reverse_iterator): ";
	for (ft::vector<int>::const_reverse_iterator rit = ft_vector.rbegin(); rit != ft_vector.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << "\n" << std::endl;


	print_title("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, capacity, resize, empty, reserve");
	print_title("BEFORE RESIZE");
	print_size(ft_vector, "vector");

	print_title("AFTER RESIZE(20)");
	ft_vector.resize(20);
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");

	print_title("AFTER RESIZE(20, 42)");
	ft_vector.resize(40, 42);
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");


	print_title("VECTOR EMPTY()");
	print_size(ft_vector, "vector");


	print_title("VECTOR RESERVE(max_size)");
	try
	{
		ft_vector.reserve(ft_vector.max_size());
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;


	print_title("VECTOR RESERVE(max_size + 1)");
	try
	{
		ft_vector.reserve(ft_vector.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	print_title("VECTOR RESERVE(50)");
	ft_vector.reserve(50);
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");
	print_title("VECTOR RESERVE(45)");
	ft_vector.reserve(45);
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");
	print_title("VECTOR RESERVE(30)");
	ft_vector.reserve(30);
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");

	print_title("VECTOR [] OPERATOR");
	std::cout << "vector : ";
	for (int i = 0; ft_vector[i]; i++)
		std::cout << ft_vector[i] << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	print_title("VECTOR AT()");
	try
	{
		std::cout << "vector : ";
		// print_size(ft_vector, "vector");
		// for (size_t i = 0; i < ft_vector.size() + 1; i++)
		// 	std::cout << "i = " << i << " vector.at(i) = " << ft_vector.at(i) << ", ";
		for (size_t i = 0; i < ft_vector.size() + 1; i++)
			std::cout << ft_vector.at(i) << ", ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	print_title("VECTOR FRONT()");
	std::cout << "vector : " << ft_vector.front() << std::endl;
	std::cout << std::endl;

	print_title("VECTOR BACK()");
	std::cout << "vector : " << ft_vector.back() << std::endl;
	std::cout << std::endl;

	print_title("VECTOR ASSIGN(first, last)");
	ft_vector.assign(ft_vector_fill.begin(), ft_vector_fill.end());
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");

	print_title("VECTOR ASSIGN(n, val)");
	ft_vector.assign(10, 42);
	print_size(ft_vector, "vector");
	print_vector(ft_vector, "vector");

	print_title("VECTOR PUSH_BACK(i * 42)");
	for (int i = 0; i <= 10; i++)
	{
		ft_vector.push_back(i * 42);
		print_size(ft_vector, "vector");
	}
	std::cout << std::endl;
	print_vector(ft_vector, "vector");

	print_title("VECTOR POP_BACK()");
	for (int i = 0; i < 10; i++)
	{
		ft_vector.pop_back();
		print_size(ft_vector, "vector");
	}
	std::cout << std::endl;
	print_vector(ft_vector, "vector");

	print_title("VECTOR INSERT(position, n, val)");
	ft_vector.insert(ft_vector.begin(), 5, 420);
	print_vector(ft_vector, "vector");

	print_title("VECTOR INSERT(position, first, last)");
	ft_vector.insert(ft_vector.end(), ft_vector_fill.begin(), ft_vector_fill.end());
	print_vector(ft_vector, "vector");

	print_title("VECTOR ERASE(position)", "erasing first half");
	for (ft::vector<int>::iterator it = (ft_vector.begin() + (ft_vector.size() / 2)); it != ft_vector.end() - 1 ; it++)
		ft_vector.erase(it);
	print_vector(ft_vector, "vector");

	print_title("VECTOR SWAP() (MEMBER)", "swaping vector and range vector");
	print_title("BEFORE SWAP");
	print_vector(ft_vector, "vector");
	print_vector(ft_vector_range, "vector_range");
	ft_vector.swap(ft_vector_range);
	print_title("AFTER SWAP");
	print_vector(ft_vector, "vector");
	print_vector(ft_vector_range, "vector_range");

	print_title("VECTOR SWAP() (NON MEMBER)", "swaping vector and range vector again");
	print_title("BEFORE SWAP");
	print_vector(ft_vector, "vector");
	print_vector(ft_vector_range, "vector_range");
	std::swap(ft_vector, ft_vector_range);
	print_title("AFTER SWAP");
	print_vector(ft_vector, "vector");
	print_vector(ft_vector_range, "vector_range");


	print_title("OPERATIONAL OPERATOR", "vector & vector_copy");
	print_vector(ft_vector, "vector");
	print_vector(ft_vector, "vector");
	std::cout << "vector == vector_copy: " << (ft_vector == ft_vector_copy) << std::endl;
	std::cout << "vector != vector_copy: " << (ft_vector != ft_vector_copy) << std::endl;
	std::cout << "vector < vector_copy: " << (ft_vector < ft_vector_copy) << std::endl;
	std::cout << "vector <= vector_copy: " << (ft_vector <= ft_vector_copy) << std::endl;
	std::cout << "vector > vector_copy: " << (ft_vector > ft_vector_copy) << std::endl;
	std::cout << "vector >= vector_copy: " << (ft_vector >= ft_vector_copy) << std::endl;
	std::cout << std::endl;

	print_title("OPERATIONAL OPERATOR", "vector_assignation & vector_copy");
	print_vector(ft_vector_assignation, "vector_assignation");
	print_vector(ft_vector_copy, "vector_copy");
	std::cout << "vector_assignation == vector_copy: " << (ft_vector_assignation == ft_vector_copy) << std::endl;
	std::cout << "vector_assignation != vector_copy: " << (ft_vector_assignation != ft_vector_copy) << std::endl;
	std::cout << "vector_assignation < vector_copy: " << (ft_vector_assignation < ft_vector_copy) << std::endl;
	std::cout << "vector_assignation <= vector_copy: " << (ft_vector_assignation <= ft_vector_copy) << std::endl;
	std::cout << "vector_assignation > vector_copy: " << (ft_vector_assignation > ft_vector_copy) << std::endl;
	std::cout << "vector_assignation >= vector_copy: " << (ft_vector_assignation >= ft_vector_copy) << std::endl;

	std::cout << std::endl;

	print_title("VECTOR CLEAR()");
	print_size(ft_vector, "vector before clear()");
	print_size(ft_vector_range, "vector_range before clear()");
	ft_vector.clear();
	print_size(ft_vector, "vector after(clear)");
	print_size(ft_vector_range, "vector_range after(clear)");
}
