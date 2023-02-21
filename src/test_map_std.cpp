/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_std.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:53:10 by alilin            #+#    #+#             */
/*   Updated: 2021/11/12 17:23:13 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TEST for Map:
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

void print_map(std::map<char, int> map, std::string name)
{
	std::cout << name << ":\n";
	for (std::map<char, int>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << (*it).first << " = " << (*it).second << ", ";
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_size(std::map<char, int> map, std::string name)
{
	std::cout << name << " size: " << map.size() << ", max_size: " << map.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << map.empty() << std::endl;
	std::cout << std::endl;
}

void test_map_std()
{
	print_title("CONSTRUCTOR", "map");
	std::map<char, int> std_map;
	print_size(std_map, "map");

	char c = 'a';
	for (int i = 1; i <= 13; i++, c++)
	{
		std_map[c] = i;
	}
	print_map(std_map, "map");
	print_size(std_map, "map");

	print_title("RANGE", "map");
	std::map<char, int> std_map_range(std_map.begin(), std_map.end());
	print_size(std_map_range, "map_range");
	print_map(std_map_range, "map_range");

	print_title("COPY CONSTRUCTOR (copy of range)", "map");
	std::map<char, int> std_map_copy(std_map_range);
	print_size(std_map_copy, "map_copy");
	print_map(std_map_copy, "map_copy");


	print_title("ASSIGNATION OPERATOR", "map");
	std::map<char, int> std_map_assignation;
	std_map_assignation = std_map_copy;
	print_size(std_map_assignation, "map_assignation");
	print_map(std_map_assignation, "map_assignation");


	print_title("ITERATORS TESTS");
	std::cout << "map (iterator): ";
	for (std::map<char, int>::iterator it = std_map.begin(); it != std_map.end(); it++)
		std::cout << (*it).first << " = " << (*it).second << ", ";
	std::cout << "\n" << std::endl;
	std::cout << "map (const_iterator): ";
	for (std::map<char, int>::const_iterator it = std_map.begin(); it != std_map.end(); it++)
		std::cout << (*it).first << " = " << (*it).second << ", ";
	std::cout << "\n" << std::endl;
	std::cout << "map (reverse_iterator): ";
	for (std::map<char, int>::reverse_iterator rit = std_map.rbegin(); rit != std_map.rend(); rit++)
		std::cout << (*rit).first << " = " << (*rit).second << ", ";
	std::cout << "\n" << std::endl;
	std::cout << "map (const_reverse_iterator): ";
	for (std::map<char, int>::const_reverse_iterator rit = std_map.rbegin(); rit != std_map.rend(); rit++)
		std::cout << (*rit).first << " = " << (*rit).second << ", ";
	std::cout << "\n" << std::endl;

	print_title("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, empty");
	print_size(std_map, "map");

	print_title("MAP INSERT(val)");
	for (int i = 14; i <= 19; i++, c++)
	{
		std_map.insert(std::make_pair(c, i));
	}
	print_map(std_map, "map");
	print_size(std_map, "map");

	print_title("MAP INSERT(position, val)");
	for (int i = 20; i <= 26; i++, c++)
	{
		std_map.insert(std::make_pair(c, i));
	}
	print_map(std_map, "map");
	print_size(std_map, "map");

	print_title("MAP INSERT(first, last)", "map -> map_copy");
	print_title("BEFORE INSERT");
	print_map(std_map_copy, "map_copy");

	print_title("AFTER INSERT");
	std_map_copy.insert(std_map.begin(), std_map.end());
	print_map(std_map_copy, "map_copy");
	print_size(std_map_copy, "map_copy");

	print_title("MAP ERASE(position)", "erasing first half of map_copy");
	std::map<char, int>::iterator std_it_half = std_map_copy.find('n');
	for (std::map<char, int>::iterator it = std_map_copy.begin(); it != std_it_half; it++)
		std_map_copy.erase(it);
	print_map(std_map_copy, "map_copy");
	print_size(std_map_copy, "map_copy");

	print_title("MAP ERASE(key)", "erasing another half of map_copy");
	c = 'n';
	for (int i = 0; i < 6; i++, c++)
	{
		std_map_copy.erase(c);
	}
	print_map(std_map_copy, "map_copy");
	print_size(std_map_copy, "map_copy");

	print_title("MAP ERASE(first, last)", "finishing the job map_copy");
	std_map_copy.erase(std_map_copy.begin(), std_map_copy.end());
	print_map(std_map_copy, "map_copy");
	print_size(std_map_copy, "map_copy");

	print_title("MAP SWAP() (MEMBER)", "swaping map_range and map_copy");
	print_title("BEFORE SWAP");
	print_map(std_map_range, "map_range");
	print_map(std_map_copy, "map_copy");
	std_map_range.swap(std_map_copy);
	print_title("AFTER SWAP");
	print_map(std_map_range, "map_range");
	print_map(std_map_copy, "map_copy");

	print_title("MAP CLEAR", "clearing map copy again");
	print_title("BEFORE");
	print_map(std_map_copy, "map_copy");
	print_size(std_map_copy, "map_copy");
	std_map_copy.clear();
	print_title("AFTER");
	print_map(std_map_copy, "map_copy");
	print_size(std_map_copy, "map_copy");

	print_title("MAP FIND(key) const and non_const");
	std::map<char, int>::iterator find_a = std_map.find('a');
	std::map<char, int>::const_iterator find_z = std_map.find('z');
	std::cout << "find('a'): " << (*find_a).first << " = " << (*find_a).second << '\n';
	std::cout << "find('z'): " << (*find_z).first << " = " << (*find_z).second << '\n';

	print_title("MAP COUNT(key)");
	std::cout << 'a';
	if (std_map.count('a') > 0)
		std::cout << " is an element of map.\n";
	else
		std::cout << " is not an element of map.\n";
	std::cout << '1';
	if (std_map.count('1') > 0)
		std::cout << " is an element of map.\n";
	else
		std::cout << " is not an element of map.\n";

	print_title("MAP LOWER_BOUND AND UPPER_BOUND", "using it to erase from b to g");
	std::map<char,int>::iterator itlow = std_map.lower_bound('b');
	std::map<char,int>::iterator itup = std_map.upper_bound('g');
	std_map.erase(itlow, itup);
	print_map(std_map, "map");
	print_size(std_map, "map");

	print_title("MAP EQUAL_RANGE", "for h");
	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
	ret = std_map.equal_range('h');
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	print_title("MAP KEY_COMP AND VALUE_COMP", "display everything lower than m");
	std::map<char,int>::key_compare mycomp = std_map.key_comp();

	char highest_key = 'm';
	std::pair<char,int> highest = *std_map.find('m');

	std::map<char,int>::iterator it = std_map.begin();
	while (std_map.value_comp()(*it, highest) && mycomp((*it).first, highest_key))
	{
		std::cout << it->first << " => " << it->second << '\n';
		it++;
	}
}
