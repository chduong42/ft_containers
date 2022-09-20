/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:36:55 by kennyduong        #+#    #+#             */
/*   Updated: 2022/08/27 19:14:54 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include <iterator>
#include <vector>

int main(void)
{
    std::iterator<std::bidirectional_iterator_tag, int> it;
    ft::iterator<ft::bidirectional_iterator_tag, int> it2;
    std::vector<int> v;

    
    return 0;   
}