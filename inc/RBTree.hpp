/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/24 17:04:51 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include<iostream>
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft 
{
	// Node
	template <class T>
	struct TreeNode {
		typedef TreeNode<T>			Node;
		typedef T					value_type;
		
		value_type					_value;
		Node* 						_parent;
		Node* 						_left;
		Node* 						_right;
		bool 						_isred;
	};

	// Red Black Tree
	template<typename Key, typename T, class Compare, class Allocator = std::allocator<T> >
	class RBTree {
		public:
			typedef Key					key_type;
			typedef T					value_type;
			typedef Compare				key_compare;
			typedef Allocator			allocator_type;
			typedef TreeNode<T>			Node;
			typedef Node*				node_pointer;
			typedef T*					pointer;
			typedef const T*			const_pointer;
			typedef T&					reference;
			typedef const T&			const_reference;
			typedef size_t				size_type;
			typedef ptrdiff_t			difference_type;
			typedef value_type*			iterator;
			typedef const value_type*	const_iterator;
			
		private:
			Node<T>*				_root;
			Node<T>*				_nil;
			size_t					_size;
	
		public:
			RBT() {};
			RBT(const RBT &x) {};
			RBT &operator=(const RBT &x) {};
			~RBT() {};
			
			void insert(const T &x) {}
			
			
	};
	
};

#endif