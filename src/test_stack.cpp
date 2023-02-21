/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:41:02 by alilin            #+#    #+#             */
/*   Updated: 2021/11/15 12:43:01 by alilin           ###   ########.fr       */
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

void test_stack()
{
  std::cout << YELLOW << "DEFAULT CONSTRUCTOR:" << SET << "stack"<< std::endl;
  ft::stack<int> ft_stack;

  std::cout << std::endl;

  std::cout << YELLOW << "SIZE:" << SET << std::endl;
  std::cout << "stack size: " << ft_stack.size() << std::endl;

  std::cout << std::endl;

  std::cout << YELLOW << "EMPTY:" << SET << std::endl;
  std::cout << "stack empty() (1/true if empty 0/false if not): " << ft_stack.empty() << std::endl;

  std::cout << std::endl;

  std::cout << YELLOW << "PUSH:" << SET << std::endl;
  for (int i = 0; i <= 10; i++)
  {
    ft_stack.push(42 * i);
    std::cout << YELLOW << "TOP:" << ft_stack.top() << std::endl;
  }

  std::cout << std::endl;

  std::cout << YELLOW << "SIZE:" << SET << std::endl;
  std::cout << "stack size: " << ft_stack.size() << std::endl;

  std::cout << std::endl;

  std::cout << YELLOW << "EMPTY:" << SET << std::endl;
  std::cout << "stack empty() (1/true if empty 0/false if not): " << ft_stack.empty() << std::endl;
  std::cout << std::endl;

  std::cout << YELLOW << "COPY CONSTRUCTOR:" << SET << std::endl;
  ft::stack<int> ft_stack_copy(ft_stack);

  std::cout << std::endl;

  std::cout << YELLOW << "POP:" << SET << std::endl;
  for (int i = 0; i <= 10; i++)
  {
    std::cout << YELLOW << "TOP:" << ft_stack.top() << std::endl;
    ft_stack.pop();
  }

  std::cout << std::endl;

  std::cout << YELLOW << "ASSIGNATION OPERATOR:" << SET << std::endl;
  ft_stack_copy = ft_stack;

  std::cout << std::endl;

  std::cout << YELLOW << "OPERATIONAL OPERATOR:" << SET << std::endl;
  std::cout << "(stack == stack_copy) : " << (ft_stack == ft_stack_copy) << std::endl;
  std::cout << "(stack != stack_copy) : " << (ft_stack != ft_stack_copy) << std::endl;
  std::cout << "(stack < stack_copy) : " << (ft_stack < ft_stack_copy) << std::endl;
  std::cout << "(stack <= stack_copy) : " << (ft_stack <= ft_stack_copy) << std::endl;
  std::cout << "(stack > stack_copy) : " << (ft_stack > ft_stack_copy) << std::endl;
  std::cout << "(stack >= stack_copy) : " << (ft_stack >= ft_stack_copy) << std::endl;
  std::cout << std::endl;

}
