/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 23:06:09 by chduong           #+#    #+#             */
/*   Updated: 2023/02/20 14:34:42 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft 
{
    template<bool B, class T = void > struct enable_if {};
    
    template<class T> struct enable_if<true, T> {typedef T type; };

    template <class T, T v> struct integral_constant {
        // Member types
        typedef T                       value_type;
        typedef integral_constant<T,v>  type;
        // Member constants
        static value_type const value = v;
        // Member functions
        operator value_type() const {return value;}
    };
    
    typedef integral_constant<bool,true> true_type;
    typedef integral_constant<bool,false> false_type;
    
    template <typename T> class is_integral : public false_type {};
    template <> class is_integral<bool> : public true_type {};
    template <> class is_integral<char> : public true_type {};
    template <> class is_integral<wchar_t> : public true_type {};
    template <> class is_integral<signed char> : public true_type {};
    template <> class is_integral<signed short> : public true_type {};
    template <> class is_integral<signed int> : public true_type {};
    template <> class is_integral<signed long> : public true_type {};
    template <> class is_integral<unsigned char> : public true_type {};
    template <> class is_integral<unsigned short> : public true_type {};
    template <> class is_integral<unsigned int> : public true_type {};
    template <> class is_integral<unsigned long> : public true_type {};
}

#endif
