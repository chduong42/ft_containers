/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/20 17:23:45 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP
# include<iostream>

namespace ft 
{
	// Node
	template <class T>
	struct Node {
		T							_value;
		Node* 						_left;
		Node* 						_right;
		Node* 						_parent;
		bool 						_isred;

		Node() : _value(), _left(NULL), _right(NULL), _parent(NULL), _isred(false) {};
	};

	// Red Black Tree
	template <class T> class RBT {
		private:
			Node<T>						*_root;
			Node<T>						*_nil;
			size_t						_size;
	
		public:
			RBT() {};
			RBT(const RBT &x) {};
			RBT &operator=(const RBT &x) {};
			~RBT() {};
			
			// Iterators
			class TreeIterator {};
			
	};
	
};

#endif