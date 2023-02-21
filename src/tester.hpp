/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:49:01 by alilin            #+#    #+#             */
/*   Updated: 2023/02/21 22:50:43 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include "vector.hpp"
#include <vector>
#include "stack.hpp"
#include <stack>
#include "map.hpp"
#include <map>
#include "set.hpp"
#include <set>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define SET "\033[0m"

void print_title(std::string title, std::string subtitle = "");
void test_vector();
void test_vector_std();
void test_stack();
void test_stack_std();
void test_map();
void test_map_std();
void test_set();
void test_set_std();


#endif
