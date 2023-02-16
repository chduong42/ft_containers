/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectionnal_it.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:20:14 by alilin            #+#    #+#             */
/*   Updated: 2023/02/16 18:01:21 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include <cstddef>

#include "iterator.hpp"
#include "rbt.hpp"

namespace ft
{
	template< class T, class N >
	class bidirectional_iterator
	{
	public:

		typedef std::ptrdiff_t difference_type;
		typedef T value_type;

		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;

		typedef N node_type;
		typedef node_type* node_ptr;
		typedef std::bidirectional_iterator_tag iterator_category;

		bidirectional_iterator() : _ptr(NULL), _root(NULL), _nil(NULL) {}
		bidirectional_iterator(node_ptr ptr, node_ptr root, node_ptr nil) : _ptr(ptr), _root(root), _nil(nil) {}
		bidirectional_iterator(bidirectional_iterator const &lhs) : _ptr(lhs._ptr), _root(lhs._root), _nil(lhs._nil) {}
		bidirectional_iterator &operator=(bidirectional_iterator const &lhs)
		{
			if (this == &lhs)
				return (*this);
			this->_ptr = lhs._ptr;
			this->_root = lhs._root;
			this->_nil = lhs._nil;
			return (*this);
		}
		virtual ~bidirectional_iterator() {}

		// Overload called when trying to copy construct a const_iterator
		// based on an iterator
		operator bidirectional_iterator<value_type const, node_type const>() const
		{
			return bidirectional_iterator<value_type const, node_type const>(_ptr, _root, _nil);
		}

		bool operator==(ft::bidirectional_iterator<value_type, node_type> const &lhs) const
		{
			return (this->_ptr == lhs._ptr);
		}

		bool operator!=(ft::bidirectional_iterator<value_type, node_type> const &lhs) const
		{
			return (this->_ptr != lhs._ptr);
		}

		template<class Iterator, class Iter>
		friend bool operator==(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs);

		template<class Iterator, class Iter>
		friend bool operator!=(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs);

		reference operator*()
		{
			return (_ptr->data);
		}

		const_reference operator*() const
		{
			return (_ptr->data);
		}

		pointer operator->()
		{
			return (&(operator*()));
		}

		const_pointer operator->() const
		{
			return (&(operator*()));
		}

		bidirectional_iterator &operator++()
		{
			if (_ptr != _nil)
				_ptr = successor(_ptr);
			return (*this);
		}

		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		bidirectional_iterator &operator--()
		{
			if (_ptr == _nil)
				_ptr = maximum(_root);
			else
				_ptr = predecessor(_ptr);
			return (*this);
		}

		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp(*this);
			operator--();
			return (tmp);
		}

	protected:

		node_ptr _ptr;
		node_ptr _root;
		node_ptr _nil;

		// find the node with the minimum key
		node_ptr minimum(node_ptr node)
		{
			while (node->left != _nil)
				node = node->left;
			return node;
		}

		// find the node with the maximum key
		node_ptr maximum(node_ptr node)
		{
			while (node->right != _nil)
				node = node->right;
			return node;
		}

		// find the successor of a given node
		node_ptr successor(node_ptr x)
		{
			// if the right subtree is not null the successor is the leftmost node in the sright subtree
			if (x->right != _nil)
			{
				return minimum(x->right);
			}
			// else it is the lowest ancestor of x whose left child is also an ancestor of x
			node_ptr y = x->parent;
			while (y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			if (y == NULL)
				return _nil;
			return y;
		}

		// find the predecessor of a given node
		node_ptr predecessor(node_ptr x)
		{
			// if the left subtree is not null the predecessor is the rightmost node in the left subtree
			if (x->left != _nil)
			{
				return maximum(x->left);
			}
			node_ptr y = x->parent;
			while (y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
	};

	template<class Iterator, class Iter>
	bool operator==(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template<class Iterator, class Iter>
	bool operator!=(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}
}

#endif
