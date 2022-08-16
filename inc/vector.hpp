/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:56:26 by kennyduong        #+#    #+#             */
/*   Updated: 2022/08/16 20:57:54 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>

namespace ft {
	template<typename T, class Allocator = std::allocator<T> >
	class vector {
		public:		//member types
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef T&										reference;
			typedef T& const								const_reference;	
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename ft::iterator_traits			iterator;
			typedef typename ft::iterator_traits const		const_iterator;
			typedef typename ft::reverse_iterator			reverse_iterator;
			typedef typename ft::reverse_iterator const		const_reverse_iterator;	
			typedef ptrdiff_t								difference_type;	
			typedef size_t									size_type;
			
			vector();
			~vector();
			
	};
}

#endif