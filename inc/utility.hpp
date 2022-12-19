/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:06:09 by chduong           #+#    #+#             */
/*   Updated: 2022/12/19 19:21:44 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft 
{
    template <class T1, class T2> struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        
        T1 first;
        T2 second;
        
        pair() : first(T1()), second(T2()) {}
        pair(const T1& a, const T2& b) : first(a), second(b) {}
        
        template <class U, class V> pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

        pair& operator=( const pair& other) {
            first = other.first;
            second = other.second;
            return *this;
        }
    };

    template <class T1,class T2> pair<T1,T2> make_pair (T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }
}

#endif