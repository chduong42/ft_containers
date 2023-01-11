/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enableif_test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:04 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/11 11:59:28 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

int main() {

  short int i = 1;    // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;

  return 0;
}