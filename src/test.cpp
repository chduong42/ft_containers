/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:36:55 by kennyduong        #+#    #+#             */
/*   Updated: 2022/08/24 16:51:28 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include <iterator>
#include <vector>

int main(void)
{
    std::vector<int> v(10, 42);
    std::iterator_traits<std::vector<int>::iterator>::difference_type n = v.end() - v.begin();
    std::vector<int>::iterator it = v.begin();
    return 0;   
}