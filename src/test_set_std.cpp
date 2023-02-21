/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_std.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:19:38 by alilin            #+#    #+#             */
/*   Updated: 2021/11/12 17:24:50 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TEST for Set:
//	Constructors
//		default, range, copy, assignation operator
//	Accessors, iterators, getters, setters:
//		iterator, const_iterator, reverse_iterator, const_reverse_iterator, begin, end, rbegin, rend
//		size, max_size, empty
//		operator[], at
//		insert, erase, swap, clear
//    key_comp, value_comp
// find count lower_bound upper_bound equal_range


#include "tester.hpp"

void print_set(std::set<char> set, std::string name)
{
	std::cout << name << ":\n";
	for (std::set<char>::iterator it = set.begin(); it != set.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_size(std::set<char> set, std::string name)
{
	std::cout << name << " size: " << set.size() << ", max_size: " << set.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << set.empty() << std::endl;
	std::cout << std::endl;
}

void test_set_std()
{
	print_title("CONSTRUCTOR", "set");
	std::set<char> std_set;
	print_size(std_set, "set");

	char c = 'a';
	for (int i = 1; i <= 13; i++, c++)
	{
		std_set.insert(c);
	}
	print_set(std_set, "set");
	print_size(std_set, "set");

	print_title("RANGE", "set");
	std::set<char> std_set_range(std_set.begin(), std_set.end());
	print_size(std_set_range, "set_range");
	print_set(std_set_range, "set_range");

	print_title("COPY CONSTRUCTOR (copy of range)", "set");
	std::set<char> std_set_copy(std_set_range);
	print_size(std_set_copy, "set_copy");
	print_set(std_set_copy, "set_copy");


	print_title("ASSIGNATION OPERATOR", "set");
	std::set<char> std_set_assignation;
	std_set_assignation = std_set_copy;
	print_size(std_set_assignation, "set_assignation");
	print_set(std_set_assignation, "set_assignation");


	print_title("ITERATORS TESTS");
	std::cout << "set (iterator): ";
	for (std::set<char>::iterator it = std_set.begin(); it != std_set.end(); it++)
		std::cout << *it << ", ";
	std::cout << "\n" << std::endl;
	std::cout << "set (const_iterator): ";
	for (std::set<char>::const_iterator it = std_set.begin(); it != std_set.end(); it++)
		std::cout << *it << ", ";
	std::cout << "\n" << std::endl;
	std::cout << "set (reverse_iterator): ";
	for (std::set<char>::reverse_iterator rit = std_set.rbegin(); rit != std_set.rend(); rit++)
		std::cout << *rit << ", ";
	std::cout << "\n" << std::endl;
	std::cout << "set (const_reverse_iterator): ";
	for (std::set<char>::const_reverse_iterator rit = std_set.rbegin(); rit != std_set.rend(); rit++)
		std::cout << *rit << ", ";
	std::cout << "\n" << std::endl;

	print_title("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, empty");
	print_size(std_set, "set");

	print_title("SET INSERT(val)");
	for (int i = 14; i <= 19; i++, c++)
	{
		std_set.insert(c);
	}
	print_set(std_set, "set");
	print_size(std_set, "set");

	print_title("SET INSERT(position, val)");
	for (int i = 20; i <= 26; i++, c++)
	{
		std_set.insert(c);
	}
	print_set(std_set, "set");
	print_size(std_set, "set");

	print_title("SET INSERT(first, last)", "set -> set_copy");
	print_title("BEFORE INSERT");
	print_set(std_set_copy, "set_copy");

	print_title("AFTER INSERT");
	std_set_copy.insert(std_set.begin(), std_set.end());
	print_set(std_set_copy, "set_copy");
	print_size(std_set_copy, "set_copy");

	print_title("SET ERASE(position)", "erasing first half of set_copy");
	std::set<char>::iterator std_it_half = std_set_copy.find('n');
	for (std::set<char>::iterator it = std_set_copy.begin(); it != std_it_half; it++)
		std_set_copy.erase(it);
	print_set(std_set_copy, "set_copy");
	print_size(std_set_copy, "set_copy");

	print_title("SET ERASE(key)", "erasing another half of set_copy");
	c = 'n';
	for (int i = 0; i < 6; i++, c++)
	{
		std_set_copy.erase(c);
	}
	print_set(std_set_copy, "set_copy");
	print_size(std_set_copy, "set_copy");

	print_title("SET ERASE(first, last)", "finishing the job set_copy");
	std_set_copy.erase(std_set_copy.begin(), std_set_copy.end());
	print_set(std_set_copy, "set_copy");
	print_size(std_set_copy, "set_copy");

	print_title("SET SWAP() (MEMBER)", "swaping set_range and set_copy");
	print_title("BEFORE SWAP");
	print_set(std_set_range, "set_range");
	print_set(std_set_copy, "set_copy");
	std_set_range.swap(std_set_copy);
	print_title("AFTER SWAP");
	print_set(std_set_range, "set_range");
	print_set(std_set_copy, "set_copy");

	print_title("SET CLEAR", "clearing set copy again");
	print_title("BEFORE");
	print_set(std_set_copy, "set_copy");
	print_size(std_set_copy, "set_copy");
	std_set_copy.clear();
	print_title("AFTER");
	print_set(std_set_copy, "set_copy");
	print_size(std_set_copy, "set_copy");

	print_title("SET FIND(key) const and non_const");
	std::set<char>::iterator find_a = std_set.find('a');
	std::set<char>::const_iterator find_z = std_set.find('z');
	std::cout << "find('a'): " << *find_a << '\n';
	std::cout << "find('z'): " << *find_z << '\n';

	print_title("SET COUNT(key)");
	std::cout << 'a';
	if (std_set.count('a') > 0)
		std::cout << " is an element of set.\n";
	else
		std::cout << " is not an element of set.\n";
	std::cout << '1';
	if (std_set.count('1') > 0)
		std::cout << " is an element of set.\n";
	else
		std::cout << " is not an element of set.\n";

	print_title("SET LOWER_BOUND AND UPPER_BOUND", "using it to erase from b to g");
	std::set<char>::iterator itlow = std_set.lower_bound('b');
	std::set<char>::iterator itup = std_set.upper_bound('g');
	std_set.erase(itlow, itup);
	print_set(std_set, "set");
	print_size(std_set, "set");

	print_title("SET EQUAL_RANGE", "for h");
	std::pair<std::set<char>::iterator,std::set<char>::iterator> ret;
	ret = std_set.equal_range('h');
	std::cout << "lower bound points to: ";
	std::cout << *(ret.first) << '\n';
	std::cout << "upper bound points to: ";
	std::cout << *(ret.second) << '\n';

	print_title("SET KEY_COMP AND VALUE_COMP", "display everything lower than m");
	std::set<char>::key_compare mycomp = std_set.key_comp();

	char highest_key = 'm';
	char highest = *std_set.find('m');

	std::set<char>::iterator it = std_set.begin();
	while (std_set.value_comp()(*it, highest) && mycomp(*it, highest_key))
	{
		std::cout << *it << '\n';
		it++;
	}
}
