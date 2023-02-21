/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_std.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:21:06 by alilin            #+#    #+#             */
/*   Updated: 2021/11/15 11:35:51 by alilin           ###   ########.fr       */
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

void print_vector(std::vector<int> vector, std::string name)
{
	std::cout << name << ": ";
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void print_size(std::vector<int> vector, std::string name)
{
	std::cout << name << " size: " << vector.size() << ", capacity: " << vector.capacity() << ", max_size: " << vector.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << vector.empty() << std::endl;
}

void test_vector_std()
{
	/********************************/
	/*		DEFAULT CONSTRUCTOR		*/
	/********************************/
	print_title("DEFAULT CONSTRUCTOR", "vector");
	std::vector<int> std_vector;
	print_size(std_vector, "vector");

	print_title("FILL CONSTRUCTOR", "vector");
	std::vector<int> std_vector_fill(10, 42);
	print_size(std_vector_fill, "vector_fill");
	print_vector(std_vector_fill, "vector_fill");

	print_title("RANGE CONSTRUCTOR", "vector");
	std::vector<int> std_vector_range(std_vector_fill.begin(), std_vector_fill.end());
	print_size(std_vector_range, "vector_range");
	print_vector(std_vector_range, "vector_range");

	print_title("COPY CONSTRUCTOR (copy of range)", "vector");
	std::vector<int> std_vector_copy(std_vector_range);
	print_size(std_vector_copy, "vector_copy");
	print_vector(std_vector_copy, "vector_copy");

	print_title("ASSIGNATION OPERATOR", "vector");
	std::vector<int> std_vector_assignation;
	std_vector_assignation = std_vector_copy;
	print_size(std_vector_assignation, "vector_assignation");
	print_vector(std_vector_assignation, "vector_assignation");

	std_vector = std_vector_assignation;


	print_title("ITERATOR TEST");
	std::cout << "vector (iterator): ";
	for (std::vector<int>::iterator it = std_vector.begin(); it != std_vector.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;
	std::cout << "vector (const_iterator): ";
	for (std::vector<int>::const_iterator it = std_vector.begin(); it != std_vector.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;
	std::cout << "vector (reverse_iterator): ";
	for (std::vector<int>::reverse_iterator rit = std_vector.rbegin(); rit != std_vector.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << "\n" << std::endl;
	std::cout << "vector (const_reverse_iterator): ";
	for (std::vector<int>::const_reverse_iterator rit = std_vector.rbegin(); rit != std_vector.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << "\n" << std::endl;


	print_title("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, capacity, resize, empty, reserve");
	print_title("BEFORE RESIZE");
	print_size(std_vector, "vector");

	print_title("AFTER RESIZE(20)");
	std_vector.resize(20);
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");

	print_title("AFTER RESIZE(20, 42)");
	std_vector.resize(40, 42);
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");


	print_title("VECTOR EMPTY()");
	print_size(std_vector, "vector");


	print_title("VECTOR RESERVE(max_size)");
	try
	{
		std_vector.reserve(std_vector.max_size());
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;


	print_title("VECTOR RESERVE(max_size + 1)");
	try
	{
		std_vector.reserve(std_vector.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	print_title("VECTOR RESERVE(50)");
	std_vector.reserve(50);
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");
	print_title("VECTOR RESERVE(45)");
	std_vector.reserve(45);
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");
	print_title("VECTOR RESERVE(30)");
	std_vector.reserve(30);
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");

	print_title("VECTOR [] OPERATOR");
	std::cout << "vector : ";
	for (int i = 0; std_vector[i]; i++)
		std::cout << std_vector[i] << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	print_title("VECTOR AT()");
	try
	{
		std::cout << "vector : ";
		// print_size(std_vector, "vector");
		// for (size_t i = 0; i < std_vector.size() + 1; i++)
		// 	std::cout << "i = " << i << " vector.at(i) = " << std_vector.at(i) << ", ";
		for (size_t i = 0; i < std_vector.size() + 1; i++)
			std::cout << std_vector.at(i) << ", ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	print_title("VECTOR FRONT()");
	std::cout << "vector : " << std_vector.front() << std::endl;
	std::cout << std::endl;

	print_title("VECTOR BACK()");
	std::cout << "vector : " << std_vector.back() << std::endl;
	std::cout << std::endl;

	print_title("VECTOR ASSIGN(first, last)");
	std_vector.assign(std_vector_fill.begin(), std_vector_fill.end());
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");

	print_title("VECTOR ASSIGN(n, val)");
	std_vector.assign(10, 42);
	print_size(std_vector, "vector");
	print_vector(std_vector, "vector");

	print_title("VECTOR PUSH_BACK(i * 42)");
	for (int i = 0; i <= 10; i++)
	{
		std_vector.push_back(i * 42);
		print_size(std_vector, "vector");
	}
	std::cout << std::endl;
	print_vector(std_vector, "vector");

	print_title("VECTOR POP_BACK()");
	for (int i = 0; i < 10; i++)
	{
		std_vector.pop_back();
		print_size(std_vector, "vector");
	}
	std::cout << std::endl;
	print_vector(std_vector, "vector");

	print_title("VECTOR INSERT(position, n, val)");
	std_vector.insert(std_vector.begin(), 5, 420);
	print_vector(std_vector, "vector");

	print_title("VECTOR INSERT(position, first, last)");
	std_vector.insert(std_vector.end(), std_vector_fill.begin(), std_vector_fill.end());
	print_vector(std_vector, "vector");

	print_title("VECTOR ERASE(position)", "erasing first half");
	for (std::vector<int>::iterator it = (std_vector.begin() + (std_vector.size() / 2)); it != std_vector.end() - 1 ; it++)
		std_vector.erase(it);
	print_vector(std_vector, "vector");

	print_title("VECTOR SWAP() (MEMBER)", "swaping vector and range vector");
	print_title("BEFORE SWAP");
	print_vector(std_vector, "vector");
	print_vector(std_vector_range, "vector_range");
	std_vector.swap(std_vector_range);
	print_title("AFTER SWAP");
	print_vector(std_vector, "vector");
	print_vector(std_vector_range, "vector_range");

	print_title("VECTOR SWAP() (NON MEMBER)", "swaping vector and range vector again");
	print_title("BEFORE SWAP");
	print_vector(std_vector, "vector");
	print_vector(std_vector_range, "vector_range");
	std::swap(std_vector, std_vector_range);
	print_title("AFTER SWAP");
	print_vector(std_vector, "vector");
	print_vector(std_vector_range, "vector_range");


	print_title("OPERATIONAL OPERATOR", "vector & vector_copy");
	print_vector(std_vector, "vector");
	print_vector(std_vector, "vector");
	std::cout << "vector == vector_copy: " << (std_vector == std_vector_copy) << std::endl;
	std::cout << "vector != vector_copy: " << (std_vector != std_vector_copy) << std::endl;
	std::cout << "vector < vector_copy: " << (std_vector < std_vector_copy) << std::endl;
	std::cout << "vector <= vector_copy: " << (std_vector <= std_vector_copy) << std::endl;
	std::cout << "vector > vector_copy: " << (std_vector > std_vector_copy) << std::endl;
	std::cout << "vector >= vector_copy: " << (std_vector >= std_vector_copy) << std::endl;
	std::cout << std::endl;

	print_title("OPERATIONAL OPERATOR", "vector_assignation & vector_copy");
	print_vector(std_vector_assignation, "vector_assignation");
	print_vector(std_vector_copy, "vector_copy");
	std::cout << "vector_assignation == vector_copy: " << (std_vector_assignation == std_vector_copy) << std::endl;
	std::cout << "vector_assignation != vector_copy: " << (std_vector_assignation != std_vector_copy) << std::endl;
	std::cout << "vector_assignation < vector_copy: " << (std_vector_assignation < std_vector_copy) << std::endl;
	std::cout << "vector_assignation <= vector_copy: " << (std_vector_assignation <= std_vector_copy) << std::endl;
	std::cout << "vector_assignation > vector_copy: " << (std_vector_assignation > std_vector_copy) << std::endl;
	std::cout << "vector_assignation >= vector_copy: " << (std_vector_assignation >= std_vector_copy) << std::endl;

	std::cout << std::endl;

	print_title("VECTOR CLEAR()");
	print_size(std_vector, "vector before clear()");
	print_size(std_vector_range, "vector_range before clear()");
	std_vector.clear();
	print_size(std_vector, "vector after(clear)");
	print_size(std_vector_range, "vector_range after(clear)");
}
