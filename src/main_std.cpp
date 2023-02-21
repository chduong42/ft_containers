/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_std.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:48:20 by alilin            #+#    #+#             */
/*   Updated: 2021/11/15 12:43:57 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void print_title(std::string title, std::string subtitle)
{
	std::cout << std::endl;
  std::cout << YELLOW << title << ": " << SET << subtitle << "\n" << std::endl;
}

void print_header(std::string container_name)
{
	std::string header = YELLOW + container_name + " TESTS:" + SET + " press enter to continue\n";
	int width = 100 - (header.length() / 2);

	std::cout << '/' << std::setfill('*') << std::setw(100) << "/\n" << std::setfill(' ') << std::endl;
	std::cout << std::setw(width) << header << std::endl;
	std::cout << '/' << std::setfill('*') << std::setw(100) << "/\n" << std::setfill(' ') << std::endl;
}

int main()
{
	print_header("VECTOR");
	std::cout << std::endl;
	while (std::cin.get() != '\n') {}
	test_vector_std();
	print_header("STACK");
	while (std::cin.get() != '\n') {}
	test_stack_std();
	print_header("MAP");
	while (std::cin.get() != '\n') {}
	test_map_std();
	print_header("SET");
	while (std::cin.get() != '\n') {}
	test_set_std();

	return 0;
}
